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

#include "stm32f303.h"
#include "../engine.h"
#include "../platform/f303.h"

typedef struct 
{
  int freq;
} F303State_t;

void DivExportF303::run() 
{
  bool do_write = conf.getBool("writeFile", true);

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

  //file header

  writer->init();

  writer->writeText("CRAP");
  writer->writeI(1); //version

  //size_offset = (uint32_t)crapwriter->tell();
  
  if(do_write)
  {
    logAppend("writing samples...");
  }

  writer->writeText("FLASH SAMPLES");

  if(do_write)
  {
    logAppend("writing wavetables/synth info dump...");
  }

  writer->writeText("REGISTERS DUMP");

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

    while (!done) {
      if (e->nextTick(false,true) || !e->playing) {
        done=true;
        for (int i=0; i<e->song.systemLen; i++) {
          e->disCont[i].dispatch->getRegisterWrites().clear();
        }
        break;
      }

      // write stuff
    }
    // end of song

    // done - close out.
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
    output.push_back(DivROMExportOutput("music.c", writer));
  }

  progress[0].amount=1.0f;

  if(do_write)
  {
    logAppend("finished!");
  }

  if(!do_write)
  {
    logAppend("total data size: blahblah");
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
