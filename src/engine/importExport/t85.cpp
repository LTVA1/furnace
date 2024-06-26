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

#include "importExport.h"
#include "../platform/t85apu.h"
#include "../engine.h"
#include "../ta-log.h"
#include "../utfutils.h"
#include "../song.h"

#ifdef HAVE_GUI
#include "../gui/gui.h"
extern FurnaceGUI g;
#endif

#define _LE(string) (string)

#define REG_WRITE 0x41
#define WAIT_TICKS 0x61
#define WAIT_50Hz 0x63
#define WAIT_60Hz 0x62
#define END_DATA 0x66

// constants
static const uint32_t currentFileVersion = 0x00000000;	// 16.8.8 bits semantic versioning
static const uint32_t currentGd3Version = 0x00000100;

constexpr int MASTER_CLOCK_PREC=(sizeof(void*)==8)?8:0;

SafeWriter* DivEngine::saveT85(bool loop, int trailingTicks)
{
    logV("exporting ATTiny85APU register dump...");
    lastError = "";
    warnings = "";

    stop();
    repeatPattern=false;
    setOrder(0);
    BUSY_BEGIN_SOFT;
    double origRate=got.rate;
    got.rate=44100;
    // determine loop point
    int loopOrder = 0;
    int loopRow = 0;
    int loopEnd = 0;
    walkSong(loopOrder,loopRow,loopEnd);
    logI("t85 export loop point: %d %d",loopOrder,loopRow);

    curOrder = 0;
    freelance = false;
    playing = false;
    extValuePresent = false;
    remainingLoops = -1;

    // play the song ourselves
    bool done = false;
    int writeCount = 0;

    int gd3Off = 0;

    int loopPos=-1;
    int loopTickSong=-1;
    int songTick=0;

    std::vector<size_t> tickPos;
    std::vector<int> tickSample;

    bool trailing=false;
    bool beenOneLoopAlready=false;
    //bool mayWriteRate=(fmod(curSubSong->hz,1.0)<0.00001 || fmod(curSubSong->hz,1.0)>0.99999);
    int countDown=MAX(0,trailingTicks)+1;

    DivDispatchContainer* t85_cont = &disCont[0];
    DivDispatch* t85_dispatch = t85_cont->dispatch;
    DivPlatformT85APU* t85_apu_dispatch = (DivPlatformT85APU*)t85_dispatch;

    int audio_type = t85_apu_dispatch->audio_type;
    int chip_clock = t85_apu_dispatch->chipClock;

    SafeWriter* w = new SafeWriter;
    w->init();

    // write header
    w->write("t85!",4);
    w->writeI(0); // will be written later, eof offset
    w->writeI(currentFileVersion);
    w->writeI(chip_clock);
    w->writeI(0x2C - 16); // "VGM" data offset
    w->writeI(0); // GD3 data offset
    w->writeI(0); // Total number of samples
    w->writeI(0); // Loop offset
    w->writeI(0); // Amount of looping samples
    w->writeI(0); // Extra header offset
    w->writeC(audio_type); // Output method

    w->writeC(0);
    w->writeC(0);
    w->writeC(0); //3 reserved bytes

    for (int i=0; i<song.systemLen; i++) 
    {
      disCont[i].dispatch->toggleRegisterDump(true);
    }

    // write song data
    playSub(false);
    size_t tickCount=0;
    bool writeLoop=false;
    bool alreadyWroteLoop=false;
    int ord=-1;

    while (!done) 
    {
      if (loopPos==-1) {
        if (loopOrder==curOrder && loopRow==curRow) 
        {
          if ((ticks-((tempoAccum+virtualTempoN)/virtualTempoD))<=0) 
          {
            writeLoop=true;
          }
        }
      }
      songTick++;

      tickPos.push_back(w->tell());
      tickSample.push_back(tickCount);
      if (nextTick(false,true)) 
      {
        if (trailing) beenOneLoopAlready=true;
        trailing=true;
        if (!loop) countDown=0;
        for (int i=0; i<chans; i++) 
        {
          chan[i].wentThroughNote=false;
        }
      }
      if (trailing) 
      {
        switch (trailingTicks) 
        {
          case -1: 
          { // automatic
            bool stillHaveTo=false;
            for (int i=0; i<chans; i++) 
            {
              if (!chan[i].goneThroughNote) continue;
              if (!chan[i].wentThroughNote) 
              {
                stillHaveTo=true;
                break;
              }
            }
            if (!stillHaveTo) countDown=0;
            break;
          }
          case -2: // one loop
            break;
          default: // custom
            countDown--;
            break;
        }
        if (song.loopModality!=2) countDown=0;

        if (countDown>0 && !beenOneLoopAlready) 
        {
          loopTickSong++;
        }
      }
      if (countDown<=0 || !playing || beenOneLoopAlready) 
      {
        done=true;
        if (!loop) 
        {
          for (int i=0; i<song.systemLen; i++) 
          {
            disCont[i].dispatch->getRegisterWrites().clear();
          }
          break;
        }

        if (!playing) 
        {
          writeLoop=false;
          loopPos=-1;
        }
      } 
      else 
      {
        // check for pattern change
        if (prevOrder!=ord) 
        {
          logI("registering order change %d on %d",prevOrder, prevRow);
          ord=prevOrder;
        }
      }
      // get register dumps
      for (int i=0; i<song.systemLen; i++) 
      {
        std::vector<DivRegWrite>& writes=disCont[i].dispatch->getRegisterWrites();
        for (DivRegWrite& j: writes) 
        {
          //performVGMWrite(w,song.system[i],j,streamIDs[i],loopTimer,loopFreq,loopSample,sampleDir,isSecond[i],pendingFreq,playingSample,setPos,sampleOff8,sampleLen8,bankOffset[i],directStream);
          w->writeC(REG_WRITE);
          w->writeC(j.addr);
          w->writeC(j.val);
          writeCount++;
        }
        writes.clear();
      }
      // check whether we need to loop
      int totalWait=cycles>>MASTER_CLOCK_PREC;

      // write wait
      if (totalWait>0) 
      {
        if (totalWait==735) 
        {
          w->writeC(WAIT_60Hz);
        } 
        else if (totalWait==882) 
        {
          w->writeC(WAIT_50Hz);
        } 
        else
        {
          w->writeC(WAIT_TICKS);
          w->writeS(totalWait);
        }
        tickCount+=totalWait;
      }
      if (writeLoop && !alreadyWroteLoop) 
      {
        writeLoop=false;
        alreadyWroteLoop=true;
        loopPos=w->tell();
        loopTickSong=songTick;
      }
    }
    // end of song
    w->writeC(END_DATA);

    got.rate=origRate;

    for (int i=0; i<song.systemLen; i++) 
    {
      disCont[i].dispatch->toggleRegisterDump(false);
    }

    // write GD3 tag
    gd3Off=(int)w->tell();
    w->write("Gd3 ",4);
    w->writeI(currentGd3Version);
    w->writeI(0); // length. will be written later

    WString ws;
    ws=utf8To16(song.name.c_str());
    w->writeWString(ws,false); // name
    ws=utf8To16(song.nameJ.c_str());
    w->writeWString(ws,false); // japanese name
    ws=utf8To16(song.category.c_str());
    w->writeWString(ws,false); // game name
    ws=utf8To16(song.categoryJ.c_str());
    w->writeWString(ws,false); // japanese game name
    ws=utf8To16(song.systemName.c_str());
    w->writeWString(ws,false); // system name
    ws=utf8To16(song.systemNameJ.c_str());
    w->writeWString(ws,false); // japanese system name
    ws=utf8To16(song.author.c_str());
    w->writeWString(ws,false); // author name
    ws=utf8To16(song.authorJ.c_str());
    w->writeWString(ws,false); // japanese author name
    w->writeS(0); // date
    w->writeWString(L"Furnace-B (chiptune tracker)",false); // ripper
    w->writeS(0); // notes

    int gd3Len=w->tell()-gd3Off-12;

    w->seek(gd3Off+8,SEEK_SET);
    w->writeI(gd3Len);

    // finish file
    size_t len=w->size()-4;
    w->seek(4,SEEK_SET);
    w->writeI(len);
    w->seek(0x14,SEEK_SET);
    w->writeI(gd3Off-0x14);
    w->writeI(tickCount);
    if (loop) 
    {
      if (loopPos==-1) 
      {
        w->writeI(0);
        w->writeI(0);
      } 
      else if (loopTickSong<0 || loopTickSong>(int)tickPos.size()) 
      {
        logW("loopTickSong out of range! %d>%d",loopTickSong,(int)tickPos.size());
        w->writeI(0);
        w->writeI(0);
      } 
      else 
      {
        int realLoopTick=tickSample[loopTickSong];
        int realLoopPos=tickPos[loopTickSong];
        logI("tickCount-realLoopTick: %d. realLoopPos: %d",tickCount-realLoopTick,realLoopPos);
        w->writeI(realLoopPos-0x1c);
        w->writeI(tickCount-realLoopTick);
      }
    } 
    else 
    {
      w->writeI(0);
      w->writeI(0);
    }

    remainingLoops=-1;
    playing=false;
    freelance=false;
    extValuePresent=false;

    logI("%d register writes total.",writeCount);

    //saveLock.unlock();
    BUSY_END;
    return w;
}