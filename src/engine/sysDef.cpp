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

#include "dispatch.h"
#include "engine.h"
#include "instrument.h"
#include "song.h"
#include "../ta-log.h"

DivSysDef* DivEngine::sysDefs[DIV_MAX_CHIP_DEFS];
DivSystem DivEngine::sysFileMapFur[DIV_MAX_CHIP_DEFS];
DivSystem DivEngine::sysFileMapDMF[DIV_MAX_CHIP_DEFS];

DivSystem DivEngine::systemFromFileFur(unsigned char val) {
  return sysFileMapFur[val];
}

unsigned char DivEngine::systemToFileFur(DivSystem val) {
  if (sysDefs[val]==NULL) return 0;
  return sysDefs[val]->id;
}

DivSystem DivEngine::systemFromFileDMF(unsigned char val) {
  return sysFileMapDMF[val];
}

unsigned char DivEngine::systemToFileDMF(DivSystem val) {
  if (sysDefs[val]==NULL) return 0;
  return sysDefs[val]->id_DMF;
}

int DivEngine::getChannelCount(DivSystem sys) {
  if (sysDefs[sys]==NULL) return 0;
  return sysDefs[sys]->channels;
}

int DivEngine::getTotalChannelCount() {
  return chans;
}

std::vector<DivInstrumentType>& DivEngine::getPossibleInsTypes() {
  return possibleInsTypes;
}

// for pre-dev103 modules
String DivEngine::getSongSystemLegacyName(DivSong& ds, bool isMultiSystemAcceptable) {
  switch (ds.systemLen) {
    case 0:
      return "help! what's going on!";
    case 1:
    {
      if (ds.system[0]==DIV_SYSTEM_AY8910) {
        switch (ds.systemFlags[0].getInt("chipType",0)) {
          case 0: // AY-3-8910
            switch (ds.systemFlags[0].getInt("clockSel",0)) {
              case 0: // AY-3-8910, 1.79MHz
              case 1: // AY-3-8910, 1.77MHz
              case 2: // AY-3-8910, 1.75MHz
                return "ZX Spectrum";
              case 3: // AY-3-8910, 2MHz
                return "Fujitsu Micro-7";
              case 4: // AY-3-8910, 1.5MHz
                return "Vectrex";
              case 5: // AY-3-8910, 1MHz
                return "Amstrad CPC";
              default:
                return "AY-3-8910";
            }
            break;
          case 1: // YM2149
            switch (ds.systemFlags[0].getInt("clockSel",0)) {
              case 0: // YM2149, 1.79MHz
                return "MSX";
              case 3: // YM2149, 2MHz
                return "Atari ST";
              default:
                return "Yamaha YM2149";
            }
            break;
          case 2: // 5B
            switch (ds.systemFlags[0].getInt("clockSel",0)) {
              case 6: // 5B NTSC
                return "Sunsoft 5B standalone##sesd";
              case 8: // 5B PAL
                return "Sunsoft 5B standalone (PAL)##sesd";
              default:
                return "Overclocked Sunsoft 5B##sesd";
            }
            break;
          case 3: // AY-3-8914
            switch (ds.systemFlags[0].getInt("clockSel",0)) {
              case 0: // AY-3-8914, 1.79MHz
                return "Intellivision";
              case 3: // AY-3-8914, 2MHz
                return "Intellivision (PAL)";
              default:
                return "Intellivision";
            }
            break;
        }
      } else if (ds.system[0]==DIV_SYSTEM_SMS) {
        switch (ds.systemFlags[0].getInt("chipType",0)) {
          case 0:
            switch (ds.systemFlags[0].getInt("clockSel",0)) {
              case 0: case 1:
                return "Sega Master System";
            }
            break;
          case 1:
            switch (ds.systemFlags[0].getInt("clockSel",0)) {
              case 2:
                return "BBC Micro";
            }
            break;
        }
      } else if (ds.system[0]==DIV_SYSTEM_YM2612) {
        switch (ds.systemFlags[0].getInt("clockSel",0)) {
          case 2:
            return "FM Towns";
        }
      } else if (ds.system[0]==DIV_SYSTEM_YM2151) {
        switch (ds.systemFlags[0].getInt("clockSel",0)) {
          case 2:
            return "Sharp X68000";
        }
      } else if (ds.system[0]==DIV_SYSTEM_SAA1099) {
        switch (ds.systemFlags[0].getInt("clockSel",0)) {
          case 0:
            return "SAM Coupé";
        }
      }

      String teeeemp = getSystemName(ds.system[0]);
      String temmrrrp = teeeemp.substr(0, teeeemp.find("##"));
      return temmrrrp;
    }
    case 2:
      if (ds.system[0]==DIV_SYSTEM_YM2612 && ds.system[1]==DIV_SYSTEM_SMS) {
        return "Sega Genesis/Mega Drive";
      }
      if (ds.system[0]==DIV_SYSTEM_YM2612_EXT && ds.system[1]==DIV_SYSTEM_SMS) {
        return "Sega Genesis Extended Channel 3##sesd0";
      }

      if (ds.system[0]==DIV_SYSTEM_OPLL && ds.system[1]==DIV_SYSTEM_SMS) {
        return "NTSC-J Sega Master System";
      }
      if (ds.system[0]==DIV_SYSTEM_OPLL_DRUMS && ds.system[1]==DIV_SYSTEM_SMS) {
        return "NTSC-J Sega Master System + drums##sesd";
      }
      if (ds.system[0]==DIV_SYSTEM_OPLL && ds.system[1]==DIV_SYSTEM_AY8910) {
        return "MSX-MUSIC";
      }
      if (ds.system[0]==DIV_SYSTEM_OPLL_DRUMS && ds.system[1]==DIV_SYSTEM_AY8910) {
        return "MSX-MUSIC + drums##sesd";
      }
      if (ds.system[0]==DIV_SYSTEM_C64_6581 && ds.system[1]==DIV_SYSTEM_C64_6581) {
        return "Commodore 64 with dual 6581##sesd";
      }
      if (ds.system[0]==DIV_SYSTEM_C64_8580 && ds.system[1]==DIV_SYSTEM_C64_8580) {
        return "Commodore 64 with dual 8580##sesd";
      }

      if (ds.system[0]==DIV_SYSTEM_YM2151 && ds.system[1]==DIV_SYSTEM_SEGAPCM_COMPAT) {
        return "YM2151 + SegaPCM Arcade (compatibility)##sesd";
      }
      if (ds.system[0]==DIV_SYSTEM_YM2151 && ds.system[1]==DIV_SYSTEM_SEGAPCM) {
        return "YM2151 + SegaPCM Arcade##sesd";
      }

      if (ds.system[0]==DIV_SYSTEM_SAA1099 && ds.system[1]==DIV_SYSTEM_SAA1099) {
        return "Creative Music System";
      }

      if (ds.system[0]==DIV_SYSTEM_GB && ds.system[1]==DIV_SYSTEM_AY8910) {
        return "Game Boy with AY expansion##sesd";
      }

      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_VRC6) {
        return "Famicom + Konami VRC6";
      }
      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_VRC7) {
        return "Famicom + Konami VRC7";
      }
      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_OPLL) {
        return "Family Noraebang";
      }
      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_FDS) {
        return "Famicom Disk System";
      }
      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_N163) {
        return "Famicom + Namco 163";
      }
      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_MMC5) {
        return "Famicom + MMC5";
      }
      if (ds.system[0]==DIV_SYSTEM_NES && ds.system[1]==DIV_SYSTEM_AY8910) {
        return "Famicom + Sunsoft 5B";
      }

      if (ds.system[0]==DIV_SYSTEM_AY8910 && ds.system[1]==DIV_SYSTEM_AY8910) {
        return "Bally Midway MCR";
      }

      if (ds.system[0]==DIV_SYSTEM_YM2151 && ds.system[1]==DIV_SYSTEM_VERA) {
        return "Commander X16";
      }
      break;
    case 3:
      if (ds.system[0]==DIV_SYSTEM_AY8910 && ds.system[1]==DIV_SYSTEM_AY8910 && ds.system[2]==DIV_SYSTEM_BUBSYS_WSG) {
        return "Konami Bubble System";
      }
      break;
  }
  if (isMultiSystemAcceptable) return "multi-system##sesd";

  String ret="";
  for (int i=0; i<ds.systemLen; i++) {
    if (i>0) ret+=" + ";
    String teeeemp = getSystemName(ds.system[i]);
    String temmrrrp = teeeemp.substr(0, teeeemp.find("##"));
    ret+=temmrrrp;
  }

  return ret;
}

const char* DivEngine::getSystemName(DivSystem sys) {
  if (sysDefs[sys]==NULL) return "Unknown##sesd";
  return sysDefs[sys]->name;
}

const char* DivEngine::getSystemNameJ(DivSystem sys) {
  if (sysDefs[sys]==NULL) return "不明";
  if (sysDefs[sys]->nameJ==NULL) return "";
  return sysDefs[sys]->nameJ;
  /*
  switch (sys) {
    case DIV_SYSTEM_NULL:
      return "不明";
    case DIV_SYSTEM_YMU759:
      return "";
    case DIV_SYSTEM_GENESIS:
      return "セガメガドライブ";
    case DIV_SYSTEM_SMS:
    case DIV_SYSTEM_SMS_OPLL:
      return "セガマスターシステム";
    case DIV_SYSTEM_GB:
      return "ゲームボーイ";
    case DIV_SYSTEM_PCE:
      return "PCエンジン";
    case DIV_SYSTEM_NES:
      return "ファミリーコンピュータ";
    case DIV_SYSTEM_C64_6581:
      return "コモドール64 (6581)";
    case DIV_SYSTEM_C64_8580:
      return "コモドール64 (8580)";
    case DIV_SYSTEM_ARCADE:
      return "Arcade";
    case DIV_SYSTEM_GENESIS_EXT:
      return "";
    case DIV_SYSTEM_YM2610:
      return "業務用ネオジオ";
    case DIV_SYSTEM_YM2610_EXT:
      return "業務用ネオジオ";
    case DIV_SYSTEM_YM2610_FULL:
      return "業務用ネオジオ";
    case DIV_SYSTEM_YM2610_FULL_EXT:
      return "業務用ネオジオ";
    case DIV_SYSTEM_AY8910:
      return "";
    case DIV_SYSTEM_AMIGA:
      return "";
    case DIV_SYSTEM_YM2151:
      return "";
    case DIV_SYSTEM_YM2612:
      return "";
    case DIV_SYSTEM_TIA:
      return "";
    case DIV_SYSTEM_SAA1099:
      return "";
    case DIV_SYSTEM_AY8930:
      return "";
    default: // TODO
      return "";
  }
  */
}

const DivSysDef* DivEngine::getSystemDef(DivSystem sys) {
  return sysDefs[sys];
}

bool DivEngine::isFMSystem(DivSystem sys) {
  if (sysDefs[sys]==NULL) return false;
  return sysDefs[sys]->isFM;
}

bool DivEngine::isSTDSystem(DivSystem sys) {
  if (sysDefs[sys]==NULL) return false;
  return sysDefs[sys]->isSTD;
}

const char* DivEngine::getChannelName(int chan) {
  if (chan<0 || chan>chans) return "??";
  if (!curSubSong->chanName[chan].empty()) return curSubSong->chanName[chan].c_str();
  if (sysDefs[sysOfChan[chan]]==NULL) return "??";
  
  const char* ret=sysDefs[sysOfChan[chan]]->chanNames[dispatchChanOfChan[chan]];
  if (ret==NULL) return "??";
  return ret;
}

const char* DivEngine::getChannelShortName(int chan) {
  if (chan<0 || chan>chans) return "??";
  if (!curSubSong->chanShortName[chan].empty()) return curSubSong->chanShortName[chan].c_str();
  if (sysDefs[sysOfChan[chan]]==NULL) return "??";
  
  const char* ret=sysDefs[sysOfChan[chan]]->chanShortNames[dispatchChanOfChan[chan]];
  if (ret==NULL) return "??";
  return ret;
}

int DivEngine::getChannelType(int chan) {
  if (chan<0 || chan>chans) return DIV_CH_NOISE;
  if (sysDefs[sysOfChan[chan]]==NULL) return DIV_CH_NOISE;
  return sysDefs[sysOfChan[chan]]->chanTypes[dispatchChanOfChan[chan]];
}

DivInstrumentType DivEngine::getPreferInsType(int chan) {
  if (chan<0 || chan>chans) return DIV_INS_STD;
  if (sysDefs[sysOfChan[chan]]==NULL) return DIV_INS_STD;
  return sysDefs[sysOfChan[chan]]->chanInsType[dispatchChanOfChan[chan]][0];
}

DivInstrumentType DivEngine::getPreferInsSecondType(int chan) {
  if (chan<0 || chan>chans) return DIV_INS_NULL;
  if (sysDefs[sysOfChan[chan]]==NULL) return DIV_INS_NULL;
  return sysDefs[sysOfChan[chan]]->chanInsType[dispatchChanOfChan[chan]][1];
}

int DivEngine::minVGMVersion(DivSystem which) {
  if (sysDefs[which]==NULL) return 0;
  return sysDefs[which]->vgmVersion;
}

#define IS_YM2610 (sysOfChan[ch]==DIV_SYSTEM_YM2610 || sysOfChan[ch]==DIV_SYSTEM_YM2610_EXT || sysOfChan[ch]==DIV_SYSTEM_YM2610_FULL || sysOfChan[ch]==DIV_SYSTEM_YM2610_FULL_EXT || sysOfChan[ch]==DIV_SYSTEM_YM2610B || sysOfChan[ch]==DIV_SYSTEM_YM2610B_EXT)
#define IS_OPM_LIKE (sysOfChan[ch]==DIV_SYSTEM_YM2151 || sysOfChan[ch]==DIV_SYSTEM_OPZ)

#define OP_EFFECT_MULTI(x,c,op,mask) \
  case x: \
    dispatchCmd(DivCommand(c,ch,op,effectVal&mask)); \
    break;

#define OP_EFFECT_SINGLE(x,c,maxOp,mask) \
  case x: \
    if ((effectVal>>4)>=0 && (effectVal>>4)<=maxOp) { \
      dispatchCmd(DivCommand(c,ch,(effectVal>>4)-1,effectVal&mask)); \
    } \
    break;

// define systems like:
// sysDefs[DIV_SYSTEM_ID]=new DivSysDef(
//   "Name", "Name (japanese, optional)", fileID, fileID_DMF, channels, isFM, isSTD, vgmVersion, waveWidth, waveHeight,
//   "Description",
//   {"Channel Names", ...},
//   {"Channel Short Names", ...},
//   {chanTypes, ...},
//   {chanPreferInsType, ...},
//   {chanPreferInsType2, ...}, (optional)
//   {{effect, {DIV_CMD_xx, "Description"}}, ...}, (effect handler, optional)
//   {{effect, {DIV_CMD_xx, "Description"}}, ...} (post effect handler, optional)
// );

template<const int val> int constVal(unsigned char, unsigned char) {
  return val;
};

int effectVal(unsigned char, unsigned char val) {
  return val;
};

int negEffectVal(unsigned char, unsigned char val) {
  return -(int)val;
};

template<const int mask> int effectValAnd(unsigned char, unsigned char val) {
  return val&mask;
};

template<const int shift> int effectValShift(unsigned char, unsigned char val) {
  return val<<shift;
};

template<const int maxOp> int effectOpVal(unsigned char, unsigned char val) {
  if ((val>>4)>maxOp) throw DivDoNotHandleEffect();
  return (val>>4)-1;
};

template<const int maxOp> int effectOpValNoZero(unsigned char, unsigned char val) {
  if ((val>>4)<1 || (val>>4)>maxOp) throw DivDoNotHandleEffect();
  return (val>>4)-1;
};

template<const int bits> int effectValLong(unsigned char cmd, unsigned char val) {
  return ((((unsigned int)cmd)&((1<<(bits-8))-1))<<8)|((unsigned int)val);
};

template<const int bits, const int shift> int effectValLongShift(unsigned char cmd, unsigned char val) {
  return (((((unsigned int)cmd)&((1<<(bits-8))-1))<<8)|((unsigned int)val))<<shift;
};

