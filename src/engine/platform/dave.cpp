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

#include "dave.h"
#include "../engine.h"
#include "../../ta-log.h"

#define CHIP_FREQBASE (8000000.0)
#define CHIP_DIVIDER (16)

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }

const char* regCheatSheetDAVE[]={

  NULL
};

const char** DivPlatformDAVE::getRegisterSheet() {
  return regCheatSheetDAVE;
}

void DivPlatformDAVE::acquire(short** buf, size_t len) {
  for(int h = 0; h < len; h++)
  {
    uint32_t result = dave.runOneCycle_();

    buf[0][h] = 0;
    buf[1][h] = 0;

    for(int i = 0; i < 4; i++)
    {
      buf[0][h] += dave.audio_out[i][0] << 4;
      buf[1][h] += dave.audio_out[i][1] << 4;

      oscBuf[i]->data[oscBuf[i]->needle++] = (dave.audio_out[i][0] + dave.audio_out[i][1]) * 8;
    }
  }

  while (!writes.empty()) { //do register writes
    QueuedWrite w=writes.front();
    if(w.addr < 0x20)
    {
      dave.writePort((uint16_t)w.addr,(uint8_t)w.val);
    }
    
    regPool[w.addr]=w.val;
    writes.pop();
  }
}

void DivPlatformDAVE::tick(bool sysTick) {
  for (int i=0; i<4; i++) 
  {
    chan[i].std.next();
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->had) {
      chan[i].outVol=VOL_SCALE_LINEAR(chan[i].vol&63,MIN(63,chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->val),63);
      rWrite(0x8 + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panleft / 63);
      rWrite(0xc + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panright / 63);
    }
    if (NEW_ARP_STRAT) {
      chan[i].handleArp();
    } else if (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->had) {
      if (!chan[i].inPorta) {
        chan[i].baseFreq=NOTE_PERIODIC(parent->calcArp(chan[i].note,chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val));
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->had) {
      if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->mode) {
        chan[i].pitch2+=chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
        CLAMP_VAR(chan[i].pitch2,-32768,32767);
      } else {
        chan[i].pitch2=chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->had) {
      chan[i].mode=chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->val & 3;
      rWrite(0 + 2*i, chan[i].freq & 0xff);
      rWrite(1 + 2*i, ((chan[i].freq & 0xf00) >> 8) | (chan[i].mode << 4));
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PAN_LEFT)->had) {
      chan[i].panleft = chan[i].std.get_div_macro_struct(DIV_MACRO_PAN_LEFT)->val & 63;
      rWrite(0x8 + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panleft / 63);
      rWrite(0xc + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panright / 63);
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PAN_RIGHT)->had) {
      chan[i].panright = chan[i].std.get_div_macro_struct(DIV_MACRO_PAN_RIGHT)->val & 63;
      rWrite(0x8 + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panleft / 63);
      rWrite(0xc + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panright / 63);
    }

    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) 
    {
      chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,true,0,chan[i].pitch2,(double)chipClock,(double)CHIP_DIVIDER);
      
      if (chan[i].freq < 0) chan[i].freq=0;
      if (chan[i].freq > 0xfff) chan[i].freq=0xfff;

      // write frequency
      rWrite(0 + 2*i, chan[i].freq & 0xff);
      rWrite(1 + 2*i, ((chan[i].freq & 0xf00) >> 8) | (chan[i].mode << 4));

      if(chan[i].keyOn)
      {
        rWrite(0x8 + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panleft / 63);
        rWrite(0xc + i, isMuted[i] ? 0 : chan[i].outVol * chan[i].panright / 63);
      }

      if (chan[i].keyOff) 
      {
        rWrite(0x8 + i, 0);
        rWrite(0xc + i, 0);
      }

      if (chan[i].keyOn) chan[i].keyOn=false;
      if (chan[i].keyOff) chan[i].keyOff=false;
      chan[i].freqChanged=false;
    }
  }
}

