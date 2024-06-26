#pragma once

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

#ifndef _INSTRUMENT_H
#define _INSTRUMENT_H
#include "safeWriter.h"
#include "dataErrors.h"
#include "../ta-utils.h"
#include "../pch.h"
#include <vector>

#include "wavetable.h"

struct DivSong;

// NOTICE!
// before adding new instrument types to this struct, please ask me first.
// absolutely zero support granted to conflicting formats.
enum DivInstrumentType: unsigned short {
  DIV_INS_STD=0,
  DIV_INS_FM=1,
  DIV_INS_GB=2,
  DIV_INS_C64=3,
  DIV_INS_AMIGA=4,
  DIV_INS_PCE=5,
  DIV_INS_AY=6,
  DIV_INS_AY8930=7,
  DIV_INS_TIA=8,
  DIV_INS_SAA1099=9,
  DIV_INS_VIC=10,
  DIV_INS_PET=11,
  DIV_INS_VRC6=12,
  DIV_INS_OPLL=13,
  DIV_INS_OPL=14,
  DIV_INS_FDS=15,
  DIV_INS_VBOY=16,
  DIV_INS_N163=17,
  DIV_INS_SCC=18,
  DIV_INS_OPZ=19,
  DIV_INS_POKEY=20,
  DIV_INS_BEEPER=21,
  DIV_INS_SWAN=22,
  DIV_INS_MIKEY=23,
  DIV_INS_VERA=24,
  DIV_INS_X1_010=25,
  DIV_INS_VRC6_SAW=26,
  DIV_INS_ES5506=27,
  DIV_INS_MULTIPCM=28,
  DIV_INS_SNES=29,
  DIV_INS_SU=30,
  DIV_INS_NAMCO=31,
  DIV_INS_OPL_DRUMS=32,
  DIV_INS_OPM=33,
  DIV_INS_NES=34,
  DIV_INS_MSM6258=35,
  DIV_INS_MSM6295=36,
  DIV_INS_ADPCMA=37,
  DIV_INS_ADPCMB=38,
  DIV_INS_SEGAPCM=39,
  DIV_INS_QSOUND=40,
  DIV_INS_YMZ280B=41,
  DIV_INS_RF5C68=42,
  DIV_INS_MSM5232=43,
  DIV_INS_T6W28=44,
  DIV_INS_K007232=45,
  DIV_INS_GA20=46,
  DIV_INS_POKEMINI=47,
  DIV_INS_SM8521=48,
  DIV_INS_PV1000=49,
  DIV_INS_K053260=50,
  // DIV_INS_YMF292=51,
  DIV_INS_TED=52,
  DIV_INS_C140=53,
  DIV_INS_C219=54,
  DIV_INS_ESFM=55,
  DIV_INS_ES5503=56,
  DIV_INS_POWERNOISE=57,
  DIV_INS_POWERNOISE_SLOPE=58,
  DIV_INS_DAVE=59,
  DIV_INS_GBA_DMA=60,
  DIV_INS_GBA_MINMOD=61,
  DIV_INS_KURUMITSU=62,
  DIV_INS_SID2=63,
  DIV_INS_NDS=64,
  DIV_INS_FZT = 65,
  DIV_INS_BIFURCATOR=66,
  DIV_INS_AT85APU=67,
  DIV_INS_MAX,
  DIV_INS_NULL
};

enum DivMacroType: unsigned char {
  DIV_MACRO_VOL=0,
  DIV_MACRO_ARP,
  DIV_MACRO_DUTY,
  DIV_MACRO_WAVE,
  DIV_MACRO_PITCH,
  DIV_MACRO_EX1,
  DIV_MACRO_EX2,
  DIV_MACRO_EX3,
  DIV_MACRO_ALG,
  DIV_MACRO_FB,
  DIV_MACRO_FMS,
  DIV_MACRO_AMS,
  DIV_MACRO_PAN_LEFT,
  DIV_MACRO_PAN_RIGHT,
  DIV_MACRO_PHASE_RESET,
  DIV_MACRO_EX4,
  DIV_MACRO_EX5,
  DIV_MACRO_EX6,
  DIV_MACRO_EX7,
  DIV_MACRO_EX8,
  
  DIV_MACRO_EX9,
  DIV_MACRO_EX10,
  DIV_MACRO_EX11,
  DIV_MACRO_EX12,
  DIV_MACRO_EX13,
  DIV_MACRO_EX14,
  DIV_MACRO_EX15,
  DIV_MACRO_EX16,
  DIV_MACRO_EX17,
  DIV_MACRO_EX18,
  DIV_MACRO_EX19,
  DIV_MACRO_EX20,
};

enum DivMacroTypeOp: unsigned char {
  DIV_MACRO_OP_AM=32,
  DIV_MACRO_OP_AR,
  DIV_MACRO_OP_DR,
  DIV_MACRO_OP_MULT,
  DIV_MACRO_OP_RR,
  DIV_MACRO_OP_SL,
  DIV_MACRO_OP_TL,
  DIV_MACRO_OP_DT2,
  DIV_MACRO_OP_RS,
  DIV_MACRO_OP_DT,
  DIV_MACRO_OP_D2R,
  DIV_MACRO_OP_SSG,
  DIV_MACRO_OP_DAM,
  DIV_MACRO_OP_DVB,
  DIV_MACRO_OP_EGT,
  DIV_MACRO_OP_KSL,
  DIV_MACRO_OP_SUS,
  DIV_MACRO_OP_VIB,
  DIV_MACRO_OP_WS,
  DIV_MACRO_OP_KSR,