void DivEngine::registerSystems() {
  logD("registering systems...");

  // Common effect handler maps

  EffectHandlerMap ayPostEffectHandlerMap={
    {0x15, {DIV_CMD_RAW_FREQ, "15xx: Set raw period##sesd"}},
    {0x16, {DIV_CMD_RAW_FREQ_HIGHER_BYTE, "16xx: Set raw period higher nybble (0-F)##sesd"}},

    {0x20, {DIV_CMD_STD_NOISE_MODE, "20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope)##sesd"}},
    {0x21, {DIV_CMD_STD_NOISE_FREQ, "21xx: Set noise frequency (0 to 1F)##sesd"}},
    {0x22, {DIV_CMD_AY_ENVELOPE_SET, "22xy: Set envelope mode (x: shape, y: enable for this channel)##sesd"}},
    {0x23, {DIV_CMD_AY_ENVELOPE_LOW, "23xx: Set envelope period low byte##sesd"}},
    {0x24, {DIV_CMD_AY_ENVELOPE_HIGH, "24xx: Set envelope period high byte##sesd"}},
    {0x25, {DIV_CMD_AY_ENVELOPE_SLIDE, "25xx: Envelope slide up##sesd0", negEffectVal}},
    {0x26, {DIV_CMD_AY_ENVELOPE_SLIDE, "26xx: Envelope slide down##sesd0"}},
    {0x29, {DIV_CMD_AY_AUTO_ENVELOPE, "29xy: Set auto-envelope (x: numerator; y: denominator)##sesd0"}},
    {0x2e, {DIV_CMD_AY_IO_WRITE, "2Exx: Write to I/O port A##sesd", constVal<0>, effectVal}},
    {0x2f, {DIV_CMD_AY_IO_WRITE, "2Fxx: Write to I/O port B##sesd", constVal<1>, effectVal}},
  };

  EffectHandlerMap ay8930PostEffectHandlerMap = {
    {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set duty cycle (0 to 8)##sesd",
      [](unsigned char, unsigned char val) -> int { return 0x10+(val&15); }}},
    
    {0x15, {DIV_CMD_RAW_FREQ, "15xx: Set raw period##sesd"}},
    {0x16, {DIV_CMD_RAW_FREQ_HIGHER_BYTE, "16xx: Set raw period higher byte##sesd"}},

    {0x20, {DIV_CMD_STD_NOISE_MODE, "20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope)##sesd"}},
    {0x21, {DIV_CMD_STD_NOISE_FREQ, "21xx: Set noise frequency (0 to 1F)##sesd"}},
    {0x22, {DIV_CMD_AY_ENVELOPE_SET, "22xy: Set envelope mode (x: shape, y: enable for this channel)##sesd"}},
    {0x23, {DIV_CMD_AY_ENVELOPE_LOW, "23xx: Set envelope period low byte##sesd"}},
    {0x24, {DIV_CMD_AY_ENVELOPE_HIGH, "24xx: Set envelope period high byte##sesd"}},
    {0x25, {DIV_CMD_AY_ENVELOPE_SLIDE, "25xx: Envelope slide up##sesd0", negEffectVal}},
    {0x26, {DIV_CMD_AY_ENVELOPE_SLIDE, "26xx: Envelope slide down##sesd0"}},
    {0x29, {DIV_CMD_AY_AUTO_ENVELOPE, "29xy: Set auto-envelope (x: numerator; y: denominator)##sesd0"}},
    {0x2e, {DIV_CMD_AY_IO_WRITE, "2Exx: Write to I/O port A##sesd", constVal<0>, effectVal}},
    {0x2f, {DIV_CMD_AY_IO_WRITE, "2Fxx: Write to I/O port B##sesd", constVal<1>, effectVal}},

    {0x27, {DIV_CMD_AY_NOISE_MASK_AND, "27xx: Set noise AND mask##sesd"}},
    {0x28, {DIV_CMD_AY_NOISE_MASK_OR, "28xx: Set noise OR mask##sesd"}},
    {0x2d, {DIV_CMD_AY_IO_WRITE, "2Dxx: NOT TO BE EMPLOYED BY THE COMPOSER##sesd", constVal<255>, effectVal}},
  };

  EffectHandlerMap fmEffectHandlerMap={
    {0x30, {DIV_CMD_FM_HARD_RESET, "30xx: Toggle hard envelope reset on new notes##sesd"}},
  };

  EffectHandlerMap fmExtChEffectHandlerMap(fmEffectHandlerMap);
  fmExtChEffectHandlerMap.insert({
    {0x18, {DIV_CMD_FM_EXTCH, "18xx: Toggle extended channel 3 mode##sesd"}},
  });

  EffectHandlerMap fmOPN2EffectHandlerMap(fmEffectHandlerMap);
  fmOPN2EffectHandlerMap.insert({
    {0x17, {DIV_CMD_SAMPLE_MODE, "17xx: Toggle PCM mode (LEGACY)##sesd0"}},
    {0xdf, {DIV_CMD_SAMPLE_DIR, "DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd0"}},
  });

  EffectHandlerMap fmOPLDrumsEffectHandlerMap(fmEffectHandlerMap);
  fmOPLDrumsEffectHandlerMap.insert({
    {0x18, {DIV_CMD_FM_EXTCH, "18xx: Toggle drums mode (1: enabled; 0: disabled)##sesd"}},
  });

  EffectHandlerMap fmOPNPostEffectHandlerMap={
    {0x11, {DIV_CMD_FM_FB, "11xx: Set feedback (0 to 7)##sesd0"}},
    {0x12, {DIV_CMD_FM_TL, "12xx: Set level of operator 1 (0 highest, 7F lowest)##sesd", constVal<0>, effectVal}},
    {0x13, {DIV_CMD_FM_TL, "13xx: Set level of operator 2 (0 highest, 7F lowest)##sesd", constVal<1>, effectVal}},
    {0x14, {DIV_CMD_FM_TL, "14xx: Set level of operator 3 (0 highest, 7F lowest)##sesd", constVal<2>, effectVal}},
    {0x15, {DIV_CMD_FM_TL, "15xx: Set level of operator 4 (0 highest, 7F lowest)##sesd", constVal<3>, effectVal}},
    {0x16, {DIV_CMD_FM_MULT, "16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd0", effectOpValNoZero<4>, effectValAnd<15>}},
    {0x19, {DIV_CMD_FM_AR, "19xx: Set attack of all operators (0 to 1F)##sesd", constVal<-1>, effectValAnd<31>}},
    {0x1a, {DIV_CMD_FM_AR, "1Axx: Set attack of operator 1 (0 to 1F)##sesd", constVal<0>, effectValAnd<31>}},
    {0x1b, {DIV_CMD_FM_AR, "1Bxx: Set attack of operator 2 (0 to 1F)##sesd", constVal<1>, effectValAnd<31>}},
    {0x1c, {DIV_CMD_FM_AR, "1Cxx: Set attack of operator 3 (0 to 1F)##sesd", constVal<2>, effectValAnd<31>}},
    {0x1d, {DIV_CMD_FM_AR, "1Dxx: Set attack of operator 4 (0 to 1F)##sesd", constVal<3>, effectValAnd<31>}},
    {0x50, {DIV_CMD_FM_AM, "50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd0", effectOpVal<4>, effectValAnd<1>}},
    {0x51, {DIV_CMD_FM_SL, "51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd0", effectOpVal<4>, effectValAnd<15>}},
    {0x52, {DIV_CMD_FM_RR, "52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd0", effectOpVal<4>, effectValAnd<15>}},
    {0x53, {DIV_CMD_FM_DT, "53xy: Set detune (x: operator from 1 to 4 (0 for all ops); y: detune where 3 is center)##sesd", effectOpVal<4>, effectValAnd<7>}},
    {0x54, {DIV_CMD_FM_RS, "54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd0", effectOpVal<4>, effectValAnd<3>}},
    {0x56, {DIV_CMD_FM_DR, "56xx: Set decay of all operators (0 to 1F)##sesd", constVal<-1>, effectValAnd<31>}},
    {0x57, {DIV_CMD_FM_DR, "57xx: Set decay of operator 1 (0 to 1F)##sesd", constVal<0>, effectValAnd<31>}},
    {0x58, {DIV_CMD_FM_DR, "58xx: Set decay of operator 2 (0 to 1F)##sesd", constVal<1>, effectValAnd<31>}},
    {0x59, {DIV_CMD_FM_DR, "59xx: Set decay of operator 3 (0 to 1F)##sesd", constVal<2>, effectValAnd<31>}},
    {0x5a, {DIV_CMD_FM_DR, "5Axx: Set decay of operator 4 (0 to 1F)##sesd", constVal<3>, effectValAnd<31>}},
    {0x5b, {DIV_CMD_FM_D2R, "5Bxx: Set decay 2 of all operators (0 to 1F)##sesd", constVal<-1>, effectValAnd<31>}},
    {0x5c, {DIV_CMD_FM_D2R, "5Cxx: Set decay 2 of operator 1 (0 to 1F)##sesd", constVal<0>, effectValAnd<31>}},
    {0x5d, {DIV_CMD_FM_D2R, "5Dxx: Set decay 2 of operator 2 (0 to 1F)##sesd", constVal<1>, effectValAnd<31>}},
    {0x5e, {DIV_CMD_FM_D2R, "5Exx: Set decay 2 of operator 3 (0 to 1F)##sesd", constVal<2>, effectValAnd<31>}},
    {0x5f, {DIV_CMD_FM_D2R, "5Fxx: Set decay 2 of operator 4 (0 to 1F)##sesd", constVal<3>, effectValAnd<31>}},
  };

  EffectHandlerMap fmOPMPostEffectHandlerMap(fmOPNPostEffectHandlerMap);
  fmOPMPostEffectHandlerMap.insert({
    {0x10, {DIV_CMD_STD_NOISE_FREQ, "10xx: Set noise frequency (xx: value; 0 disables noise)##sesd"}},
    {0x17, {DIV_CMD_FM_LFO, "17xx: Set LFO speed##sesd"}},
    {0x18, {DIV_CMD_FM_LFO_WAVE, "18xx: Set LFO waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"}},
    {0x1e, {DIV_CMD_FM_AM_DEPTH, "1Exx: Set AM depth (0 to 7F)##sesd", effectValAnd<127>}},
    {0x1f, {DIV_CMD_FM_PM_DEPTH, "1Fxx: Set PM depth (0 to 7F)##sesd", effectValAnd<127>}},
    {0x55, {DIV_CMD_FM_SSG, "55xy: Set detune 2 (x: operator from 1 to 4 (0 for all ops); y: detune from 0 to 3)##sesd", effectOpVal<4>, effectValAnd<3>}},
  });

  EffectHandlerMap fmOPZPostEffectHandlerMap(fmOPMPostEffectHandlerMap);
  fmOPZPostEffectHandlerMap.insert({
    {0x24, {DIV_CMD_FM_LFO2, "24xx: Set LFO 2 speed##sesd"}},
    {0x25, {DIV_CMD_FM_LFO2_WAVE, "25xx: Set LFO 2 waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"}},
    {0x26, {DIV_CMD_FM_AM2_DEPTH, "26xx: Set AM 2 depth (0 to 7F)##sesd", effectValAnd<127>}},
    {0x27, {DIV_CMD_FM_PM2_DEPTH, "27xx: Set PM 2 depth (0 to 7F)##sesd", effectValAnd<127>}},
    {0x28, {DIV_CMD_FM_REV, "28xy: Set reverb (x: operator from 1 to 4 (0 for all ops); y: reverb from 0 to 7)##sesd", effectOpVal<4>, effectValAnd<7>}},
    {0x2a, {DIV_CMD_FM_WS, "2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd0", effectOpVal<4>, effectValAnd<7>}},
    {0x2b, {DIV_CMD_FM_EG_SHIFT, "2Bxy: Set envelope generator shift (x: operator from 1 to 4 (0 for all ops); y: shift from 0 to 3)##sesd", effectOpVal<4>, effectValAnd<3>}},
    {0x2c, {DIV_CMD_FM_FINE, "2Cxy: Set fine multiplier (x: operator from 1 to 4 (0 for all ops); y: fine)##sesd", effectOpVal<4>, effectValAnd<15>}},
  });
  const EffectHandler fmOPZFixFreqHandler[4]={
    {DIV_CMD_FM_FIXFREQ, "3xyy: Set fixed frequency of operator 1 (x: octave from 0 to 7; y: frequency)##sesd", constVal<0>, effectValLong<11>},
    {DIV_CMD_FM_FIXFREQ, "3xyy: Set fixed frequency of operator 2 (x: octave from 8 to F; y: frequency)##sesd", constVal<1>, effectValLong<11>},
    {DIV_CMD_FM_FIXFREQ, "4xyy: Set fixed frequency of operator 3 (x: octave from 0 to 7; y: frequency)##sesd", constVal<2>, effectValLong<11>},
    {DIV_CMD_FM_FIXFREQ, "4xyy: Set fixed frequency of operator 4 (x: octave from 8 to F; y: frequency)##sesd", constVal<3>, effectValLong<11>},
  };
  for (int i=0; i<32; i++) {
    fmOPZPostEffectHandlerMap.emplace(0x30+i,fmOPZFixFreqHandler[i/8]);
  }

  fmOPNPostEffectHandlerMap.insert({
    {0x10, {DIV_CMD_FM_LFO, "10xy: Setup LFO (x: enable; y: speed)##sesd"}},
    {0x55, {DIV_CMD_FM_SSG, "55xy: Set SSG envelope (x: operator from 1 to 4 (0 for all ops); y: 0-7 on, 8 off)##sesd", effectOpVal<4>, effectValAnd<15>}},
  });
  EffectHandlerMap fmOPN2PostEffectHandlerMap(fmOPNPostEffectHandlerMap);

  fmOPNPostEffectHandlerMap.insert(ayPostEffectHandlerMap.begin(), ayPostEffectHandlerMap.end());

  EffectHandlerMap fmOPNAPostEffectHandlerMap(fmOPNPostEffectHandlerMap);
  fmOPNAPostEffectHandlerMap.insert({
    {0x1f, {DIV_CMD_ADPCMA_GLOBAL_VOLUME, "1Fxx: Set ADPCM-A global volume (0 to 3F)##sesd"}},
  });

  EffectHandlerMap fmOPLLPostEffectHandlerMap={
    {0x11, {DIV_CMD_FM_FB, "11xx: Set feedback (0 to 7)##sesd1"}},
    {0x12, {DIV_CMD_FM_TL, "12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd0", constVal<0>, effectVal}},
    {0x13, {DIV_CMD_FM_TL, "13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd0", constVal<1>, effectVal}},
    {0x16, {DIV_CMD_FM_MULT, "16xy: Set operator multiplier (x: operator from 1 to 2; y: multiplier)##sesd", effectOpValNoZero<2>, effectValAnd<15>}},
    {0x19, {DIV_CMD_FM_AR, "19xx: Set attack of all operators (0 to F)##sesd0", constVal<-1>, effectValAnd<15>}},
    {0x1a, {DIV_CMD_FM_AR, "1Axx: Set attack of operator 1 (0 to F)##sesd0", constVal<0>, effectValAnd<15>}},
    {0x1b, {DIV_CMD_FM_AR, "1Bxx: Set attack of operator 2 (0 to F)##sesd0", constVal<1>, effectValAnd<15>}},
    {0x50, {DIV_CMD_FM_AM, "50xy: Set AM (x: operator from 1 to 2 (0 for all ops); y: AM)##sesd", effectOpVal<2>, effectValAnd<1>}},
    {0x51, {DIV_CMD_FM_SL, "51xy: Set sustain level (x: operator from 1 to 2 (0 for all ops); y: sustain)##sesd", effectOpVal<2>, effectValAnd<15>}},
    {0x52, {DIV_CMD_FM_RR, "52xy: Set release (x: operator from 1 to 2 (0 for all ops); y: release)##sesd", effectOpVal<2>, effectValAnd<15>}},
    {0x53, {DIV_CMD_FM_VIB, "53xy: Set vibrato (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd", effectOpVal<2>, effectValAnd<1>}},
    {0x54, {DIV_CMD_FM_RS, "54xy: Set envelope scale (x: operator from 1 to 2 (0 for all ops); y: scale from 0 to 3)##sesd", effectOpVal<2>, effectValAnd<3>}},
    {0x55, {DIV_CMD_FM_SUS, "55xy: Set envelope sustain (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd", effectOpVal<2>, effectValAnd<1>}},
    {0x56, {DIV_CMD_FM_DR, "56xx: Set decay of all operators (0 to F)##sesd0", constVal<-1>, effectValAnd<15>}},
    {0x57, {DIV_CMD_FM_DR, "57xx: Set decay of operator 1 (0 to F)##sesd0", constVal<0>, effectValAnd<15>}},
    {0x58, {DIV_CMD_FM_DR, "58xx: Set decay of operator 2 (0 to F)##sesd0", constVal<1>, effectValAnd<15>}},
    {0x5b, {DIV_CMD_FM_KSR, "5Bxy: Set whether key will scale envelope (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd", effectOpVal<2>, effectValAnd<1>}},
  };

  EffectHandlerMap fmOPLPostEffectHandlerMap={
    {0x10, {DIV_CMD_FM_LFO, "10xx: Set global AM depth (0: 1dB, 1: 4.8dB)##sesd", effectValAnd<1>}},
    {0x11, {DIV_CMD_FM_FB, "11xx: Set feedback (0 to 7)##sesd2"}},
    {0x12, {DIV_CMD_FM_TL, "12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd1", constVal<0>, effectVal}},
    {0x13, {DIV_CMD_FM_TL, "13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd1", constVal<1>, effectVal}},
    {0x14, {DIV_CMD_FM_TL, "14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd0", constVal<2>, effectVal}},
    {0x15, {DIV_CMD_FM_TL, "15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd0", constVal<3>, effectVal}},
    {0x16, {DIV_CMD_FM_MULT, "16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd1", effectOpValNoZero<4>, effectValAnd<15>}},
    {0x17, {DIV_CMD_FM_LFO, "17xx: Set global vibrato depth (0: normal, 1: double)##sesd", [](unsigned char, unsigned char val) -> int { return (val&1)+2; }}},
    {0x19, {DIV_CMD_FM_AR, "19xx: Set attack of all operators (0 to F)##sesd1", constVal<-1>, effectValAnd<15>}},
    {0x1a, {DIV_CMD_FM_AR, "1Axx: Set attack of operator 1 (0 to F)##sesd1", constVal<0>, effectValAnd<15>}},
    {0x1b, {DIV_CMD_FM_AR, "1Bxx: Set attack of operator 2 (0 to F)##sesd1", constVal<1>, effectValAnd<15>}},
    {0x1c, {DIV_CMD_FM_AR, "1Cxx: Set attack of operator 3 (0 to F)##sesd0", constVal<2>, effectValAnd<15>}},
    {0x1d, {DIV_CMD_FM_AR, "1Dxx: Set attack of operator 4 (0 to F)##sesd0", constVal<3>, effectValAnd<15>}},
    {0x2a, {DIV_CMD_FM_WS, "2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 3 in OPL2 and 0 to 7 in OPL3)##sesd", effectOpVal<4>, effectValAnd<7>}},
    {0x50, {DIV_CMD_FM_AM, "50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd1", effectOpVal<4>, effectValAnd<1>}},
    {0x51, {DIV_CMD_FM_SL, "51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd1", effectOpVal<4>, effectValAnd<15>}},
    {0x52, {DIV_CMD_FM_RR, "52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd1", effectOpVal<4>, effectValAnd<15>}},
    {0x53, {DIV_CMD_FM_VIB, "53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0", effectOpVal<4>, effectValAnd<1>}},
    {0x54, {DIV_CMD_FM_RS, "54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd1", effectOpVal<4>, effectValAnd<3>}},
    {0x55, {DIV_CMD_FM_SUS, "55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0", effectOpVal<4>, effectValAnd<1>}},
    {0x56, {DIV_CMD_FM_DR, "56xx: Set decay of all operators (0 to F)##sesd1", constVal<-1>, effectValAnd<15>}},
    {0x57, {DIV_CMD_FM_DR, "57xx: Set decay of operator 1 (0 to F)##sesd1", constVal<0>, effectValAnd<15>}},
    {0x58, {DIV_CMD_FM_DR, "58xx: Set decay of operator 2 (0 to F)##sesd1", constVal<1>, effectValAnd<15>}},
    {0x59, {DIV_CMD_FM_DR, "59xx: Set decay of operator 3 (0 to F)##sesd0", constVal<2>, effectValAnd<15>}},
    {0x5a, {DIV_CMD_FM_DR, "5Axx: Set decay of operator 4 (0 to F)##sesd0", constVal<3>, effectValAnd<15>}},
    {0x5b, {DIV_CMD_FM_KSR, "5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0", effectOpVal<4>, effectValAnd<1>}},
  };

  EffectHandlerMap c64PostEffectHandlerMap={
    {0x10, {DIV_CMD_WAVE, "10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd"}},
    {0x11, {DIV_CMD_C64_CUTOFF, "11xx: Set coarse cutoff (not recommended; use 4xxx instead)##sesd"}},
    {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set coarse pulse width (not recommended; use 3xxx instead)##sesd"}},
    {0x13, {DIV_CMD_C64_RESONANCE, "13xx: Set resonance (0 to F)##sesd"}},
    {0x14, {DIV_CMD_C64_FILTER_MODE, "14xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"}},
    {0x15, {DIV_CMD_C64_RESET_TIME, "15xx: Set envelope reset time##sesd"}},
    {0x1a, {DIV_CMD_C64_RESET_MASK, "1Axx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"}},
    {0x1b, {DIV_CMD_C64_FILTER_RESET, "1Bxy: Reset cutoff (x: on new note; y: now)##sesd"}},
    {0x1c, {DIV_CMD_C64_DUTY_RESET, "1Cxy: Reset pulse width (x: on new note; y: now)##sesd"}},
    {0x1e, {DIV_CMD_C64_EXTENDED, "1Exy: Change other parameters (LEGACY)##sesd"}},
    {0x20, {DIV_CMD_C64_AD, "20xy: Set attack/decay (x: attack; y: decay)##sesd"}},
    {0x21, {DIV_CMD_C64_SR, "21xy: Set sustain/release (x: sustain; y: release)##sesd"}},

    {0x22, {DIV_CMD_PW_SLIDE_UP, "22xx: Pulse width slide up##sesd"}},
    {0x23, {DIV_CMD_PW_SLIDE_DN, "23xx: Pulse width slide down##sesd"}},

    {0x24, {DIV_CMD_CUTOFF_SLIDE_UP, "24xx: Cutoff slide up##sesd"}},
    {0x25, {DIV_CMD_CUTOFF_SLIDE_DN, "25xx: Cutoff slide down##sesd"}},
  };
  const EffectHandler c64FineDutyHandler(DIV_CMD_C64_FINE_DUTY, "3xxx: Set pulse width (0 to FFF)##sesd", effectValLong<12>);
  const EffectHandler c64FineCutoffHandler(DIV_CMD_C64_FINE_CUTOFF, "4xxx: Set cutoff (0 to 7FF)##sesd", effectValLong<11>);
  for (int i=0; i<16; i++) c64PostEffectHandlerMap.emplace(0x30+i,c64FineDutyHandler);
  for (int i=0; i<8; i++) c64PostEffectHandlerMap.emplace(0x40+i,c64FineCutoffHandler);

  EffectHandlerMap waveOnlyEffectHandlerMap={
    {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd0"}},
    {0x11, {DIV_CMD_WAVE_LOCAL, "11xx: Set waveform (local)##sesd"}},
  };

  EffectHandlerMap segaPCMPostEffectHandlerMap={
    {0x20, {DIV_CMD_SAMPLE_FREQ, "20xx: Set PCM frequency##sesd"}}
  };

  EffectHandlerMap fmESFMPostEffectHandlerMap={
    {0x10, {DIV_CMD_FM_AM_DEPTH, "10xy: Set AM depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: 1dB, 1: 4.8dB))##sesd", effectOpVal<4>, effectValAnd<1>}},
    {0x12, {DIV_CMD_FM_TL, "12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd2", constVal<0>, effectVal}},
    {0x13, {DIV_CMD_FM_TL, "13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd2", constVal<1>, effectVal}},
    {0x14, {DIV_CMD_FM_TL, "14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd1", constVal<2>, effectVal}},
    {0x15, {DIV_CMD_FM_TL, "15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd1", constVal<3>, effectVal}},
    {0x16, {DIV_CMD_FM_MULT, "16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd2", effectOpValNoZero<4>, effectValAnd<15>}},
    {0x17, {DIV_CMD_FM_PM_DEPTH, "17xy: Set vibrato depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: normal, 1: double))##sesd", effectOpVal<4>, effectValAnd<1>}},
    {0x19, {DIV_CMD_FM_AR, "19xx: Set attack of all operators (0 to F)##sesd", constVal<-1>, effectValAnd<15>}},
    {0x1a, {DIV_CMD_FM_AR, "1Axx: Set attack of operator 1 (0 to F)##sesd2", constVal<0>, effectValAnd<15>}},
    {0x1b, {DIV_CMD_FM_AR, "1Bxx: Set attack of operator 2 (0 to F)##sesd2", constVal<1>, effectValAnd<15>}},
    {0x1c, {DIV_CMD_FM_AR, "1Cxx: Set attack of operator 3 (0 to F)##sesd1", constVal<2>, effectValAnd<15>}},
    {0x1d, {DIV_CMD_FM_AR, "1Dxx: Set attack of operator 4 (0 to F)##sesd1", constVal<3>, effectValAnd<15>}},
    {0x20, {DIV_CMD_ESFM_OP_PANNING, "20xy: Set panning of operator 1 (x: left; y: right)##sesd", constVal<0>, effectVal}},
    {0x21, {DIV_CMD_ESFM_OP_PANNING, "21xy: Set panning of operator 2 (x: left; y: right)##sesd", constVal<1>, effectVal}},
    {0x22, {DIV_CMD_ESFM_OP_PANNING, "22xy: Set panning of operator 3 (x: left; y: right)##sesd", constVal<2>, effectVal}},
    {0x23, {DIV_CMD_ESFM_OP_PANNING, "23xy: Set panning of operator 4 (x: left; y: right)##sesd", constVal<3>, effectVal}},
    {0x24, {DIV_CMD_ESFM_OUTLVL, "24xy: Set output level register (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd", effectOpVal<4>, effectValAnd<7>}},
    {0x25, {DIV_CMD_ESFM_MODIN, "25xy: Set modulation input level (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd", effectOpVal<4>, effectValAnd<7>}},
    {0x26, {DIV_CMD_ESFM_ENV_DELAY, "26xy: Set envelope delay (x: operator from 1 to 4 (0 for all ops); y: delay from 0 to 7)##sesd", effectOpVal<4>, effectValAnd<7>}},
    {0x27, {DIV_CMD_STD_NOISE_MODE, "27xx: Set noise mode for operator 4 (x: mode from 0 to 3)##sesd", effectValAnd<3>}},
    {0x2a, {DIV_CMD_FM_WS, "2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd1", effectOpVal<4>, effectValAnd<7>}},
    {0x2f, {DIV_CMD_FM_FIXFREQ, "2Fxy: Set fixed frequency block (x: operator from 1 to 4; y: octave from 0 to 7)##sesd", effectOpValNoZero<4>, effectValAnd<7>}},
    {0x40, {DIV_CMD_FM_DT, "40xx: Set detune of operator 1 (80: center)##sesd", constVal<0>, effectVal}},
    {0x41, {DIV_CMD_FM_DT, "41xx: Set detune of operator 2 (80: center)##sesd", constVal<1>, effectVal}},
    {0x42, {DIV_CMD_FM_DT, "42xx: Set detune of operator 3 (80: center)##sesd", constVal<2>, effectVal}},
    {0x43, {DIV_CMD_FM_DT, "43xx: Set detune of operator 4 (80: center)##sesd", constVal<3>, effectVal}},
    {0x50, {DIV_CMD_FM_AM, "50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd2", effectOpVal<4>, effectValAnd<1>}},
    {0x51, {DIV_CMD_FM_SL, "51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd2", effectOpVal<4>, effectValAnd<15>}},
    {0x52, {DIV_CMD_FM_RR, "52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd2", effectOpVal<4>, effectValAnd<15>}},
    {0x53, {DIV_CMD_FM_VIB, "53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1", effectOpVal<4>, effectValAnd<1>}},
    {0x54, {DIV_CMD_FM_RS, "54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd2", effectOpVal<4>, effectValAnd<3>}},
    {0x55, {DIV_CMD_FM_SUS, "55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1", effectOpVal<4>, effectValAnd<1>}},
    {0x56, {DIV_CMD_FM_DR, "56xx: Set decay of all operators (0 to F)##sesd2", constVal<-1>, effectValAnd<15>}},
    {0x57, {DIV_CMD_FM_DR, "57xx: Set decay of operator 1 (0 to F)##sesd2", constVal<0>, effectValAnd<15>}},
    {0x58, {DIV_CMD_FM_DR, "58xx: Set decay of operator 2 (0 to F)##sesd2", constVal<1>, effectValAnd<15>}},
    {0x59, {DIV_CMD_FM_DR, "59xx: Set decay of operator 3 (0 to F)##sesd1", constVal<2>, effectValAnd<15>}},
    {0x5a, {DIV_CMD_FM_DR, "5Axx: Set decay of operator 4 (0 to F)##sesd1", constVal<3>, effectValAnd<15>}},
    {0x5b, {DIV_CMD_FM_KSR, "5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1", effectOpVal<4>, effectValAnd<1>}}
  };
  const EffectHandler fmESFMFixFreqFNumHandler[4]={
    {DIV_CMD_FM_FIXFREQ, "3xyy: Set fixed frequency F-num of operator 1 (x: high 2 bits from 0 to 3; y: low 8 bits of F-num)##sesd", constVal<4>, effectValLong<10>},
    {DIV_CMD_FM_FIXFREQ, "3xyy: Set fixed frequency F-num of operator 2 (x: high 2 bits from 4 to 7; y: low 8 bits of F-num)##sesd", constVal<5>, effectValLong<10>},
    {DIV_CMD_FM_FIXFREQ, "3xyy: Set fixed frequency F-num of operator 3 (x: high 2 bits from 8 to B; y: low 8 bits of F-num)##sesd", constVal<6>, effectValLong<10>},
    {DIV_CMD_FM_FIXFREQ, "3xyy: Set fixed frequency F-num of operator 4 (x: high 2 bits from C to F; y: low 8 bits of F-num)##sesd", constVal<7>, effectValLong<10>},
  };
  for (int i=0; i<16; i++) {
    fmESFMPostEffectHandlerMap.emplace(0x30+i,fmESFMFixFreqFNumHandler[i/4]);
  }

  EffectHandlerMap SID2PostEffectHandlerMap={
    {0x10, {DIV_CMD_WAVE, "10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd1"}},
    {0x11, {DIV_CMD_C64_RESONANCE, "11xx: Set resonance (0 to FF)##sesd"}},
    {0x12, {DIV_CMD_C64_FILTER_MODE, "12xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"}},
    {0x13, {DIV_CMD_C64_RESET_MASK, "13xx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"}},
    {0x14, {DIV_CMD_C64_FILTER_RESET, "14xy: Reset cutoff (x: on new note; y: now)##sesd"}},
    {0x15, {DIV_CMD_C64_DUTY_RESET, "15xy: Reset pulse width (x: on new note; y: now)##sesd"}},
    {0x16, {DIV_CMD_C64_EXTENDED, "16xy: Change other parameters##sesd"}},

    {0x17, {DIV_CMD_PW_SLIDE_UP, "17xx: Pulse width slide up##sesd"}},
    {0x18, {DIV_CMD_PW_SLIDE_DN, "18xx: Pulse width slide down##sesd"}},

    {0x19, {DIV_CMD_CUTOFF_SLIDE_UP, "19xx: Cutoff slide up##sesd"}},
    {0x1A, {DIV_CMD_CUTOFF_SLIDE_DN, "1Axx: Cutoff slide down##sesd"}},
  };
  const EffectHandler SID2FineDutyHandler(DIV_CMD_C64_FINE_DUTY, "3xxx: Set pulse width (0 to FFF)##sesd1", effectValLong<12>);
  const EffectHandler SID2FineCutoffHandler(DIV_CMD_C64_FINE_CUTOFF, "4xxx: Set cutoff (0 to FFF)##sesd1", effectValLong<11>);
  for (int i=0; i<16; i++) SID2PostEffectHandlerMap.emplace(0x30+i,SID2FineDutyHandler);
  for (int i=0; i<16; i++) SID2PostEffectHandlerMap.emplace(0x40+i,SID2FineCutoffHandler);

  // SysDefs

  // this chip uses YMZ ADPCM, but the emulator uses ADPCM-B because I got it wrong back then.
  sysDefs[DIV_SYSTEM_YMU759]=new DivSysDef(
    "Yamaha YMU759 (MA-2)", NULL, 0x01, 0x01, 17, true, false, 0, false, (1U<<DIV_SAMPLE_DEPTH_YMZ_ADPCM)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B), 0, 0,
    "a chip which found its way inside mobile phones in the 2000's.\nas proprietary as it is, it passed away after losing to MP3 in the mobile hardware battle.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd", "PCM##sesd"        }, // name
    {"1",         "2",         "3",         "4",         "5",         "6",         "7",         "8",         "9",         "10",         "11",         "12",         "13",         "14",         "15",         "16",         "PCM##sesd"        }, // short
    {DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,   DIV_CH_FM,    DIV_CH_FM,    DIV_CH_FM,    DIV_CH_FM,    DIV_CH_FM,    DIV_CH_FM,    DIV_CH_FM,    DIV_CH_PCM   }, // type
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL,  DIV_INS_OPL,  DIV_INS_OPL,  DIV_INS_OPL,  DIV_INS_OPL,  DIV_INS_OPL,  DIV_INS_OPL,  DIV_INS_AMIGA}  // ins
  );

  sysDefs[DIV_SYSTEM_GENESIS]=new DivSysDef(
    "Sega Genesis/Mega Drive", "セガメガドライブ", 0x02, 0x02, 10, true, true, 0, true, 0, 0, 0,
    "<COMPOUND SYSTEM!>##sesd0",
    {}, {}, {}, {}
  );

  sysDefs[DIV_SYSTEM_GENESIS_EXT]=new DivSysDef(
    "Sega Genesis Extended Channel 3##sesd1", NULL, 0x42, 0x42, 13, true, true, 0, true, 0, 0, 0,
    "<COMPOUND SYSTEM!>##sesd1",
    {}, {}, {}, {}
  );

  sysDefs[DIV_SYSTEM_SMS]=new DivSysDef(
    "TI SN76489", NULL, 0x03, 0x03, 4, false, true, 0x150, false, 0, 0, 0,
    "a square/noise sound chip found on the Sega Master System, ColecoVision, Tandy, TI's own 99/4A and a few other places.##sesd",
    {"Square 1##sesd", "Square 2##sesd", "Square 3##sesd", "Noise##sesd"},
    {"S1##sesd", "S2##sesd", "S3##sesd", "NO##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_NOISE},
    {DIV_INS_STD, DIV_INS_STD, DIV_INS_STD, DIV_INS_STD},
    {},
    {
      {0x20, {DIV_CMD_STD_NOISE_MODE, "20xy: Set noise mode (x: preset freq/ch3 freq; y: thin pulse/noise)##sesd"}}
    }
  );

  sysDefs[DIV_SYSTEM_SMS_OPLL]=new DivSysDef(
    "Sega Master System + FM Expansion", NULL, 0x43, 0x43, 13, true, true, 0, true, 0, 0, 0,
    "<COMPOUND SYSTEM!>##sesd2",
    {}, {}, {}, {}
  );

  sysDefs[DIV_SYSTEM_GB]=new DivSysDef(
    "Game Boy", NULL, 0x04, 0x04, 4, false, true, 0x161, false, 0, 32, 16,
    "the most popular portable game console of the era.##sesd",
    {"Pulse 1##sesd", "Pulse 2##sesd", "Wavetable##sesd", "Noise##sesd"},
    {"S1##sesd", "S2##sesd", "WA##sesd", "NO##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_WAVE, DIV_CH_NOISE},
    {DIV_INS_GB, DIV_INS_GB, DIV_INS_GB, DIV_INS_GB},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd1"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Set noise length (0: long; 1: short)##sesd"}},
      {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set duty cycle (0 to 3)##sesd"}},
      {0x13, {DIV_CMD_GB_SWEEP_TIME, "13xy: Setup sweep (x: time; y: shift)##sesd"}},
      {0x14, {DIV_CMD_GB_SWEEP_DIR, "14xx: Set sweep direction (0: up; 1: down)##sesd"}},
      {0x15, {DIV_CMD_WAVE_LOCAL, "15xx: Set waveform (local)##sesd"}}
    }
  );

  sysDefs[DIV_SYSTEM_PCE]=new DivSysDef(
    "PC Engine/TurboGrafx-16", NULL, 0x05, 0x05, 6, false, true, 0x161, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 32, 32,
    "an '80s game console with a wavetable sound chip, popular in Japan.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_PCE, DIV_INS_PCE, DIV_INS_PCE, DIV_INS_PCE, DIV_INS_PCE, DIV_INS_PCE},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd2"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Toggle noise mode##sesd0"}},
      {0x12, {DIV_CMD_PCE_LFO_MODE, "12xx: Setup LFO (0: disabled; 1: 1x depth; 2: 16x depth; 3: 256x depth)##sesd"}},
      {0x13, {DIV_CMD_PCE_LFO_SPEED, "13xx: Set LFO speed##sesd"}},
      {0x17, {DIV_CMD_SAMPLE_MODE, "17xx: Toggle PCM mode (LEGACY)##sesd1"}},
      {0x18, {DIV_CMD_WAVE_LOCAL, "18xx: Set waveform (local)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_NES]=new DivSysDef(
    "NES (Ricoh 2A03)", NULL, 0x06, 0x06, 5, false, true, 0x161, false, (1U<<DIV_SAMPLE_DEPTH_1BIT_DPCM)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "also known as Famicom in Japan, it's the most well-known game console of the '80s.##sesd",
    {"Pulse 1##sesd", "Pulse 2##sesd", "Triangle##sesd", "Noise##sesd", "DPCM##sesd"},
    {"S1##sesd", "S2##sesd", "TR##sesd", "NO##sesd", "DMC##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_WAVE, DIV_CH_NOISE, DIV_CH_PCM},
    {DIV_INS_NES, DIV_INS_NES, DIV_INS_NES, DIV_INS_NES, DIV_INS_NES},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    {
      {0x11, {DIV_CMD_NES_DMC, "11xx: Write to delta modulation counter (0 to 7F)##sesd"}},
      {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd0"}},
      {0x13, {DIV_CMD_NES_SWEEP, "13xy: Sweep up (x: time; y: shift)##sesd",constVal<0>,effectVal}},
      {0x14, {DIV_CMD_NES_SWEEP, "14xy: Sweep down (x: time; y: shift)##sesd",constVal<1>,effectVal}},
      {0x15, {DIV_CMD_NES_ENV_MODE, "15xx: Set envelope mode (0: envelope, 1: length, 2: looping, 3: constant)##sesd"}},
      {0x16, {DIV_CMD_NES_LENGTH, "16xx: Set length counter (refer to manual for a list of values)##sesd"}},
      {0x17, {DIV_CMD_NES_COUNT_MODE, "17xx: Set frame counter mode (0: 4-step, 1: 5-step)##sesd"}},
      {0x18, {DIV_CMD_SAMPLE_MODE, "18xx: Select PCM/DPCM mode (0: PCM; 1: DPCM)##sesd"}},
      {0x19, {DIV_CMD_NES_LINEAR_LENGTH, "19xx: Set triangle linear counter (0 to 7F; 80 and higher halt)##sesd"}},
      {0x20, {DIV_CMD_SAMPLE_FREQ, "20xx: Set DPCM frequency (0 to F)##sesd"}}
    }
  );

  sysDefs[DIV_SYSTEM_NES_VRC7]=new DivSysDef(
    "NES + Konami VRC7", NULL, 0x46, 0x46, 11, true, true, 0, true, 0, 0, 0,
    "<COMPOUND SYSTEM!>##sesd3",
    {}, {}, {}, {}
  );

  sysDefs[DIV_SYSTEM_NES_FDS]=new DivSysDef(
    "Famicom Disk System", NULL, 0, 0x86, 6, false, true, 0, true, 0, 0, 0,
    "<COMPOUND SYSTEM!>##sesd4",
    {}, {}, {}, {}
  );

  sysDefs[DIV_SYSTEM_C64_6581]=new DivSysDef(
    "Commodore 64 (C64, 6581 SID)", NULL, 0x47, 0x47, 3, false, true, 0, false, 0, 0, 0,
    "this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd"},
    {DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_C64, DIV_INS_C64, DIV_INS_C64},
    {},
    {},
    c64PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_C64_8580]=new DivSysDef(
    "Commodore 64 (C64, 8580 SID)", NULL, 0x07, 0x07, 3, false, true, 0, false, 0, 0, 0,
    "this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.\nthis is the newer revision of the chip.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd"},
    {DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_C64, DIV_INS_C64, DIV_INS_C64},
    {},
    {},
    c64PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_ARCADE]=new DivSysDef(
    "DefleCade", NULL, 0x08, 0x08, 13, true, false, 0, true, 0, 0, 0,
    "<COMPOUND SYSTEM!>##sesd5",
    {}, {}, {}, {}
  );

  sysDefs[DIV_SYSTEM_YM2610]=new DivSysDef(
    "Neo Geo CD", NULL, 0x09, 0x09, 13, true, true, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd"},
    {"F1", "F2", "F3", "F4", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    fmEffectHandlerMap,
    fmOPNAPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2610_EXT]=new DivSysDef(
    "Neo Geo CD Extended Channel 2##sesd", NULL, 0x49, 0x49, 16, true, true, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd",
    {"FM 1", "FM 2 OP1", "FM 2 OP2", "FM 2 OP3", "FM 2 OP4", "FM 3", "FM 4", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd"},
    {"F1", "O1", "O2", "O3", "O4", "F3", "F4", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd"},
    {DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_AY8910]=new DivSysDef(
    "AY-3-8910", NULL, 0x80, 0, 3, false, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip is everywhere! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nthe discovery of envelope bass helped it beat the SN76489 with ease.##sesd",
    {"PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd"},
    {"S1##sesd", "S2##sesd", "S3##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_AY, DIV_INS_AY, DIV_INS_AY},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    ayPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_AMIGA]=new DivSysDef(
    "Amiga", NULL, 0x81, 0, 4, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 256,
    "a computer from the '80s with full sampling capabilities, giving it a sound ahead of its time.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    {},
    {
      {0x10, {DIV_CMD_AMIGA_FILTER, "10xx: Toggle filter (0 disables; 1 enables)##sesd"}},
      {0x11, {DIV_CMD_AMIGA_AM, "11xx: Toggle AM with next channel##sesd"}},
      {0x12, {DIV_CMD_AMIGA_PM, "12xx: Toggle period modulation with next channel##sesd"}},
      {0x13, {DIV_CMD_WAVE, "13xx: Set waveform##sesd"}},
      {0x14, {DIV_CMD_WAVE_LOCAL, "14xx: Set waveform (local)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_YM2151]=new DivSysDef(
    "Yamaha YM2151 (OPM)", NULL, 0x82, 0, 8, true, false, 0x150, false, 0, 0, 0,
    "this was Yamaha's first integrated FM chip.\nit was used in several synthesizers, computers and arcade boards.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPM, DIV_INS_OPM, DIV_INS_OPM, DIV_INS_OPM, DIV_INS_OPM, DIV_INS_OPM, DIV_INS_OPM, DIV_INS_OPM},
    {},
    fmEffectHandlerMap,
    fmOPMPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2612]=new DivSysDef(
    "Yamaha YM2612 (OPN2)", NULL, 0x83, 0, 6, true, false, 0x150, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6"},
    {"F1", "F2", "F3", "F4", "F5", "F6"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    fmOPN2EffectHandlerMap,
    fmOPN2PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_TIA]=new DivSysDef(
    "Atari 2600 (TIA)", NULL, 0x84, 0, 2, false, true, 0, false, 0, 0, 0,
    "it's a challenge to make music on this chip which barely has musical capabilities...##sesd",
    {"Channel 1##sesd", "Channel 2##sesd"},
    {"CH1##sesd", "CH2##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_TIA, DIV_INS_TIA},
    {},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd0"}},
      {0x11, {DIV_CMD_RAW_FREQ, "11xx: Set raw period (0-1F)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_SAA1099]=new DivSysDef(
    "Philips SAA1099", NULL, 0x97, 0, 6, false, true, 0x171, false, 0, 0, 0,
    "supposedly an upgrade from the AY-3-8910, this was present on the Creative Music System (Game Blaster) and SAM Coupé.##sesd",
    {"PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "PSG 4##sesd", "PSG 5##sesd", "PSG 6##sesd"},
    {"S1##sesd", "S2##sesd", "S3##sesd", "S4##sesd", "S5##sesd", "S6##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_SAA1099, DIV_INS_SAA1099, DIV_INS_SAA1099, DIV_INS_SAA1099, DIV_INS_SAA1099, DIV_INS_SAA1099},
    {},
    {},
    {
      {0x10, {DIV_CMD_STD_NOISE_MODE, "10xy: Set channel mode (x: noise; y: tone)##sesd"}},
      {0x11, {DIV_CMD_STD_NOISE_FREQ, "11xx: Set noise frequency##sesd"}},
      {0x12, {DIV_CMD_SAA_ENVELOPE, "12xx: Setup envelope (refer to docs for more information)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_AY8930]=new DivSysDef(
    "Microchip AY8930", NULL, 0x9a, 0, 3, false, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "an improved version of the AY-3-8910 with a bigger frequency range, duty cycles, configurable noise and per-channel envelopes!##sesd",
    {"PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd"},
    {"S1##sesd", "S2##sesd", "S3##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_AY8930, DIV_INS_AY8930, DIV_INS_AY8930},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    ay8930PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_VIC20]=new DivSysDef(
    "Commodore VIC-20", NULL, 0x85, 0, 4, false, true, 0, false, 0, 0, 0,
    "Commodore's successor to the PET.\nits square wave channels are more than just square...##sesd",
    {"Low", "Mid", "High", "Noise##sesd"},
    {"LO", "MID", "HI", "NO##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_NOISE},
    {DIV_INS_VIC, DIV_INS_VIC, DIV_INS_VIC, DIV_INS_VIC},
    {},
    waveOnlyEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_PET]=new DivSysDef(
    "Commodore PET", NULL, 0x86, 0, 1, false, true, 0, false, 0, 0, 0,
    "one channel of 1-bit wavetable which is better (and worse) than the PC Speaker.##sesd",
    {"Wave##sesd"},
    {"PET"},
    {DIV_CH_PULSE},
    {DIV_INS_PET},
    {},
    waveOnlyEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_SNES]=new DivSysDef(
    "SNES", NULL, 0x87, 0, 8, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_BRR, 0, 16,
    "FM? nah... samples! Nintendo's answer to Sega.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_SNES, DIV_INS_SNES, DIV_INS_SNES, DIV_INS_SNES, DIV_INS_SNES, DIV_INS_SNES, DIV_INS_SNES, DIV_INS_SNES},
    {},
    {
      {0x18, {DIV_CMD_SNES_ECHO_ENABLE, "18xx: Enable echo buffer##sesd"}},
      {0x19, {DIV_CMD_SNES_ECHO_DELAY, "19xx: Set echo delay (0 to F)##sesd"}},
      {0x1a, {DIV_CMD_SNES_ECHO_VOL_LEFT, "1Axx: Set left echo volume##sesd"}},
      {0x1b, {DIV_CMD_SNES_ECHO_VOL_RIGHT, "1Bxx: Set right echo volume##sesd"}},
      {0x1c, {DIV_CMD_SNES_ECHO_FEEDBACK, "1Cxx: Set echo feedback##sesd"}},
      {0x1e, {DIV_CMD_SNES_GLOBAL_VOL_LEFT, "1Exx: Set dry output volume (left)##sesd"}},
      {0x1f, {DIV_CMD_SNES_GLOBAL_VOL_RIGHT, "1Fxx: Set dry output volume (right)##sesd"}},
      {0x30, {DIV_CMD_SNES_ECHO_FIR, "30xx: Set echo filter coefficient 0##sesd",constVal<0>,effectVal}},
      {0x31, {DIV_CMD_SNES_ECHO_FIR, "31xx: Set echo filter coefficient 1##sesd",constVal<1>,effectVal}},
      {0x32, {DIV_CMD_SNES_ECHO_FIR, "32xx: Set echo filter coefficient 2##sesd",constVal<2>,effectVal}},
      {0x33, {DIV_CMD_SNES_ECHO_FIR, "33xx: Set echo filter coefficient 3##sesd",constVal<3>,effectVal}},
      {0x34, {DIV_CMD_SNES_ECHO_FIR, "34xx: Set echo filter coefficient 4##sesd",constVal<4>,effectVal}},
      {0x35, {DIV_CMD_SNES_ECHO_FIR, "35xx: Set echo filter coefficient 5##sesd",constVal<5>,effectVal}},
      {0x36, {DIV_CMD_SNES_ECHO_FIR, "36xx: Set echo filter coefficient 6##sesd",constVal<6>,effectVal}},
      {0x37, {DIV_CMD_SNES_ECHO_FIR, "37xx: Set echo filter coefficient 7##sesd",constVal<7>,effectVal}},
    },
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd3"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Toggle noise mode##sesd1"}},
      {0x12, {DIV_CMD_SNES_ECHO, "12xx: Toggle echo on this channel##sesd"}},
      {0x13, {DIV_CMD_SNES_PITCH_MOD, "13xx: Toggle pitch modulation##sesd"}},
      {0x14, {DIV_CMD_SNES_INVERT, "14xy: Toggle invert (x: left; y: right)##sesd"}},
      {0x15, {DIV_CMD_SNES_GAIN_MODE, "15xx: Set envelope mode (0: ADSR, 1: gain/direct, 2: dec, 3: exp, 4: inc, 5: bent)##sesd"}},
      {0x16, {DIV_CMD_SNES_GAIN, "16xx: Set gain (00 to 7F if direct; 00 to 1F otherwise)##sesd"}},
      {0x17, {DIV_CMD_WAVE_LOCAL, "17xx: Set waveform (local)##sesd"}},
      {0x1d, {DIV_CMD_STD_NOISE_FREQ, "1Dxx: Set noise frequency (00 to 1F)##sesd"}},
      {0x20, {DIV_CMD_FM_AR, "20xx: Set attack (0 to F)##sesd"}},
      {0x21, {DIV_CMD_FM_DR, "21xx: Set decay (0 to 7)##sesd"}},
      {0x22, {DIV_CMD_FM_SL, "22xx: Set sustain (0 to 7)##sesd"}},
      {0x23, {DIV_CMD_FM_RR, "23xx: Set release (00 to 1F)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_VRC6]=new DivSysDef(
    "Konami VRC6", NULL, 0x88, 0, 3, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "an expansion chip for the Famicom, featuring a quirky sawtooth channel.##sesd",
    {"VRC6 1", "VRC6 2", "VRC6 Saw##sesd"},
    {"V1", "V2", "VS##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_WAVE},
    {DIV_INS_VRC6, DIV_INS_VRC6, DIV_INS_VRC6_SAW},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_NULL},
    {
      {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set duty cycle (pulse: 0 to 7)##sesd"}},
      {0x17, {DIV_CMD_SAMPLE_MODE, "17xx: Toggle PCM mode (LEGACY)##sesd2"}},
    }
  );

  sysDefs[DIV_SYSTEM_OPLL]=new DivSysDef(
    "Yamaha YM2413 (OPLL)", NULL, 0x89, 0, 9, true, false, 0x150, false, 0, 0, 0,
    "cost-reduced version of the OPL with 16 patches and only one of them is user-configurable.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8", "FM 9"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL},
    {},
    fmEffectHandlerMap,
    fmOPLLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_FDS]=new DivSysDef(
    "Famicom Disk System (chip)##sesd", NULL, 0x8a, 0, 1, false, true, 0x161, false, 0, 64, 64,
    "a disk drive for the Famicom which also contains one wavetable channel.##sesd",
    {"FDS"},
    {"FDS"},
    {DIV_CH_WAVE},
    {DIV_INS_FDS},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd4"}},
      {0x11, {DIV_CMD_FDS_MOD_DEPTH, "11xx: Set modulation depth##sesd"}},
      {0x12, {DIV_CMD_FDS_MOD_HIGH, "12xy: Set modulation speed high byte (x: enable; y: value)##sesd"}},
      {0x13, {DIV_CMD_FDS_MOD_LOW, "13xx: Set modulation speed low byte##sesd"}},
      {0x14, {DIV_CMD_FDS_MOD_POS, "14xx: Set modulator position##sesd"}},
      {0x15, {DIV_CMD_FDS_MOD_WAVE, "15xx: Set modulator table to waveform##sesd"}},
      {0x16, {DIV_CMD_WAVE_LOCAL, "16xx: Set waveform (local)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_MMC5]=new DivSysDef(
    "MMC5", NULL, 0x8b, 0, 3, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "an expansion chip for the Famicom, featuring a little-known PCM channel.##sesd",
    {"Pulse 1##sesd", "Pulse 2##sesd", "PCM##sesd"},
    {"S1##sesd", "S2##sesd", "PCM##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM},
    {DIV_INS_NES, DIV_INS_NES, DIV_INS_AMIGA},
    {},
    {
      {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd1"}},
    }
  );

  sysDefs[DIV_SYSTEM_N163]=new DivSysDef(
    "Namco 163", NULL, 0x8c, 0, 8, false, true, 0, false, 0, 0, 16,
    "an expansion chip for the Famicom, with full wavetable.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_N163, DIV_INS_N163, DIV_INS_N163, DIV_INS_N163, DIV_INS_N163, DIV_INS_N163, DIV_INS_N163, DIV_INS_N163},
    {},
    {
      {0x18, {DIV_CMD_N163_CHANNEL_LIMIT, "18xx: Change channel limits (0 to 7, x + 1)##sesd"}},
      {0x20, {DIV_CMD_N163_GLOBAL_WAVE_LOAD, "20xx: Load a waveform into memory##sesd"}},
      {0x21, {DIV_CMD_N163_GLOBAL_WAVE_LOADPOS, "21xx: Set position for wave load##sesd"}}
    },
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Select waveform##sesd"}},
      {0x11, {DIV_CMD_N163_WAVE_POSITION, "11xx: Set waveform position in RAM##sesd"}},
      {0x12, {DIV_CMD_N163_WAVE_LENGTH, "12xx: Set waveform length in RAM (04 to FC in steps of 4)##sesd"}},
      {0x15, {DIV_CMD_N163_WAVE_LOADPOS, "15xx: Set waveform load position##sesd"}},
      {0x16, {DIV_CMD_N163_WAVE_LOADLEN, "16xx: Set waveform load length (04 to FC in steps of 4)##sesd"}},
      {0x17, {DIV_CMD_WAVE_LOCAL, "17xx: Select waveform (local)##sesd1"}},
    }
  );

  sysDefs[DIV_SYSTEM_YM2203]=new DivSysDef(
    "Yamaha YM2203 (OPN)", NULL, 0x8d, 0, 6, true, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)##sesd",
    {"FM 1", "FM 2", "FM 3", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd"},
    {"F1", "F2", "F3", "S1##sesd", "S2##sesd", "S3##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY},
    {},
    fmEffectHandlerMap,
    fmOPNPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2203_EXT]=new DivSysDef(
    "Yamaha YM2203 (OPN) Extended Channel 3##sesd", NULL, 0xb6, 0, 9, true, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "S1##sesd", "S2##sesd", "S3##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY},
    {},
    {},
    fmOPNPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2203_CSM]=new DivSysDef(
    "Yamaha YM2203 (OPN) CSM", NULL, 0xc3, 0, 10, true, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "CSM Timer##sesd", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "CSM", "S1##sesd", "S2##sesd", "S3##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_NOISE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY},
    {},
    {},
    fmOPNPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2608]=new DivSysDef(
    "Yamaha YM2608 (OPNA)", NULL, 0x8e, 0, 16, true, true, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "Square 1##sesd", "Square 2##sesd", "Square 3##sesd", "Kick##sesd", "Snare##sesd", "Top##sesd", "HiHat##sesd", "Tom##sesd", "Rim##sesd", "ADPCM##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "S1##sesd", "S2##sesd", "S3##sesd", "BD##sesd", "SD##sesd", "TP##sesd", "HH##sesd", "TM##sesd", "RM##sesd", "P##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    fmEffectHandlerMap,
    fmOPNAPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2608_EXT]=new DivSysDef(
    "Yamaha YM2608 (OPNA) Extended Channel 3##sesd", NULL, 0xb7, 0, 19, true, true, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6", "Square 1##sesd", "Square 2##sesd", "Square 3##sesd", "Kick##sesd", "Snare##sesd", "Top##sesd", "HiHat##sesd", "Tom##sesd", "Rim##sesd", "ADPCM##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "F6", "S1##sesd", "S2##sesd", "S3##sesd", "BD##sesd", "SD##sesd", "TP##sesd", "HH##sesd", "TM##sesd", "RM##sesd", "P##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2608_CSM]=new DivSysDef(
    "Yamaha YM2608 (OPNA) Extended Channel 3 and CSM##sesd", NULL, 0xc4, 0, 20, true, true, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6", "CSM Timer##sesd", "Square 1##sesd", "Square 2##sesd", "Square 3##sesd", "Kick##sesd", "Snare##sesd", "Top##sesd", "HiHat##sesd", "Tom##sesd", "Rim##sesd", "ADPCM##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "F6", "CSM", "S1##sesd", "S2##sesd", "S3##sesd", "BD##sesd", "SD##sesd", "TP##sesd", "HH##sesd", "TM##sesd", "RM##sesd", "P##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPL]=new DivSysDef(
    "Yamaha YM3526 (OPL)", NULL, 0x8f, 0, 9, true, false, 0x151, false, 0, 0, 0,
    "OPN, but what if you only had two operators, no stereo, no detune and a lower ADSR parameter range?##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8", "FM 9"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL},
    {},
    fmEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPL2]=new DivSysDef(
    "Yamaha YM3812 (OPL2)", NULL, 0x90, 0, 9, true, false, 0x151, false, 0, 0, 0,
    "OPL, but what if you had more waveforms to choose than the normal sine?##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8", "FM 9"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL},
    {},
    fmEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPL3]=new DivSysDef(
    "Yamaha YMF262 (OPL3)", NULL, 0x91, 0, 18, true, false, 0x151, false, 0, 0, 0,
    "OPL2, but what if you had twice the channels, 4-op mode, stereo and even more waveforms?##sesd",
    {"4OP 1##sesd", "FM 2", "4OP 3##sesd", "FM 4", "4OP 5##sesd", "FM 6", "4OP 7##sesd", "FM 8", "4OP 9##sesd", "FM 10", "4OP 11##sesd", "FM 12", "FM 13", "FM 14", "FM 15", "FM 16", "FM 17", "FM 18"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18"},
    {DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL},
    {},
    fmEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  // TODO: add 12-bit and 16-bit big endian formats
  sysDefs[DIV_SYSTEM_MULTIPCM]=new DivSysDef(
    "MultiPCM", NULL, 0x92, 0, 28, false, true, 0, false, (1U<<DIV_SAMPLE_DEPTH_8BIT)|(1U<<DIV_SAMPLE_DEPTH_16BIT), 0, 0,
    "how many channels of PCM do you want?\nMultiPCM: yes##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd", "Channel 17##sesd", "Channel 18##sesd", "Channel 19##sesd", "Channel 20##sesd", "Channel 21##sesd", "Channel 22##sesd", "Channel 23##sesd", "Channel 24##sesd", "Channel 25##sesd", "Channel 26##sesd", "Channel 27##sesd", "Channel 28##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM}
  );

  sysDefs[DIV_SYSTEM_PCSPKR]=new DivSysDef(
    "PC Speaker##sesd", NULL, 0x93, 0, 1, false, true, 0, false, 0, 0, 0,
    "good luck! you get one square and no volume control.##sesd",
    {"Square##sesd"},
    {"SQ##sesd"},
    {DIV_CH_PULSE},
    {DIV_INS_BEEPER}
  );

  sysDefs[DIV_SYSTEM_PONG]=new DivSysDef(
    "Pong", NULL, 0xfc, 0, 1, false, true, 0, false, 0, 0, 0,
    "please don't use this chip. it was added as a joke.##sesd",
    {"Square##sesd"},
    {"SQ##sesd"},
    {DIV_CH_PULSE},
    {DIV_INS_BEEPER}
  );

  sysDefs[DIV_SYSTEM_POKEY]=new DivSysDef(
    "POKEY", NULL, 0x94, 0, 4, false, true, 0x161, false, 0, 0, 0,
    "TIA, but better and more flexible.\nused in the Atari 8-bit family of computers (400/800/XL/XE).##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_POKEY, DIV_INS_POKEY, DIV_INS_POKEY, DIV_INS_POKEY},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform (0 to 7)##sesd0"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Set AUDCTL##sesd"}},
      {0x12, {DIV_CMD_STD_NOISE_FREQ, "12xx: Toggle two-tone mode##sesd"}},
      {0x13, {DIV_CMD_RAW_FREQ, "13xx: Set raw period##sesd"}},
      {0x14, {DIV_CMD_RAW_FREQ_HIGHER_BYTE, "14xx: Set raw period (higher byte; only for 16-bit mode)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_RF5C68]=new DivSysDef(
    "Ricoh RF5C68", NULL, 0x95, 0, 8, false, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this is like SNES' sound chip but without interpolation and the rest of nice bits.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_RF5C68, DIV_INS_RF5C68, DIV_INS_RF5C68, DIV_INS_RF5C68, DIV_INS_RF5C68, DIV_INS_RF5C68, DIV_INS_RF5C68, DIV_INS_RF5C68},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA}
  );

  sysDefs[DIV_SYSTEM_SWAN]=new DivSysDef(
    "WonderSwan", NULL, 0x96, 0, 4, false, true, 0x171, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 32, 16,
    "developed by the makers of the Game Boy and the Virtual Boy...##sesd",
    {"Wave##sesd", "Wave/PCM", "Wave/Sweep", "Wave/Noise"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_WAVE, DIV_CH_PCM, DIV_CH_WAVE, DIV_CH_NOISE},
    {DIV_INS_SWAN, DIV_INS_SWAN, DIV_INS_SWAN, DIV_INS_SWAN},
    {DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_NULL, DIV_INS_NULL},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd5"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Setup noise mode (0: disabled; 1-8: enabled/tap)##sesd"}},
      {0x12, {DIV_CMD_WS_SWEEP_TIME, "12xx: Setup sweep period (0: disabled; 1-20: enabled/period)##sesd"}},
      {0x13, {DIV_CMD_WS_SWEEP_AMOUNT, "13xx: Set sweep amount##sesd"}},
      {0x17, {DIV_CMD_SAMPLE_MODE, "17xx: Toggle PCM mode (LEGACY)##sesd3"}},
      {0x18, {DIV_CMD_WAVE_LOCAL, "18xx: Set waveform (local)##sesd1"}},
    }
  );

  sysDefs[DIV_SYSTEM_OPZ]=new DivSysDef(
    "Yamaha YM2414 (OPZ)", NULL, 0x98, 0, 8, true, false, 0, false, 0, 0, 0,
    "like OPM, but with more waveforms, fixed frequency mode and totally... undocumented.\nused in the Yamaha TX81Z and some other synthesizers.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPZ, DIV_INS_OPZ, DIV_INS_OPZ, DIV_INS_OPZ, DIV_INS_OPZ, DIV_INS_OPZ, DIV_INS_OPZ, DIV_INS_OPZ},
    {},
    {
      {0x2f, {DIV_CMD_FM_HARD_RESET, "2Fxx: Toggle hard envelope reset on new notes##sesd"}},
    },
    fmOPZPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_POKEMINI]=new DivSysDef(
    "Pokémon Mini", NULL, 0x99, 0, 1, false, true, 0, false, 0, 0, 0,
    "this one is like PC Speaker but has duty cycles.##sesd",
    {"Pulse##sesd"},
    {"P##sesd"},
    {DIV_CH_PULSE},
    {DIV_INS_POKEMINI}
  );

  sysDefs[DIV_SYSTEM_SEGAPCM]=new DivSysDef(
    "SegaPCM", NULL, 0x9b, 0, 16, false, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "used in some Sega arcade boards (like OutRun), and usually paired with a YM2151.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    segaPCMPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_VBOY]=new DivSysDef(
    "Virtual Boy", NULL, 0x9c, 0, 6, false, true, 0x171, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 32, 64,
    "a console which failed to sell well due to its headache-inducing features.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Noise##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "NO##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_NOISE},
    {DIV_INS_VBOY, DIV_INS_VBOY, DIV_INS_VBOY, DIV_INS_VBOY, DIV_INS_VBOY, DIV_INS_VBOY},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd6"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Set noise length (0 to 7)##sesd"}},
      {0x12, {DIV_CMD_STD_NOISE_FREQ, "12xy: Setup envelope (x: enabled/loop (1: enable, 3: enable+loop); y: speed/direction (0-7: down, 8-F: up))##sesd"}},
      {0x13, {DIV_CMD_GB_SWEEP_TIME, "13xy: Setup sweep (x: speed; y: shift; channel 5 only)##sesd"}},
      {0x14, {DIV_CMD_FDS_MOD_DEPTH, "14xy: Setup modulation (x: enabled/loop (1: enable, 3: enable+loop); y: speed; channel 5 only)##sesd"}},
      {0x15, {DIV_CMD_FDS_MOD_WAVE, "15xx: Set modulation waveform (x: wavetable; channel 5 only)##sesd"}},
      {0x16, {DIV_CMD_WAVE_LOCAL, "16xx: Set waveform (local)##sesd1"}},
    }
  );

  sysDefs[DIV_SYSTEM_VRC7]=new DivSysDef(
    "Konami VRC7", NULL, 0x9d, 0, 6, true, false, 0x151, false, 0, 0, 0,
    "like OPLL, but even more cost reductions applied. three less FM channels, and no drums mode...##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6"},
    {"F1", "F2", "F3", "F4", "F5", "F6"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL},
    {},
    fmEffectHandlerMap,
    fmOPLLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2610B]=new DivSysDef(
    "Yamaha YM2610B (OPNB2)", NULL, 0x9e, 0, 16, true, false, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd", "ADPCM-B##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "B"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    fmEffectHandlerMap,
    fmOPNAPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_SFX_BEEPER]=new DivSysDef(
    "ZX Spectrum Beeper##sesd", NULL, 0x9f, 0, 6, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "the ZX Spectrum only had a basic beeper capable of...\n...a bunch of thin pulses and tons of other interesting stuff!\nFurnace provides a thin pulse system.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_BEEPER, DIV_INS_BEEPER, DIV_INS_BEEPER, DIV_INS_BEEPER, DIV_INS_BEEPER, DIV_INS_BEEPER},
    {},
    {
      {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set pulse width##sesd0"}},
      {0x17, {DIV_CMD_SAMPLE_MODE, "17xx: Trigger overlay drum##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_YM2612_EXT]=new DivSysDef(
    "Yamaha YM2612 (OPN2) Extended Channel 3##sesd", NULL, 0xa0, 0, 9, true, false, 0x150, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "F6"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    fmOPN2EffectHandlerMap,
    fmOPN2PostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2612_CSM]=new DivSysDef(
    "Yamaha YM2612 (OPN2) CSM", NULL, 0xc1, 0, 10, true, false, 0x150, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one includes CSM mode control for special effects on Channel 3.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6", "CSM Timer##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "F6", "CSM"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_NULL},
    fmOPN2EffectHandlerMap,
    fmOPN2PostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_SCC]=new DivSysDef(
    "Konami SCC", NULL, 0xa1, 0, 5, false, true, 0x161, false, 0, 32, 256,
    "a wavetable chip made by Konami for use with the MSX.\nthe last channel shares its wavetable with the previous one though.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_SCC, DIV_INS_SCC, DIV_INS_SCC, DIV_INS_SCC, DIV_INS_SCC},
    {},
    waveOnlyEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPL_DRUMS]=new DivSysDef(
    "Yamaha YM3526 (OPL) with drums##sesd", NULL, 0xa2, 0, 11, true, false, 0x151, false, 0, 0, 0,
    "the OPL chip but with drums mode enabled.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "Kick/FM 7##sesd", "Snare##sesd", "Tom##sesd", "Top##sesd", "HiHat##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "BD##sesd", "SD##sesd", "TM##sesd", "TP##sesd", "HH##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL},
    fmOPLDrumsEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPL2_DRUMS]=new DivSysDef(
    "Yamaha YM3812 (OPL2) with drums##sesd", NULL, 0xa3, 0, 11, true, false, 0x151, false, 0, 0, 0,
    "the OPL2 chip but with drums mode enabled.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "Kick/FM 7##sesd", "Snare##sesd", "Tom##sesd", "Top##sesd", "HiHat##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "BD##sesd", "SD##sesd", "TM##sesd", "TP##sesd", "HH##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL},
    fmOPLDrumsEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPL3_DRUMS]=new DivSysDef(
    "Yamaha YMF262 (OPL3) with drums##sesd", NULL, 0xa4, 0, 20, true, false, 0x151, false, 0, 0, 0,
    "the OPL3 chip but with drums mode enabled.##sesd",
    {"4OP 1##sesd", "FM 2", "4OP 3##sesd", "FM 4", "4OP 5##sesd", "FM 6", "4OP 7##sesd", "FM 8", "4OP 9##sesd", "FM 10", "4OP 11##sesd", "FM 12", "FM 13", "FM 14", "FM 15", "Kick/FM 16##sesd", "Snare##sesd", "Tom##sesd", "Top##sesd", "HiHat##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "BD##sesd", "SD##sesd", "TM##sesd", "TP##sesd", "HH##sesd"},
    {DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL},
    fmOPLDrumsEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2610_FULL]=new DivSysDef(
    "Yamaha YM2610 (OPNB)", NULL, 0xa5, 0, 14, true, false, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd", "ADPCM-B##sesd"},
    {"F1", "F2", "F3", "F4", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "B"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    fmEffectHandlerMap,
    fmOPNAPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2610_FULL_EXT]=new DivSysDef(
    "Yamaha YM2610 (OPNB) Extended Channel 2##sesd", NULL, 0xa6, 0, 17, true, false, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd",
    {"FM 1", "FM 2 OP1", "FM 2 OP2", "FM 2 OP3", "FM 2 OP4", "FM 3", "FM 4", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd", "ADPCM-B##sesd"},
    {"F1", "O1", "O2", "O3", "O4", "F3", "F4", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "B"},
    {DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2610_CSM]=new DivSysDef(
    "Yamaha YM2610 (OPNB) CSM", NULL, 0xc2, 0, 18, true, false, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 2.##sesd",
    {"FM 1", "FM 2 OP1", "FM 2 OP2", "FM 2 OP3", "FM 2 OP4", "FM 3", "FM 4", "CSM Timer##sesd", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd", "ADPCM-B##sesd"},
    {"F1", "O1", "O2", "O3", "O4", "F3", "F4", "CSM", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "B"},
    {DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_OPLL_DRUMS]=new DivSysDef(
    "Yamaha YM2413 (OPLL) with drums##sesd", NULL, 0xa7, 0, 11, true, false, 0x150, false, 0, 0, 0,
    "the OPLL chip but with drums mode turned on.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "Kick##sesd", "Snare##sesd", "Tom##sesd", "Top##sesd", "HiHat##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "BD##sesd", "SD##sesd", "TM##sesd", "TP##sesd", "HH##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL, DIV_INS_OPLL},
    {},
    fmOPLDrumsEffectHandlerMap,
    fmOPLLPostEffectHandlerMap
  );

  EffectHandlerMap lynxEffectHandlerMap;
  const EffectHandler lynxLFSRHandler(DIV_CMD_LYNX_LFSR_LOAD, "3xxx: Load LFSR (0 to FFF)##sesd", effectValLong<12>);
  for (int i=0; i<16; i++) {
    lynxEffectHandlerMap.emplace(0x30+i, lynxLFSRHandler);
  }

  sysDefs[DIV_SYSTEM_LYNX]=new DivSysDef(
    "Atari Lynx (MIKEY)", NULL, 0xa8, 0, 4, false, true, 0x172, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "a portable console made by Atari. it has all of Atari's trademark waveforms.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_MIKEY, DIV_INS_MIKEY, DIV_INS_MIKEY, DIV_INS_MIKEY},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    lynxEffectHandlerMap
  );

  EffectHandlerMap qSoundEffectHandlerMap={
      {0x10, {DIV_CMD_QSOUND_ECHO_FEEDBACK, "10xx: Set echo feedback level (00 to FF)##sesd"}},
      {0x11, {DIV_CMD_QSOUND_ECHO_LEVEL, "11xx: Set channel echo level (00 to FF)##sesd"}},
      {0x12, {DIV_CMD_QSOUND_SURROUND, "12xx: Toggle QSound algorithm (0: disabled; 1: enabled)##sesd"}},
  };
  const EffectHandler qSoundEchoDelayHandler(DIV_CMD_QSOUND_ECHO_DELAY, "3xxx: Set echo delay buffer length (000 to AA5)##sesd", effectValLong<12>);
  for (int i=0; i<16; i++) {
    qSoundEffectHandlerMap.emplace(0x30+i, qSoundEchoDelayHandler);
  }

  sysDefs[DIV_SYSTEM_QSOUND]=new DivSysDef(
    "Capcom QSound", NULL, 0xe0, 0, 19, false, true, 0x161, false, (1U<<DIV_SAMPLE_DEPTH_QSOUND_ADPCM)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "used in some of Capcom's arcade boards. surround-like sampled sound with echo.##sesd",
    {"PCM 1##sesd", "PCM 2##sesd", "PCM 3##sesd", "PCM 4##sesd", "PCM 5##sesd", "PCM 6##sesd", "PCM 7##sesd", "PCM 8##sesd", "PCM 9##sesd", "PCM 10##sesd", "PCM 11##sesd", "PCM 12##sesd", "PCM 13##sesd", "PCM 14##sesd", "PCM 15##sesd", "PCM 16##sesd", "ADPCM 1##sesd", "ADPCM 2##sesd", "ADPCM 3##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "A1", "A2", "A3"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND, DIV_INS_QSOUND},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    qSoundEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_VERA]=new DivSysDef(
    "VERA", NULL, 0xac, 0, 17, false, true, 0, false, (1U<<DIV_SAMPLE_DEPTH_8BIT)|(1U<<DIV_SAMPLE_DEPTH_16BIT), 0, 0,
    "the chip used in a computer design created by The 8-Bit Guy.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd", "PCM##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "PCM##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM},
    {DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_VERA, DIV_INS_AMIGA},
    {},
    {
      {0x20, {DIV_CMD_WAVE, "20xx: Set waveform##sesd"}},
      {0x22, {DIV_CMD_STD_NOISE_MODE, "22xx: Set duty cycle (0 to 3F)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_YM2610B_EXT]=new DivSysDef(
    "Yamaha YM2610B (OPNB2) Extended Channel 3##sesd", NULL, 0xde, 0, 19, true, false, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd", "ADPCM-B##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "F6", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "B"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2610B_CSM]=new DivSysDef(
    "Yamaha YM2610B (OPNB2) CSM", NULL, 0xc5, 0, 20, true, false, 0x151, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_A)|(1U<<DIV_SAMPLE_DEPTH_ADPCM_B)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6", "CSM Timer##sesd", "PSG 1##sesd", "PSG 2##sesd", "PSG 3##sesd", "ADPCM-A 1##sesd", "ADPCM-A 2##sesd", "ADPCM-A 3##sesd", "ADPCM-A 4##sesd", "ADPCM-A 5##sesd", "ADPCM-A 6##sesd", "ADPCM-B##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "F6", "CSM", "S1##sesd", "S2##sesd", "S3##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "B"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AY, DIV_INS_AY, DIV_INS_AY, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMA, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    fmOPNAPostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_SEGAPCM_COMPAT]=new DivSysDef(
    "SegaPCM (compatible 5-channel mode)##sesd", NULL, 0xa9, 0, 5, false, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this is the same thing as SegaPCM, but only exposes 5 of the channels for compatibility with DefleMask.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd"},
    {"P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM, DIV_INS_SEGAPCM},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    segaPCMPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_X1_010]=new DivSysDef(
    "Seta/Allumer X1-010", NULL, 0xb0, 0, 16, false, true, 0x171, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 128, 256,
    "a sound chip used in several Seta/Allumer-manufactured arcade boards with too many channels of wavetable sound, which also are capable of sampled sound.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010, DIV_INS_X1_010},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd7"}},
      {0x11, {DIV_CMD_X1_010_ENVELOPE_SHAPE, "11xx: Set envelope shape##sesd"}},
      {0x12, {DIV_CMD_X1_010_SAMPLE_BANK_SLOT, "12xx: Set sample bank slot (0 to 7)##sesd"}},
      {0x17, {DIV_CMD_SAMPLE_MODE, "17xx: Toggle PCM mode (LEGACY)##sesd4"}},
      {0x18, {DIV_CMD_WAVE_LOCAL, "18xx: Set waveform (local)##sesd2"}},
    },
    {
      {0x20, {DIV_CMD_SAMPLE_FREQ, "20xx: Set PCM frequency (1 to FF)##sesd"}},
      {0x22, {DIV_CMD_X1_010_ENVELOPE_MODE, "22xx: Set envelope mode (bit 0: enable; bit 1: one-shot; bit 2: split shape to L/R; bit 3/5: H.invert right/left; bit 4/6: V.invert right/left)##sesd"}},
      {0x23, {DIV_CMD_X1_010_ENVELOPE_PERIOD, "23xx: Set envelope period##sesd"}},
      {0x25, {DIV_CMD_X1_010_ENVELOPE_SLIDE, "25xx: Envelope slide up##sesd1"}},
      {0x26, {DIV_CMD_X1_010_ENVELOPE_SLIDE, "26xx: Envelope slide down##sesd1", negEffectVal}},
      {0x29, {DIV_CMD_X1_010_AUTO_ENVELOPE, "29xy: Set auto-envelope (x: numerator; y: denominator)##sesd1"}},
    }
  );

  sysDefs[DIV_SYSTEM_BUBSYS_WSG]=new DivSysDef(
    "Konami Bubble System WSG", NULL, 0xad, 0, 2, false, true, 0, false, 0, 32, 16,
    "this is the wavetable part of the Bubble System, which also had two AY-3-8910s.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd"},
    {"CH1##sesd", "CH2##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_SCC, DIV_INS_SCC},
    {},
    waveOnlyEffectHandlerMap
  );

  // to Grauw: feel free to change this to 24 during development of OPL4's PCM part.
  // TODO: add 12-bit and 16-bit big-endian sample formats
  sysDefs[DIV_SYSTEM_OPL4]=new DivSysDef(
    "Yamaha YMF278B (OPL4)", NULL, 0xae, 0, 42, true, true, 0, false, (1U<<DIV_SAMPLE_DEPTH_8BIT)|(1U<<DIV_SAMPLE_DEPTH_16BIT), 0, 0,
    "like OPL3, but this time it also has a 24-channel version of MultiPCM.##sesd",
    {"4OP 1##sesd", "FM 2", "4OP 3##sesd", "FM 4", "4OP 5##sesd", "FM 6", "4OP 7##sesd", "FM 8", "4OP 9##sesd", "FM 10", "4OP 11##sesd", "FM 12", "FM 13", "FM 14", "FM 15", "FM 16", "FM 17", "FM 18", "PCM 1##sesd", "PCM 2##sesd", "PCM 3##sesd", "PCM 4##sesd", "PCM 5##sesd", "PCM 6##sesd", "PCM 7##sesd", "PCM 8##sesd", "PCM 9##sesd", "PCM 10##sesd", "PCM 11##sesd", "PCM 12##sesd", "PCM 13##sesd", "PCM 14##sesd", "PCM 15##sesd", "PCM 16##sesd", "PCM 17##sesd", "PCM 18##sesd", "PCM 19##sesd", "PCM 20##sesd", "PCM 21##sesd", "PCM 22##sesd", "PCM 23##sesd", "PCM 24##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "P7##sesd", "P8##sesd", "P9##sesd", "P10##sesd", "P11##sesd", "P12##sesd", "P13##sesd", "P14##sesd", "P15##sesd", "P16##sesd", "P17##sesd", "P18##sesd", "P19##sesd", "P20##sesd", "P21##sesd", "P22##sesd", "P23##sesd", "P24##sesd"},
    {DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM}
  );

  // TODO: same here
  sysDefs[DIV_SYSTEM_OPL4_DRUMS]=new DivSysDef(
    "Yamaha YMF278B (OPL4) with drums##sesd", NULL, 0xaf, 0, 44, true, true, 0, false, (1U<<DIV_SAMPLE_DEPTH_8BIT)|(1U<<DIV_SAMPLE_DEPTH_16BIT), 0, 0,
    "the OPL4 but with drums mode turned on.##sesd",
    {"4OP 1##sesd", "FM 2", "4OP 3##sesd", "FM 4", "4OP 5##sesd", "FM 6", "4OP 7##sesd", "FM 8", "4OP 9##sesd", "FM 10", "4OP 11##sesd", "FM 12", "FM 13", "FM 14", "FM 15", "Kick/FM 16##sesd", "Snare##sesd", "Tom##sesd", "Top##sesd", "HiHat##sesd", "PCM 1##sesd", "PCM 2##sesd", "PCM 3##sesd", "PCM 4##sesd", "PCM 5##sesd", "PCM 6##sesd", "PCM 7##sesd", "PCM 8##sesd", "PCM 9##sesd", "PCM 10##sesd", "PCM 11##sesd", "PCM 12##sesd", "PCM 13##sesd", "PCM 14##sesd", "PCM 15##sesd", "PCM 16##sesd", "PCM 17##sesd", "PCM 18##sesd", "PCM 19##sesd", "PCM 20##sesd", "PCM 21##sesd", "PCM 22##sesd", "PCM 23##sesd", "PCM 24##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "BD##sesd", "SD##sesd", "TM##sesd", "TP##sesd", "HH##sesd", "P1##sesd", "P2##sesd", "P3##sesd", "P4##sesd", "P5##sesd", "P6##sesd", "P7##sesd", "P8##sesd", "P9##sesd", "P10##sesd", "P11##sesd", "P12##sesd", "P13##sesd", "P14##sesd", "P15##sesd", "P16##sesd", "P17##sesd", "P18##sesd", "P19##sesd", "P20##sesd", "P21##sesd", "P22##sesd", "P23##sesd", "P24##sesd"},
    {DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM, DIV_INS_MULTIPCM}
  );

  EffectHandlerMap es5506PreEffectHandlerMap={
      {0x11, {DIV_CMD_ES5506_FILTER_MODE, "11xx: Set filter mode (00 to 03)##sesd",effectValAnd<3>}},
      {0x14, {DIV_CMD_ES5506_FILTER_K1, "14xx: Set filter coefficient K1 low byte (00 to FF)##sesd",effectValShift<0>,constVal<0x00ff>}},
      {0x15, {DIV_CMD_ES5506_FILTER_K1, "15xx: Set filter coefficient K1 high byte (00 to FF)##sesd",effectValShift<8>,constVal<0xff00>}},
      {0x16, {DIV_CMD_ES5506_FILTER_K2, "16xx: Set filter coefficient K2 low byte (00 to FF)##sesd",effectValShift<0>,constVal<0x00ff>}},
      {0x17, {DIV_CMD_ES5506_FILTER_K2, "17xx: Set filter coefficient K2 high byte (00 to FF)##sesd",effectValShift<8>,constVal<0xff00>}},
      {0x18, {DIV_CMD_ES5506_FILTER_K1_SLIDE, "18xx: Set filter coefficient K1 slide up (00 to FF)##sesd",effectVal,constVal<0>}},
      {0x19, {DIV_CMD_ES5506_FILTER_K1_SLIDE, "19xx: Set filter coefficient K1 slide down (00 to FF)##sesd",effectVal,constVal<1>}},
      {0x1a, {DIV_CMD_ES5506_FILTER_K2_SLIDE, "1Axx: Set filter coefficient K2 slide up (00 to FF)##sesd",effectVal,constVal<0>}},
      {0x1b, {DIV_CMD_ES5506_FILTER_K2_SLIDE, "1Bxx: Set filter coefficient K2 slide down (00 to FF)##sesd",effectVal,constVal<1>}},
      {0x22, {DIV_CMD_ES5506_ENVELOPE_LVRAMP, "22xx: Set envelope left volume ramp (signed) (00 to FF)##sesd",effectVal}},
      {0x23, {DIV_CMD_ES5506_ENVELOPE_RVRAMP, "23xx: Set envelope right volume ramp (signed) (00 to FF)##sesd",effectVal}},
      {0x24, {DIV_CMD_ES5506_ENVELOPE_K1RAMP, "24xx: Set envelope filter coefficient k1 ramp (signed) (00 to FF)##sesd",effectVal,constVal<0>}},
      {0x25, {DIV_CMD_ES5506_ENVELOPE_K1RAMP, "25xx: Set envelope filter coefficient k1 ramp (signed, slower) (00 to FF)##sesd",effectVal,constVal<1>}},
      {0x26, {DIV_CMD_ES5506_ENVELOPE_K2RAMP, "26xx: Set envelope filter coefficient k2 ramp (signed) (00 to FF)##sesd",effectVal,constVal<0>}},
      {0x27, {DIV_CMD_ES5506_ENVELOPE_K2RAMP, "27xx: Set envelope filter coefficient k2 ramp (signed, slower) (00 to FF)##sesd",effectVal,constVal<1>}},
      {0xdf, {DIV_CMD_SAMPLE_DIR, "DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd1"}}
  };
  EffectHandlerMap es5506PostEffectHandlerMap={
      {0x12, {DIV_CMD_ES5506_PAUSE, "120x: Set pause (bit 0)##sesd",effectValAnd<1>}}
  };
  const EffectHandler es5506ECountHandler(DIV_CMD_ES5506_ENVELOPE_COUNT, "2xxx: Set envelope count (000 to 1FF)##sesd", effectValLong<9>);
  const EffectHandler es5506K1Handler(DIV_CMD_ES5506_FILTER_K1, "3xxx: Set filter coefficient K1 (000 to FFF)##sesd", effectValLongShift<12,4>,constVal<0xfff0>);
  const EffectHandler es5506K2Handler(DIV_CMD_ES5506_FILTER_K2, "4xxx: Set filter coefficient K2 (000 to FFF)##sesd", effectValLongShift<12,4>,constVal<0xfff0>);
  for (int i=0; i<2; i++) es5506PreEffectHandlerMap.emplace(0x20+i,es5506ECountHandler);
  for (int i=0; i<16; i++) es5506PreEffectHandlerMap.emplace(0x30+i, es5506K1Handler);
  for (int i=0; i<16; i++) es5506PreEffectHandlerMap.emplace(0x40+i, es5506K2Handler);

  // TODO: custom sample format
  sysDefs[DIV_SYSTEM_ES5506]=new DivSysDef(
    "Ensoniq ES5506", NULL, 0xb1, 0, 32, false, true, 0/*0x171*/, false, (1U<<DIV_SAMPLE_DEPTH_16BIT), 0, 0,
    "a sample chip made by Ensoniq, which is the basis for the GF1 chip found in Gravis' Ultrasound cards.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd", "Channel 17##sesd", "Channel 18##sesd", "Channel 19##sesd", "Channel 20##sesd", "Channel 21##sesd", "Channel 22##sesd", "Channel 23##sesd", "Channel 24##sesd", "Channel 25##sesd", "Channel 26##sesd", "Channel 27##sesd", "Channel 28##sesd", "Channel 29##sesd", "Channel 30##sesd", "Channel 31##sesd", "Channel 32##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506, DIV_INS_ES5506},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    es5506PreEffectHandlerMap,
    es5506PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_Y8950]=new DivSysDef(
    "Yamaha Y8950", NULL, 0xb2, 0, 10, true, false, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_ADPCM_B, 0, 0,
    "like OPL but with an ADPCM channel.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8", "FM 9", "ADPCM##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "P##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PCM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA},
    fmEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_Y8950_DRUMS]=new DivSysDef(
    "Yamaha Y8950 with drums##sesd", NULL, 0xb3, 0, 12, true, false, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_ADPCM_B, 0, 0,
    "the Y8950 chip, in drums mode.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "Kick/FM 7##sesd", "Snare##sesd", "Tom##sesd", "Top##sesd", "HiHat##sesd", "ADPCM##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "BD##sesd", "SD##sesd", "TM##sesd", "TP##sesd", "HH##sesd", "P##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_PCM},
    {DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_OPL_DRUMS, DIV_INS_ADPCMB},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_OPL, DIV_INS_AMIGA},
    fmOPLDrumsEffectHandlerMap,
    fmOPLPostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_SCC_PLUS]=new DivSysDef(
    "Konami SCC+", NULL, 0xb4, 0, 5, false, true, 0x161, false, 0, 32, 256,
    "this is a variant of Konami's SCC chip with the last channel's wavetable being independent.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_SCC, DIV_INS_SCC, DIV_INS_SCC, DIV_INS_SCC, DIV_INS_SCC},
    {},
    waveOnlyEffectHandlerMap
  );

  EffectHandlerMap suEffectHandlerMap={
    {0x10, {DIV_CMD_WAVE, "10xx: Set waveform (0 to 7)##sesd1"}},
    {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set pulse width (0 to 7F)##sesd"}},
    {0x13, {DIV_CMD_C64_RESONANCE, "13xx: Set resonance (0 to FF)##sesd"}},
    {0x14, {DIV_CMD_C64_FILTER_MODE, "14xx: Set filter mode (bit 0: ring mod; bit 1: low pass; bit 2: high pass; bit 3: band pass)##sesd"}},
    {0x15, {DIV_CMD_SU_SWEEP_PERIOD_LOW, "15xx: Set frequency sweep period low byte##sesd", constVal<0>, effectVal}},
    {0x16, {DIV_CMD_SU_SWEEP_PERIOD_HIGH, "16xx: Set frequency sweep period high byte##sesd", constVal<0>, effectVal}},
    {0x17, {DIV_CMD_SU_SWEEP_PERIOD_LOW, "17xx: Set volume sweep period low byte##sesd", constVal<1>, effectVal}},
    {0x18, {DIV_CMD_SU_SWEEP_PERIOD_HIGH, "18xx: Set volume sweep period high byte##sesd", constVal<1>, effectVal}},
    {0x19, {DIV_CMD_SU_SWEEP_PERIOD_LOW, "19xx: Set cutoff sweep period low byte##sesd", constVal<2>, effectVal}},
    {0x1a, {DIV_CMD_SU_SWEEP_PERIOD_HIGH, "1Axx: Set cutoff sweep period high byte##sesd", constVal<2>, effectVal}},
    {0x1b, {DIV_CMD_SU_SWEEP_BOUND, "1Bxx: Set frequency sweep boundary##sesd", constVal<0>, effectVal}},
    {0x1c, {DIV_CMD_SU_SWEEP_BOUND, "1Cxx: Set volume sweep boundary##sesd", constVal<1>, effectVal}},
    {0x1d, {DIV_CMD_SU_SWEEP_BOUND, "1Dxx: Set cutoff sweep boundary##sesd", constVal<2>, effectVal}},
    {0x1e, {DIV_CMD_SU_SYNC_PERIOD_LOW, "1Exx: Set phase reset period low byte##sesd"}},
    {0x1f, {DIV_CMD_SU_SYNC_PERIOD_HIGH, "1Fxx: Set phase reset period high byte##sesd"}},
    {0x20, {DIV_CMD_SU_SWEEP_ENABLE, "20xx: Toggle frequency sweep (bit 0-6: speed; bit 7: direction is up)##sesd", constVal<0>, effectVal}},
    {0x21, {DIV_CMD_SU_SWEEP_ENABLE, "21xx: Toggle volume sweep (bit 0-4: speed; bit 5: direction is up; bit 6: loop; bit 7: alternate)##sesd", constVal<1>, effectVal}},
    {0x22, {DIV_CMD_SU_SWEEP_ENABLE, "22xx: Toggle cutoff sweep (bit 0-6: speed; bit 7: direction is up)##sesd", constVal<2>, effectVal}},
  };
  const EffectHandler suCutoffHandler(DIV_CMD_C64_FINE_CUTOFF, "4xxx: Set cutoff (0 to FFF)##sesd", effectValLong<12>);
  for (int i=0; i<16; i++) {
    suEffectHandlerMap.emplace(0x40+i, suCutoffHandler);
  }

  sysDefs[DIV_SYSTEM_SOUND_UNIT]=new DivSysDef(
    "tildearrow Sound Unit", NULL, 0xb5, 0, 8, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "tildearrow's fantasy sound chip. put SID, AY and VERA in a blender, and you get this!##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_SU, DIV_INS_SU, DIV_INS_SU, DIV_INS_SU, DIV_INS_SU, DIV_INS_SU, DIV_INS_SU, DIV_INS_SU},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    suEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_MSM6295]=new DivSysDef(
    "OKI MSM6295", NULL, 0xaa, 0, 4, false, true, 0x161, false, 1U<<DIV_SAMPLE_DEPTH_VOX, 0, 0,
    "an ADPCM sound chip manufactured by OKI and used in many arcade boards.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_MSM6295, DIV_INS_MSM6295, DIV_INS_MSM6295, DIV_INS_MSM6295},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {
      {0x20, {DIV_CMD_SAMPLE_FREQ, "20xx: Set chip output rate (0: clock/132; 1: clock/165)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_MSM6258]=new DivSysDef(
    "OKI MSM6258", NULL, 0xab, 0, 1, false, true, 0x150, false, 1U<<DIV_SAMPLE_DEPTH_VOX, 0, 0,
    "an ADPCM sound chip manufactured by OKI and used in the Sharp X68000.##sesd",
    {"Sample##sesd"},
    {"PCM##sesd"},
    {DIV_CH_PCM},
    {DIV_INS_MSM6258},
    {DIV_INS_AMIGA},
    {
      {0x20, {DIV_CMD_SAMPLE_FREQ, "20xx: Set frequency divider (0-2)##sesd"}},
      {0x21, {DIV_CMD_SAMPLE_MODE, "21xx: Select clock rate (0: full; 1: half)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_YMZ280B]=new DivSysDef(
    "Yamaha YMZ280B (PCMD8)", NULL, 0xb8, 0, 8, false, true, 0x151, false, 1U<<DIV_SAMPLE_DEPTH_YMZ_ADPCM, 0, 0,
    "used in some arcade boards. Can play back either 4-bit ADPCM, 8-bit PCM or 16-bit PCM.##sesd",
    {"PCM 1##sesd", "PCM 2##sesd", "PCM 3##sesd", "PCM 4##sesd", "PCM 5##sesd", "PCM 6##sesd", "PCM 7##sesd", "PCM 8##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_YMZ280B, DIV_INS_YMZ280B, DIV_INS_YMZ280B, DIV_INS_YMZ280B, DIV_INS_YMZ280B, DIV_INS_YMZ280B, DIV_INS_YMZ280B, DIV_INS_YMZ280B},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA}
  );

  EffectHandlerMap namcoEffectHandlerMap={
    {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd8"}},
    {0x11, {DIV_CMD_WAVE_LOCAL, "11xx: Select waveform (local)##sesd1"}},
  };

  EffectHandlerMap namcoC30EffectHandlerMap={
    {0x10, {DIV_CMD_WAVE, "10xx: Set waveform##sesd9"}},
    {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Toggle noise mode##sesd2"}},
  };

  sysDefs[DIV_SYSTEM_NAMCO]=new DivSysDef(
    "Namco WSG", NULL, 0xb9, 0, 3, false, true, 0, false, 0, 32, 16,
    "a wavetable sound chip used in Pac-Man, among other early Namco arcade games.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO},
    {},
    namcoEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_NAMCO_15XX]=new DivSysDef(
    "Namco C15 WSG", NULL, 0xba, 0, 8, false, true, 0, false, 0, 32, 16,
    "successor of the original Namco WSG chip, used in later Namco arcade games.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO},
    {},
    namcoEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_NAMCO_CUS30]=new DivSysDef(
    "Namco C30 WSG", NULL, 0xbb, 0, 8, false, true, 0, false, 0, 32, 16,
    "like Namco C15 but with stereo sound.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE},
    {DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO, DIV_INS_NAMCO},
    {},
    namcoC30EffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_MSM5232]=new DivSysDef(
    "OKI MSM5232", NULL, 0xbc, 0, 8, false, true, 0, false, 0, 0, 0,
    "a square wave additive synthesis chip made by OKI. used in some arcade machines and instruments.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_MSM5232, DIV_INS_MSM5232, DIV_INS_MSM5232, DIV_INS_MSM5232, DIV_INS_MSM5232, DIV_INS_MSM5232, DIV_INS_MSM5232, DIV_INS_MSM5232},
    {},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xy: Set group control (x: sustain; y: part toggle bitmask)##sesd"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Set noise mode##sesd0"}},
      {0x12, {DIV_CMD_FM_AR, "12xx: Set group attack (0 to 5)##sesd"}},
      {0x13, {DIV_CMD_FM_DR, "13xx: Set group decay (0 to 11)##sesd"}}
    }
  );

  sysDefs[DIV_SYSTEM_YM2612_DUALPCM]=new DivSysDef(
    "Yamaha YM2612 (OPN2) with DualPCM##sesd", NULL, 0xbe, 0, 7, true, false, 0x150, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6/PCM 1##sesd", "PCM 2##sesd"},
    {"F1", "F2", "F3", "F4", "F5", "P1##sesd", "P2##sesd"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AMIGA},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_NULL},
    fmOPN2EffectHandlerMap,
    fmOPN2PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_YM2612_DUALPCM_EXT]=new DivSysDef(
    "Yamaha YM2612 (OPN2) Extended Channel 3 with DualPCM and CSM##sesd", NULL, 0xbd, 0, 11, true, false, 0x150, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd",
    {"FM 1", "FM 2", "FM 3 OP1", "FM 3 OP2", "FM 3 OP3", "FM 3 OP4", "FM 4", "FM 5", "FM 6/PCM 1##sesd", "PCM 2##sesd", "CSM Timer##sesd"},
    {"F1", "F2", "O1", "O2", "O3", "O4", "F4", "F5", "P1##sesd", "P2##sesd", "CSM"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_OP, DIV_CH_FM, DIV_CH_FM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_NOISE},
    {DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_FM, DIV_INS_AMIGA, DIV_INS_FM},
    {DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_NULL, DIV_INS_AMIGA, DIV_INS_NULL, DIV_INS_NULL},
    fmOPN2EffectHandlerMap,
    fmOPN2PostEffectHandlerMap,
    fmExtChEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_T6W28]=new DivSysDef(
    "T6W28", NULL, 0xbf, 0, 4, false, true, 0x160, false, 0, 0, 0,
    "an SN76489 derivative used in Neo Geo Pocket, has independent stereo volume and noise channel frequency.##sesd",
    {"Square 1##sesd", "Square 2##sesd", "Square 3##sesd", "Noise##sesd"},
    {"S1##sesd", "S2##sesd", "S3##sesd", "NO##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_NOISE},
    {DIV_INS_T6W28, DIV_INS_T6W28, DIV_INS_T6W28, DIV_INS_T6W28},
    {},
    {
      {0x20, {DIV_CMD_STD_NOISE_MODE, "20xx: Set noise length (0: short, 1: long)##sesd"}}
    }
  );

  sysDefs[DIV_SYSTEM_PCM_DAC]=new DivSysDef(
    "Generic PCM DAC##sesd", NULL, 0xc0, 0, 1, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_16BIT, 0, 256,
    "as generic sample playback as it gets.##sesd",
    {"Sample##sesd"},
    {"PCM##sesd"},
    {DIV_CH_PCM},
    {DIV_INS_AMIGA}
  );

  sysDefs[DIV_SYSTEM_K007232]=new DivSysDef(
    "Konami K007232", NULL, 0xc6, 0, 2, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this PCM chip was widely used at Konami arcade boards in 1986-1990.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd"},
    {"CH1##sesd", "CH2##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_K007232, DIV_INS_K007232},
    {DIV_INS_AMIGA, DIV_INS_AMIGA}
  );

  sysDefs[DIV_SYSTEM_GA20]=new DivSysDef(
    "Irem GA20", NULL, 0xc7, 0, 4, false, true, 0x171, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "yet another PCM chip from Irem. like Amiga, but less pitch resolution and no sample loop.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_GA20, DIV_INS_GA20, DIV_INS_GA20, DIV_INS_GA20},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA}
  );

  sysDefs[DIV_SYSTEM_SM8521]=new DivSysDef(
    "Sharp SM8521", NULL, 0xc8, 0, 3, false, true, 0, false, 0, 32, 16,
    "a SoC with wavetable sound hardware.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Noise##sesd"},
    {"CH1##sesd", "CH2##sesd", "NS"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_NOISE},
    {DIV_INS_SM8521, DIV_INS_SM8521, DIV_INS_SM8521},
    {},
    waveOnlyEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_PV1000]=new DivSysDef(
    "Casio PV-1000", NULL, 0xcb, 0, 3, false, true, 0, false, 0, 0, 0,
    "a game console with 3 channels of square wave. it's what happens after fusing TIA and VIC together.##sesd",
    {"Square 1##sesd", "Square 2##sesd", "Square 3##sesd"},
    {"S1##sesd", "S2##sesd", "S3##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_PV1000, DIV_INS_PV1000, DIV_INS_PV1000},
    {},
    {
      {0x10, {DIV_CMD_STD_NOISE_MODE, "10xx: Set ring modulation (0: disable, 1: enable)##sesd"}}
    }
  );

  sysDefs[DIV_SYSTEM_SFX_BEEPER_QUADTONE]=new DivSysDef(
    "ZX Spectrum Beeper (QuadTone Engine)##sesd", NULL, 0xca, 0, 5, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "another ZX Spectrum beeper system with full PWM pulses and 3-level volume per channel. it also has a pitchable overlay sample channel.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "PCM##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "PCM##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PULSE, DIV_CH_PCM},
    {DIV_INS_POKEMINI, DIV_INS_POKEMINI, DIV_INS_POKEMINI, DIV_INS_POKEMINI, DIV_INS_AMIGA},
    {},
    {
      {0x12, {DIV_CMD_STD_NOISE_MODE, "12xx: Set pulse width##sesd1"}}
    }
  );

  sysDefs[DIV_SYSTEM_K053260]=new DivSysDef(
    "Konami K053260", NULL, 0xcc, 0, 4, false, true, 0x161, false, (1U<<DIV_SAMPLE_DEPTH_ADPCM_K)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "this PCM chip was widely used at Konami arcade boards in 1990-1992.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_K053260, DIV_INS_K053260, DIV_INS_K053260, DIV_INS_K053260},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {
      {0xdf, {DIV_CMD_SAMPLE_DIR, "DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd2"}}
    }
  );

  sysDefs[DIV_SYSTEM_TED]=new DivSysDef(
    "MOS Technology TED", NULL, 0xcd, 0, 2, false, true, 0, false, 0, 0, 0,
    "two square waves (one may be turned into noise). used in the Commodore Plus/4, 16 and 116.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd"},
    {"CH1##sesd", "CH2##sesd"},
    {DIV_CH_PULSE, DIV_CH_PULSE},
    {DIV_INS_TED, DIV_INS_TED},
    {}
  );

  sysDefs[DIV_SYSTEM_C140]=new DivSysDef(
    "Namco C140", NULL, 0xce, 0, 24, false, true, 0x161, false, (1U<<DIV_SAMPLE_DEPTH_MULAW)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "Namco's first PCM chip from 1987. it's pretty good for being so.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd", "Channel 17##sesd", "Channel 18##sesd", "Channel 19##sesd", "Channel 20##sesd", "Channel 21##sesd", "Channel 22##sesd", "Channel 23##sesd", "Channel 24##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140, DIV_INS_C140},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {}
  );

  sysDefs[DIV_SYSTEM_C219]=new DivSysDef(
    "Namco C219", NULL, 0xcf, 0, 16, false, true, 0x161, false, (1U<<DIV_SAMPLE_DEPTH_C219)|(1U<<DIV_SAMPLE_DEPTH_8BIT), 0, 0,
    "Namco's PCM chip used in their NA-1/2 hardware.\nvery similar to C140, but has noise generator.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
    {DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219, DIV_INS_C219},
    {DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    {
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Set noise mode##sesd1"}},
      {0x12, {DIV_CMD_SNES_INVERT, "12xy: Set invert mode (x: surround; y: invert)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_ESFM]=new DivSysDef(
    "ESS ES1xxx series (ESFM)##sesd", NULL, 0xd1, 0, 18, true, false, 0, false, 0, 0, 0, 
    "a unique FM synth featured in PC sound cards.\nbased on the OPL3 design, but with lots of its features extended.##sesd",
    {"FM 1", "FM 2", "FM 3", "FM 4", "FM 5", "FM 6", "FM 7", "FM 8", "FM 9", "FM 10", "FM 11", "FM 12", "FM 13", "FM 14", "FM 15", "FM 16", "FM 17", "FM 18"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18"},
    {DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM, DIV_CH_FM},
    {DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM, DIV_INS_ESFM},
    {},
    {
      {0x2e, {DIV_CMD_FM_HARD_RESET, "2Exx: Toggle hard envelope reset on new notes##sesd"}},
    },
    fmESFMPostEffectHandlerMap
  );
  
  sysDefs[DIV_SYSTEM_ES5503]=new DivSysDef(
    "Ensoniq ES5503", NULL, 0xd2, 0, 32, false, true, 0x171, false, (1U<<DIV_SAMPLE_DEPTH_8BIT), 256, 256,
    "first Ensoniq chip used in their synths and Apple IIGS computer. Has 32 hard-panned 8-bit wavetable/sample channels, can do oscillator sync (like SID) and amplitude modulation. Can have up to 128 KiB (2 banks of 64 KiB) of memory for wavetables/samples.\nAs Robert Yannes (SID chip creator) said, it's more or less what SID chip could be if he was given enough time for its development.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd", "Channel 9##sesd", "Channel 10##sesd", "Channel 11##sesd", "Channel 12##sesd", "Channel 13##sesd", "Channel 14##sesd", "Channel 15##sesd", "Channel 16##sesd", "Channel 17##sesd", "Channel 18##sesd", "Channel 19##sesd", "Channel 20##sesd", "Channel 21##sesd", "Channel 22##sesd", "Channel 23##sesd", "Channel 24##sesd", "Channel 25##sesd", "Channel 26##sesd", "Channel 27##sesd", "Channel 28##sesd", "Channel 29##sesd", "Channel 30##sesd", "Channel 31##sesd", "Channel 32##sesd"},
    {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE },
    {DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503, DIV_INS_ES5503},
    {},
    {
      {0x11, {DIV_CMD_ES5503_NUM_ENABLED_OSC, "11xx: Set number of enabled oscillators (2-1F)##sesd"}},
      {0x12, {DIV_CMD_ES5503_OSC_OUTPUT, "12xx: Set oscillator output (0-7, 0=left, 1=right)##sesd"}},
      {0x13, {DIV_CMD_ES5503_WAVE_LENGTH, "13xx: Set wave/sample length (0-7, 0=256, 1=512, 2=1024, etc.)##sesd"}},
      {0x14, {DIV_CMD_ES5503_WAVE_POS, "14xx: Set wave/sample position in memory (xx*256 offset)##sesd"}},
      {0x15, {DIV_CMD_ES5503_OSC_MODE, "15xx: Set oscillator mode (0-3)##sesd"}},
    },
    {}
  );
  
  sysDefs[DIV_SYSTEM_POWERNOISE]=new DivSysDef(
    "PowerNoise", NULL, 0xd4, 0, 4, false, false, 0, false, 0, 0, 0, 
    "a fantasy sound chip designed by jvsTSX and The Beesh-Spweesh!\nused in the Hexheld fantasy console.##sesd",
    {"Noise 1##sesd", "Noise 2##sesd", "Noise 3##sesd", "Slope##sesd"},
    {"N1##sesd", "N2##sesd", "N3##sesd", "SL##sesd"},
    {DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_WAVE},
    {DIV_INS_POWERNOISE, DIV_INS_POWERNOISE, DIV_INS_POWERNOISE, DIV_INS_POWERNOISE_SLOPE},
    {},
    {
      {0x20, {DIV_CMD_POWERNOISE_COUNTER_LOAD, "20xx: Load low byte of noise channel LFSR (00 to FF) or slope channel accumulator (00 to 7F)##sesd", constVal<0>, effectVal}},
      {0x21, {DIV_CMD_POWERNOISE_COUNTER_LOAD, "21xx: Load high byte of noise channel LFSR (00 to FF)##sesd", constVal<1>, effectVal}},
      {0x22, {DIV_CMD_POWERNOISE_IO_WRITE, "22xx: Write to I/O port A##sesd", constVal<0>, effectVal}},
      {0x23, {DIV_CMD_POWERNOISE_IO_WRITE, "23xx: Write to I/O port B##sesd", constVal<1>, effectVal}},
    },
    {}
  );

  sysDefs[DIV_SYSTEM_DAVE]=new DivSysDef(
    "DAVE", NULL, 0xd5, 0, 6, false, true, 0, false, 1U<<DIV_SAMPLE_DEPTH_8BIT, 0, 0,
    "this chip was featured in the Enterprise 128 computer. it is similar to POKEY, but with stereo output, more features and frequency precision and the ability to turn left or right (or both) channel into a 6-bit DAC for sample playback.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Noise##sesd", "DAC Left##sesd", "DAC Right##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "NO##sesd", "L##sesd", "R##sesd"},
    {DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_WAVE, DIV_CH_NOISE, DIV_CH_PCM, DIV_CH_PCM},
    {DIV_INS_DAVE, DIV_INS_DAVE, DIV_INS_DAVE, DIV_INS_DAVE, DIV_INS_AMIGA, DIV_INS_AMIGA},
    {},
    {
      {0x10, {DIV_CMD_WAVE, "10xx: Set waveform (0 to 4; 0 to 3 on noise)##sesd"}},
      {0x11, {DIV_CMD_STD_NOISE_MODE, "11xx: Set noise frequency source (0: fixed; 1-3: channels 1 to 3)##sesd"}},
      {0x12, {DIV_CMD_DAVE_HIGH_PASS, "12xx: Toggle high-pass with next channel##sesd"}},
      {0x13, {DIV_CMD_DAVE_RING_MOD, "13xx: Toggle ring modulation with channel+2##sesd"}},
      {0x14, {DIV_CMD_DAVE_SWAP_COUNTERS, "14xx: Toggle swap counters (noise only)##sesd"}},
      {0x15, {DIV_CMD_DAVE_LOW_PASS, "15xx: Toggle low pass (noise only)##sesd"}},
      {0x16, {DIV_CMD_DAVE_CLOCK_DIV, "16xx: Set clock divider (0: /2; 1: /3)##sesd"}},
    }
  );

  sysDefs[DIV_SYSTEM_SID2]=new DivSysDef(
    "SID2", NULL, 0xf0, 0, 3, false, true, 0, false, 0, 0, 0,
    "a fictional sound chip by LTVA. like SID, but with many of its problems fixed. also features extended functionality like more wave mixing modes, tonal noise, filter and volume per channel.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd"},
    {DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_SID2, DIV_INS_SID2, DIV_INS_SID2},
    {},
    {},
    SID2PostEffectHandlerMap
  );

  sysDefs[DIV_SYSTEM_DUMMY]=new DivSysDef(
    "Dummy System##sesd", NULL, 0xfd, 0, 8, false, true, 0, false, 0, 0, 0,
    "this is a system designed for testing purposes.##sesd",
    {"Channel 1##sesd", "Channel 2##sesd", "Channel 3##sesd", "Channel 4##sesd", "Channel 5##sesd", "Channel 6##sesd", "Channel 7##sesd", "Channel 8##sesd"},
    {"CH1##sesd", "CH2##sesd", "CH3##sesd", "CH4##sesd", "CH5##sesd", "CH6##sesd", "CH7##sesd", "CH8##sesd"},
    {DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE, DIV_CH_NOISE},
    {DIV_INS_STD, DIV_INS_STD, DIV_INS_STD, DIV_INS_STD, DIV_INS_STD, DIV_INS_STD, DIV_INS_STD, DIV_INS_STD}
  );

  for (int i=0; i<DIV_MAX_CHIP_DEFS; i++) {
    if (sysDefs[i]==NULL) continue;
    if (sysDefs[i]->id!=0) {
      sysFileMapFur[sysDefs[i]->id]=(DivSystem)i;
    }
    if (sysDefs[i]->id_DMF!=0) {
      sysFileMapDMF[sysDefs[i]->id_DMF]=(DivSystem)i;
    }
  }

  systemsRegistered=true;
}
