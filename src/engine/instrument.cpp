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

#include "dataErrors.h"
#include "engine.h"
#include "instrument.h"
#include "../ta-log.h"
#include "../fileutils.h"

const DivInstrument defaultIns;

#define _C(x) x==other.x

#define UNUSED(x) (void)(x)

bool DivInstrumentFM::operator==(const DivInstrumentFM& other) {
  return (
    _C(alg) &&
    _C(fb) &&
    _C(fms) &&
    _C(ams) &&
    _C(fms2) &&
    _C(ams2) &&
    _C(ops) &&
    _C(opllPreset) &&
    _C(fixedDrums) &&
    _C(kickFreq) &&
    _C(snareHatFreq) &&
    _C(tomTopFreq) &&
    _C(op[0]) &&
    _C(op[1]) &&
    _C(op[2]) &&
    _C(op[3])
  );
}

bool DivInstrumentFM::Operator::operator==(const DivInstrumentFM::Operator& other) {
  return (
    _C(enable) &&
    _C(am) &&
    _C(ar) &&
    _C(dr) &&
    _C(mult) &&
    _C(rr) &&
    _C(sl) &&
    _C(tl) &&
    _C(dt2) &&
    _C(rs) &&
    _C(dt) &&
    _C(d2r) &&
    _C(ssgEnv) &&
    _C(dam) &&
    _C(dvb) &&
    _C(egt) &&
    _C(ksl) &&
    _C(sus) &&
    _C(vib) &&
    _C(ws) &&
    _C(ksr) &&
    _C(kvs)
  );
}

bool DivInstrumentGB::operator==(const DivInstrumentGB& other) {
  return (
    _C(envVol) &&
    _C(envDir) &&
    _C(envLen) &&
    _C(soundLen) &&
    _C(hwSeqLen) &&
    _C(softEnv) &&
    _C(alwaysInit)
  );
}

bool DivInstrumentC64::operator==(const DivInstrumentC64& other) {
  return (
    _C(triOn) &&
    _C(sawOn) &&
    _C(pulseOn) &&
    _C(noiseOn) &&
    _C(a) &&
    _C(d) &&
    _C(s) &&
    _C(r) &&
    _C(duty) &&
    _C(ringMod) &&
    _C(oscSync) &&
    _C(toFilter) &&
    _C(initFilter) &&
    _C(dutyIsAbs) &&
    _C(filterIsAbs) &&
    _C(noTest) &&
    _C(res) &&
    _C(cut) &&
    _C(hp) &&
    _C(lp) &&
    _C(bp) &&
    _C(ch3off)
  );
}

bool DivInstrumentAmiga::operator==(const DivInstrumentAmiga& other) {
  return (
    _C(initSample) &&
    _C(useNoteMap) &&
    _C(useSample) &&
    _C(useWave) &&
    _C(waveLen)
  );
}

bool DivInstrumentX1_010::operator==(const DivInstrumentX1_010& other) {
  return _C(bankSlot);
}

bool DivInstrumentN163::operator==(const DivInstrumentN163& other) {
  return (
    _C(wave) &&
    _C(wavePos) &&
    _C(waveLen) &&
    _C(waveMode) &&
    _C(perChanPos) &&
    _C(wavePosCh[0]) &&
    _C(wavePosCh[1]) &&
    _C(wavePosCh[2]) &&
    _C(wavePosCh[3]) &&
    _C(wavePosCh[4]) &&
    _C(wavePosCh[5]) &&
    _C(wavePosCh[6]) &&
    _C(wavePosCh[7]) &&
    _C(waveLenCh[0]) &&
    _C(waveLenCh[1]) &&
    _C(waveLenCh[2]) &&
    _C(waveLenCh[3]) &&
    _C(waveLenCh[4]) &&
    _C(waveLenCh[5]) &&
    _C(waveLenCh[6]) &&
    _C(waveLenCh[7])
  );
}

bool DivInstrumentFDS::operator==(const DivInstrumentFDS& other) {
  return (
    (memcmp(modTable,other.modTable,32)==0) &&
    _C(modSpeed) &&
    _C(modDepth) &&
    _C(initModTableWithFirstWave)
  );
}

bool DivInstrumentMultiPCM::operator==(const DivInstrumentMultiPCM& other) {
  return (
    _C(ar) &&
    _C(d1r) &&
    _C(dl) &&
    _C(d2r) &&
    _C(rr) &&
    _C(rc) &&
    _C(lfo) &&
    _C(vib) &&
    _C(am)
  );
}

bool DivInstrumentWaveSynth::operator==(const DivInstrumentWaveSynth& other) {
  return (
    _C(wave1) &&
    _C(wave2) &&
    _C(rateDivider) &&
    _C(effect) &&
    _C(oneShot) &&
    _C(enabled) &&
    _C(global) &&
    _C(speed) &&
    _C(param1) &&
    _C(param2) &&
    _C(param3) &&
    _C(param4)
  );
}

bool DivInstrumentSoundUnit::operator==(const DivInstrumentSoundUnit& other) {
  return (
    _C(switchRoles) &&
    _C(hwSeqLen)
  );
}

bool DivInstrumentES5506::operator==(const DivInstrumentES5506& other) {
  return (
    _C(filter.mode) &&
    _C(filter.k1) &&
    _C(filter.k2) &&
    _C(envelope.ecount) &&
    _C(envelope.lVRamp) &&
    _C(envelope.rVRamp) &&
    _C(envelope.k1Ramp) &&
    _C(envelope.k2Ramp) &&
    _C(envelope.k1Slow) &&
    _C(envelope.k2Slow)
  );
}

bool DivInstrumentES5503::operator==(const DivInstrumentES5503& other) {
  return (
    _C(initial_osc_mode) &&
    _C(softpan_virtual_channel) &&
    _C(phase_reset_on_start)
  );
}

bool DivInstrumentSNES::operator==(const DivInstrumentSNES& other) {
  return (
    _C(useEnv) &&
    _C(sus) &&
    _C(gainMode) &&
    _C(gain) &&
    _C(a) &&
    _C(d) &&
    _C(s) &&
    _C(r) &&
    _C(d2)
  );
}

bool DivInstrumentESFM::operator==(const DivInstrumentESFM& other) {
  return (
    _C(noise) &&
    _C(op[0]) &&
    _C(op[1]) &&
    _C(op[2]) &&
    _C(op[3])
  );
}

bool DivInstrumentESFM::Operator::operator==(const DivInstrumentESFM::Operator& other) {
  return (
    _C(delay) &&
    _C(outLvl) &&
    _C(modIn) &&
    _C(left) &&
    _C(right) &&
    _C(fixed) &&
    _C(ct) &&
    _C(dt)
  );
}

bool DivInstrumentSID2::operator==(const DivInstrumentSID2& other) {
  return (
    _C(volume) &&
    _C(mix_mode) &&
    _C(noise_mode)
  );
}

bool DivInstrumentPowerNoise::operator==(const DivInstrumentPowerNoise& other) {
  return _C(octave);
}

bool DivInstrumentPOKEY::operator==(const DivInstrumentPOKEY& other) {
  return _C(raw_freq_macro_mode);
}

#undef _C

#define FEATURE_BEGIN(x) \
  w->write(x,2); \
  size_t featStartSeek=w->tell(); \
  w->writeS(0);

#define FEATURE_END \
  size_t featEndSeek=w->tell(); \
  w->seek(featStartSeek,SEEK_SET); \
  w->writeS(featEndSeek-featStartSeek-2); \
  w->seek(featEndSeek,SEEK_SET);

void DivInstrument::writeFeatureNA(SafeWriter* w) {
  FEATURE_BEGIN("NA");

  w->writeString(name,false);

  FEATURE_END;
}

void DivInstrument::writeFeatureFM(SafeWriter* w, bool fui) {
  FEATURE_BEGIN("FM");

  int opCount=4;
  if (fui) {
    if (type==DIV_INS_OPLL) {
      opCount=2;
    } else if (type==DIV_INS_OPL) {
      opCount=(fm.ops==4)?4:2;
    }
  }
  
  w->writeC(
    (fm.op[3].enable?128:0)|
    (fm.op[2].enable?64:0)|
    (fm.op[1].enable?32:0)|
    (fm.op[0].enable?16:0)|
    opCount
  );

  // base data
  w->writeC(((fm.alg&7)<<4)|(fm.fb&7));
  w->writeC(((fm.fms2&7)<<5)|((fm.ams&3)<<3)|(fm.fms&7));
  w->writeC(((fm.ams2&3)<<6)|((fm.ops==4)?32:0)|(fm.opllPreset&31));

  // operator data
  for (int i=0; i<opCount; i++) {
    DivInstrumentFM::Operator& op=fm.op[i];

    w->writeC((op.ksr?128:0)|((op.dt&7)<<4)|(op.mult&15));
    w->writeC((op.sus?128:0)|(op.tl&127));
    w->writeC(((op.rs&3)<<6)|(op.vib?32:0)|(op.ar&31));
    w->writeC((op.am?128:0)|((op.ksl&3)<<5)|(op.dr&31));
    w->writeC((op.egt?128:0)|((op.kvs&3)<<5)|(op.d2r&31));
    w->writeC(((op.sl&15)<<4)|(op.rr&15));
    w->writeC(((op.dvb&15)<<4)|(op.ssgEnv&15));
    w->writeC(((op.dam&7)<<5)|((op.dt2&3)<<3)|(op.ws&7));
  }

  FEATURE_END;
}

void DivInstrument::writeMacro(SafeWriter* w, const DivInstrumentMacro& m) {
  if (!m.len) return;

  // determine word size
  int macroMin=0x7fffffff;
  int macroMax=0x80000000;
  for (int i=0; i<m.len; i++) {
    if (m.val[i]<macroMin) macroMin=m.val[i];
    if (m.val[i]>macroMax) macroMax=m.val[i];
  }

  unsigned char wordSize=192; // 32-bit

  if (macroMin>=0 && macroMax<=255) {
    wordSize=0; // 8-bit unsigned
  } else if (macroMin>=-128 && macroMax<=127) {
    wordSize=64; // 8-bit signed
  } else if (macroMin>=-32768 && macroMax<=32767) {
    wordSize=128; // 16-bit signed
  } else {
    wordSize=192; // 32-bit signed
  }

  w->writeC(m.macroType&31);
  w->writeC(m.len);
  w->writeC(m.loop);
  w->writeC(m.rel);
  w->writeC(m.mode);
  w->writeC((m.open&0x3f)|wordSize);
  w->writeC(m.delay);
  w->writeC(m.speed);

  switch (wordSize) {
    case 0:
      for (int i=0; i<m.len; i++) {
        w->writeC((unsigned char)m.val[i]);
      }
      break;
    case 64:
      for (int i=0; i<m.len; i++) {
        w->writeC((signed char)m.val[i]);
      }
      break;
    case 128:
      for (int i=0; i<m.len; i++) {
        w->writeS((short)m.val[i]);
      }
      break;
    default: // 192
      for (int i=0; i<m.len; i++) {
        w->writeI(m.val[i]);
      }
      break;
  }
}

void DivInstrument::writeFeatureMA(SafeWriter* w) {
  FEATURE_BEGIN("MA");

  // if you update the macro header, please update this value as well.
  // it's the length.
  w->writeS(8);
  
  // write macros
  
  for(int i = 0; i < 32; i++)
  {
    writeMacro(w,*std.get_macro(DIV_MACRO_VOL + i, false));
  }

  // "stop reading" code
  w->writeC(-1);

  FEATURE_END;
}

void DivInstrument::writeFeature64(SafeWriter* w) {
  FEATURE_BEGIN("64");

  w->writeC(
    (c64.dutyIsAbs?0x80:0)|
    (c64.initFilter?0x40:0)|
    (c64.toFilter?0x10:0)|
    (c64.noiseOn?8:0)|
    (c64.pulseOn?4:0)|
    (c64.sawOn?2:0)|
    (c64.triOn?1:0)
  );

  w->writeC(
    (c64.oscSync?0x80:0)|
    (c64.ringMod?0x40:0)|
    (c64.noTest?0x20:0)|
    (c64.filterIsAbs?0x10:0)|
    (c64.ch3off?8:0)|
    (c64.bp?4:0)|
    (c64.hp?2:0)|
    (c64.lp?1:0)
  );

  w->writeC(((c64.a&15)<<4)|(c64.d&15));
  w->writeC(((c64.s&15)<<4)|(c64.r&15));
  w->writeS(c64.duty);
  w->writeS((unsigned short)((c64.cut&2047)|(c64.res<<12)));

  FEATURE_END;
}