  DIV_MACRO_OP_EX1,
  DIV_MACRO_OP_EX2,
  DIV_MACRO_OP_EX3,
  DIV_MACRO_OP_EX4,
  DIV_MACRO_OP_EX5,
  DIV_MACRO_OP_EX6,
  DIV_MACRO_OP_EX7,
  DIV_MACRO_OP_EX8,
  DIV_MACRO_OP_EX9,
  DIV_MACRO_OP_EX10,
  DIV_MACRO_OP_EX11,
  DIV_MACRO_OP_EX12,
};

// FM operator structure:
// - OPN:
//   - AM, AR, DR, MULT, RR, SL, TL, RS, DT, D2R, SSG-EG
// - OPM:
//   - AM, AR, DR, MULT, RR, SL, TL, DT2, RS, DT, D2R
// - OPLL:
//   - AM, AR, DR, MULT, RR, SL, TL, SSG-EG&8 = EG-S
//   - KSL, VIB, KSR
// - OPL:
//   - AM, AR, DR, MULT, RR, SL, TL, SSG-EG&8 = EG-S
//   - KSL, VIB, WS (OPL2/3), KSR
// - OPZ:
//   - AM, AR, DR, MULT (CRS), RR, SL, TL, DT2, RS, DT, D2R
//   - WS, DVB = MULT (FINE), DAM = REV, KSL = EGShift, EGT = Fixed

struct DivInstrumentFM {
  unsigned char alg, fb, fms, ams, fms2, ams2, ops, opllPreset;
  bool fixedDrums;
  unsigned short kickFreq, snareHatFreq, tomTopFreq;

  bool operator==(const DivInstrumentFM& other);
  bool operator!=(const DivInstrumentFM& other) {
    return !(*this==other);
  }
  struct Operator {
    bool enable;
    unsigned char am, ar, dr, mult, rr, sl, tl, dt2, rs, dt, d2r, ssgEnv;
    unsigned char dam, dvb, egt, ksl, sus, vib, ws, ksr; // YMU759/OPL/OPZ
    unsigned char kvs;

    bool operator==(const Operator& other);
    bool operator!=(const Operator& other) {
      return !(*this==other);
    }
    Operator():
      enable(true),
      am(0),
      ar(0),
      dr(0),
      mult(0),
      rr(0),
      sl(0),
      tl(0),
      dt2(0),
      rs(0),
      dt(0),
      d2r(0),
      ssgEnv(0),
      dam(0),
      dvb(0),
      egt(0),
      ksl(0),
      sus(0),
      vib(0),
      ws(0),
      ksr(0),
      kvs(2) {}
  } op[4];
  DivInstrumentFM():
    alg(0),
    fb(0),
    fms(0),
    ams(0),
    fms2(0),
    ams2(0),
    ops(2),
    opllPreset(0),
    fixedDrums(false),
    kickFreq(0x520),
    snareHatFreq(0x550),
    tomTopFreq(0x1c0) {
    // default instrument
    fb=4;
    op[0].tl=42;
    op[0].ar=31;
    op[0].dr=8;
    op[0].sl=15;
    op[0].rr=3;
    op[0].mult=5;
    op[0].dt=5;

    op[2].tl=18;
    op[2].ar=31;
    op[2].dr=10;
    op[2].sl=15;
    op[2].rr=4;
    op[2].mult=1;
    op[2].dt=0;

    op[1].tl=48;
    op[1].ar=31;
    op[1].dr=4;
    op[1].sl=11;
    op[1].rr=1;
    op[1].mult=1;
    op[1].dt=5;

    op[3].tl=2;
    op[3].ar=31;
    op[3].dr=9;
    op[3].sl=15;
    op[3].rr=9;
    op[3].mult=1;
    op[3].dt=0;
  }
};

// this is getting out of hand
struct DivInstrumentMacro {
  int val[256];
  unsigned int mode;
  unsigned char open;
  unsigned char len, delay, speed, loop, rel;
  // 0-31: normal
  // 32+: operator (top 3 bits select operator, starting from 1)
  unsigned char macroType;
  
  // the following variables are used by the GUI and not saved in the file
  int vScroll, vZoom;
  int typeMemory[18];
  unsigned char lenMemory;

  explicit DivInstrumentMacro(unsigned char initType, bool initOpen=false):
    mode(0),
    open(initOpen),
    len(0),
    delay(0),
    speed(1),
    loop(255),
    rel(255),
    macroType(initType),
    vScroll(0),
    vZoom(-1),
    lenMemory(0) {
    memset(val,0,256*sizeof(int));
    memset(typeMemory,0,18*sizeof(int));
  }
};

struct DivInstrumentSTD
{
  std::vector<DivInstrumentMacro> macros;

  struct OpMacro
  {
    std::vector<DivInstrumentMacro> macros;