int DivPlatformDAVE::dispatch(DivCommand c) {
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_POKEY);
      if (c.value!=DIV_NOTE_NULL) {
        chan[c.chan].baseFreq=NOTE_PERIODIC(c.value);
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;
      chan[c.chan].macroInit(ins);
      if (!parent->song.brokenOutVol && !chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->will) {
        chan[c.chan].outVol=chan[c.chan].vol;
      }
      chan[c.chan].insChanged=false;
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].macroInit(NULL);
      break;
    case DIV_CMD_NOTE_OFF_ENV:
    case DIV_CMD_ENV_RELEASE:
      chan[c.chan].std.release();
      break;
    case DIV_CMD_INSTRUMENT:
      if (chan[c.chan].ins!=c.value || c.value2==1) {
        chan[c.chan].ins=c.value;
        chan[c.chan].insChanged=true;
      }
      break;
    case DIV_CMD_VOLUME:
      if (chan[c.chan].vol!=c.value) {
        chan[c.chan].vol=c.value;
        if (!chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->has) {
          chan[c.chan].outVol=c.value;
          if (chan[c.chan].active) {
          }
        }
      }
      break;
    case DIV_CMD_GET_VOLUME:
      if (chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->has) {
        return chan[c.chan].vol;
      }
      return chan[c.chan].outVol;
      break;
    case DIV_CMD_PITCH:
      chan[c.chan].pitch=c.value;
      chan[c.chan].freqChanged=true;
      break;
    case DIV_CMD_NOTE_PORTA: {
      int destFreq=NOTE_PERIODIC(c.value2);
      bool return2=false;
      if (destFreq>chan[c.chan].baseFreq) {
        chan[c.chan].baseFreq+=c.value;
        if (chan[c.chan].baseFreq>=destFreq) {
          chan[c.chan].baseFreq=destFreq;
          return2=true;
        }
      } else {
        chan[c.chan].baseFreq-=c.value;
        if (chan[c.chan].baseFreq<=destFreq) {
          chan[c.chan].baseFreq=destFreq;
          return2=true;
        }
      }
      chan[c.chan].freqChanged=true;
      if (return2) {
        chan[c.chan].inPorta=false;
        return 2;
      }
      break;
    }
    case DIV_CMD_LEGATO:
      chan[c.chan].baseFreq=NOTE_PERIODIC(c.value);
      chan[c.chan].freqChanged=true;
      chan[c.chan].note=c.value;
      break;
    case DIV_CMD_PRE_PORTA:
      if (chan[c.chan].active && c.value2) {
        if (parent->song.resetMacroOnPorta) chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_POKEY));
      }
      if (!chan[c.chan].inPorta && c.value && !parent->song.brokenPortaArp && chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=NOTE_PERIODIC(chan[c.chan].note);
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_GET_VOLMAX:
      return 63;
      break;
    case DIV_CMD_MACRO_OFF:
      chan[c.chan].std.mask(c.value,true);
      break;
    case DIV_CMD_MACRO_ON:
      chan[c.chan].std.mask(c.value,false);
      break;
    case DIV_CMD_MACRO_RESTART:
      chan[c.chan].std.restart(c.value);
      break;
    default:
      break;
  }
  return 1;
}

void DivPlatformDAVE::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
}

void DivPlatformDAVE::forceIns() {
  for (int i=0; i<4; i++) {
    chan[i].insChanged=true;
    chan[i].freqChanged=true;
  }
}

void* DivPlatformDAVE::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformDAVE::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivChannelPair DivPlatformDAVE::getPaired(int ch) {
  return DivChannelPair();
}

DivDispatchOscBuffer* DivPlatformDAVE::getOscBuffer(int ch) {
  return oscBuf[ch];
}

unsigned char* DivPlatformDAVE::getRegisterPool() {
  return regPool;
}

int DivPlatformDAVE::getRegisterPoolSize() {
  return 32;
}

void DivPlatformDAVE::reset() {
  while (!writes.empty()) writes.pop();
  memset(regPool,0,16);
  for (int i=0; i<4; i++) {
    chan[i]=DivPlatformDAVE::Channel();
    chan[i].std.setEngine(parent);
  }
  if (dumpWrites) {
    addWrite(0xffffffff,0);
  }

  for(int i = 0; i < 0x20; i++)
  {
    dave.writePort((uint16_t)i, (uint8_t)0);
  }

  dave.reset();
}

bool DivPlatformDAVE::keyOffAffectsArp(int ch) {
  return true;
}

float DivPlatformDAVE::getPostAmp() {
  return 1.0f;
}

void DivPlatformDAVE::notifyInsDeletion(void* ins) {
  for (int i=0; i<4; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void DivPlatformDAVE::setFlags(const DivConfig& flags) {
  chipClock = (int)CHIP_FREQBASE;

  CHECK_CUSTOM_CLOCK;

  rate = chipClock / CHIP_DIVIDER;

  for (int i=0; i<4; i++)
  {
    oscBuf[i]->rate=rate;
  }
}

void DivPlatformDAVE::poke(unsigned int addr, unsigned short val) {
  rWrite(addr,val);
}

void DivPlatformDAVE::poke(std::vector<DivRegWrite>& wlist) {
  for (DivRegWrite& i: wlist) rWrite(i.addr,i.val);
}

int DivPlatformDAVE::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;
  for (int i=0; i<4; i++) {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }

  setFlags(flags);
  reset();
  return 4;
}

int DivPlatformDAVE::getOutputCount()
{
  return 2;
}

void DivPlatformDAVE::quit() {
  for (int i=0; i<4; i++) {
    delete oscBuf[i];
  }
}

DivPlatformDAVE::~DivPlatformDAVE() {
}
