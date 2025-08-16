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

orders part: uint32_t x, then array [F303_NUM_CHANNELS][x] of uint32_t offsets of cmd stream for each "pattern" of each channel: [0][0] [0][1] [1][0] [1][1] [2][0] [2][1], ... if x = 2

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

#define WRITE_8BITS(x) our_data.push_back(x);
#define WRITE_16BITS(x) our_data.push_back(x & 0xFF); our_data.push_back((x >> 8) & 0xFF);
#define WRITE_32BITS(x) our_data.push_back(x & 0xFF); our_data.push_back((x >> 8) & 0xFF); our_data.push_back((x >> 16) & 0xFF); our_data.push_back((x >> 24) & 0xFF);

#define WRITE_32BITS_AT(addr, x) our_data[addr] = (x & 0xFF); our_data[addr + 1] = ((x >> 8) & 0xFF); our_data[addr + 2] = ((x >> 16) & 0xFF); our_data[addr + 3] = ((x >> 24) & 0xFF);

#define WRITE_STRING(x) \
for(int ttt = 0; ttt < strlen(x); ttt++) \
{ \
  our_data.push_back(x[ttt]); \
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

  logAppend("playing and logging register writes...");

  float hz = e->getCurHz();

  uint32_t samples_offset = 16; //samples begin right after the offsets, other offsets are unknown rn
  uint32_t wavetables_offset = 0;
  uint32_t orders_offset = 0;
  uint32_t cmd_offset = 0;

  auto orders = new uint32_t[F303_NUM_CHANNELS][256];
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

  std::vector<uint8_t> wavetable_optimize; //wavetable_optimize[i] = j means that wavetable i was optimized into j (deduplication)

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
    logAppendf("loop point: %d %d",loopOrder,loopRow);
    e->warnings="";

    //walk song to find how many frames it is to loop point
    DivSubSong* s = e->curSubSong;
    //DivGroovePattern curSpeeds=s->speeds;

    //int groove_counter = 0;

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
            //short effectVal = p->data[r][5+(eff<<1)];

            if (p->data[r][4 + (eff << 1)] == 0xff)
            {
                //loop = false;
                goto finish;
            }
          }
        }

        //groove_counter++;
        //groove_counter %= curSpeeds.len;

        //loop_point_addr += curSpeeds.val[groove_counter];

        if(o == loopOrder && r == loopRow && (loopOrder != 0 || loopRow != 0))
        {
          //goto finish;
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

    while (!done) {
      if (e->nextTick(false,true) || !e->playing) {
        done=true;
        for (int i=0; i<e->song.systemLen; i++) {
          e->disCont[i].dispatch->getRegisterWrites().clear();
        }
        break;
      }

      // write stuff


      //TODO: write "wait till next frame" command for each chan?

      int row = 0;
      int order = 0;
      e->getCurSongPos(row, order);

      if(curr_order != order)
      {
        for(int i = 0; i < F303_NUM_CHANNELS; i++)
        {
          pattern_written[i][s->orders.ord[i][curr_order]] = true; //so we do not write duplicates
        }

        curr_order = order;
      }

      // get register dumps
      std::vector<DivRegWrite>& writes=e->disCont[0].dispatch->getRegisterWrites();
      if (writes.size() > 0) 
      {
        for (int curr_write = 0; curr_write < (int)writes.size(); curr_write++)
        {
          DivRegWrite w = writes[curr_write];
          //crapwriter->writeI(write.addr); //TODO replace with actual commands
          //crapwriter->writeI(write.val);

          int channel = ((w.addr >> 8) & 0xFF);
          
          if(!f303->isMuted[channel])
          {
            switch(w.addr & 0xff)
            {
              case WRITE_SAMPLE_OFF:
              {
                
                break;
              }
              case WRITE_SAMPLE_LEN:
              {
                
                break;
              }
              case WRITE_FREQ:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                else //noise chan
                {
                  
                }
                break;
              }
              case WRITE_WAVETABLE_MODE:
              {
                
                break;
              }
              case WRITE_SAMPLE_LOOP:
              {
                
                break;
              }
              case WRITE_VOLUME:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                else //noise chan
                {
                  
                }
                break;
              }
              case WRITE_PAN_RIGHT:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                else //noise chan
                {
                  
                }
                break;
              }
              case WRITE_PAN_LEFT:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                else //noise chan
                {
                  
                }
                break;
              }
              case WRITE_ACC:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                else //noise chan
                {
                  
                }
                break;
              }
              case WRITE_NOISE_LFSR_BITS:
              {
                if(((w.addr >> 8) & 0xFF) == F303_NUM_CHANNELS - 1)
                {
                  
                }
                break;
              }
              case WRITE_NOISE_LFSR_VALUE:
              {
                if(((w.addr >> 8) & 0xFF) == F303_NUM_CHANNELS - 1)
                {
                  
                }
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
                }
                break;
              }
              case WRITE_WAVE_TYPE:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                break;
              }
              case WRITE_DUTY:
              {
                if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
                {
                  
                }
                break;
              }
              default: break;
            }
          }
        }

        writes.clear();
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

    WRITE_STRING("SAMPLES");

    for(int i = 0; i < (int)f303->getSampleMemUsage(0); i++)
    {
      WRITE_8BITS(((uint8_t*)f303->getSampleMem(0))[i]);
    }
    
    if(do_write)
    {
      logAppend("writing wavetables...");
    }

    WRITE_STRING("WAVETABLES");

    uint32_t tell = our_data.size();
    WRITE_32BITS_AT(4, tell); //wavetable offset rewritten

    for(int i = 0; i < (int)our_wavetables.size(); i++)
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

    tell = our_data.size();
    WRITE_32BITS_AT(8, tell); //orders offset rewritten

    WRITE_8BITS(s->ordersLen);

    for(int i = 0; i < F303_NUM_CHANNELS; i++)
    {
      for(int j = 0; j < (int)s->ordersLen; j++)
      {
        WRITE_32BITS(orders[i][j]);
      }
    }

    if(do_write)
    {
      logAppend("writing \"registers dump\"...");
    }

    WRITE_STRING("PATTERNS OF COMMANDS");

    tell = our_data.size();
    WRITE_32BITS_AT(12, tell); //cmds offset rewritten

    //write...

    if(do_write)
    {
      writer->writeText(fmt::sprintf("const uint32_t music_size = %d;\n\n", (int)our_data.size()));
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
    delete[] orders;
    delete[] patterns;

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