    DivInstrumentMacro* op_get_macro(uint8_t macro_id, bool allocate)
    {
      static DivInstrumentMacro dummy = DivInstrumentMacro(0xff); //empty macro

      if(macro_id < 0x40)
      {
        for(int i = 0; i < (int)macros.size(); i++)
        {
          if(macros[i].macroType == macro_id) return &macros[i];
        }

        if(allocate)
        {
          macros.push_back(DivInstrumentMacro(macro_id));
          return &macros[macros.size() - 1];
        }
        else
        {
          //DivInstrumentMacro* macro = new DivInstrumentMacro(macro_id);
          return &dummy;
        }
      }

      return NULL;
    }
  };

  std::vector<OpMacro> ops;

  std::vector<DivWavetable*> local_waves;

  OpMacro* get_op_macro(uint8_t index)
  {
    if(index >= ops.size())
    {
      int limit = index + 1 - ops.size();

      for(int j = 0; j < limit; j++)
      {
        ops.push_back(OpMacro());
      }
    }

    return &ops[index];
  }

  DivInstrumentMacro* get_macro(uint8_t macro_id, bool allocate)
  {
    static DivInstrumentMacro dummy = DivInstrumentMacro(0xff); //empty macro

    if(macro_id < 0x20) //allocate new macro for main instrument
    {
      for(int i = 0; i < (int)macros.size(); i++)
      {
        if(macros[i].macroType == macro_id) return &macros[i];
      }

      if(allocate)
      {
        macros.push_back(DivInstrumentMacro(macro_id));
        return &macros.back();
      }
      else
      {
        //DivInstrumentMacro* macro = new DivInstrumentMacro(macro_id);
        return &dummy;
      }
    }

    return NULL;
  }
};

struct DivInstrumentGB {
  unsigned char envVol, envDir, envLen, soundLen, hwSeqLen;
  bool softEnv, alwaysInit, doubleWave;
  enum HWSeqCommands: unsigned char {
    DIV_GB_HWCMD_ENVELOPE=0,
    DIV_GB_HWCMD_SWEEP,
    DIV_GB_HWCMD_WAIT,
    DIV_GB_HWCMD_WAIT_REL,
    DIV_GB_HWCMD_LOOP,
    DIV_GB_HWCMD_LOOP_REL,

    DIV_GB_HWCMD_MAX
  };

  typedef struct {
    unsigned char cmd;
    unsigned short data;
  } HWSeqCommandGB;

  std::vector<HWSeqCommandGB> hwSeq;

  HWSeqCommandGB* get_gb_hw_seq(int i, bool allocate)
  {
    static HWSeqCommandGB dummy;

    if(hwSeq.size() != 0)
    {
      return &hwSeq[i];
    }
    else
    {
      if(allocate)
      {
        hwSeq.resize(256);
        return &hwSeq[i];
      }
      else
      {
        memset((void*)&dummy, 0, sizeof(dummy));
        return &dummy;
      }
    }
  }

  bool operator==(const DivInstrumentGB& other);
  bool operator!=(const DivInstrumentGB& other) {
    return !(*this==other);
  }

  DivInstrumentGB():
    envVol(15),
    envDir(0),
    envLen(2),
    soundLen(64),
    hwSeqLen(0),
    softEnv(false),
    alwaysInit(false),
    doubleWave(false) {}
};

struct DivInstrumentC64 {
  bool triOn, sawOn, pulseOn, noiseOn;
  unsigned char a, d, s, r;
  unsigned short duty;
  unsigned char ringMod, oscSync;
  bool toFilter, initFilter, dutyIsAbs, filterIsAbs, noTest, resetDuty;
  unsigned char res;
  unsigned short cut;
  bool hp, lp, bp, ch3off;

  bool operator==(const DivInstrumentC64& other);
  bool operator!=(const DivInstrumentC64& other) {
    return !(*this==other);
  }

  DivInstrumentC64():
    triOn(false),
    sawOn(true),
    pulseOn(false),
    noiseOn(false),
    a(0),
    d(8),
    s(0),
    r(0),
    duty(2048),
    ringMod(0),
    oscSync(0),
    toFilter(false),
    initFilter(false),
    dutyIsAbs(false),
    filterIsAbs(false),
    noTest(false),
    resetDuty(true),
    res(0),
    cut(0),
    hp(false),
    lp(false),
    bp(false),
    ch3off(false) {}
};

struct DivInstrumentAmiga {
  struct SampleMap {
    int freq;
    short map;
    signed char dpcmFreq;
    signed char dpcmDelta;
    SampleMap(int f=0, short m=-1, signed char df=15, signed char dd=-1):
      freq(f),
      map(m),
      dpcmFreq(df),
      dpcmDelta(dd) {}
  };
  short initSample;
  bool useNoteMap;
  bool useSample;
  bool useWave;
  unsigned char waveLen;
  std::vector<SampleMap> noteMap;

