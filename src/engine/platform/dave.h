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

#ifndef _DAVE_H
#define _DAVE_H

#include "../dispatch.h"
#include "../../fixedQueue.h"

#include "sound/dave.h"

class DivPlatformDAVE: public DivDispatch {
  struct Channel: public SharedChannel<int> {
    unsigned char mode;
    bool ring_mod, lowpass, highpass;
    unsigned char clock_source;
    unsigned int panleft, panright;
    Channel():
      SharedChannel<int>(63),
      mode(0),
      ring_mod(false),
      lowpass(false),
      highpass(false),
      clock_source(0),
      panleft(63),
      panright(63) {}
  };
  Channel chan[4];
  DivDispatchOscBuffer* oscBuf[4];
  bool isMuted[4];
  struct QueuedWrite {
    unsigned char addr;
    unsigned char val;
    QueuedWrite(): addr(0), val(0) {}
    QueuedWrite(unsigned char a, unsigned char v): addr(a), val(v) {}
  };
  FixedQueue<QueuedWrite,128> writes;
  Ep128::Dave dave;
  unsigned char regPool[32];
  friend void putDispatchChip(void*,int);
  friend void putDispatchChan(void*,int,int);
  public:
    void acquire(short** buf, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivMacroInt* getChanMacroInt(int ch);
    DivChannelPair getPaired(int chan);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    unsigned char* getRegisterPool();
    int getRegisterPoolSize();
    void reset();
    void forceIns();
    void tick(bool sysTick=true);
    void muteChannel(int ch, bool mute);
    bool keyOffAffectsArp(int ch);
    float getPostAmp();
    void setFlags(const DivConfig& flags);
    void notifyInsDeletion(void* ins);
    void poke(unsigned int addr, unsigned short val);
    void poke(std::vector<DivRegWrite>& wlist);
    const char** getRegisterSheet();
    int init(DivEngine* parent, int channels, int sugRate, const DivConfig& flags);
    void quit();
    int getOutputCount();
    unsigned short getPan(int ch);
    ~DivPlatformDAVE();
};

#endif
