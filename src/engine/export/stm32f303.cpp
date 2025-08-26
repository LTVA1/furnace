/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2024 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*

DATA FORMAT:

4 bytes: samples offset
4 bytes: wavetables offset
4 bytes: cmd offset
4 bytes: orders offset

samples part: just plain samples data, u8 mono pcm

wavetables part: plain wavetables data, x times, 256 u8 mono pcm bytes per wavetable

orders part: uint8_t x, then int16_t order to jump to when end of orders reached (loop) or -1 if no loop, then array [F303_NUM_CHANNELS][x] of uint32_t offsets of cmd stream for each "pattern" of each channel: [0][0] [0][1] [1][0] [1][1] [2][0] [2][1], ... if x = 2

cmd part: just plain commands data for all streams of all channels in any order, but the "pattern" for each channel and each order pos is not interrupted
*/

#include "stm32f303.h"
#include "../engine.h"
#include "../waveSynth.h"
#include "../platform/f303.h"
#include <cstdint>

typedef struct 
{
  int freq;
} F303State_t;

typedef struct 
{
  uint8_t data[256];
} Wavetable_t;

typedef struct 
{
  std::vector<DivRegWrite> data;
} Cmd_stream_pattern_t; //needs to be converted to final format later

//little-endian

#define WRITE_8BITS(x) our_data.push_back((x) & 0xFF);
#define WRITE_16BITS(x) our_data.push_back((x) & 0xFF); our_data.push_back(((x) >> 8) & 0xFF);
#define WRITE_24BITS(x) our_data.push_back((x) & 0xFF); our_data.push_back(((x) >> 8) & 0xFF); our_data.push_back(((x) >> 16) & 0xFF);
#define WRITE_32BITS(x) our_data.push_back((x) & 0xFF); our_data.push_back(((x) >> 8) & 0xFF); our_data.push_back(((x) >> 16) & 0xFF); our_data.push_back(((x) >> 24) & 0xFF);

#define WRITE_8BITS_AT(addr, x) our_data[addr] = ((x) & 0xFF);
#define WRITE_32BITS_AT(addr, x) our_data[addr] = ((x) & 0xFF); our_data[addr + 1] = (((x) >> 8) & 0xFF); our_data[addr + 2] = (((x) >> 16) & 0xFF); our_data[addr + 3] = (((x) >> 24) & 0xFF);

#define WRITE_STRING(x) \
for(int ttt = 0; ttt < strlen(x); ttt++) \
{ \
  our_data.push_back(x[ttt]); \
}

#define CMD_PCM_OFFSET 0x10
#define CMD_PCM_LENGTH 0x20
#define CMD_PCM_FREQ 0x30
#define CMD_PCM_WAVETABLE_MODE 0x40 /* LSB is whether wavetable is used (otherwise sample) */
#define CMD_PCM_SAMPLE_LOOP 0x50 /* LSB is whether sample is looped */
#define CMD_PCM_WAVETABLE_NUM 0x60
#define CMD_PCM_WAVE_TYPE 0x70 /* 2 LSBs: custom wavetable, pulse, triangle, sawtooth */
#define CMD_PCM_DUTY 0x80

#define CMD_NOISE_LFSR_LOAD 0xA1
#define CMD_NOISE_LFSR_FEEDBACK 0xA2
#define CMD_NOISE_LFSR_FREQ 0xA3

#define CMD_WAIT_SHORT 0x90 /* lower nibble is number of frames to wait */
#define CMD_WAIT_LONG 0xB0 /* next byte is how many frames to wait */
#define CMD_WRITE_ACC 0xFB
#define CMD_VOLUME 0xFC
#define CMD_PAN_RIGHT 0xFD
#define CMD_PAN_LEFT 0xFE
#define CMD_END 0xFF

int compare_wavetables(uint8_t* data1, uint8_t* data2)
{
  for(int i = 0; i < 256; i++)
  {
    if(data1[i] != data2[i]) return 1;
  }

  return 0;
}