  SampleMap* get_amiga_sample_map(int i, bool allocate)
  {
    static SampleMap dummy;

    if(noteMap.size() != 0)
    {
      return &noteMap[i];
    }
    else
    {
      if(allocate)
      {
        noteMap.resize(120);

        for(int j = 0; j < 120; j++)
        {
          noteMap[j].map=-1;
          noteMap[j].freq=j;
        }

        return &noteMap[i];
      }
      else
      {
        memset((void*)&dummy, 0, sizeof(dummy));
        return &dummy;
      }
    }
  }

  bool operator==(const DivInstrumentAmiga& other);
  bool operator!=(const DivInstrumentAmiga& other) {
    return !(*this==other);
  }

  /**
   * get the sample at specified note.
   * @return the sample.
   */
  inline short getSample(int note) {
    if (useNoteMap) {
      if (note<0) note=0;
      if (note>119) note=119;
      return noteMap[note].map;
    }
    return initSample;
  }

  /**
   * get the sample playback note at specified note.
   * @return the note, or -1 if not using note map.
   */
  inline int getFreq(int note) {
    if (useNoteMap) {
      if (note<0) note=0;
      if (note>119) note=119;
      return noteMap[note].freq;
    }
    return note;
  }

  /**
   * get the DPCM pitch at specified note.
   * @return the pitch, or -1 if not using note map.
   */
  inline signed char getDPCMFreq(int note) {
    if (useNoteMap) {
      if (note<0) note=0;
      if (note>119) note=119;
      return noteMap[note].dpcmFreq;
    }
    return -1;
  }

  /**
   * get the DPCM delta counter value at specified note.
   * @return the delta counter value, or -1 if not using note map.
   */
  inline signed char getDPCMDelta(int note) {
    if (useNoteMap) {
      if (note<0) note=0;
      if (note>119) note=119;
      return noteMap[note].dpcmDelta;
    }
    return -1;
  }

  DivInstrumentAmiga():
    initSample(0),
    useNoteMap(false),
    useSample(false),
    useWave(false),
    waveLen(31) {}
};

struct DivInstrumentX1_010 {
  int bankSlot;

  bool operator==(const DivInstrumentX1_010& other);
  bool operator!=(const DivInstrumentX1_010& other) {
    return !(*this==other);
  }

  DivInstrumentX1_010():
    bankSlot(0) {}
};

struct DivInstrumentN163 {
  int wave, wavePos, waveLen;
  unsigned char waveMode;
  bool perChanPos;
  int wavePosCh[8];
  int waveLenCh[8];

  bool operator==(const DivInstrumentN163& other);
  bool operator!=(const DivInstrumentN163& other) {
    return !(*this==other);
  }

  DivInstrumentN163():
    wave(-1),
    wavePos(0),
    waveLen(32),
    waveMode(3),
    perChanPos(false) {
    for (int i=0; i<8; i++) {
      wavePosCh[i]=(i&3)<<5;
      waveLenCh[i]=32;
    }
  }
};

struct DivInstrumentFDS {
  signed char modTable[32];
  int modSpeed, modDepth;
  // this is here for compatibility.
  bool initModTableWithFirstWave;

  bool operator==(const DivInstrumentFDS& other);
  bool operator!=(const DivInstrumentFDS& other) {
    return !(*this==other);
  }

  DivInstrumentFDS():
    modSpeed(0),
    modDepth(0),
    initModTableWithFirstWave(false) {
    memset(modTable,0,32);
  }
};

struct DivInstrumentMultiPCM {
  unsigned char ar, d1r, dl, d2r, rr, rc;
  unsigned char lfo, vib, am;

  bool operator==(const DivInstrumentMultiPCM& other);
  bool operator!=(const DivInstrumentMultiPCM& other) {
    return !(*this==other);
  }

  DivInstrumentMultiPCM():
    ar(15), d1r(15), dl(0), d2r(0), rr(15), rc(15),
    lfo(0), vib(0), am(0) {
  }
};

enum DivWaveSynthEffects {
  DIV_WS_NONE=0,
  // one waveform effects
  DIV_WS_INVERT,
  DIV_WS_ADD,
  DIV_WS_SUBTRACT,
  DIV_WS_AVERAGE,
  DIV_WS_PHASE,
  DIV_WS_CHORUS,

  DIV_WS_SINGLE_MAX,
  
  // two waveform effects
  DIV_WS_NONE_DUAL=128,
  DIV_WS_WIPE,
  DIV_WS_FADE,
  DIV_WS_PING_PONG,
  DIV_WS_OVERLAY,
  DIV_WS_NEGATIVE_OVERLAY,
  DIV_WS_SLIDE,
  DIV_WS_MIX,
  DIV_WS_PHASE_MOD,

  DIV_WS_DUAL_MAX
};

struct DivInstrumentWaveSynth {
  int wave1, wave2;
  unsigned char rateDivider;
  unsigned char effect;
  bool oneShot, enabled, global, wave1global, wave2global;
  unsigned char speed, param1, param2, param3, param4;

  bool operator==(const DivInstrumentWaveSynth& other);
  bool operator!=(const DivInstrumentWaveSynth& other) {
    return !(*this==other);
  }

  DivInstrumentWaveSynth():
    wave1(0),
    wave2(0),
    rateDivider(1),
    effect(DIV_WS_NONE),
    oneShot(false),
    enabled(false),
    global(false),
    wave1global(true),
    wave2global(true),
    speed(0),
    param1(0),
    param2(0),
    param3(0),
    param4(0) {}
};