void DivInstrument::writeFeatureGB(SafeWriter* w) {
  FEATURE_BEGIN("GB");

  w->writeC(((gb.envLen&7)<<5)|(gb.envDir?16:0)|(gb.envVol&15));
  w->writeC(gb.soundLen);

  w->writeC(
    (gb.alwaysInit?2:0)|
    (gb.softEnv?1:0)
  );

  w->writeC(gb.hwSeqLen);
  for (int i=0; i<gb.hwSeqLen; i++) {
    w->writeC(gb.get_gb_hw_seq(i, true)->cmd);
    w->writeS(gb.get_gb_hw_seq(i, true)->data);
  }

  FEATURE_END;
}

void DivInstrument::writeFeatureSM(SafeWriter* w) {
  FEATURE_BEGIN("SM");

  w->writeS(amiga.initSample);
  w->writeC(
    (amiga.useWave?4:0)|
    (amiga.useSample?2:0)|
    (amiga.useNoteMap?1:0)
  );
  w->writeC(amiga.waveLen);

  if (amiga.useNoteMap) {
    for (int note=0; note<120; note++) {
      w->writeS(amiga.get_amiga_sample_map(note, true)->freq);
      w->writeS(amiga.get_amiga_sample_map(note, true)->map);
    }
  }

  FEATURE_END;
}

void DivInstrument::writeFeatureOx(SafeWriter* w, int ope) {
  char opCode[3];
  opCode[0]='O';
  opCode[1]='1'+ope;
  opCode[2]=0;

  FEATURE_BEGIN(opCode);

  // if you update the macro header, please update this value as well.
  // it's the length.
  w->writeS(8);
  
  // write macros
  DivInstrumentSTD::OpMacro& o=*std.get_op_macro(ope);

  for(int i = 0; i < 32; i++)
  {
    writeMacro(w,*o.op_get_macro(DIV_MACRO_OP_AM + i, false));
  }

  // "stop reading" code
  w->writeC(-1);

  FEATURE_END;
}

void DivInstrument::writeFeatureLD(SafeWriter* w) {
  FEATURE_BEGIN("LD");

  w->writeC(fm.fixedDrums);
  w->writeS(fm.kickFreq);
  w->writeS(fm.snareHatFreq);
  w->writeS(fm.tomTopFreq);

  FEATURE_END;
}

void DivInstrument::writeFeatureSN(SafeWriter* w) {
  FEATURE_BEGIN("SN");

  w->writeC(((snes.d&7)<<4)|(snes.a&15));
  w->writeC(((snes.s&7)<<5)|(snes.r&31));

  w->writeC(
    (snes.useEnv?16:0)|
    (snes.sus?8:0)|
    (snes.gainMode)
  );
  
  w->writeC(snes.gain);

  w->writeC(((snes.sus&3)<<5)|(snes.d2&31));

  FEATURE_END;
}

void DivInstrument::writeFeatureN1(SafeWriter* w) {
  FEATURE_BEGIN("N1");

  w->writeI(n163.wave);
  w->writeC(n163.wavePos);
  w->writeC(n163.waveLen);
  w->writeC(n163.waveMode);

  w->writeC(n163.perChanPos);

  if (n163.perChanPos) {
    for (int i=0; i<8; i++) {
      w->writeC(n163.wavePosCh[i]);
    }
    for (int i=0; i<8; i++) {
      w->writeC(n163.waveLenCh[i]);
    }
  }

  FEATURE_END;
}

void DivInstrument::writeFeatureFD(SafeWriter* w) {
  FEATURE_BEGIN("FD");

  w->writeI(fds.modSpeed);
  w->writeI(fds.modDepth);
  w->writeC(fds.initModTableWithFirstWave);
  w->write(fds.modTable,32);

  FEATURE_END;
}

void DivInstrument::writeFeatureWS(SafeWriter* w) {
  FEATURE_BEGIN("WS");

  w->writeI(ws.wave1);
  w->writeI(ws.wave2);
  w->writeC(ws.rateDivider);
  w->writeC(ws.effect);
  w->writeC((ws.enabled ? 1 : 0) | ((ws.wave1global ? 1 : 0) << 1) | ((ws.wave2global ? 1 : 0) << 2));
  w->writeC(ws.global);
  w->writeC(ws.speed);
  w->writeC(ws.param1);
  w->writeC(ws.param2);
  w->writeC(ws.param3);
  w->writeC(ws.param4);

  FEATURE_END;
}

size_t DivInstrument::writeFeatureSL(SafeWriter* w, std::vector<int>& list, const DivSong* song) {
  bool sampleUsed[256];
  memset(sampleUsed,0,256*sizeof(bool));

  if (amiga.initSample>=0 && amiga.initSample<(int)song->sample.size()) {
    sampleUsed[amiga.initSample]=true;
  }

  if (amiga.useNoteMap) {
    for (int i=0; i<120; i++) {
      if (amiga.get_amiga_sample_map(i, true)->map>=0 && amiga.get_amiga_sample_map(i, true)->map<(int)song->sample.size()) {
        sampleUsed[amiga.get_amiga_sample_map(i, true)->map]=true;
      }
    }
  }

  for (size_t i=0; i<song->sample.size(); i++) {
    if (sampleUsed[i]) {
      list.push_back(i);
    }
  }

  if (list.empty()) return 0;

  FEATURE_BEGIN("SL");

  w->writeC(list.size());

  for (int i: list) {
    w->writeC(i);
  }

  size_t ret=w->tell();

  // pointers (these will be filled later)
  for (size_t i=0; i<list.size(); i++) {
    w->writeI(0);
  }

  FEATURE_END;

  return ret;
}

size_t DivInstrument::writeFeatureWL(SafeWriter* w, std::vector<int>& list, const DivSong* song) {
  bool waveUsed[256];
  memset(waveUsed,0,256*sizeof(bool));

  for (int i=0; i<std.get_macro(DIV_MACRO_WAVE, false)->len; i++) {
    if (std.get_macro(DIV_MACRO_WAVE, false)->val[i]>=0 && std.get_macro(DIV_MACRO_WAVE, false)->val[i]<(int)song->wave.size()) {
      waveUsed[std.get_macro(DIV_MACRO_WAVE, false)->val[i]]=true;
    }
  }

  if (ws.enabled) {
    if (ws.wave1>=0 && ws.wave1<(int)song->wave.size()) {
      waveUsed[ws.wave1]=true;
    }
    if ((ws.effect&0x80) && ws.wave2>=0 && ws.wave2<(int)song->wave.size()) {
      waveUsed[ws.wave2]=true;
    }
  }

  for (size_t i=0; i<song->wave.size(); i++) {
    if (waveUsed[i]) {
      list.push_back(i);
    }
  }

  if (list.empty()) return 0;

  FEATURE_BEGIN("WL");

  w->writeC(list.size());

  for (int i: list) {
    w->writeC(i);
  }

  size_t ret=w->tell();

  // pointers (these will be filled later)
  for (size_t i=0; i<list.size(); i++) {
    w->writeI(0);
  }

  FEATURE_END;

  return ret;
}

void DivInstrument::writeFeatureMP(SafeWriter* w) {
  FEATURE_BEGIN("MP");

  w->writeC(multipcm.ar);
  w->writeC(multipcm.d1r);
  w->writeC(multipcm.dl);
  w->writeC(multipcm.d2r);
  w->writeC(multipcm.rr);
  w->writeC(multipcm.rc);
  w->writeC(multipcm.lfo);
  w->writeC(multipcm.vib);
  w->writeC(multipcm.am);

  FEATURE_END;
}

void DivInstrument::writeFeatureSU(SafeWriter* w) {
  FEATURE_BEGIN("SU");

  w->writeC(su.switchRoles);

  w->writeC(su.hwSeqLen);
  for (int i=0; i<su.hwSeqLen; i++) {
    w->writeC(su.get_su_hw_seq(i, true)->cmd);
    w->writeC(su.get_su_hw_seq(i, true)->bound);
    w->writeC(su.get_su_hw_seq(i, true)->val);
    w->writeS(su.get_su_hw_seq(i, true)->speed);
  }

  FEATURE_END;
}

void DivInstrument::writeFeatureES(SafeWriter* w) {
  FEATURE_BEGIN("ES");

  w->writeC(es5506.filter.mode);
  w->writeS(es5506.filter.k1);
  w->writeS(es5506.filter.k2);
  w->writeS(es5506.envelope.ecount);
  w->writeC(es5506.envelope.lVRamp);
  w->writeC(es5506.envelope.rVRamp);
  w->writeC(es5506.envelope.k1Ramp);
  w->writeC(es5506.envelope.k2Ramp);
  w->writeC(es5506.envelope.k1Slow);
  w->writeC(es5506.envelope.k2Slow);

  FEATURE_END;
}

void DivInstrument::writeFeatureX1(SafeWriter* w) {
  FEATURE_BEGIN("X1");

  w->writeI(x1_010.bankSlot);

  FEATURE_END;
}

void DivInstrument::writeFeatureNE(SafeWriter* w) {
  FEATURE_BEGIN("NE");

  w->writeC(amiga.useNoteMap?1:0);

  if (amiga.useNoteMap) {
    for (int note=0; note<120; note++) {
      w->writeC(amiga.get_amiga_sample_map(note, true)->dpcmFreq);
      w->writeC(amiga.get_amiga_sample_map(note, true)->dpcmDelta);
    }
  }

  FEATURE_END;
}

void DivInstrument::writeFeatureEF(SafeWriter* w) {
  FEATURE_BEGIN("EF");

  w->writeC(esfm.noise&3);
  for (int i=0; i<4; i++) {
    DivInstrumentESFM::Operator& op=esfm.op[i];

    w->writeC(((op.delay&7)<<5)|((op.outLvl&7)<<2)|((op.right&1)<<1)|(op.left&1));
    w->writeC((op.fixed&1)<<3|(op.modIn&7));
    w->writeC(op.ct);
    w->writeC(op.dt);
  }
  
  FEATURE_END;
}

void DivInstrument::writeFeatureE3(SafeWriter* w) {
  FEATURE_BEGIN("E3");
  
  w->writeC((es5503.initial_osc_mode << 6)|((uint8_t)es5503.softpan_virtual_channel << 5)|((uint8_t)es5503.phase_reset_on_start << 4));

  FEATURE_END;
}

void DivInstrument::writeFeaturePN(SafeWriter* w) {
  FEATURE_BEGIN("PN");

  w->writeC(powernoise.octave);

  FEATURE_END;
}

void DivInstrument::writeFeatureS2(SafeWriter* w) {
  FEATURE_BEGIN("S2");

  w->writeC(
    (c64.dutyIsAbs?0x80:0)|
    (c64.initFilter?0x40:0)|
    (c64.toFilter?0x10:0)|
    (c64.noiseOn?8:0)|
    (c64.pulseOn?4:0)|
    (c64.sawOn?2:0)|
    (c64.triOn?1:0)
  );

  w->writeC(
    (c64.oscSync?0x80:0)|
    (c64.ringMod?0x40:0)|
    (c64.noTest?0x20:0)|
    (c64.filterIsAbs?0x10:0)|
    (c64.ch3off?8:0)|
    (c64.bp?4:0)|
    (c64.hp?2:0)|
    (c64.lp?1:0)
  );

  w->writeC(((c64.a&15)<<4)|(c64.d&15));
  w->writeC(((c64.s&15)<<4)|(c64.r&15));
  w->writeS(c64.duty);
  w->writeS(c64.cut&4095);
  w->writeC(c64.res);

  w->writeC(sid2.volume | (sid2.mix_mode << 4) | (sid2.noise_mode << 6));

  FEATURE_END;
}

void DivInstrument::writeFeatureLW(SafeWriter* w) 
{
  FEATURE_BEGIN("LW");

  w->writeI((int)std.local_waves.size());
  for (int i=0; i<(int)std.local_waves.size(); i++) 
  {
    DivWavetable* wave=std.local_waves[i];
    wave->putWaveData(w);
  }

  FEATURE_END;
}

void DivInstrument::writeFeaturePO(SafeWriter* w)
{
  FEATURE_BEGIN("PO");

  w->writeC(pokey.raw_freq_macro_mode);

  FEATURE_END;
}

