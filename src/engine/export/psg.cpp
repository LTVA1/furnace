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

// thanks asiekierka!
// I have ported your code to this ROM export framework.

#include "psg.h"
#include "../engine.h"
#include "../ta-log.h"
#include <fmt/printf.h>
#include <array>
#include <vector>

void DivExportPSG::run() {

  double origRate = e->got.rate;
  e->stop();
  e->repeatPattern=false;
  e->setOrder(0);

  logAppend("playing and logging register writes...");

  SafeWriter* writers[32];

  uint16_t loop_point_addr[32] = { 0x10 }; //by default loop to beginning
  uint16_t last_frame_addr[32] = { 0 };
  bool loop = true;

  for(int i = 0; i < e->song.systemLen; i++)
  {
    auto w = new SafeWriter;
    w->init();

    w->writeText("PSG\x1A");

    for (int j = 0; j < 12; j++)
    {
      w->writeC(0);
    }

    w->writeC(0xFF); //next frame

    for (int j = 0; j < 16; j++)
    {
      w->writeC(j); //reset registers
      w->writeC(0);
    }

    writers[i] = w;
  }

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
    DivGroovePattern curSpeeds=s->speeds;

    int groove_counter = 0;

    for(int o = 0; o < s->ordersLen; o++)
    {
      for(int r = 0; r < s->patLen; r++)
      {
        begin:;

        for(int ch = 0; ch < e->chans; ch++)
        {
          DivPattern* p = s->pat[ch].getPattern(s->orders.ord[ch][o],false);

          for(int eff = 0; eff < DIV_MAX_EFFECTS; eff++)
          {
            short effectVal = p->data[r][5+(eff<<1)];

            if (p->data[r][4 + (eff << 1)] == 0xff)
            {
                loop = false;
                goto finish;
            }
          }
        }

        groove_counter++;
        groove_counter %= curSpeeds.len;

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
    for(int i = 0; i < e->song.systemLen; i++)
    {
      e->disCont[i].dispatch->toggleRegisterDump(true);
    }

    bool got_loop_point = false;

    while (!done) {
      if (e->nextTick(false,true) || !e->playing) {
        done=true;
        for (int i=0; i<e->song.systemLen; i++) {
          e->disCont[i].dispatch->getRegisterWrites().clear();
        }
        break;
      }

      int row = 0;
      int order = 0;
      e->getCurSongPos(row, order);

      progress[0].amount = (float)(order * e->curSubSong->patLen + row) / (float)(e->curSubSong->ordersLen * e->curSubSong->patLen) * 0.95f;

      if(row == loopRow && order == loopOrder && !got_loop_point)
      {
        for(int i = 0; i < e->song.systemLen; i++)
        {
          SafeWriter* w = writers[i];

          if(row == 0 && order == 0 && loop)
          {
            loop_point_addr[i] = 0x10;
          }
          else if(loop)
          {
            loop_point_addr[i] = (uint16_t)w->tell();
          }
          //loop_point_addr[i] = (uint16_t)w->tell();
        }

        got_loop_point = true;
      }

      // write wait
      for(int i = 0; i < e->song.systemLen; i++)
      {
        SafeWriter* w = writers[i];
        last_frame_addr[i] = (uint16_t)w->tell();
        w->writeC(0xff); // next frame
      }
      // get register dumps
      for(int i = 0; i < e->song.systemLen; i++)
      {
        std::vector<DivRegWrite>& writes=e->disCont[i].dispatch->getRegisterWrites();
        SafeWriter* w = writers[i];
        if (writes.size() > 0) 
        {
          for (DivRegWrite& write: writes)
          {
            if ((write.addr) < 16)
            {
              w->writeC(write.addr);
              w->writeC(write.val & 0xff);
            }
          }
            
          writes.clear();
        }
      }
    }
    // end of song

    for(int i = 0; i < e->song.systemLen; i++)
    {
      writers[i]->writeC(0xfe);

      if(!loop) //after end mark store loop point
      {
        writers[i]->writeS(last_frame_addr[i]);
      }
      else
      {
        writers[i]->writeS(loop_point_addr[i]);
      }
    }

    // done - close out.
    e->got.rate=origRate;

    for(int i = 0; i < e->song.systemLen; i++)
    {
      e->disCont[i].dispatch->toggleRegisterDump(false);
    }

    e->remainingLoops=-1;
    e->playing=false;
    e->freelance=false;
    e->extValuePresent=false;
  });

  logAppend("writing data...");
  progress[0].amount=0.95f;

  for(int i = 0; i < e->song.systemLen; i++)
  {
    output.push_back(DivROMExportOutput(fmt::sprintf("ay_%d.psg", i + 1),writers[i]));
  }

  progress[0].amount=1.0f;
  
  logAppend("finished!");

  running=false;
}

bool DivExportPSG::go(DivEngine* eng) {
  progress[0].name="Progress";
  progress[0].amount=0.0f;

  e=eng;
  running=true;
  failed=false;
  mustAbort=false;
  exportThread=new std::thread(&DivExportPSG::run,this);
  return true;
}

void DivExportPSG::wait() {
  if (exportThread!=NULL) {
    logV("waiting for export thread...");
    exportThread->join();
    delete exportThread;
  }
}

void DivExportPSG::abort() {
  mustAbort=true;
  wait();
}

bool DivExportPSG::isRunning() {
  return running;
}

bool DivExportPSG::hasFailed() {
  return failed;
}

DivROMExportProgress DivExportPSG::getProgress(int index) {
  if (index<0 || index>1) return progress[1];
  return progress[index];
}