struct DivInstrumentSoundUnit {
  bool switchRoles;
  unsigned char hwSeqLen;
  enum HWSeqCommands: unsigned char {
    DIV_SU_HWCMD_VOL=0,
    DIV_SU_HWCMD_PITCH,
    DIV_SU_HWCMD_CUT,
    DIV_SU_HWCMD_WAIT,
    DIV_SU_HWCMD_WAIT_REL,
    DIV_SU_HWCMD_LOOP,
    DIV_SU_HWCMD_LOOP_REL,

    DIV_SU_HWCMD_MAX
  };

  typedef struct {
    unsigned char cmd;
    unsigned char bound;
    unsigned char val;
    unsigned short speed;
    unsigned short padding;
  } HWSeqCommandSU;

  std::vector<HWSeqCommandSU> hwSeq;

  bool operator==(const DivInstrumentSoundUnit& other);
  bool operator!=(const DivInstrumentSoundUnit& other) {
    return !(*this==other);
  }

  DivInstrumentSoundUnit():
    switchRoles(false),
    hwSeqLen(0) {}

  HWSeqCommandSU* get_su_hw_seq(int i, bool allocate)
  {
    static HWSeqCommandSU dummy;

    if(hwSeq.size() != 0)
    {
      return &hwSeq[i];
    }
    else
    {
      if(allocate)
      {
        hwSeq.resize(256);
        return &hwSeq[i];
      }
      else
      {
        memset((void*)&dummy, 0, sizeof(dummy));
        return &dummy;
      }
    }
  }
};

struct DivInstrumentES5506 {
  struct Filter {
    enum FilterMode: unsigned char { // filter mode for pole 4,3
      FILTER_MODE_HPK2_HPK2=0,
      FILTER_MODE_HPK2_LPK1,
      FILTER_MODE_LPK2_LPK2,
      FILTER_MODE_LPK2_LPK1,
    };
    FilterMode mode;
    unsigned char virtual_filter_mode;
    unsigned short k1, k2;
    Filter():
      mode(FILTER_MODE_LPK2_LPK1),
      virtual_filter_mode(0),
      k1(0xffff),
      k2(0xffff) {}
  };
  struct Envelope {
    unsigned short ecount;
    signed char lVRamp, rVRamp;
    signed char k1Ramp, k2Ramp;
    bool k1Slow, k2Slow;
    Envelope():
      ecount(0),
      lVRamp(0),
      rVRamp(0),
      k1Ramp(0),
      k2Ramp(0),
      k1Slow(false),
      k2Slow(false) {}
  };
  Filter filter;
  Envelope envelope;

  bool friendly_mode;

  bool operator==(const DivInstrumentES5506& other);
  bool operator!=(const DivInstrumentES5506& other) {
    return !(*this==other);
  }

  DivInstrumentES5506():
    filter(Filter()),
    envelope(Envelope()),
    friendly_mode(false) {}
};

struct DivInstrumentES5503 {
  unsigned char initial_osc_mode;
  bool softpan_virtual_channel;
  bool phase_reset_on_start;

  enum WaveTableLengths: unsigned char {
    DIV_ES5503_WAVE_LENGTH_MAX=8,
  };
  
  bool operator==(const DivInstrumentES5503& other);
  bool operator!=(const DivInstrumentES5503& other) {
    return !(*this==other);
  }

  DivInstrumentES5503():
    initial_osc_mode(0), softpan_virtual_channel(false),
    phase_reset_on_start(true) {

    }
};

struct DivInstrumentSNES {
  enum GainMode: unsigned char {
    GAIN_MODE_DIRECT=0,
    GAIN_MODE_DEC_LINEAR=4,
    GAIN_MODE_DEC_LOG=5,
    GAIN_MODE_INC_LINEAR=6,
    GAIN_MODE_INC_INVLOG=7
  };
  bool useEnv;
  // 0: no sustain (key off = cut)
  // 1: sustain (R = d2; key off = dec linear to r)
  // 2: sustain (R = d2; key off = dec exponential to r)
  // 3: sustain (R = d2; key off = R to r)
  unsigned char sus;
  GainMode gainMode;
  unsigned char gain;
  unsigned char a, d, s, r, d2;

  bool operator==(const DivInstrumentSNES& other);
  bool operator!=(const DivInstrumentSNES& other) {
    return !(*this==other);
  }

  DivInstrumentSNES():
    useEnv(true),
    sus(0),
    gainMode(GAIN_MODE_DIRECT),
    gain(127),
    a(15),
    d(7),
    s(7),
    r(0),
    d2(0) {}
};

// ESFM operator structure:
// - DELAY, OUT, MOD, L, R, NOISE
//   - Virtual: CT, DT, FIXED
//   - In FM struct: AM, DAM, AR, DR, MULT, RR, SL, TL
//   - In FM struct: KSL, VIB, DVB, WS, SUS, KSR
//   - Not in struct: FNUML, FNUMH, BLOCK

struct DivInstrumentESFM {
  bool operator==(const DivInstrumentESFM& other);
  bool operator!=(const DivInstrumentESFM& other) {
    return !(*this==other);
  }