void DivInstrument::putInsData2(SafeWriter* w, bool fui, const DivSong* song, bool insName, bool tilde_version) {
  size_t blockStartSeek=0;
  size_t blockEndSeek=0;
  size_t slSeek=0;
  size_t wlSeek=0;
  std::vector<int> waveList;
  std::vector<int> sampleList;

  std::vector<unsigned int> wavePtr;
  std::vector<unsigned int> samplePtr;

  if (fui) {
    //w->write("FINS",4);
    w->write(tilde_version ? "FINS" : "FINB",4); //Furnace-B version
  } else {
    //w->write("INS2",4);
    w->write(tilde_version ? "INS2" : "IN2B",4); //Furnace-B version
    blockStartSeek=w->tell();
    w->writeI(0);
  }

  w->writeS(DIV_ENGINE_VERSION);

  unsigned short init_type = type;

  if(tilde_version)
  {
    switch(init_type)
    {
      case DIV_INS_ES5503:
      case DIV_INS_POWERNOISE:
      case DIV_INS_POWERNOISE_SLOPE:
      case DIV_INS_DAVE:
      case DIV_INS_SID2:
        init_type = init_type - (unsigned short)1; //tildearrow's verson modules are incompatible with these inst indices so we comply...
      default: break;
    }
  }

  w->writeC(init_type);
  w->writeC(0);

  // write features
  bool featureNA=false;
  bool featureFM=false;
  bool featureMA=false;
  bool feature64=false;
  bool featureGB=false;
  bool featureSM=false;
  bool featureOx[4];
  bool featureLD=false;
  bool featureSN=false;
  bool featureN1=false;
  bool featureFD=false;
  bool featureWS=false;
  bool featureSL=false;
  bool featureWL=false;
  bool featureMP=false;
  bool featureSU=false;
  bool featureES=false;
  bool featureX1=false;
  bool featureNE=false;
  bool featureEF=false;
  bool featureE3=false;
  bool featurePN=false;
  bool featureS2=false;

  bool featureLW=(std.local_waves.size() > 0 ? true : false);

  bool featurePO=false;

  bool checkForWL=false;

  featureOx[0]=false;
  featureOx[1]=false;
  featureOx[2]=false;
  featureOx[3]=false;

  // turn on base features if .fui
  if (fui) {
    switch (type) {
      case DIV_INS_STD:
        break;
      case DIV_INS_FM:
        featureFM=true;
        break;
      case DIV_INS_GB:
        featureGB=true;
        checkForWL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_C64:
        feature64=true;
        break;
      case DIV_INS_AMIGA:
        featureSM=true;
        if (!amiga.useWave) featureSL=true;
        break;
      case DIV_INS_PCE:
        checkForWL=true;
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_AY:
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        break;
      case DIV_INS_AY8930:
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        break;
      case DIV_INS_TIA:
        break;
      case DIV_INS_SAA1099:
        break;
      case DIV_INS_VIC:
        break;
      case DIV_INS_PET:
        break;
      case DIV_INS_VRC6:
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        break;
      case DIV_INS_OPLL:
        featureFM=true;
        if (fm.fixedDrums) featureLD=true;
        break;
      case DIV_INS_OPL:
        featureFM=true;
        if (fm.fixedDrums) featureLD=true;
        break;
      case DIV_INS_FDS:
        checkForWL=true;
        featureFD=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_VBOY:
        checkForWL=true;
        featureFD=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_N163:
        checkForWL=true;
        featureN1=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_SCC:
        checkForWL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_OPZ:
        featureFM=true;
        break;
      case DIV_INS_BEEPER:
        break;
      case DIV_INS_SWAN:
        checkForWL=true;
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_MIKEY:
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        break;
      case DIV_INS_VERA:
        break;
      case DIV_INS_X1_010:
        checkForWL=true;
        featureX1=true;
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_VRC6_SAW:
        break;
      case DIV_INS_ES5506:
        featureSM=true;
        featureSL=true;
        featureES=true;
        break;
      case DIV_INS_MULTIPCM:
        featureSM=true;
        featureSL=true;
        featureMP=true;
        break;
      case DIV_INS_SNES:
        featureSM=true;
        if (!amiga.useWave) featureSL=true;
        featureSN=true;
        checkForWL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_SU:
        featureSM=true;
        if (amiga.useSample) featureSL=true;
        featureSU=true;
        break;
      case DIV_INS_NAMCO:
        checkForWL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_OPL_DRUMS:
        featureFM=true;
        if (fm.fixedDrums) featureLD=true;
        break;
      case DIV_INS_OPM:
        featureFM=true;
        break;
      case DIV_INS_NES:
        featureSM=true;
        featureNE=true;
        featureSL=true;
        break;
      case DIV_INS_MSM6258:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_MSM6295:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_ADPCMA:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_ADPCMB:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_SEGAPCM:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_QSOUND:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_YMZ280B:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_RF5C68:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_MSM5232:
        break;
      case DIV_INS_T6W28:
        break;
      case DIV_INS_K007232:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_GA20:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_POKEMINI:
        break;
      case DIV_INS_SM8521:
        checkForWL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_PV1000:
        break;
      case DIV_INS_K053260:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_TED:
        break;
      case DIV_INS_C140:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_C219:
        featureSM=true;
        featureSL=true;
        break;
      case DIV_INS_ESFM:
        featureFM=true;
        featureEF=true;
        break;
      case DIV_INS_ES5503:
        featureE3=true;
        checkForWL=true;
        if (ws.enabled) featureWS=true;
        break;
      case DIV_INS_POWERNOISE:
        featurePN=true;
        break;
      case DIV_INS_POWERNOISE_SLOPE:
        featurePN=true;
        break;
      case DIV_INS_DAVE:
        break;
      case DIV_INS_GBA_DMA:
        break;
      case DIV_INS_GBA_MINMOD:
        break;
      case DIV_INS_KURUMITSU:
        break;
      case DIV_INS_SID2:
        featureS2=true;
        break;
      case DIV_INS_POKEY:
        featurePO=true;
        break;
      case DIV_INS_MAX:
        break;
      case DIV_INS_NULL:
        break;
    }
  } else {
    // turn on features depending on what is set
    // almost 40 years of C++, and there still isn't an official way to easily compare two structs.
    // even Java, which many regard as having a slow runtime, has .equals().
    if (fm!=defaultIns.fm) {
      featureFM=true;
      featureLD=true;
    }
    if (c64!=defaultIns.c64) {
      feature64=true;
    }
    if (gb!=defaultIns.gb) {
      featureGB=true;
    }
    if (amiga!=defaultIns.amiga) {
      featureSM=true;
      featureNE=true;
    }
    if (snes!=defaultIns.snes) {
      featureSN=true;
    }
    if (n163!=defaultIns.n163) {
      featureN1=true;
    }
    if (fds!=defaultIns.fds) {
      featureFD=true;
    }
    if (ws!=defaultIns.ws) {
      featureWS=true;
    }
    if (multipcm!=defaultIns.multipcm) {
      featureMP=true;
    }
    if (su!=defaultIns.su) {
      featureSU=true;
    }
    if (es5506!=defaultIns.es5506) {
      featureES=true;
    }
    if (x1_010!=defaultIns.x1_010) {
      featureX1=true;
    }
    if (esfm!=defaultIns.esfm) {
      featureEF=true;
    }
    if (es5503!=defaultIns.es5503) {
      featureE3=true;
    }
    if (powernoise!=defaultIns.powernoise) {
      featurePN=true;
    }
    if (type == DIV_INS_SID2 && (sid2!=defaultIns.sid2 || c64!=defaultIns.c64)) {
      featureS2=true;
    }
    if (pokey!=defaultIns.pokey) {
      featurePO=true;
    }
  }

  // check ins name
  if (!name.empty() && insName) {
    featureNA=true;
  }

  // check macros
  if (std.get_macro(DIV_MACRO_VOL, false)->len ||
      std.get_macro(DIV_MACRO_ARP, false)->len ||
      std.get_macro(DIV_MACRO_DUTY, false)->len ||
      std.get_macro(DIV_MACRO_WAVE, false)->len ||
      std.get_macro(DIV_MACRO_PITCH, false)->len ||
      std.get_macro(DIV_MACRO_EX1, false)->len ||
      std.get_macro(DIV_MACRO_EX2, false)->len ||
      std.get_macro(DIV_MACRO_EX3, false)->len ||
      std.get_macro(DIV_MACRO_ALG, false)->len ||
      std.get_macro(DIV_MACRO_FB, false)->len ||
      std.get_macro(DIV_MACRO_FMS, false)->len ||
      std.get_macro(DIV_MACRO_AMS, false)->len ||
      std.get_macro(DIV_MACRO_PAN_LEFT, false)->len ||
      std.get_macro(DIV_MACRO_PAN_RIGHT, false)->len ||
      std.get_macro(DIV_MACRO_PHASE_RESET, false)->len ||
      std.get_macro(DIV_MACRO_EX4, false)->len ||
      std.get_macro(DIV_MACRO_EX5, false)->len ||
      std.get_macro(DIV_MACRO_EX6, false)->len ||
      std.get_macro(DIV_MACRO_EX7, false)->len ||
      std.get_macro(DIV_MACRO_EX8, false)->len ||
      std.get_macro(DIV_MACRO_EX9, false)->len ||
      std.get_macro(DIV_MACRO_EX10, false)->len ||
      std.get_macro(DIV_MACRO_EX11, false)->len ||
      std.get_macro(DIV_MACRO_EX12, false)->len ||
      std.get_macro(DIV_MACRO_EX13, false)->len ||
      std.get_macro(DIV_MACRO_EX14, false)->len ||
      std.get_macro(DIV_MACRO_EX15, false)->len ||
      std.get_macro(DIV_MACRO_EX16, false)->len ||
      std.get_macro(DIV_MACRO_EX17, false)->len ||
      std.get_macro(DIV_MACRO_EX18, false)->len ||
      std.get_macro(DIV_MACRO_EX19, false)->len ||
      std.get_macro(DIV_MACRO_EX20, false)->len) {
    featureMA=true;
  }

  // check whether to write wavetable list
  if (checkForWL && fui) {
    if (std.get_macro(DIV_MACRO_WAVE, false)->len || ws.enabled) {
      featureWL=true;
    }
  }

  if (featureFM || !fui) {
    // check FM macros
    int opCount=4;
    bool storeExtendedAsWell=true;
    if (fui) {
      if (type==DIV_INS_OPLL) {
        opCount=2;
      } else if (type==DIV_INS_OPL) {
        opCount=(fm.ops==4)?4:2;
      } else if (type==DIV_INS_FM || type==DIV_INS_OPM) {
        storeExtendedAsWell=false;
      }
    }
    for (int i=0; i<opCount; i++)
    {
      DivInstrumentSTD::OpMacro& m=*std.get_op_macro(i);

      if (m.op_get_macro(DIV_MACRO_OP_AM, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_AR, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_DR, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_MULT, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_RR, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_SL, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_TL, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_DT2, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_RS, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_DT, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_D2R, false)->len ||
          m.op_get_macro(DIV_MACRO_OP_SSG, false)->len)
      {
        featureOx[i]=true;
      }

      if (storeExtendedAsWell)
      {
        if (m.op_get_macro(DIV_MACRO_OP_DAM, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_DVB, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EGT, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_KSL, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_SUS, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_VIB, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_WS, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_KSR, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX1, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX2, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX3, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX4, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX5, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX6, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX7, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX8, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX9, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX10, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX11, false)->len ||
            m.op_get_macro(DIV_MACRO_OP_EX12, false)->len)
        {
          featureOx[i]=true;
        }
      }
    }
  }

  // write features
  if (featureNA) {
    writeFeatureNA(w);
  }
  if (featureFM) {
    writeFeatureFM(w,fui);
  }
  if (featureMA) {
    writeFeatureMA(w);
  }
  if (feature64) {
    writeFeature64(w);
  }
  if (featureGB) {
    writeFeatureGB(w);
  }
  if (featureSM) {
    writeFeatureSM(w);
  }
  for (int i=0; i<4; i++) {
    if (featureOx[i]) {
      writeFeatureOx(w,i);
    }
  }
  if (featureLD) {
    writeFeatureLD(w);
  }
  if (featureSN) {
    writeFeatureSN(w);
  }
  if (featureN1) {
    writeFeatureN1(w);
  }
  if (featureFD) {
    writeFeatureFD(w);
  }
  if (featureWS) {
    writeFeatureWS(w);
  }
  if (featureSL) {
    slSeek=writeFeatureSL(w,sampleList,song);
  }
  if (featureWL) {
    wlSeek=writeFeatureWL(w,waveList,song);
  }
  if (featureMP) {
    writeFeatureMP(w);
  }
  if (featureSU) {
    writeFeatureSU(w);
  }
  if (featureES) {
    writeFeatureES(w);
  }
  if (featureX1) {
    writeFeatureX1(w);
  }
  if (featureNE) {
    writeFeatureNE(w);
  }
  if (featureEF) {
    writeFeatureEF(w);
  }
  if (featureE3) {
    writeFeatureE3(w);
  }
  if (featurePN) {
    writeFeaturePN(w);
  }
  if (featureS2) {
    writeFeatureS2(w);
  }
  if (featureLW) {
    writeFeatureLW(w);
  }
  if (featurePO) {
    writeFeaturePO(w);
  }

  if (fui && (featureSL || featureWL)) {
    w->write("EN",2);

    if (wlSeek!=0 && !waveList.empty()) {
      for (int i: waveList) {
        if (i<0 || i>=(int)song->wave.size()) {
          wavePtr.push_back(0);
          continue;
        }
        DivWavetable* wave=song->wave[i];

        wavePtr.push_back(w->tell());
        wave->putWaveData(w);
      }

      w->seek(wlSeek,SEEK_SET);
      for (unsigned int i: wavePtr) {
        w->writeI(i);
      }
      w->seek(0,SEEK_END);
    }

    if (slSeek!=0 && !sampleList.empty()) {
      for (int i: sampleList) {
        if (i<0 || i>=(int)song->sample.size()) {
          samplePtr.push_back(0);
          continue;
        }
        DivSample* sample=song->sample[i];

        samplePtr.push_back(w->tell());
        sample->putSampleData(w);
      }

      w->seek(slSeek,SEEK_SET);
      for (unsigned int i: samplePtr) {
        w->writeI(i);
      }
      w->seek(0,SEEK_END);
    }
  }

  if (!fui) {
    w->write("EN",2);
  }

  blockEndSeek=w->tell();
  if (!fui) {
    w->seek(blockStartSeek,SEEK_SET);
    w->writeI(blockEndSeek-blockStartSeek-4);
  }
  w->seek(0,SEEK_END);
}