void write_command(int chan, DivRegWrite& w, std::vector<uint8_t>& our_data)
{
  switch(w.addr & 0xff)
  {
    case WRITE_SAMPLE_OFF:
    {
      WRITE_8BITS(CMD_PCM_OFFSET | (w.val >> 16) & 0xF); //20 bits is enough
      WRITE_16BITS(w.val & 0xFFFF);
      break;
    }
    case WRITE_SAMPLE_LEN:
    {
      WRITE_8BITS(CMD_PCM_LENGTH | (w.val >> 16) & 0xF); //20 bits is enough
      WRITE_16BITS(w.val & 0xFFFF);
      break;
    }
    case WRITE_FREQ:
    {
      if(chan == F303_NUM_CHANNELS - 1)
      {
        WRITE_8BITS(CMD_NOISE_LFSR_FREQ);
        WRITE_32BITS(w.val);
      }
      else
      {
        WRITE_8BITS(CMD_PCM_FREQ);
        WRITE_32BITS(w.val);
      }
      break;
    }
    case WRITE_WAVETABLE_MODE:
    {
      WRITE_8BITS(CMD_PCM_WAVETABLE_MODE | (w.val ? 1 : 0));
      break;
    }
    case WRITE_SAMPLE_LOOP:
    {
      WRITE_8BITS(CMD_PCM_SAMPLE_LOOP | (w.val ? 1 : 0));
      break;
    }
    case WRITE_VOLUME:
    {
      WRITE_8BITS(CMD_VOLUME);
      WRITE_8BITS(w.val);
      break;
    }
    case WRITE_PAN_RIGHT:
    {
      WRITE_8BITS(CMD_PAN_RIGHT);
      WRITE_8BITS(w.val);
      break;
    }
    case WRITE_PAN_LEFT:
    {
      WRITE_8BITS(CMD_PAN_LEFT);
      WRITE_8BITS(w.val);
      break;
    }
    case WRITE_ACC:
    {
      WRITE_8BITS(CMD_WRITE_ACC);
      WRITE_32BITS(w.val);
      break;
    }
    case WRITE_NOISE_LFSR_BITS:
    {
      WRITE_8BITS(CMD_NOISE_LFSR_FEEDBACK);
      WRITE_32BITS(w.val);
      break;
    }
    case WRITE_NOISE_LFSR_VALUE:
    {
      WRITE_8BITS(CMD_NOISE_LFSR_LOAD);
      WRITE_32BITS(w.val);
      break;
    }
    case WRITE_WAVETABLE_NUM:
    {
      if(w.val < (1 << 12))
      {
        WRITE_8BITS(CMD_PCM_WAVETABLE_NUM | (w.val >> 8) & 0xF); //12 bits is enough?
        WRITE_8BITS(w.val & 0xFF);
      }
      break;
    }
    case WRITE_WAVE_TYPE:
    {
      WRITE_8BITS(CMD_PCM_WAVE_TYPE | (w.val & 3));
      break;
    }
    case WRITE_DUTY:
    {
      WRITE_8BITS(CMD_PCM_DUTY);
      WRITE_8BITS(w.val & 0xFF);
      break;
    }
    case WRITE_FRAME_DELAY:
    {
      if(w.val < 16)
      {
        WRITE_8BITS(CMD_WAIT_SHORT | (w.val & 0xf));
      }
      else if(w.val < 256)
      {
        WRITE_8BITS(CMD_WAIT_LONG);
        WRITE_8BITS(w.val & 0xff);
      }
      else
      {
        int track = w.val;

        while(track > 255)
        {
          WRITE_8BITS(CMD_WAIT_LONG);
          WRITE_8BITS(0xff);

          track -= 255;
        }

        if(track < 16)
        {
          WRITE_8BITS(CMD_WAIT_SHORT | (track & 0xf));
        }
        else if(track < 256)
        {
          WRITE_8BITS(CMD_WAIT_LONG);
          WRITE_8BITS(track & 0xff);
        }
      }
      break;
    }
    case WRITE_END:
    {
      WRITE_8BITS(CMD_END);
      break;
    }
    default: break;
  }
}