  // Only works on OP4, so putting it outside the Operator struct instead
  unsigned char noise;
  struct Operator {
    unsigned char delay, outLvl, modIn, left, right, fixed;
    signed char ct, dt;

    bool operator==(const Operator& other);
    bool operator!=(const Operator& other) {
      return !(*this==other);
    }
    Operator():
      delay(0),
      outLvl(0),
      modIn(0),
      left(1),
      right(1),
      fixed(0),
      ct(0),
      dt(0) {}
  } op[4];
  DivInstrumentESFM():
    noise(0)
    {
      op[0].modIn=4;
      op[0].outLvl=0;

      op[1].modIn=7;
      op[1].outLvl=0;

      op[2].modIn=7;
      op[2].outLvl=0;

      op[3].modIn=7;
      op[3].outLvl=7;
    }
};

struct DivInstrumentPowerNoise {
  unsigned char octave;

  bool operator==(const DivInstrumentPowerNoise& other);
  bool operator!=(const DivInstrumentPowerNoise& other) {
    return !(*this==other);
  }
  DivInstrumentPowerNoise():
    octave(0) {}
};

struct DivInstrumentSID2 {
  unsigned char volume;
  unsigned char mix_mode;
  unsigned char noise_mode;

  bool operator==(const DivInstrumentSID2& other);
  bool operator!=(const DivInstrumentSID2& other) {
    return !(*this==other);
  }
  DivInstrumentSID2():
    volume(15),
    mix_mode(0),
    noise_mode(0) {}
};

struct DivInstrumentPOKEY {
  unsigned char raw_freq_macro_mode;

  bool operator==(const DivInstrumentPOKEY& other);
  bool operator!=(const DivInstrumentPOKEY& other) {
    return !(*this==other);
  }
  DivInstrumentPOKEY():
    raw_freq_macro_mode(0) {}
};

struct FZTInstrumentAdsr {
  unsigned char a, d, s, r, volume;

  FZTInstrumentAdsr():
    a(0x4),
    d(0x28),
    s(0x80),
    r(0x30),
    volume(0x80) {}
};

#define FZT_INST_PROG_LEN 16

typedef enum {
    SE_WAVEFORM_NONE = 0,
    SE_WAVEFORM_NOISE = 1,
    SE_WAVEFORM_PULSE = 2,
    SE_WAVEFORM_TRIANGLE = 4,
    SE_WAVEFORM_SAW = 8,
    SE_WAVEFORM_NOISE_METAL = 16,
    SE_WAVEFORM_SINE = 32,
} SoundEngineWaveformType;

typedef enum {
    SE_ENABLE_FILTER = 1,
    SE_ENABLE_GATE = 2,
    SE_ENABLE_RING_MOD = 4,
    SE_ENABLE_HARD_SYNC = 8,
    SE_ENABLE_KEYDOWN_SYNC = 16, // sync oscillators on keydown
} SoundEngineFlags;

typedef enum {
    FIL_OUTPUT_LOWPASS = 1,
    FIL_OUTPUT_HIGHPASS = 2,
    FIL_OUTPUT_BANDPASS = 3,
    FIL_OUTPUT_LOW_HIGH = 4,
    FIL_OUTPUT_HIGH_BAND = 5,
    FIL_OUTPUT_LOW_BAND = 6,
    FIL_OUTPUT_LOW_HIGH_BAND = 7,
    /* ============ */
    FIL_MODES = 8,
} SoundEngineFilterModes;

typedef enum {
    ATTACK = 1,
    DECAY = 2,
    SUSTAIN = 3,
    RELEASE = 4,
    DONE = 5,
} SoundEngineEnvelopeStates;

typedef enum {
    TE_ENABLE_VIBRATO = 1,
    TE_ENABLE_PWM = 2,
    TE_PROG_NO_RESTART = 4,
    TE_SET_CUTOFF = 8,
    TE_SET_PW = 16,
    TE_RETRIGGER_ON_SLIDE = 32, // call trigger instrument function even if slide command is there
} TrackerEngineFlags;

#define MIDDLE_C (12 * 4)
#define MAX_NOTE (12 * 7 + 11)

struct DivInstrumentFZT {

  enum FztCommands: unsigned short {
    TE_EFFECT_ARPEGGIO = 0x0000,
    TE_EFFECT_PORTAMENTO_UP = 0x0100,
    TE_EFFECT_PORTAMENTO_DOWN = 0x0200,
    TE_EFFECT_VIBRATO = 0x0400,
    TE_EFFECT_PWM = 0x1100,
    TE_EFFECT_SET_PW = 0x1200,
    TE_EFFECT_PW_DOWN = 0x1400,
    TE_EFFECT_PW_UP = 0x1300,
    TE_EFFECT_SET_CUTOFF = 0x1500,
    TE_EFFECT_VOLUME_FADE = 0x0a00,
    TE_EFFECT_SET_WAVEFORM = 0x1000,
    TE_EFFECT_SET_VOLUME = 0x1600,