#define READ_FEAT_BEGIN \
  unsigned short featLen=reader.readS(); \
  size_t endOfFeat=reader.tell()+featLen;

#define READ_FEAT_END \
  if (reader.tell()<endOfFeat) reader.seek(endOfFeat,SEEK_SET);

void DivInstrument::readFeatureNA(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  name=reader.readString();

  if(version == 192) //fix bug when older Furnace-B versions added "##sggu" to default instrument name
  {
    // Find position of substring in string
    String fucccckkk = "##sggu";
    size_t pos = name.find(fucccckkk);
    if (pos != std::string::npos)
    {
        // Remove found substring from string
        name.erase(pos, fucccckkk.length());
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureFM(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  unsigned char opCount=reader.readC();

  fm.op[0].enable=(opCount&16);
  fm.op[1].enable=(opCount&32);
  fm.op[2].enable=(opCount&64);
  fm.op[3].enable=(opCount&128);

  opCount&=15;

  unsigned char next=reader.readC();
  fm.alg=(next>>4)&7;
  fm.fb=next&7;

  next=reader.readC();
  fm.fms2=(next>>5)&7;
  fm.ams=(next>>3)&3;
  fm.fms=next&7;

  next=reader.readC();
  fm.ams2=(next>>6)&3;
  fm.ops=(next&32)?4:2;
  fm.opllPreset=next&31;

  // read operators
  for (int i=0; i<opCount; i++) {
    DivInstrumentFM::Operator& op=fm.op[i];

    next=reader.readC();
    op.ksr=(next&128)?1:0;
    op.dt=(next>>4)&7;
    op.mult=next&15;

    next=reader.readC();
    op.sus=(next&128)?1:0;
    op.tl=next&127;

    next=reader.readC();
    op.rs=(next>>6)&3;
    op.vib=(next&32)?1:0;
    op.ar=next&31;

    next=reader.readC();
    op.am=(next&128)?1:0;
    op.ksl=(next>>5)&3;
    op.dr=next&31;

    next=reader.readC();
    op.egt=(next&128)?1:0;
    op.kvs=(next>>5)&3;
    op.d2r=next&31;

    next=reader.readC();
    op.sl=(next>>4)&15;
    op.rr=next&15;

    next=reader.readC();
    op.dvb=(next>>4)&15;
    op.ssgEnv=next&15;

    next=reader.readC();
    op.dam=(next>>5)&7;
    op.dt2=(next>>3)&3;
    op.ws=next&7;
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureMA(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  unsigned short macroHeaderLen=reader.readS();

  DivInstrumentMacro* target=std.get_macro(DIV_MACRO_VOL, true);

  while (reader.tell()<endOfFeat) {
    size_t endOfMacroHeader=reader.tell()+macroHeaderLen;
    unsigned char macroCode=reader.readC();

    // end of macro list
    if (macroCode==255) break;

    if (macroCode > 31)
    {
      logW("invalid macro code %d!", macroCode); break; //only 32 macros per instrument!!!
    }

    target = std.get_macro(DIV_MACRO_VOL + macroCode, true);

    target->len=reader.readC();
    target->loop=reader.readC();
    target->rel=reader.readC();
    target->mode=reader.readC();

    unsigned char wordSize=reader.readC();
    target->open=wordSize&15;
    wordSize>>=6;

    target->delay=reader.readC();
    target->speed=reader.readC();

    reader.seek(endOfMacroHeader,SEEK_SET);

    // read macro
    switch (wordSize) {
      case 0:
        for (int i=0; i<target->len; i++) {
          target->val[i]=(unsigned char)reader.readC();
        }
        break;
      case 1:
        for (int i=0; i<target->len; i++) {
          target->val[i]=(signed char)reader.readC();
        }
        break;
      case 2:
        for (int i=0; i<target->len; i++) {
          target->val[i]=reader.readS();
        }
        break;
      default:
        for (int i=0; i<target->len; i++) {
          target->val[i]=reader.readI();
        }
        break;
    }
  }

  if (version<193) {
    if (type==DIV_INS_AY || type==DIV_INS_AY8930) {
      for (int j=0; j<std.get_macro(DIV_MACRO_WAVE, true)->len; j++) {
        std.get_macro(DIV_MACRO_WAVE, true)->val[j]++;
      }
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeature64(SafeReader& reader, bool& volIsCutoff, short version) {
  READ_FEAT_BEGIN;

  unsigned char next=reader.readC();
  c64.dutyIsAbs=next&128;
  c64.initFilter=next&64;
  volIsCutoff=next&32;
  c64.toFilter=next&16;
  c64.noiseOn=next&8;
  c64.pulseOn=next&4;
  c64.sawOn=next&2;
  c64.triOn=next&1;

  next=reader.readC();
  c64.oscSync=(next&128)?1:0;
  c64.ringMod=(next&64)?1:0;
  c64.noTest=next&32;
  c64.filterIsAbs=next&16;
  c64.ch3off=next&8;
  c64.bp=next&4;
  c64.hp=next&2;
  c64.lp=next&1;

  next=reader.readC();
  c64.a=(next>>4)&15;
  c64.d=next&15;

  next=reader.readC();
  c64.s=(next>>4)&15;
  c64.r=next&15;

  c64.duty=reader.readS()&4095;

  unsigned short cr=reader.readS();
  c64.cut=cr&2047;
  c64.res=cr>>12;

  READ_FEAT_END;
}

void DivInstrument::readFeatureGB(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  unsigned char next=reader.readC();
  gb.envLen=(next>>5)&7;
  gb.envDir=(next&16)?1:0;
  gb.envVol=next&15;

  gb.soundLen=reader.readC();

  next=reader.readC();
  gb.alwaysInit=next&2;
  gb.softEnv=next&1;

  gb.hwSeqLen=reader.readC();
  for (int i=0; i<gb.hwSeqLen; i++) {
    gb.get_gb_hw_seq(i, true)->cmd=reader.readC();
    gb.get_gb_hw_seq(i, true)->data=reader.readS();
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureSM(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  amiga.initSample=reader.readS();

  unsigned char next=reader.readC();
  amiga.useWave=next&4;
  amiga.useSample=next&2;
  amiga.useNoteMap=next&1;

  amiga.waveLen=(unsigned char)reader.readC();

  if (amiga.useNoteMap) {
    for (int note=0; note<120; note++) {
      amiga.get_amiga_sample_map(note, true)->freq=reader.readS();
      amiga.get_amiga_sample_map(note, true)->map=reader.readS();
    }

    if (version<152) {
      for (int note=0; note<120; note++) {
        amiga.get_amiga_sample_map(note, true)->freq=note;
      }
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureOx(SafeReader& reader, int op, short version) {
  READ_FEAT_BEGIN;

  unsigned short macroHeaderLen=reader.readS();

  DivInstrumentMacro* target=std.get_op_macro(op)->op_get_macro(DIV_MACRO_OP_AM, true);

  while (reader.tell()<endOfFeat) {
    size_t endOfMacroHeader=reader.tell()+macroHeaderLen;
    unsigned char macroCode=reader.readC();

    // end of macro list
    if (macroCode==255) break;

    if (macroCode > DIV_MACRO_OP_AM + 31)
    {
      logW("invalid op %d macro code %d!", op, macroCode); break; //only 32 macros per FM op!!!
    }

    target=std.ops[op].op_get_macro(DIV_MACRO_OP_AM + macroCode, true);

    target->len=reader.readC();
    target->loop=reader.readC();
    target->rel=reader.readC();
    target->mode=reader.readC();

    unsigned char wordSize=reader.readC();
    target->open=wordSize&7;
    wordSize>>=6;

    target->delay=reader.readC();
    target->speed=reader.readC();

    reader.seek(endOfMacroHeader,SEEK_SET);

    // read macro
    switch (wordSize) {
      case 0:
        for (int i=0; i<target->len; i++) {
          target->val[i]=(unsigned char)reader.readC();
        }
        break;
      case 1:
        for (int i=0; i<target->len; i++) {
          target->val[i]=(signed char)reader.readC();
        }
        break;
      case 2:
        for (int i=0; i<target->len; i++) {
          target->val[i]=reader.readS();
        }
        break;
      default:
        for (int i=0; i<target->len; i++) {
          target->val[i]=reader.readI();
        }
        break;
    }

    // <167 TL macro compat
    if (macroCode==6 && version<167) {
      if (target->open&6) {
        for (int j=0; j<2; j++) {
          target->val[j]^=0x7f;
        }
      } else {
        for (int j=0; j<target->len; j++) {
          target->val[j]^=0x7f;
        }
      }
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureLD(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  fm.fixedDrums=reader.readC();
  fm.kickFreq=reader.readS();
  fm.snareHatFreq=reader.readS();
  fm.tomTopFreq=reader.readS();

  READ_FEAT_END;
}

void DivInstrument::readFeatureSN(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  unsigned char next=reader.readC();
  snes.d=(next>>4)&7;
  snes.a=next&15;

  next=reader.readC();
  snes.s=(next>>5)&7;
  snes.r=next&31;

  next=reader.readC();
  snes.useEnv=next&16;
  snes.sus=(next&8)?1:0;
  snes.gainMode=(DivInstrumentSNES::GainMode)(next&7);

  if (snes.gainMode==1 || snes.gainMode==2 || snes.gainMode==3) snes.gainMode=DivInstrumentSNES::GAIN_MODE_DIRECT;

  snes.gain=reader.readC();
  
  if (version>=131) {
    next=reader.readC();
    snes.sus=(next>>5)&3;
    snes.d2=next&31;
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureN1(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  n163.wave=reader.readI();
  n163.wavePos=(unsigned char)reader.readC();
  n163.waveLen=(unsigned char)reader.readC();
  n163.waveMode=(unsigned char)reader.readC();

  if (version>=164) {
    n163.perChanPos=reader.readC();
    if (n163.perChanPos) {
      for (int i=0; i<8; i++) {
        n163.wavePosCh[i]=(unsigned char)reader.readC();
      }
      for (int i=0; i<8; i++) {
        n163.waveLenCh[i]=(unsigned char)reader.readC();
      }
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureFD(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  fds.modSpeed=reader.readI();
  fds.modDepth=reader.readI();
  fds.initModTableWithFirstWave=reader.readC();
  reader.read(fds.modTable,32);

  READ_FEAT_END;
}

void DivInstrument::readFeatureWS(SafeReader& reader, short version, bool tildearrow_version) {
  READ_FEAT_BEGIN;

  ws.wave1=reader.readI();
  ws.wave2=reader.readI();
  ws.rateDivider=reader.readC();
  ws.effect=reader.readC();
  unsigned char temp = reader.readC();
  ws.enabled = temp & 1;
  ws.wave1global = temp & 2;
  ws.wave2global = temp & 4;
  if(tildearrow_version || version < 193)
  {
    ws.wave1global = true;
    ws.wave2global = true;
  }
  ws.global=reader.readC();
  ws.speed=reader.readC();
  ws.param1=reader.readC();
  ws.param2=reader.readC();
  ws.param3=reader.readC();
  ws.param4=reader.readC();

  READ_FEAT_END;
}

void DivInstrument::readFeatureSL(SafeReader& reader, DivSong* song, short version) {
  READ_FEAT_BEGIN;

  unsigned int samplePtr[256];
  unsigned char sampleIndex[256];
  unsigned char sampleRemap[256];
  memset(samplePtr,0,256*sizeof(unsigned int));
  memset(sampleIndex,0,256);
  memset(sampleRemap,0,256);

  unsigned char sampleCount=reader.readC();

  for (int i=0; i<sampleCount; i++) {
    sampleIndex[i]=reader.readC();
  }
  for (int i=0; i<sampleCount; i++) {
    samplePtr[i]=reader.readI();
  }

  size_t lastSeek=reader.tell();

  // load samples
  for (int i=0; i<sampleCount; i++) {
    reader.seek(samplePtr[i],SEEK_SET);
    if (song->sample.size()>=256) {
      break;
    }
    DivSample* sample=new DivSample;
    int sampleCount=(int)song->sample.size();

    DivDataErrors result=sample->readSampleData(reader,version);
    if (result==DIV_DATA_SUCCESS) {
      song->sample.push_back(sample);
      song->sampleLen=sampleCount+1;
      sampleRemap[sampleIndex[i]]=sampleCount;
    } else {
      delete sample;
      sampleRemap[sampleIndex[i]]=0;
    }
  }

  reader.seek(lastSeek,SEEK_SET);

  // re-map samples
  if (amiga.initSample>=0 && amiga.initSample<256) {
    amiga.initSample=sampleRemap[amiga.initSample];
  }

  if (amiga.useNoteMap) {
    for (int i=0; i<120; i++) {
      if (amiga.get_amiga_sample_map(i, true)->map>=0 && amiga.get_amiga_sample_map(i, true)->map<256) {
        amiga.get_amiga_sample_map(i, true)->map=sampleRemap[amiga.get_amiga_sample_map(i, true)->map];
      }
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureWL(SafeReader& reader, DivSong* song, short version) {
  READ_FEAT_BEGIN;

  unsigned int wavePtr[256];
  unsigned char waveIndex[256];
  unsigned char waveRemap[256];
  memset(wavePtr,0,256*sizeof(unsigned int));
  memset(waveIndex,0,256);
  memset(waveRemap,0,256);

  unsigned char waveCount=reader.readC();

  for (int i=0; i<waveCount; i++) {
    waveIndex[i]=reader.readC();
  }
  for (int i=0; i<waveCount; i++) {
    wavePtr[i]=reader.readI();
  }

  size_t lastSeek=reader.tell();

  // load wavetables
  for (int i=0; i<waveCount; i++) {
    reader.seek(wavePtr[i],SEEK_SET);
    if (song->wave.size()>=256) {
      break;
    }
    DivWavetable* wave=new DivWavetable;
    int waveCount=(int)song->wave.size();

    DivDataErrors result=wave->readWaveData(reader,version);
    if (result==DIV_DATA_SUCCESS) {
      song->wave.push_back(wave);
      song->waveLen=waveCount+1;
      waveRemap[waveIndex[i]]=waveCount;
    } else {
      delete wave;
      waveRemap[waveIndex[i]]=0;
    }
  }

  reader.seek(lastSeek,SEEK_SET);

  // re-map wavetables
  if (ws.enabled) {
    if (ws.wave1>=0 && ws.wave1<256) ws.wave1=waveRemap[ws.wave1];
    if (ws.effect&0x80) {
      if (ws.wave2>=0 && ws.wave2<256) ws.wave2=waveRemap[ws.wave2];
    }
  }
  if (n163.wave>=0 && n163.wave<256) n163.wave=waveRemap[n163.wave];
  for (int i=0; i<std.get_macro(DIV_MACRO_WAVE, false)->len; i++) {
    if (std.get_macro(DIV_MACRO_WAVE, false)->val[i]>=0 && std.get_macro(DIV_MACRO_WAVE, false)->val[i]<256) std.get_macro(DIV_MACRO_WAVE, false)->val[i]=waveRemap[std.get_macro(DIV_MACRO_WAVE, false)->val[i]];
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureMP(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  multipcm.ar=reader.readC();
  multipcm.d1r=reader.readC();
  multipcm.dl=reader.readC();
  multipcm.d2r=reader.readC();
  multipcm.rr=reader.readC();
  multipcm.rc=reader.readC();
  multipcm.lfo=reader.readC();
  multipcm.vib=reader.readC();
  multipcm.am=reader.readC();

  READ_FEAT_END;
}

void DivInstrument::readFeatureSU(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  su.switchRoles=reader.readC();

  if (version>=185) {
    su.hwSeqLen=reader.readC();
    for (int i=0; i<su.hwSeqLen; i++) {
      su.get_su_hw_seq(i, true)->cmd=reader.readC();
      su.get_su_hw_seq(i, true)->bound=reader.readC();
      su.get_su_hw_seq(i, true)->val=reader.readC();
      su.get_su_hw_seq(i, true)->speed=reader.readS();
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureES(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  es5506.filter.mode=(DivInstrumentES5506::Filter::FilterMode)reader.readC();
  es5506.filter.k1=reader.readS();
  es5506.filter.k2=reader.readS();
  es5506.envelope.ecount=reader.readS();
  es5506.envelope.lVRamp=reader.readC();
  es5506.envelope.rVRamp=reader.readC();
  es5506.envelope.k1Ramp=reader.readC();
  es5506.envelope.k2Ramp=reader.readC();
  es5506.envelope.k1Slow=reader.readC();
  es5506.envelope.k2Slow=reader.readC();

  READ_FEAT_END;
}

void DivInstrument::readFeatureX1(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  x1_010.bankSlot=reader.readI();

  READ_FEAT_END;
}

void DivInstrument::readFeatureNE(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  amiga.useNoteMap=reader.readC();

  if (amiga.useNoteMap) 
  {
    amiga.get_amiga_sample_map(0, true)->dpcmFreq = 0;

    for (int note=0; note<120; note++) 
    {
      amiga.get_amiga_sample_map(note, true)->dpcmFreq=reader.readC();
      amiga.get_amiga_sample_map(note, true)->dpcmDelta=reader.readC();

      if(version < 193)
      {
        amiga.get_amiga_sample_map(note, true)->freq = 0;
      }
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureEF(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  unsigned char next=reader.readC();
  esfm.noise=next&3;

  for (int i=0; i<4; i++) {
    DivInstrumentESFM::Operator& op=esfm.op[i];

    next=reader.readC();
    op.delay=(next>>5)&7;
    op.outLvl=(next>>2)&7;
    op.right=(next>>1)&1;
    op.left=next&1;

    next=reader.readC();
    op.modIn=next&7;
    op.fixed=(next>>3)&1;

    op.ct=reader.readC();
    op.dt=reader.readC();
  }

  READ_FEAT_END;
}

void DivInstrument::readFeatureE3(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  uint8_t temp = reader.readC();

  es5503.initial_osc_mode = temp >> 6;
  es5503.softpan_virtual_channel = (temp >> 5) & 1;
  es5503.phase_reset_on_start = (temp >> 4) & 1;

  READ_FEAT_END;
}

void DivInstrument::readFeaturePN(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  powernoise.octave=reader.readC();

  READ_FEAT_END;
}

void DivInstrument::readFeatureS2(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  unsigned char next=reader.readC();
  c64.dutyIsAbs=next&128;
  c64.initFilter=next&64;
  //volIsCutoff=next&32;
  c64.toFilter=next&16;
  c64.noiseOn=next&8;
  c64.pulseOn=next&4;
  c64.sawOn=next&2;
  c64.triOn=next&1;

  next=reader.readC();
  c64.oscSync=(next&128)?1:0;
  c64.ringMod=(next&64)?1:0;
  c64.noTest=next&32;
  c64.filterIsAbs=next&16;
  c64.ch3off=next&8;
  c64.bp=next&4;
  c64.hp=next&2;
  c64.lp=next&1;

  next=reader.readC();
  c64.a=(next>>4)&15;
  c64.d=next&15;

  next=reader.readC();
  c64.s=(next>>4)&15;
  c64.r=next&15;

  c64.duty=reader.readS()&4095;

  c64.cut=reader.readS();
  c64.res=reader.readC();

//  w->writeS(c64.cut&4095);
//  w->writeC(c64.res);

  uint8_t temp = reader.readC();

  sid2.volume = temp & 0xf;
  sid2.mix_mode = (temp >> 4) & 3;
  sid2.noise_mode = temp >> 6;

  READ_FEAT_END;
}

void DivInstrument::readFeatureLW(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  int waves = reader.readI();

  for (int i=0; i<waves; i++) 
  {
    DivWavetable* wave=new DivWavetable;

    if (wave->readWaveData(reader,version)==DIV_DATA_SUCCESS) 
    {
      std.local_waves.push_back(wave);
    }
  }

  READ_FEAT_END;
}

void DivInstrument::readFeaturePO(SafeReader& reader, short version) {
  READ_FEAT_BEGIN;

  pokey.raw_freq_macro_mode = reader.readC();

  READ_FEAT_END;
}

DivDataErrors DivInstrument::readInsDataNew(SafeReader& reader, short version, bool fui, DivSong* song, bool tildearrow_version) {
  unsigned char featCode[2];
  bool volIsCutoff=false;

  int dataLen=reader.size()-4;
  if (!fui) {
    dataLen=reader.readI();
  }
  dataLen+=reader.tell();

  logV("data length: %d",dataLen);

  reader.readS(); // format version. ignored.

  type=(DivInstrumentType)reader.readS();

  if(type >= DIV_INS_MAX) //invalid instrument type!
  {
    return DIV_DATA_INVALID_DATA;
  }

  if(tildearrow_version)
  {
    //the PowerNoise instrument indices are incompatible between tildearrow Furnace and Furnace-B (because Furnace-B also has the ES5503 instrument which lacks in tildearrow version so ES5503 and powernoise indices overlap). Thus we need to convert!
    if(type == 56) //powernoise noise inst
    {
      type = DIV_INS_POWERNOISE;
      goto proceed;
    }

    if(type == 57) //powernoise slope inst
    {
      type = DIV_INS_POWERNOISE_SLOPE;
      goto proceed;
    }

    if(type == 58) //powernoise slope inst
    {
      type = DIV_INS_DAVE;
      goto proceed;
    }
  }
  
  proceed:;

  // feature reading loop
  while ((int)reader.tell()<dataLen) {
    // read feature code
    reader.read(featCode,2);
    logV("- %c%c",featCode[0],featCode[1]);

    if (memcmp(featCode,"EN",2)==0) { // end of instrument
      break;
    } else if (memcmp(featCode,"NA",2)==0) { // name
      readFeatureNA(reader,version);
    } else if (memcmp(featCode,"FM",2)==0) { // FM
      readFeatureFM(reader,version);
    } else if (memcmp(featCode,"MA",2)==0) { // macros
      readFeatureMA(reader,version);
    } else if (memcmp(featCode,"64",2)==0) { // C64
      readFeature64(reader,volIsCutoff,version);
    } else if (memcmp(featCode,"GB",2)==0) { // Game Boy
      readFeatureGB(reader,version);
    } else if (memcmp(featCode,"SM",2)==0) { // sample
      readFeatureSM(reader,version);
    } else if (memcmp(featCode,"O1",2)==0) { // op1 macros
      readFeatureOx(reader,0,version);
    } else if (memcmp(featCode,"O2",2)==0) { // op2 macros
      readFeatureOx(reader,1,version);
    } else if (memcmp(featCode,"O3",2)==0) { // op3 macros
      readFeatureOx(reader,2,version);
    } else if (memcmp(featCode,"O4",2)==0) { // op4 macros
      readFeatureOx(reader,3,version);
    } else if (memcmp(featCode,"LD",2)==0) { // OPL drums
      readFeatureLD(reader,version);
    } else if (memcmp(featCode,"SN",2)==0) { // SNES
      readFeatureSN(reader,version);
    } else if (memcmp(featCode,"N1",2)==0) { // Namco 163
      readFeatureN1(reader,version);
    } else if (memcmp(featCode,"FD",2)==0) { // FDS/VB
      readFeatureFD(reader,version);
    } else if (memcmp(featCode,"WS",2)==0) { // WaveSynth
      readFeatureWS(reader,version,tildearrow_version);
    } else if (memcmp(featCode,"SL",2)==0 && fui && song!=NULL) { // sample list
      readFeatureSL(reader,song,version);
    } else if (memcmp(featCode,"WL",2)==0 && fui && song!=NULL) { // wave list
      readFeatureWL(reader,song,version);
    } else if (memcmp(featCode,"MP",2)==0) { // MultiPCM
      readFeatureMP(reader,version);
    } else if (memcmp(featCode,"SU",2)==0) { // Sound Unit
      readFeatureSU(reader,version);
    } else if (memcmp(featCode,"ES",2)==0) { // ES5506
      readFeatureES(reader,version);
    } else if (memcmp(featCode,"X1",2)==0) { // X1-010
      readFeatureX1(reader,version);
    } else if (memcmp(featCode,"NE",2)==0) { // NES (DPCM)
      readFeatureNE(reader,version);
    } else if (memcmp(featCode,"EF",2)==0) { // ESFM
      readFeatureEF(reader,version);
    } else if (memcmp(featCode,"E3",2)==0) { // ES5503
      readFeatureE3(reader,version);
    } else if (memcmp(featCode,"PN",2)==0) { // PowerNoise
      readFeaturePN(reader,version);
    } else if (memcmp(featCode,"S2",2)==0) { // SID2
      readFeatureS2(reader,version);
    } else if (memcmp(featCode,"LW",2)==0) { // local wavetables
      readFeatureLW(reader,version);
    } else if (memcmp(featCode,"PO",2)==0) { // POKEY
      readFeaturePO(reader,version);
    } else {
      if (song==NULL && (memcmp(featCode,"SL",2)==0 || (memcmp(featCode,"WL",2)==0))) {
        // nothing
      } else {
        logW("unknown feature code %c%c!",featCode[0],featCode[1]);
      }
      // skip feature
      unsigned short skip=reader.readS();
      reader.seek(skip,SEEK_CUR);
    }
  }

  if((ws.wave1global == false || ws.wave2global == false) && std.local_waves.size() == 0) //just to be sure that we don't reference default wave
  {
    ws.wave1global = true;
    ws.wave2global = true;
  }

  // <187 C64 cutoff macro compatibility
  if (type==DIV_INS_C64 && volIsCutoff && version<187) 
  {
    DivInstrumentMacro* m = std.get_macro(DIV_MACRO_ALG, true);
    m = std.get_macro(DIV_MACRO_VOL, true);

    UNUSED(m);
    
    for (int i=0; i<256; i++) 
    {
      std.get_macro(DIV_MACRO_ALG, true)->val[i]=std.get_macro(DIV_MACRO_VOL, true)->val[i];
    }

    std.get_macro(DIV_MACRO_ALG, true)->len = std.get_macro(DIV_MACRO_VOL, true)->len;
    std.get_macro(DIV_MACRO_ALG, true)->delay = std.get_macro(DIV_MACRO_VOL, true)->delay;
    std.get_macro(DIV_MACRO_ALG, true)->lenMemory = std.get_macro(DIV_MACRO_VOL, true)->lenMemory;
    std.get_macro(DIV_MACRO_ALG, true)->mode = std.get_macro(DIV_MACRO_VOL, true)->mode;
    std.get_macro(DIV_MACRO_ALG, true)->rel = std.get_macro(DIV_MACRO_VOL, true)->rel;
    std.get_macro(DIV_MACRO_ALG, true)->speed = std.get_macro(DIV_MACRO_VOL, true)->speed;
    std.get_macro(DIV_MACRO_ALG, true)->loop = std.get_macro(DIV_MACRO_VOL, true)->loop;
    std.get_macro(DIV_MACRO_ALG, true)->open = std.get_macro(DIV_MACRO_VOL, true)->open;

    std.get_macro(DIV_MACRO_VOL, true)->len = 0;
    std.get_macro(DIV_MACRO_VOL, true)->open = 1;

    if (!c64.filterIsAbs) {
      for (int i=0; i<256; i++) {
        std.get_macro(DIV_MACRO_ALG, true)->val[i]=-std.get_macro(DIV_MACRO_ALG, true)->val[i];
      }
    }
  }

  // <187 special/test/gate merge
  if (type==DIV_INS_C64 && version<187) {
    convertC64SpecialMacro();
  }

  return DIV_DATA_SUCCESS;
}

#define READ_MACRO_VALS(x,y) \
  for (int macroValPos=0; macroValPos<y; macroValPos++) x[macroValPos]=reader.readI();

DivDataErrors DivInstrument::readInsDataOld(SafeReader &reader, short version, bool tildearrow_version) {
  bool volIsCutoff=false;
  reader.readI(); // length. ignored.

  reader.readS(); // format version. ignored.
  type=(DivInstrumentType)reader.readC();
  reader.readC();
  name=reader.readString();

  // FM
  fm.alg=reader.readC();
  fm.fb=reader.readC();
  fm.fms=reader.readC();
  fm.ams=reader.readC();
  fm.ops=reader.readC();
  if (version>=60) {
    fm.opllPreset=reader.readC();
  } else {
    reader.readC();
  }
  reader.readC();
  reader.readC();

  for (int j=0; j<4; j++) {
    DivInstrumentFM::Operator& op=fm.op[j];
    op.am=reader.readC();
    op.ar=reader.readC();
    op.dr=reader.readC();
    op.mult=reader.readC();
    op.rr=reader.readC();
    op.sl=reader.readC();
    op.tl=reader.readC();
    op.dt2=reader.readC();
    op.rs=reader.readC();
    op.dt=reader.readC();
    op.d2r=reader.readC();
    op.ssgEnv=reader.readC();

    op.dam=reader.readC();
    op.dvb=reader.readC();
    op.egt=reader.readC();
    op.ksl=reader.readC();
    op.sus=reader.readC();
    op.vib=reader.readC();
    op.ws=reader.readC();
    op.ksr=reader.readC();

    if (version>=114) {
      op.enable=reader.readC();
    } else {
      reader.readC();
    }

    if (version>=115) {
      op.kvs=reader.readC();
    } else {
      op.kvs=2;
      reader.readC();
    }

    // reserved
    for (int k=0; k<10; k++) reader.readC();
  }

  // GB
  gb.envVol=reader.readC();
  gb.envDir=reader.readC();
  gb.envLen=reader.readC();
  gb.soundLen=reader.readC();

  // C64
  c64.triOn=reader.readC();
  c64.sawOn=reader.readC();
  c64.pulseOn=reader.readC();
  c64.noiseOn=reader.readC();
  c64.a=reader.readC();
  c64.d=reader.readC();
  c64.s=reader.readC();
  c64.r=reader.readC();
  c64.duty=reader.readS();
  c64.ringMod=reader.readC();
  c64.oscSync=reader.readC();
  c64.toFilter=reader.readC();
  c64.initFilter=reader.readC();
  volIsCutoff=reader.readC();
  c64.res=reader.readC();
  c64.lp=reader.readC();
  c64.bp=reader.readC();
  c64.hp=reader.readC();
  c64.ch3off=reader.readC();
  c64.cut=reader.readS();
  c64.dutyIsAbs=reader.readC();
  c64.filterIsAbs=reader.readC();

  // Amiga
  amiga.initSample=reader.readS();
  if (version>=82) {
    amiga.useWave=reader.readC();
    amiga.waveLen=(unsigned char)reader.readC();
  } else {
    reader.readC();
    reader.readC();
  }
  // reserved
  for (int k=0; k<12; k++) reader.readC();

  // standard
  std.get_macro(DIV_MACRO_VOL, true)->len=reader.readI();
  std.get_macro(DIV_MACRO_ARP, true)->len=reader.readI();
  std.get_macro(DIV_MACRO_DUTY, true)->len=reader.readI();
  std.get_macro(DIV_MACRO_WAVE, true)->len=reader.readI();
  if (version>=17) {
    std.get_macro(DIV_MACRO_PITCH, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX1, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX2, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX3, true)->len=reader.readI();
  }
  std.get_macro(DIV_MACRO_VOL, true)->loop=reader.readI();
  std.get_macro(DIV_MACRO_ARP, true)->loop=reader.readI();
  std.get_macro(DIV_MACRO_DUTY, true)->loop=reader.readI();
  std.get_macro(DIV_MACRO_WAVE, true)->loop=reader.readI();
  if (version>=17) {
    std.get_macro(DIV_MACRO_PITCH, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX1, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX2, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX3, true)->loop=reader.readI();
  }
  std.get_macro(DIV_MACRO_ARP, true)->mode=reader.readC();
  // these 3 were macro heights before but they are not used anymore
  int oldVolHeight=reader.readC();
  int oldDutyHeight=reader.readC();
  reader.readC(); // oldWaveHeight
  READ_MACRO_VALS(std.get_macro(DIV_MACRO_VOL, true)->val,std.get_macro(DIV_MACRO_VOL, true)->len);
  READ_MACRO_VALS(std.get_macro(DIV_MACRO_ARP, true)->val,std.get_macro(DIV_MACRO_ARP, true)->len);
  READ_MACRO_VALS(std.get_macro(DIV_MACRO_DUTY, true)->val,std.get_macro(DIV_MACRO_DUTY, true)->len);
  READ_MACRO_VALS(std.get_macro(DIV_MACRO_WAVE, true)->val,std.get_macro(DIV_MACRO_WAVE, true)->len);
  if (version<31) {
    if (!std.get_macro(DIV_MACRO_ARP, true)->mode) for (int j=0; j<std.get_macro(DIV_MACRO_ARP, true)->len; j++) {
      std.get_macro(DIV_MACRO_ARP, true)->val[j]-=12;
    }
  }
  if (type==DIV_INS_C64 && version<87) {
    if (volIsCutoff && !c64.filterIsAbs) for (int j=0; j<std.get_macro(DIV_MACRO_VOL, true)->len; j++) {
      std.get_macro(DIV_MACRO_VOL, true)->val[j]-=18;
    }
    if (!c64.dutyIsAbs) for (int j=0; j<std.get_macro(DIV_MACRO_DUTY, true)->len; j++) {
      std.get_macro(DIV_MACRO_DUTY, true)->val[j]-=12;
    }
  }
  if (version<193) {
    if (type==DIV_INS_AY || type==DIV_INS_AY8930) {
      for (int j=0; j<std.get_macro(DIV_MACRO_WAVE, true)->len; j++) {
        std.get_macro(DIV_MACRO_WAVE, true)->val[j]++;
      }
    }
  }
  if (version>=17) {
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_PITCH, true)->val,std.get_macro(DIV_MACRO_PITCH, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX1, true)->val,std.get_macro(DIV_MACRO_EX1, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX2, true)->val,std.get_macro(DIV_MACRO_EX2, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX3, true)->val,std.get_macro(DIV_MACRO_EX3, true)->len);
  } else {
    if (type==DIV_INS_STD) {
      if (oldVolHeight==31) {
        type=DIV_INS_PCE;
      }
      if (oldDutyHeight==31) {
        type=DIV_INS_AY;
      }
    }
  }

  // FM macros
  if (version>=29) {
    std.get_macro(DIV_MACRO_ALG, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_FB, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_FMS, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_AMS, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_ALG, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_FB, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_FMS, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_AMS, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_VOL, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_ARP, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_DUTY, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_WAVE, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_PITCH, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX1, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX2, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX3, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_ALG, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_FB, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_FMS, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_AMS, true)->open=reader.readC();

    READ_MACRO_VALS(std.get_macro(DIV_MACRO_ALG, true)->val,std.get_macro(DIV_MACRO_ALG, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_FB, true)->val,std.get_macro(DIV_MACRO_FB, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_FMS, true)->val,std.get_macro(DIV_MACRO_FMS, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_AMS, true)->val,std.get_macro(DIV_MACRO_AMS, true)->len);

    for (int i=0; i<4; i++) {
      DivInstrumentSTD::OpMacro& op=*std.get_op_macro(i);

      op.op_get_macro(DIV_MACRO_OP_AM, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_AR, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DR, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_MULT, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_RR, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SL, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_TL, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DT2, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_RS, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DT, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_D2R, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SSG, true)->len=reader.readI();

      op.op_get_macro(DIV_MACRO_OP_AM, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_AR, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DR, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_MULT, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_RR, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SL, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_TL, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DT2, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_RS, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DT, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_D2R, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SSG, true)->loop=reader.readI();

      op.op_get_macro(DIV_MACRO_OP_AM, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_AR, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DR, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_MULT, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_RR, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SL, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_TL, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DT2, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_RS, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DT, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_D2R, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SSG, true)->open=reader.readC();
    }

    // FM macro low 8 bits
    for (int i=0; i<4; i++) {
      DivInstrumentSTD::OpMacro& op=*std.get_op_macro(i);
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_AM, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_AM, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_AR, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_AR, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_DR, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_DR, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_MULT, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_MULT, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_RR, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_RR, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_SL, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_SL, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_TL, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_TL, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_DT2, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_DT2, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_RS, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_RS, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_DT, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_DT, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_D2R, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_D2R, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_SSG, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_SSG, true)->val[j]=(unsigned char)reader.readC();
      }
    }
  }

  // release points
  if (version>=44) {
    std.get_macro(DIV_MACRO_VOL, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_ARP, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_DUTY, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_WAVE, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_PITCH, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX1, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX2, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX3, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_ALG, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_FB, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_FMS, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_AMS, true)->rel=reader.readI();

    for (int i=0; i<4; i++) {
      DivInstrumentSTD::OpMacro& op=*std.get_op_macro(i);

      op.op_get_macro(DIV_MACRO_OP_AM, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_AR, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DR, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_MULT, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_RR, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SL, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_TL, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DT2, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_RS, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DT, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_D2R, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SSG, true)->rel=reader.readI();
    }
  }

  // extended op macros
  if (version>=61) {
    for (int i=0; i<4; i++) {
      DivInstrumentSTD::OpMacro& op=*std.get_op_macro(i);

      op.op_get_macro(DIV_MACRO_OP_DAM, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DVB, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_EGT, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_KSL, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SUS, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_VIB, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_WS, true)->len=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_KSR, true)->len=reader.readI();

      op.op_get_macro(DIV_MACRO_OP_DAM, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DVB, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_EGT, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_KSL, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SUS, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_VIB, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_WS, true)->loop=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_KSR, true)->loop=reader.readI();

      op.op_get_macro(DIV_MACRO_OP_DAM, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_DVB, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_EGT, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_KSL, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_SUS, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_VIB, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_WS, true)->rel=reader.readI();
      op.op_get_macro(DIV_MACRO_OP_KSR, true)->rel=reader.readI();

      op.op_get_macro(DIV_MACRO_OP_DAM, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DVB, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_EGT, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_KSL, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SUS, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_VIB, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_WS, true)->open=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_KSR, true)->open=reader.readC();
    }

    for (int i=0; i<4; i++) {
      DivInstrumentSTD::OpMacro& op=*std.get_op_macro(i);
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_DAM, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_DAM, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_DVB, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_DVB, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_EGT, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_EGT, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_KSL, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_KSL, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_SUS, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_SUS, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_VIB, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_VIB, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_WS, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_WS, true)->val[j]=(unsigned char)reader.readC();
      }
      for (int j=0; j<op.op_get_macro(DIV_MACRO_OP_KSR, true)->len; j++) {
        op.op_get_macro(DIV_MACRO_OP_KSR, true)->val[j]=(unsigned char)reader.readC();
      }
    }
  }

  // OPL drum data
  if (version>=63) {
    fm.fixedDrums=reader.readC();
    reader.readC(); // reserved
    fm.kickFreq=reader.readS();
    fm.snareHatFreq=reader.readS();
    fm.tomTopFreq=reader.readS();
  }

  // clear noise macro if PCE instrument and version<63
  if (version<63 && type==DIV_INS_PCE) {
    std.get_macro(DIV_MACRO_DUTY, true)->len=0;
    std.get_macro(DIV_MACRO_DUTY, true)->loop=255;
    std.get_macro(DIV_MACRO_DUTY, true)->rel=255;
  }

  // clear wave macro if OPLL instrument and version<70
  if (version<70 && type==DIV_INS_OPLL) {
    std.get_macro(DIV_MACRO_WAVE, true)->len=0;
    std.get_macro(DIV_MACRO_WAVE, true)->loop=255;
    std.get_macro(DIV_MACRO_WAVE, true)->rel=255;
  }

  // sample map
  if (version>=67) {
    amiga.useNoteMap=reader.readC();
    if (amiga.useNoteMap) {
      for (int note=0; note<120; note++) {
        amiga.get_amiga_sample_map(note, true)->freq=reader.readI();
      }
      for (int note=0; note<120; note++) {
        amiga.get_amiga_sample_map(note, true)->map=reader.readS();
      }

      if (version<152) {
        for (int note=0; note<120; note++) {
          amiga.get_amiga_sample_map(note, true)->freq=note;
        }
      }
    }
  }

  // N163
  if (version>=73) {
    n163.wave=reader.readI();
    n163.wavePos=(unsigned char)reader.readC();
    n163.waveLen=(unsigned char)reader.readC();
    n163.waveMode=(unsigned char)reader.readC();
    reader.readC(); // reserved
  }

  if (version>=76) {
    // more macros
    std.get_macro(DIV_MACRO_PAN_LEFT, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX4, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX5, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX6, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX7, true)->len=reader.readI();
    std.get_macro(DIV_MACRO_EX8, true)->len=reader.readI();

    std.get_macro(DIV_MACRO_PAN_LEFT, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX4, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX5, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX6, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX7, true)->loop=reader.readI();
    std.get_macro(DIV_MACRO_EX8, true)->loop=reader.readI();

    std.get_macro(DIV_MACRO_PAN_LEFT, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX4, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX5, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX6, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX7, true)->rel=reader.readI();
    std.get_macro(DIV_MACRO_EX8, true)->rel=reader.readI();

    std.get_macro(DIV_MACRO_PAN_LEFT, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX4, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX5, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX6, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX7, true)->open=reader.readC();
    std.get_macro(DIV_MACRO_EX8, true)->open=reader.readC();

    READ_MACRO_VALS(std.get_macro(DIV_MACRO_PAN_LEFT, true)->val,std.get_macro(DIV_MACRO_PAN_LEFT, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_PAN_RIGHT, true)->val,std.get_macro(DIV_MACRO_PAN_RIGHT, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_PHASE_RESET, true)->val,std.get_macro(DIV_MACRO_PHASE_RESET, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX4, true)->val,std.get_macro(DIV_MACRO_EX4, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX5, true)->val,std.get_macro(DIV_MACRO_EX5, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX6, true)->val,std.get_macro(DIV_MACRO_EX6, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX7, true)->val,std.get_macro(DIV_MACRO_EX7, true)->len);
    READ_MACRO_VALS(std.get_macro(DIV_MACRO_EX8, true)->val,std.get_macro(DIV_MACRO_EX8, true)->len);

    // FDS
    fds.modSpeed=reader.readI();
    fds.modDepth=reader.readI();
    fds.initModTableWithFirstWave=reader.readC();
    reader.readC(); // reserved
    reader.readC();
    reader.readC();
    reader.read(fds.modTable,32);
  }

  // OPZ
  if (version>=77) {
    fm.fms2=reader.readC();
    fm.ams2=reader.readC();
  }

  // wave synth
  if (version>=79) {
    ws.wave1=reader.readI();
    ws.wave2=reader.readI();
    ws.rateDivider=reader.readC();
    ws.effect=reader.readC();
    ws.enabled=reader.readC();
    ws.global=reader.readC();
    ws.speed=reader.readC();
    ws.param1=reader.readC();
    ws.param2=reader.readC();
    ws.param3=reader.readC();
    ws.param4=reader.readC();
  }

  // other macro modes
  if (version>=84) {
    std.get_macro(DIV_MACRO_VOL, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_DUTY, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_WAVE, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_PITCH, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX1, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX2, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX3, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_ALG, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_FB, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_FMS, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_AMS, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_PAN_LEFT, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX4, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX5, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX6, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX7, true)->mode=reader.readC();
    std.get_macro(DIV_MACRO_EX8, true)->mode=reader.readC();
  }

  // C64 no test
  if (version>=89) {
    c64.noTest=reader.readC();
  }

  // MultiPCM
  if (version>=93) {
    multipcm.ar=reader.readC();
    multipcm.d1r=reader.readC();
    multipcm.dl=reader.readC();
    multipcm.d2r=reader.readC();
    multipcm.rr=reader.readC();
    multipcm.rc=reader.readC();
    multipcm.lfo=reader.readC();
    multipcm.vib=reader.readC();
    multipcm.am=reader.readC();
    // reserved
    for (int k=0; k<23; k++) reader.readC();
  }

  // Sound Unit
  if (version>=104) {
    amiga.useSample=reader.readC();
    su.switchRoles=reader.readC();
  }

  // GB hardware sequence
  if (version>=105) {
    gb.hwSeqLen=reader.readC();
    for (int i=0; i<gb.hwSeqLen; i++) {
      gb.get_gb_hw_seq(i, true)->cmd=reader.readC();
      gb.get_gb_hw_seq(i, true)->data=reader.readS();
    }
  }

  // GB additional flags
  if (version>=106) {
    gb.softEnv=reader.readC();
    gb.alwaysInit=reader.readC();
  }

  // ES5506
  if (version>=107) {
    es5506.filter.mode=(DivInstrumentES5506::Filter::FilterMode)reader.readC();
    es5506.filter.k1=reader.readS();
    es5506.filter.k2=reader.readS();
    es5506.envelope.ecount=reader.readS();
    es5506.envelope.lVRamp=reader.readC();
    es5506.envelope.rVRamp=reader.readC();
    es5506.envelope.k1Ramp=reader.readC();
    es5506.envelope.k2Ramp=reader.readC();
    es5506.envelope.k1Slow=reader.readC();
    es5506.envelope.k2Slow=reader.readC();
  }

  // SNES
  if (version>=109) {
    snes.useEnv=reader.readC();
    if (version<118) {
      // why why why
      reader.readC();
      reader.readC();
    } else {
      snes.gainMode=(DivInstrumentSNES::GainMode)reader.readC();
      snes.gain=reader.readC();
    }
    snes.a=reader.readC();
    snes.d=reader.readC();
    snes.s=reader.readC();
    snes.sus=(snes.s&8)?1:0;
    snes.s&=7;
    snes.r=reader.readC();
  }

  // macro speed/delay
  if (version>=111) {
    std.get_macro(DIV_MACRO_VOL, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_ARP, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_DUTY, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_WAVE, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_PITCH, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX1, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX2, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX3, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_ALG, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_FB, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_FMS, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_AMS, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_PAN_LEFT, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX4, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX5, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX6, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX7, true)->speed=reader.readC();
    std.get_macro(DIV_MACRO_EX8, true)->speed=reader.readC();

    std.get_macro(DIV_MACRO_VOL, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_ARP, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_DUTY, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_WAVE, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_PITCH, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX1, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX2, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX3, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_ALG, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_FB, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_FMS, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_AMS, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_PAN_LEFT, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_PAN_RIGHT, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_PHASE_RESET, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX4, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX5, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX6, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX7, true)->delay=reader.readC();
    std.get_macro(DIV_MACRO_EX8, true)->delay=reader.readC();

    // op macro speed/delay
    for (int i=0; i<4; i++) {
      DivInstrumentSTD::OpMacro& op=*std.get_op_macro(i);

      op.op_get_macro(DIV_MACRO_OP_AM, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_AR, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DR, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_MULT, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_RR, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SL, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_TL, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DT2, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_RS, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DT, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_D2R, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SSG, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DAM, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DVB, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_EGT, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_KSL, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SUS, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_VIB, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_WS, true)->speed=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_KSR, true)->speed=reader.readC();

      op.op_get_macro(DIV_MACRO_OP_AM, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_AR, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DR, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_MULT, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_RR, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SL, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_TL, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DT2, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_RS, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DT, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_D2R, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SSG, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DAM, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_DVB, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_EGT, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_KSL, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_SUS, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_VIB, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_WS, true)->delay=reader.readC();
      op.op_get_macro(DIV_MACRO_OP_KSR, true)->delay=reader.readC();
    }
  }

  // old arp macro format
  if (version<112) {
    if (std.get_macro(DIV_MACRO_ARP, true)->mode) {
      std.get_macro(DIV_MACRO_ARP, true)->mode=0;
      for (int i=0; i<std.get_macro(DIV_MACRO_ARP, true)->len; i++) {
        std.get_macro(DIV_MACRO_ARP, true)->val[i]^=0x40000000;
      }
      if ((std.get_macro(DIV_MACRO_ARP, true)->loop>=std.get_macro(DIV_MACRO_ARP, true)->len || (std.get_macro(DIV_MACRO_ARP, true)->rel>std.get_macro(DIV_MACRO_ARP, true)->loop && std.get_macro(DIV_MACRO_ARP, true)->rel<std.get_macro(DIV_MACRO_ARP, true)->len)) && std.get_macro(DIV_MACRO_ARP, true)->len<255) {
        std.get_macro(DIV_MACRO_ARP, true)->val[std.get_macro(DIV_MACRO_ARP, true)->len++]=0;
      }
    }
  }

  // <167 TL macro compat
  if (version<167) {
    for (int i = 0; i < 4; i++) 
    {
      std.ops.push_back(DivInstrumentSTD::OpMacro());
    }

    for (int i=0; i<4; i++) {
      if (std.ops[i].op_get_macro(DIV_MACRO_OP_TL, true)->open&6) {
          for (int j=0; j<2; j++) {
          std.ops[i].op_get_macro(DIV_MACRO_OP_TL, true)->val[j]^=0x7f;
        }
      } else {
        for (int j=0; j<std.ops[i].op_get_macro(DIV_MACRO_OP_TL, true)->len; j++) {
          std.ops[i].op_get_macro(DIV_MACRO_OP_TL, true)->val[j]^=0x7f;
        }
      }
    }
  }

  // <187 C64 cutoff macro compatibility
  if (type==DIV_INS_C64 && volIsCutoff && version<187) 
  {
    DivInstrumentMacro* m = std.get_macro(DIV_MACRO_ALG, true);
    m = std.get_macro(DIV_MACRO_VOL, true);

    UNUSED(m);

    for (int i=0; i<256; i++) 
    {
      std.get_macro(DIV_MACRO_ALG, true)->val[i]=std.get_macro(DIV_MACRO_VOL, true)->val[i];
    }

    std.get_macro(DIV_MACRO_ALG, true)->len = std.get_macro(DIV_MACRO_VOL, true)->len;
    std.get_macro(DIV_MACRO_ALG, true)->delay = std.get_macro(DIV_MACRO_VOL, true)->delay;
    std.get_macro(DIV_MACRO_ALG, true)->lenMemory = std.get_macro(DIV_MACRO_VOL, true)->lenMemory;
    std.get_macro(DIV_MACRO_ALG, true)->mode = std.get_macro(DIV_MACRO_VOL, true)->mode;
    std.get_macro(DIV_MACRO_ALG, true)->rel = std.get_macro(DIV_MACRO_VOL, true)->rel;
    std.get_macro(DIV_MACRO_ALG, true)->speed = std.get_macro(DIV_MACRO_VOL, true)->speed;
    std.get_macro(DIV_MACRO_ALG, true)->loop = std.get_macro(DIV_MACRO_VOL, true)->loop;
    std.get_macro(DIV_MACRO_ALG, true)->open = std.get_macro(DIV_MACRO_VOL, true)->open;

    std.get_macro(DIV_MACRO_VOL, true)->len = 0;
    std.get_macro(DIV_MACRO_VOL, true)->open = 1;

    if (!c64.filterIsAbs) {
      for (int i=0; i<256; i++) {
        std.get_macro(DIV_MACRO_ALG, true)->val[i]=-std.get_macro(DIV_MACRO_ALG, true)->val[i];
      }
    }
  }

  // <187 special/test/gate merge
  if (type==DIV_INS_C64 && version<187) {
    convertC64SpecialMacro();
  }

  return DIV_DATA_SUCCESS;
}

DivDataErrors DivInstrument::readInsData(SafeReader& reader, short version, DivSong* song) {
  // 0: old (INST)
  // 1: new (INS2, length)
  // 2: new (FINS, no length)
  int type=-1;

  bool tildearrow_version = false;

  char magic[4];
  reader.read(magic,4);
  if (memcmp(magic,"INST",4)==0) {
    type=0;
    tildearrow_version = true;
  } else if (memcmp(magic,"INS2",4)==0) {
    type=1;
    tildearrow_version = true;
  } else if (memcmp(magic,"FINS",4)==0) {
    type=2;
    tildearrow_version = true;
  } else if (memcmp(magic,"IN2B",4)==0) {
    type=1;
    tildearrow_version = false;
  } else if (memcmp(magic,"FINB",4)==0) {
    type=2;
    tildearrow_version = false;
  } else {
    logE("invalid instrument header!");
    return DIV_DATA_INVALID_HEADER;
  }

  if (type==1 || type==2) {
    logV("reading new instrument data...");
    return readInsDataNew(reader,version,type==2,song,tildearrow_version);
  }
  return readInsDataOld(reader,version,tildearrow_version);
}

void DivInstrument::convertC64SpecialMacro() {
  // merge special and test/gate macros into new special macro
  int maxLen=MAX(std.get_macro(DIV_MACRO_EX3, false)->len,std.get_macro(DIV_MACRO_EX4, false)->len);

  // skip if ex4 is not a sequence macro
  if (std.get_macro(DIV_MACRO_EX4, false)->open&6) return;

  // move ex4 macro up and fill in gate
  for (int i=0; i<std.get_macro(DIV_MACRO_EX4, false)->len; i++) {
    std.get_macro(DIV_MACRO_EX4, false)->val[i]=(std.get_macro(DIV_MACRO_EX4, false)->val[i]&1)?9:1;
  }
  
  // merge ex3 into ex4 if viable to
  if (std.get_macro(DIV_MACRO_EX3, false)->len>0 && !(std.get_macro(DIV_MACRO_EX3, false)->open&6)) {
    if (std.get_macro(DIV_MACRO_EX4, false)->len>0 && std.get_macro(DIV_MACRO_EX4, false)->len<maxLen) {
      for (int i=std.get_macro(DIV_MACRO_EX4, false)->len; i<maxLen; i++) {
        std.get_macro(DIV_MACRO_EX4, false)->val[i]=std.get_macro(DIV_MACRO_EX3, false)->val[std.get_macro(DIV_MACRO_EX4, false)->len-1];
      }
    } else {
      for (int i=0; i<maxLen; i++) {
        std.get_macro(DIV_MACRO_EX4, false)->val[i]=1;
      }
    }
    for (int i=0; i<maxLen; i++) {
      if (i>=std.get_macro(DIV_MACRO_EX3, false)->len) {
        std.get_macro(DIV_MACRO_EX4, false)->val[i]|=(std.get_macro(DIV_MACRO_EX3, false)->val[std.get_macro(DIV_MACRO_EX3, false)->len-1]&3)<<1;
      } else {
        std.get_macro(DIV_MACRO_EX4, false)->val[i]|=(std.get_macro(DIV_MACRO_EX3, false)->val[i]&3)<<1;
      }
    }
  }
  std.get_macro(DIV_MACRO_EX4, false)->len=maxLen;

  *std.get_macro(DIV_MACRO_EX3, false)=DivInstrumentMacro(DIV_MACRO_EX3);
}

bool DivInstrument::save(const char* path, DivSong* song, bool writeInsName) {
  SafeWriter* w=new SafeWriter();
  w->init();

  putInsData2(w,true,song,writeInsName,false);

  FILE* outFile=ps_fopen(path,"wb");
  if (outFile==NULL) {
    logE("could not save instrument: %s!",strerror(errno));
    w->finish();
    return false;
  }
  if (fwrite(w->getFinalBuf(),1,w->size(),outFile)!=w->size()) {
    logW("did not write entire instrument!");
  }
  fclose(outFile);
  w->finish();
  return true;
}

bool DivInstrument::saveDMP(const char* path) {
  SafeWriter* w=new SafeWriter();
  w->init();

  // write version
  w->writeC(11);

  // guess the system
  switch (type) {
    case DIV_INS_FM:
      // we can't tell Genesis and Neo Geo apart
      w->writeC(0x02);
      w->writeC(1);
      break;
    case DIV_INS_STD:
      w->writeC(0x03);
      w->writeC(0);
      break;
    case DIV_INS_NES:
      w->writeC(0x06);
      w->writeC(0);
      break;
    case DIV_INS_GB:
      w->writeC(0x04);
      w->writeC(0);
      break;
    case DIV_INS_C64:
      w->writeC(0x07);
      w->writeC(0);
      break;
    case DIV_INS_PCE:
      w->writeC(0x05);
      w->writeC(0);
      break;
    case DIV_INS_OPLL:
      // ???
      w->writeC(0x13);
      w->writeC(1);
      break;
    case DIV_INS_OPM:
      w->writeC(0x08);
      w->writeC(1);
      break;
    case DIV_INS_OPZ:
      // data will be lost
      w->writeC(0x08);
      w->writeC(1);
      break;
    case DIV_INS_FDS:
      // ???
      w->writeC(0x06);
      w->writeC(0);
      break;
    default:
      // not supported by .dmp
      w->finish();
      return false;
  }

  if (type==DIV_INS_FM || type==DIV_INS_OPM || type==DIV_INS_OPLL || type==DIV_INS_OPZ) {
    w->writeC(fm.fms);
    w->writeC(fm.fb);
    w->writeC(fm.alg);
    w->writeC(fm.ams);

    // TODO: OPLL params
    for (int i=0; i<4; i++) {
      DivInstrumentFM::Operator& op=fm.op[i];
      w->writeC(op.mult);
      w->writeC(op.tl);
      w->writeC(op.ar);
      w->writeC(op.dr);
      w->writeC(op.sl);
      w->writeC(op.rr);
      w->writeC(op.am);
      w->writeC(op.rs);
      w->writeC(op.dt|(op.dt2<<4));
      w->writeC(op.d2r);
      w->writeC(op.ssgEnv);
    }
  } else {
    if (type!=DIV_INS_GB) {
      w->writeC(std.get_macro(DIV_MACRO_VOL, false)->len);
      for (int i=0; i<std.get_macro(DIV_MACRO_VOL, false)->len; i++) {
        w->writeI(std.get_macro(DIV_MACRO_VOL, false)->val[i]);
      }
      if (std.get_macro(DIV_MACRO_VOL, false)->len>0) w->writeC(std.get_macro(DIV_MACRO_VOL, false)->loop);
    }

    bool arpMacroMode=false;
    int arpMacroHowManyFixed=0;
    int realArpMacroLen=std.get_macro(DIV_MACRO_ARP, false)->len;
    for (int j=0; j<std.get_macro(DIV_MACRO_ARP, false)->len; j++) {
      if ((std.get_macro(DIV_MACRO_ARP, false)->val[j]&0xc0000000)==0x40000000 || (std.get_macro(DIV_MACRO_ARP, false)->val[j]&0xc0000000)==0x80000000) {
        arpMacroHowManyFixed++;
      }
    }
    if (arpMacroHowManyFixed>=std.get_macro(DIV_MACRO_ARP, false)->len-1) {
      arpMacroMode=true;
    }
    if (std.get_macro(DIV_MACRO_ARP, false)->len>0) {
      if (arpMacroMode && std.get_macro(DIV_MACRO_ARP, false)->val[std.get_macro(DIV_MACRO_ARP, false)->len-1]==0 && std.get_macro(DIV_MACRO_ARP, false)->loop>=std.get_macro(DIV_MACRO_ARP, false)->len) {
        realArpMacroLen--;
      }
    }

    if (realArpMacroLen>127) realArpMacroLen=127;

    w->writeC(realArpMacroLen);

    if (arpMacroMode) {
      for (int j=0; j<realArpMacroLen; j++) {
        if ((std.get_macro(DIV_MACRO_ARP, false)->val[j]&0xc0000000)==0x40000000 || (std.get_macro(DIV_MACRO_ARP, false)->val[j]&0xc0000000)==0x80000000) {
          w->writeI(std.get_macro(DIV_MACRO_ARP, false)->val[j]^0x40000000);
        } else {
          w->writeI(std.get_macro(DIV_MACRO_ARP, false)->val[j]);
        }
      }
    } else {
      for (int j=0; j<realArpMacroLen; j++) {
        if ((std.get_macro(DIV_MACRO_ARP, false)->val[j]&0xc0000000)==0x40000000 || (std.get_macro(DIV_MACRO_ARP, false)->val[j]&0xc0000000)==0x80000000) {
          w->writeI((std.get_macro(DIV_MACRO_ARP, false)->val[j]^0x40000000)+12);
        } else {
          w->writeI(std.get_macro(DIV_MACRO_ARP, false)->val[j]+12);
        }
      }
    }
    if (realArpMacroLen>0) {
      w->writeC(std.get_macro(DIV_MACRO_ARP, false)->loop);
    }
    w->writeC(arpMacroMode);

    w->writeC(std.get_macro(DIV_MACRO_DUTY, false)->len);
    for (int i=0; i<std.get_macro(DIV_MACRO_DUTY, false)->len; i++) {
      w->writeI(std.get_macro(DIV_MACRO_DUTY, false)->val[i]);
    }
    if (std.get_macro(DIV_MACRO_DUTY, false)->len>0) w->writeC(std.get_macro(DIV_MACRO_DUTY, false)->loop);

    w->writeC(std.get_macro(DIV_MACRO_WAVE, false)->len);
    for (int i=0; i<std.get_macro(DIV_MACRO_WAVE, false)->len; i++) {
      if (type==DIV_INS_AY) {
        w->writeI(std.get_macro(DIV_MACRO_WAVE, false)->val[i]-1);
      } else {
        w->writeI(std.get_macro(DIV_MACRO_WAVE, false)->val[i]);
      }
    }
    if (std.get_macro(DIV_MACRO_WAVE, false)->len>0) w->writeC(std.get_macro(DIV_MACRO_WAVE, false)->loop);

    if (type==DIV_INS_C64) {
      w->writeC(c64.triOn);
      w->writeC(c64.sawOn);
      w->writeC(c64.pulseOn);
      w->writeC(c64.noiseOn);
      w->writeC(c64.a);
      w->writeC(c64.d);
      w->writeC(c64.s);
      w->writeC(c64.r);
      w->writeC((c64.duty*100)/4095);
      w->writeC(c64.ringMod);
      w->writeC(c64.oscSync);
      w->writeC(c64.toFilter);
      w->writeC(0); // this was volIsCutoff...
      w->writeC(c64.initFilter);
      w->writeC(c64.res);
      w->writeC((c64.cut*100)/2047);
      w->writeC(c64.hp);
      w->writeC(c64.lp);
      w->writeC(c64.bp);
      w->writeC(c64.ch3off);
    }
    if (type==DIV_INS_GB) {
      w->writeC(gb.envVol);
      w->writeC(gb.envDir);
      w->writeC(gb.envLen);
      w->writeC(gb.soundLen);
    }
  }

  FILE* outFile=ps_fopen(path,"wb");
  if (outFile==NULL) {
    logE("could not save instrument: %s!",strerror(errno));
    w->finish();
    return false;
  }
  if (fwrite(w->getFinalBuf(),1,w->size(),outFile)!=w->size()) {
    logW("did not write entire instrument!");
  }
  fclose(outFile);
  w->finish();
  return true;
}