void DivExportF303::run() 
{
  bool do_write = conf.getBool("writeFile", true);
  bool raw_binary = conf.getBool("rawBin", false);

  SafeWriter* writer=new SafeWriter;

  DivPlatformF303* f303=(DivPlatformF303*)e->getDispatch(0);

  running=false;

  F303State_t state;

  memset((void*)&state, 0, sizeof(F303State_t));

  double origRate = e->got.rate;
  e->stop();
  e->repeatPattern=false;
  e->setOrder(0);

  bool loop = true;
  int16_t loop_order = -1;

  logAppend("playing and logging register writes...");

  float hz = e->getCurHz();

  uint32_t samples_offset = 16; //samples begin right after the offsets, other offsets are unknown rn
  uint32_t wavetables_offset = 0;
  uint32_t orders_offset = 0;
  uint32_t cmd_offset = 0;

  //auto orders = new uint32_t[F303_NUM_CHANNELS][256];
  auto patterns = new Cmd_stream_pattern_t[F303_NUM_CHANNELS][256];
  auto pattern_written = new bool[F303_NUM_CHANNELS][256];

  for(int i = 0; i < F303_NUM_CHANNELS; i++)
  {
    for(int j = 0; j < F303_NUM_CHANNELS; j++)
    {
      pattern_written[i][j] = false;
    }
  }

  std::vector<uint8_t> our_data;

  std::vector<Wavetable_t> our_wavetables; //afterwards there would be deduplication

  std::vector<int> wavetable_optimize; //wavetable_optimize[i] = j means that wavetable i was optimized into j (deduplication)

  DivSubSong* ss = e->curSubSong;
  uint32_t num_wavetables = e->song.waveLen; //this will be incremented if we find a new wavetable and then decremented when duplicate wavetables are found
  our_wavetables.reserve(num_wavetables);

  for(int i = 0; i < num_wavetables; i++) //copy the waves from wavetables list
  {
    our_wavetables.push_back(Wavetable_t());

    for(int j = 0; j < 256; j++)
    {
      our_wavetables[i].data[j] = e->song.wave[i]->data[j] & 0xFF;
    }
  }

  writer->init();

  e->synchronizedSoft([&]() {

    // Determine loop point.
    int loopOrder=0;
    int loopRow=0;
    int loopEnd=0;
    e->walkSong(loopOrder,loopRow,loopEnd);
    loop_order = loopOrder;
    logAppendf("loop point: %d %d",loopOrder,loopRow);
    e->warnings="";

    //walk song to find how many frames it is to loop point
    DivSubSong* s = e->curSubSong;

    for(int o = 0; o < s->ordersLen; o++)
    {
      for(int r = 0; r < s->patLen; r++)
      {
        //begin:;

        for(int ch = 0; ch < e->chans; ch++)
        {
          DivPattern* p = s->pat[ch].getPattern(s->orders.ord[ch][o],false);

          for(int eff = 0; eff < DIV_MAX_EFFECTS; eff++)
          {
            if (p->data[r][4 + (eff << 1)] == 0xff)
            {
              loop = false;
              goto finish;
            }
          }
        }
      }
    }

    finish:;

    // Reset the playback state.
    e->curOrder=0;
    e->freelance=false;
    e->playing=false;
    e->extValuePresent=false;
    e->remainingLoops=-1;

    // Prepare to write song data.
    e->playSub(false);
    bool done=false;
    e->disCont[0].dispatch->toggleRegisterDump(true);

    bool got_loop_point = false;

    int curr_order = 0;

    int frame_delay[F303_NUM_CHANNELS] = { 1 };

    while (!done) {
      if (e->nextTick(false,true) || !e->playing) {
        done=true;
        for (int i=0; i<e->song.systemLen; i++) {
          e->disCont[i].dispatch->getRegisterWrites().clear();
        }
        break;
      }

      // write stuff

      int row = 0;
      int order = 0;
      e->getCurSongPos(row, order);

      // get register dumps
      std::vector<DivRegWrite>& writes=e->disCont[0].dispatch->getRegisterWrites();

      bool has_writes[F303_NUM_CHANNELS] = { false };

      if (writes.size() > 0)
      {
        for (int curr_write = 0; curr_write < (int)writes.size(); curr_write++)
        {
          DivRegWrite w = writes[curr_write];

          int channel = ((w.addr >> 8) & 0xFF);

          if(channel < F303_NUM_CHANNELS && !has_writes[channel])
          {
            has_writes[channel] = true;
          }
        }
      }

      for(int i = 0; i < F303_NUM_CHANNELS; i++)
      {
        int patt_index = s->orders.ord[i][curr_order];

        if(has_writes[i] && !pattern_written[i][patt_index])
        {
          patterns[i][patt_index].data.push_back(DivRegWrite(WRITE_FRAME_DELAY, frame_delay[i])); //write delay
        }

        if(has_writes[i])
        {
          frame_delay[i] = 1;
        }
        else
        {
          frame_delay[i]++;
        }
      }

      if(curr_order != order)
      {
        for(int i = 0; i < F303_NUM_CHANNELS; i++)
        {
          int patt_index = s->orders.ord[i][curr_order];
          patterns[i][patt_index].data.push_back(DivRegWrite(WRITE_END, 0)); //write pattern end marker
          pattern_written[i][patt_index] = true; //so we do not write duplicates
        }

        curr_order = order;
      }

      if (writes.size() > 0) 
      {
        for (int curr_write = 0; curr_write < (int)writes.size(); curr_write++)
        {
          DivRegWrite w = writes[curr_write];

          int channel = ((w.addr >> 8) & 0xFF);

          int patt_index = s->orders.ord[channel][curr_order];
          
          if(!f303->isMuted[channel] && !pattern_written[channel][patt_index])
          {
            switch(w.addr & 0xff)
            {
              case WRITE_SAMPLE_OFF:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_SAMPLE_OFF, w.val));
                break;
              }
              case WRITE_SAMPLE_LEN:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_SAMPLE_LEN, w.val));
                break;
              }
              case WRITE_FREQ:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_FREQ, w.val));
                break;
              }
              case WRITE_WAVETABLE_MODE:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_WAVETABLE_MODE, w.val));
                break;
              }
              case WRITE_SAMPLE_LOOP:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_SAMPLE_LOOP, w.val));
                break;
              }
              case WRITE_VOLUME:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_VOLUME, w.val));
                break;
              }
              case WRITE_PAN_RIGHT:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_PAN_RIGHT, w.val));
                break;
              }
              case WRITE_PAN_LEFT:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_PAN_LEFT, w.val));
                break;
              }
              case WRITE_ACC:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_ACC, w.val));
                break;
              }
              case WRITE_NOISE_LFSR_BITS:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_NOISE_LFSR_BITS, w.val));
                break;
              }
              case WRITE_NOISE_LFSR_VALUE:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_NOISE_LFSR_VALUE, w.val));
                break;
              }
              case WRITE_WAVETABLE_NUM:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  if(w.val == 0xFFFF) //some custom wavetable from ws output
                  {
                    our_wavetables.push_back(Wavetable_t());

                    for(int j = 0; j < 256; j++)
                    {
                      our_wavetables[our_wavetables.size() - 1].data[j] = f303->ws[channel].output[j] & 0xFF;
                    }
                  }

                  patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_WAVETABLE_NUM, (unsigned int)(our_wavetables.size() - 1)));
                }
                break;
              }
              case WRITE_WAVE_TYPE:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_WAVE_TYPE, w.val));
                break;
              }
              case WRITE_DUTY:
              {
                patterns[channel][patt_index].data.push_back(DivRegWrite(WRITE_DUTY, w.val));
                break;
              }
              default: break;
            }
          }
        }

        writes.clear();
      }
    }

    for(int i = 0; i < F303_NUM_CHANNELS; i++)
    {
      int patt_index = s->orders.ord[i][curr_order];
      if(!pattern_written[i][patt_index])
      {
        patterns[i][patt_index].data.push_back(DivRegWrite(WRITE_END, 0)); //write pattern end marker
      }
      
      pattern_written[i][patt_index] = true; //so we do not write duplicates
    }

    //optimize wavetables...
    for(int i = 0; i < (int)our_wavetables.size(); i++)
    {
      wavetable_optimize.push_back(i);
    }

    //on this stage wavetable_optimize[i] = i

    //go through the list and find any duplicates in the waves with indices higher than the current one
    //do not erase them from the array, just correct all the further indices in wavetable_optimize array
    int optimized_wavetable_size = 0;

    for(int i = 0; i < (int)our_wavetables.size(); i++)
    {
      for(int j = i + 1; j < (int)our_wavetables.size(); j++)
      {
        if(!compare_wavetables(our_wavetables[i].data, our_wavetables[j].data))
        {
          wavetable_optimize[j] = i;
        }
      }
    }

    for(int i = 0; i < (int)our_wavetables.size(); i++) //find the hhighest index that determines how many unique waves we have
    {
      if((optimized_wavetable_size - 1) < wavetable_optimize[i]) optimized_wavetable_size = wavetable_optimize[i] + 1;
    }

    //write correct indices for optimized wavetables in the commands streams

    for(int i = 0; i < F303_NUM_CHANNELS; i++)
    {
      for(int j = 0; j < 256; j++)
      {
        for(int k = 0; k < (int)patterns[i][j].data.size(); k++)
        {
          if(patterns[i][j].data[k].addr == WRITE_WAVETABLE_NUM && patterns[i][j].data[k].val != wavetable_optimize[patterns[i][j].data[k].val])
          {
            patterns[i][j].data[k].val = wavetable_optimize[patterns[i][j].data[k].val];
          }
        }
      }
    }

    // end of song
    WRITE_32BITS(samples_offset);
    WRITE_32BITS(wavetables_offset);
    WRITE_32BITS(orders_offset);
    WRITE_32BITS(cmd_offset);

    if(do_write)
    {
      logAppend("writing samples...");
    }

    //WRITE_STRING("SAMPLES");

    for(int i = 0; i < (int)f303->getSampleMemUsage(0); i++)
    {
      WRITE_8BITS(((uint8_t*)f303->getSampleMem(0))[i]);
    }
    
    if(do_write)
    {
      logAppend("writing wavetables...");
    }

    WRITE_STRING("WAVETABLES");

    uint32_t tell = (uint32_t)our_data.size();
    WRITE_32BITS_AT(4, tell); //wavetable offset rewritten

    for(int i = 0; i < optimized_wavetable_size; i++)
    {
      for(int j = 0; j < 256; j++)
      {
        WRITE_8BITS(our_wavetables[i].data[j]);
      }
    }

    if(do_write)
    {
      logAppend("writing orders...");
    }

    WRITE_STRING("ORDERS");

    tell = (uint32_t)our_data.size();
    WRITE_32BITS_AT(8, tell); //orders offset rewritten

    WRITE_8BITS(s->ordersLen);

    WRITE_16BITS(loop ? loop_order : -1);

    uint32_t ord_addr = (uint32_t)our_data.size();

    for(int i = 0; i < F303_NUM_CHANNELS; i++)
    {
      for(int j = 0; j < (int)s->ordersLen; j++)
      {
        WRITE_32BITS(0);
      }
    }

    if(do_write)
    {
      logAppend("writing \"registers dump\"...");
    }

    WRITE_STRING("PATTERNS OF COMMANDS");

    tell = (uint32_t)our_data.size();
    WRITE_32BITS_AT(12, tell); //cmds offset rewritten

    //write...

    for(int i = 0; i < F303_NUM_CHANNELS; i++)
    {
      for(int j = 0; j < 256; j++)
      {
        for(int o = 0; o < s->ordersLen; o++)
        {
          if(s->orders.ord[i][o] == j)
          {
            WRITE_32BITS_AT(ord_addr + i * 4 * s->ordersLen + o * 4, (uint32_t)our_data.size());

            if(patterns[i][j].data.size() == 0) //empty pattern but is used
            //write one END command
            {
              patterns[i][j].data.push_back(DivRegWrite(WRITE_END, 0));
            }
          }
        }
        if(patterns[i][j].data.size() > 0)
        {
          for(int k = 0; k < (int)patterns[i][j].data.size(); k++)
          {
            write_command(i, patterns[i][j].data[k], our_data);
          }
        }
      }
    }

    if(do_write)
    {
      writer->writeText(fmt::sprintf("#include <stdint.h>\n\nconst uint32_t music_size = %d;\n\n", (int)our_data.size()));
      writer->writeText("const uint8_t music[] =\n{");

      for(int i = 0; i < (int)our_data.size(); i++)
      {
        if((i & 31) == 0)
        {
          writer->writeText("\n    ");
        }

        writer->writeText(fmt::sprintf(((i == (int)our_data.size() - 1) ? "0x%02X" : "0x%02X, "), our_data[i]));
      }

      writer->writeText("\n};");
    }

    // done - close out.
    //delete[] orders;
    delete[] patterns;
    delete[] pattern_written;

    e->got.rate=origRate;

    e->disCont[0].dispatch->toggleRegisterDump(false);

    e->remainingLoops=-1;
    e->playing=false;
    e->freelance=false;
    e->extValuePresent=false;
  });

  if(do_write)
  {
    logAppend("writing data...");
  }
  progress[0].amount=0.95f;

  // finish

  if(do_write)
  {
    if(raw_binary)
    {
      output.reserve(2);

      SafeWriter* writer_bin=new SafeWriter;
      writer_bin->init();

      for(int i = 0; i < (int)our_data.size(); i++)
      {
        writer_bin->writeC(our_data[i]);
      }

      output.push_back(DivROMExportOutput("music.bin", writer_bin));
    }
    output.push_back(DivROMExportOutput("music.c", writer));
  }

  progress[0].amount=1.0f;

  if(do_write)
  {
    logAppend("finished!");
  }

  if(!do_write)
  {
    logAppend(fmt::sprintf("total data size: %d bytes", (int)our_data.size()));
  }

  running=false;
}

bool DivExportF303::go(DivEngine* eng) {
  progress[0].name="Progress";
  progress[0].amount=0.0f;
  progress[1].name="";
  e=eng;
  running=true;
  failed=false;
  exportThread=new std::thread(&DivExportF303::run,this);
  return true;
}

void DivExportF303::wait() {
  if (exportThread!=NULL) {
    logV("waiting for export thread...");
    exportThread->join();
    delete exportThread;
  }
}

void DivExportF303::abort() {
  mustAbort=true;
  wait();
}

bool DivExportF303::isRunning() {
  return running;
}

bool DivExportF303::hasFailed() {
  return false;
}

DivROMExportProgress DivExportF303::getProgress(int index) {
  if(index > 1) return progress[1];
  return progress[index];
}