    TE_EFFECT_EXT_TOGGLE_FILTER = 0x1700,
    TE_EFFECT_EXT_PORTA_UP = 0xf100,
    TE_EFFECT_EXT_PORTA_DN = 0xf200,
    TE_EFFECT_EXT_FILTER_MODE = 0x1800,
    //TE_EFFECT_EXT_PATTERN_LOOP = 0x0e60, // e60 = start, e61-e6f = end and indication how many loops you want
    //is not supported in Furnace yet
    TE_EFFECT_EXT_RETRIGGER = 0x0c00,
    TE_EFFECT_EXT_FINE_VOLUME_DOWN = 0xf400,
    TE_EFFECT_EXT_FINE_VOLUME_UP = 0xf300,
    TE_EFFECT_EXT_NOTE_CUT = 0xec00,
    TE_EFFECT_EXT_PHASE_RESET = 0x1900,

    TE_EFFECT_SET_SPEED_PROG_PERIOD = 0x0f00,
    TE_EFFECT_CUTOFF_UP = 0x1A00, // Gxx
    TE_EFFECT_CUTOFF_DOWN = 0x1B00, // Hxx
    TE_EFFECT_SET_RESONANCE = 0x1C00, // Ixx
    TE_EFFECT_RESONANCE_UP = 0x1D00, // Jxx
    TE_EFFECT_RESONANCE_DOWN = 0x1E00, // Kxx

    TE_EFFECT_SET_ATTACK = 0x2100, // Lxx
    TE_EFFECT_SET_DECAY = 0x2200, // Mxx
    TE_EFFECT_SET_SUSTAIN = 0x2300, // Nxx
    TE_EFFECT_SET_RELEASE = 0x2400, // Oxx

    TE_EFFECT_SET_RING_MOD_SRC = 0x1f00, // Rxx
    TE_EFFECT_SET_HARD_SYNC_SRC = 0x2000, // Sxx

    TE_EFFECT_PORTA_UP_SEMITONE = 0x2600, // Txx
    TE_EFFECT_PORTA_DOWN_SEMITONE = 0x2700, // Uxx
    TE_EFFECT_PITCH = 0xE500, //Vxx
    /*
    TE_EFFECT_ = 0x2000, //Wxx
    */
    TE_EFFECT_ARPEGGIO_ABS = 0x2800, // Yxx
    TE_EFFECT_TRIGGER_RELEASE = 0x2900, // Zxx

    /* These effects work only in instrument program */
    TE_PROGRAM_LOOP_BEGIN = 0x7d00,
    TE_PROGRAM_LOOP_END = 0x7e00,
    TE_PROGRAM_JUMP = 0x7f00,
    TE_PROGRAM_NOP = 0x7ffe,
    TE_PROGRAM_END = 0x7fff,
  };

  unsigned char waveform;
  unsigned short flags;
  unsigned short sound_engine_flags;

  unsigned char slide_speed;

  FZTInstrumentAdsr adsr;

  unsigned char ring_mod, hard_sync; // 0xff = self

  unsigned char pw; // store only one byte since we don't have the luxury of virtually unlimited memory!

  typedef struct {
    unsigned short cmd;
    unsigned char val;
    bool unite;
  } ProgramFZT;

  ProgramFZT program[FZT_INST_PROG_LEN];

  unsigned char program_period;

  unsigned char vibrato_speed, vibrato_depth, vibrato_delay;
  unsigned char pwm_speed, pwm_depth, pwm_delay;

  unsigned char filter_cutoff, filter_resonance, filter_type;

  unsigned char base_note;
  signed char finetune;

  bool operator==(const DivInstrumentFZT& other);
  bool operator!=(const DivInstrumentFZT& other) {
    return !(*this==other);
  }

  DivInstrumentFZT():
    waveform(SE_WAVEFORM_PULSE),
    flags(TE_SET_CUTOFF | TE_SET_PW | TE_ENABLE_VIBRATO),
    sound_engine_flags(SE_ENABLE_KEYDOWN_SYNC),
    slide_speed(0),
    ring_mod(0),
    hard_sync(0),
    pw(0x80),
    program_period(1),
    vibrato_speed(0x60),
    vibrato_depth(0x20),
    vibrato_delay(0x20),
    pwm_speed(0),
    pwm_depth(0),
    pwm_delay(0),
    filter_cutoff(0xd0),
    filter_resonance(0),
    filter_type(FIL_OUTPUT_LOWPASS),
    base_note(MIDDLE_C),
    finetune(0) 
    {
      for(int i = 0; i < FZT_INST_PROG_LEN; i++)
      {
        program[i].cmd = TE_PROGRAM_NOP;
        program[i].val = 0;
        program[i].unite = false;
      }

      program[0].cmd = TE_EFFECT_ARPEGGIO;
      program[0].val = 0;
      program[1].cmd = TE_EFFECT_ARPEGGIO;
      program[1].val = 0xf0;
      program[2].cmd = TE_EFFECT_ARPEGGIO;
      program[2].val = 0xf1;
      program[3].cmd = TE_PROGRAM_JUMP;
      program[3].val = 0;
    }
};

struct DivInstrument {
  String name;
  DivInstrumentType type;
  DivInstrumentFM fm;
  DivInstrumentSTD std;
  DivInstrumentGB gb;
  DivInstrumentC64 c64;
  DivInstrumentAmiga amiga;
  DivInstrumentX1_010 x1_010;
  DivInstrumentN163 n163;
  DivInstrumentFDS fds;
  DivInstrumentMultiPCM multipcm;
  DivInstrumentWaveSynth ws;
  DivInstrumentSoundUnit su;
  DivInstrumentES5506 es5506;
  DivInstrumentSNES snes;
  DivInstrumentESFM esfm;
  DivInstrumentES5503 es5503;
  DivInstrumentPowerNoise powernoise;
  DivInstrumentSID2 sid2;
  DivInstrumentPOKEY pokey;
  DivInstrumentFZT fzt;

  /**
   * these are internal functions.
   */
  void writeMacro(SafeWriter* w, const DivInstrumentMacro& m);
  void writeFeatureNA(SafeWriter* w);
  void writeFeatureFM(SafeWriter* w, bool fui);
  void writeFeatureMA(SafeWriter* w, bool tildearrow_version);
  void writeFeature64(SafeWriter* w);
  void writeFeatureGB(SafeWriter* w);
  void writeFeatureSM(SafeWriter* w);
  void writeFeatureOx(SafeWriter* w, int op);
  void writeFeatureLD(SafeWriter* w);
  void writeFeatureSN(SafeWriter* w);
  void writeFeatureN1(SafeWriter* w);
  void writeFeatureFD(SafeWriter* w);
  void writeFeatureWS(SafeWriter* w);
  size_t writeFeatureSL(SafeWriter* w, std::vector<int>& list, const DivSong* song);
  size_t writeFeatureWL(SafeWriter* w, std::vector<int>& list, const DivSong* song);
  void writeFeatureMP(SafeWriter* w);
  void writeFeatureSU(SafeWriter* w);
  void writeFeatureES(SafeWriter* w);
  void writeFeatureX1(SafeWriter* w);
  void writeFeatureNE(SafeWriter* w);
  void writeFeatureEF(SafeWriter* w);
  void writeFeatureE3(SafeWriter* w);
  void writeFeaturePN(SafeWriter* w);
  void writeFeatureS2(SafeWriter* w);
  void writeFeatureLW(SafeWriter* w);
  void writeFeaturePO(SafeWriter* w);
  void writeFeatureFZ(SafeWriter* w);

  void readFeatureNA(SafeReader& reader, short version);
  void readFeatureFM(SafeReader& reader, short version);
  void readFeatureMA(SafeReader& reader, short version, bool tildearrow_version);
  void readFeature64(SafeReader& reader, bool& volIsCutoff, short version);
  void readFeatureGB(SafeReader& reader, short version);
  void readFeatureSM(SafeReader& reader, short version);
  void readFeatureOx(SafeReader& reader, int op, short version);
  void readFeatureLD(SafeReader& reader, short version);
  void readFeatureSN(SafeReader& reader, short version);
  void readFeatureN1(SafeReader& reader, short version);
  void readFeatureFD(SafeReader& reader, short version);
  void readFeatureWS(SafeReader& reader, short version, bool tildearrow_version);
  void readFeatureSL(SafeReader& reader, DivSong* song, short version);
  void readFeatureWL(SafeReader& reader, DivSong* song, short version);
  void readFeatureMP(SafeReader& reader, short version);
  void readFeatureSU(SafeReader& reader, short version);
  void readFeatureES(SafeReader& reader, short version);
  void readFeatureX1(SafeReader& reader, short version);
  void readFeatureNE(SafeReader& reader, short version);
  void readFeatureEF(SafeReader& reader, short version);
  void readFeatureE3(SafeReader& reader, short version);
  void readFeaturePN(SafeReader& reader, short version);
  void readFeatureS2(SafeReader& reader, short version);
  void readFeatureLW(SafeReader& reader, short version);
  void readFeaturePO(SafeReader& reader, short version);
  void readFeatureFZ(SafeReader& reader, short version);

  DivDataErrors readInsDataOld(SafeReader& reader, short version, bool tildearrow_version);
  DivDataErrors readInsDataNew(SafeReader& reader, short version, bool fui, DivSong* song, bool tildearrow_version);

  void convertC64SpecialMacro();

  /**
   * save the instrument to a SafeWriter.
   * @param w the SafeWriter in question.
   */
  void putInsData2(SafeWriter* w, bool fui=false, const DivSong* song=NULL, bool insName=true, bool tilde_version=false);

  /**
   * read instrument data in .fui format.
   * @param reader the reader.
   * @param version the format version.
   * @return a DivDataErrors.
   */
  DivDataErrors readInsData(SafeReader& reader, short version, DivSong* song=NULL);

  /**
   * save this instrument to a file.
   * @param path file path.
   * @param song if new format, a DivSong to read wavetables and samples.
   * @param writeInsName whether to write the instrument name or not. ignored if old format.
   * @return whether it was successful.
   */
  bool save(const char* path, DivSong* song=NULL, bool writeInsName=true);

  /**
   * save this instrument to a file in .dmp format.
   * @param path file path.
   * @return whether it was successful.
   */
  bool saveDMP(const char* path);
  DivInstrument():
    name(""),
    type(DIV_INS_FM) {
  }
};
#endif