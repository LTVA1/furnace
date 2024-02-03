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

#include "../engine/chipUtils.h"
#include "gui.h"
#include "misc/cpp/imgui_stdlib.h"
#include <imgui.h>

bool rerender_es5503 = true;

bool FurnaceGUI::drawSysConf(int chan, int sysPos, DivSystem type, DivConfig& flags, bool modifyOnChange, bool fromMenu) {
  bool altered=false;
  bool mustRender=false;
  bool restart=modifyOnChange;
  bool supportsCustomRate=true;

  switch (type) {
    case DIV_SYSTEM_YM2612:
    case DIV_SYSTEM_YM2612_EXT: 
    case DIV_SYSTEM_YM2612_DUALPCM:
    case DIV_SYSTEM_YM2612_DUALPCM_EXT:
    case DIV_SYSTEM_YM2612_CSM: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=0;
      if (flags.has("chipType")) {
        chipType=flags.getInt("chipType",0);
      } else {
        chipType=flags.getBool("ladderEffect",0)?1:0;
      }
      bool noExtMacros=flags.getBool("noExtMacros",false);
      bool fbAllOps=flags.getBool("fbAllOps",false);

      ImGui::Text(_L("Clock rate:##sgsc0"));
      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (7.67MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (7.61MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("FM Towns (8MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("AtGames Genesis (6.13MHz)",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("Sega System 32 (8.05MHz)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Chip type:##sgsc0"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("YM3438 (9-bit DAC)##sgsc"),chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("YM2612 (9-bit DAC with distortion)##sgsc"),chipType==1)) {
        chipType=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("YMF276 (external DAC)##sgsc"),chipType==2)) {
        chipType=2;
        altered=true;
      }
      ImGui::Unindent();

      if (type==DIV_SYSTEM_YM2612_EXT || type==DIV_SYSTEM_YM2612_DUALPCM_EXT || type==DIV_SYSTEM_YM2612_CSM) {
        if (ImGui::Checkbox(_L("Disable ExtCh FM macros (compatibility)##sgsc0"),&noExtMacros)) {
          altered=true;
        }
        if (ImGui::Checkbox(_L("Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc0"),&fbAllOps)) {
          altered=true;
        }
      }
      
      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("chipType",chipType);
          flags.set("noExtMacros",noExtMacros);
          flags.set("fbAllOps",fbAllOps);
        });
      }
      break;
    }
    case DIV_SYSTEM_SMS: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool noPhaseReset=flags.getBool("noPhaseReset",false);
      bool noEasyNoise=flags.getBool("noEasyNoise",false);

      ImGui::Text(_L("Clock rate:##sgsc1"));
      ImGui::Indent();
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("3.55MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz (BBC Micro)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton(_L("1.79MHz (Half NTSC)##sgsc"),clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz (Exed Exes)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz (Sega System 1)",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      if (ImGui::RadioButton("447KHz (TI-99/4A)",clockSel==6)) {
        clockSel=6;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Chip type:##sgsc1"));
      ImGui::Indent();
      if (ImGui::RadioButton("Sega VDP/Master System",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76489",chipType==1)) {
        chipType=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("TI SN76489 with Atari-like short noise##sgsc"),chipType==2)) {
        chipType=2;
        altered=true;
      }
      if (ImGui::RadioButton("Game Gear",chipType==3)) {
        chipType=3;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76489A",chipType==4)) {
        chipType=4;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76496",chipType==5)) {
        chipType=5;
        altered=true;
      }
      if (ImGui::RadioButton("NCR 8496",chipType==6)) {
        chipType=6;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Tandy PSSJ 3-voice sound##sgsc"),chipType==7)) {
        chipType=7;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN94624",chipType==8)) {
        chipType=8;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76494",chipType==9)) {
        chipType=9;
        altered=true;
      }
      ImGui::Unindent();

      if (ImGui::Checkbox(_L("Disable noise period change phase reset##sgsc"),&noPhaseReset)) {
        altered=true;
      }

      if (ImGui::Checkbox(_L("Disable easy period to note mapping on upper octaves##sgsc0"),&noEasyNoise)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("chipType",chipType);
          flags.set("noPhaseReset",noPhaseReset);
          flags.set("noEasyNoise",noEasyNoise);
        });
      }
      break;
    }
    case DIV_SYSTEM_PCE: {
      bool clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool noAntiClick=flags.getBool("noAntiClick",false);

      if (ImGui::Checkbox(_L("Pseudo-PAL##sgsc0"),&clockSel)) {
        altered=true;
      }
      if (ImGui::Checkbox(_L("Disable anti-click##sgsc0"),&noAntiClick)) {
        altered=true;
      }
      ImGui::Text(_L("Chip revision:##sgsc0"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("HuC6280 (original)##sgsc"),chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("HuC6280A (SuperGrafx)",chipType==1)) {
        chipType=1;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("chipType",chipType);
          flags.set("noAntiClick",noAntiClick);
        });
      }
      break;
    }
    case DIV_SYSTEM_SOUND_UNIT: {
      int clockSel=flags.getInt("clockSel",0);
      bool echo=flags.getBool("echo",false);
      bool swapEcho=flags.getBool("swapEcho",false);
      int sampleMemSize=flags.getInt("sampleMemSize",0);
      bool pdm=flags.getBool("pdm",false);
      int echoDelay=flags.getInt("echoDelay",0);
      int echoFeedback=flags.getInt("echoFeedback",0);
      int echoResolution=flags.getInt("echoResolution",0);
      int echoVol=(signed char)flags.getInt("echoVol",0);

      ImGui::Text(_L("CPU rate:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton("6.18MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("5.95MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Sample memory:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("8K (rev A/B/E)##sgsc"),sampleMemSize==0)) {
        sampleMemSize=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("64K (rev D/F)##sgsc"),sampleMemSize==1)) {
        sampleMemSize=1;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("DAC resolution:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("16-bit (rev A/B/D/F)##sgsc"),pdm==0)) {
        pdm=false;
        altered=true;
      }
      if (ImGui::RadioButton(_L("8-bit + TDM (rev C/E)##sgsc"),pdm==1)) {
        pdm=true;
        altered=true;
      }
      ImGui::Unindent();
      if (ImGui::Checkbox(_L("Enable echo##sgsc0"),&echo)) {
        altered=true;
      }
      if (ImGui::Checkbox(_L("Swap echo channels##sgsc"),&swapEcho)) {
        altered=true;
      }
      ImGui::Text(_L("Echo delay:##sgsc0"));
      if (CWSliderInt("##EchoBufSize",&echoDelay,0,63)) {
        if (echoDelay<0) echoDelay=0;
        if (echoDelay>63) echoDelay=63;
        altered=true;
      } rightClickable
      ImGui::Text(_L("Echo resolution:##sgsc"));
      if (CWSliderInt("##EchoResolution",&echoResolution,0,15)) {
        if (echoResolution<0) echoResolution=0;
        if (echoResolution>15) echoResolution=15;
        altered=true;
      } rightClickable
      ImGui::Text(_L("Echo feedback:##sgsc0"));
      if (CWSliderInt("##EchoFeedback",&echoFeedback,0,15)) {
        if (echoFeedback<0) echoFeedback=0;
        if (echoFeedback>15) echoFeedback=15;
        altered=true;
      } rightClickable
      ImGui::Text(_L("Echo volume:##sgsc0"));
      if (CWSliderInt("##EchoVolume",&echoVol,-128,127)) {
        if (echoVol<-128) echoVol=-128;
        if (echoVol>127) echoVol=127;
        altered=true;
      } rightClickable

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("echo",echo);
          flags.set("swapEcho",swapEcho);
          flags.set("sampleMemSize",sampleMemSize);
          flags.set("pdm",pdm);
          flags.set("echoDelay",echoDelay);
          flags.set("echoFeedback",echoFeedback);
          flags.set("echoResolution",echoResolution);
          flags.set("echoVol",(unsigned char)echoVol);
        });
      }
      break;
    }
    case DIV_SYSTEM_GB: {
      int chipType=flags.getInt("chipType",0);
      bool noAntiClick=flags.getBool("noAntiClick",false);
      bool invertWave=flags.getBool("invertWave",true);
      bool enoughAlready=flags.getBool("enoughAlready",false);

      if (ImGui::Checkbox(_L("Disable anti-click##sgsc1"),&noAntiClick)) {
        altered=true;
      }
      ImGui::Text(_L("Chip revision:##sgsc1"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Original (DMG)##sgsc"),chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Game Boy Color (rev C)##sgsc"),chipType==1)) {
        chipType=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Game Boy Color (rev E)##sgsc"),chipType==2)) {
        chipType=2;
        altered=true;
      }
      if (ImGui::RadioButton("Game Boy Advance",chipType==3)) {
        chipType=3;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Wave channel orientation:##sgsc"));
      if (chipType==3) {
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Normal##sgsc"),!invertWave)) {
          invertWave=false;
          altered=true;
        }
        if (ImGui::RadioButton(_L("Inverted##sgsc"),invertWave)) {
          invertWave=true;
          altered=true;
        }
        ImGui::Unindent();
      } else {
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Exact data (inverted)##sgsc"),!invertWave)) {
          invertWave=false;
          altered=true;
        }
        if (ImGui::RadioButton(_L("Exact output (normal)##sgsc"),invertWave)) {
          invertWave=true;
          altered=true;
        }
        ImGui::Unindent();
      }
      if (ImGui::Checkbox(_L("Pretty please one more compat flag when I use arpeggio and my sound length##sgsc"),&enoughAlready)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("chipType",chipType);
          flags.set("noAntiClick",noAntiClick);
          flags.set("invertWave",invertWave);
          flags.set("enoughAlready",enoughAlready);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPLL:
    case DIV_SYSTEM_OPLL_DRUMS:
    case DIV_SYSTEM_VRC7: {
      int clockSel=flags.getInt("clockSel",0);
      int patchSet=flags.getInt("patchSet",0);
      bool noTopHatFreq=flags.getBool("noTopHatFreq",false);
      bool fixedAll=flags.getBool("fixedAll",false);

      ImGui::Text(_L("Clock rate:##sgsc2"));
      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (3.58MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (3.55MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Arcade (4MHz)##sgsc"),clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Half NTSC (1.79MHz)##sgsc"),clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      ImGui::Unindent();
      if (type!=DIV_SYSTEM_VRC7) {
        ImGui::Text(_L("Patch set:##sgsc"));
        ImGui::Indent();
        if (ImGui::RadioButton("Yamaha YM2413",patchSet==0)) {
          patchSet=0;
          altered=true;
        }
        if (ImGui::RadioButton("Yamaha YMF281",patchSet==1)) {
          patchSet=1;
          altered=true;
        }
        if (ImGui::RadioButton("Yamaha YM2423",patchSet==2)) {
          patchSet=2;
          altered=true;
        }
        if (ImGui::RadioButton("Konami VRC7",patchSet==3)) {
          patchSet=3;
          altered=true;
        }
        ImGui::Unindent();
      }

      if (type==DIV_SYSTEM_OPLL_DRUMS) {
        if (ImGui::Checkbox(_L("Ignore top/hi-hat frequency changes##sgsc"),&noTopHatFreq)) {
          altered=true;
        }
        if (ImGui::Checkbox(_L("Apply fixed frequency to all drums at once##sgsc"),&fixedAll)) {
          altered=true;
        }
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          if (type!=DIV_SYSTEM_VRC7) {
            flags.set("patchSet",patchSet);
          }
          flags.set("noTopHatFreq",noTopHatFreq);
          flags.set("fixedAll",fixedAll);
        });
      }
      break;
    }
    case DIV_SYSTEM_YM2151: {
      int clockSel=flags.getInt("clockSel",0);
      bool brokenPitch=flags.getBool("brokenPitch",false);

      ImGui::Indent();
      if (ImGui::RadioButton("NTSC/X16 (3.58MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (3.55MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("X1/X68000 (4MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      if (ImGui::Checkbox(_L("Broken pitch macro/slides (compatibility)##sgsc0"),&brokenPitch)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("brokenPitch",brokenPitch);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPZ: {
      bool clockSel=flags.getInt("clockSel",0);
      bool brokenPitch=flags.getBool("brokenPitch",false);

      if (ImGui::Checkbox(_L("Pseudo-PAL##sgsc1"),&clockSel)) {
        altered=true;
      }

      if (ImGui::Checkbox(_L("Broken pitch macro/slides (compatibility)##sgsc1"),&brokenPitch)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("brokenPitch",brokenPitch);
        });
      }
      break;
    }
    case DIV_SYSTEM_NES: {
      int clockSel=flags.getInt("clockSel",0);
      bool dpcmMode=flags.getBool("dpcmMode",true);

      ImGui::Text(_L("Clock rate:##sgsc20"));

      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (1.79MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (1.67MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("Dendy (1.77MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("DPCM channel mode:##sgsc"));

      ImGui::Indent();
      if (ImGui::RadioButton(_L("DPCM (muffled samples; low CPU usage)##sgsc"),dpcmMode)) {
        dpcmMode=true;
        altered=true;
      }
      if (ImGui::RadioButton(_L("PCM (crisp samples; high CPU usage)##sgsc"),!dpcmMode)) {
        dpcmMode=false;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("dpcmMode",dpcmMode);
        });
      }
      break;
    }
    case DIV_SYSTEM_VRC6:
    case DIV_SYSTEM_FDS:
    case DIV_SYSTEM_MMC5: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text(_L("Clock rate:##sgsc18"));

      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (1.79MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (1.67MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("Dendy (1.77MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_C64_8580:
    case DIV_SYSTEM_C64_6581: {
      int clockSel=flags.getInt("clockSel",0);
      bool keyPriority=flags.getBool("keyPriority",true);
      bool no1EUpdate=flags.getBool("no1EUpdate",false);
      bool multiplyRel=flags.getBool("multiplyRel",false);
      int testAttack=flags.getInt("testAttack",0);
      int testDecay=flags.getInt("testDecay",0);
      int testSustain=flags.getInt("testSustain",0);
      int testRelease=flags.getInt("testRelease",0);
      int initResetTime=flags.getInt("initResetTime",2);

      ImGui::Text(_L("Clock rate:##sgsc19"));

      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (1.02MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (0.99MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("SSI 2001 (0.89MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Global parameter priority:##sgsc0"));

      ImGui::Indent();
      if (ImGui::RadioButton(_L("Left to right##sgsc0"),!keyPriority)) {
        keyPriority=false;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Last used channel##sgsc0"),keyPriority)) {
        keyPriority=true;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Hard reset envelope:##sgsc"));

      if (CWSliderInt(_L("Attack##sgsc"),&testAttack,0,15)) {
        if (testAttack<0) testAttack=0;
        if (testAttack>15) testAttack=15;
        altered=true;
      }
      if (CWSliderInt(_L("Decay##sgsc"),&testDecay,0,15)) {
        if (testDecay<0) testDecay=0;
        if (testDecay>15) testDecay=15;
        altered=true;
      }
      if (CWSliderInt(_L("Sustain##sgsc"),&testSustain,0,15)) {
        if (testSustain<0) testSustain=0;
        if (testSustain>15) testSustain=15;
        altered=true;
      }
      if (CWSliderInt(_L("Release##sgsc"),&testRelease,0,15)) {
        if (testRelease<0) testRelease=0;
        if (testRelease>15) testRelease=15;
        altered=true;
      }

      ImGui::Text(_L("Envelope reset time:##sgsc"));

      pushWarningColor(initResetTime<1 || initResetTime>4);
      if (CWSliderInt("##InitReset",&initResetTime,0,16)) {
        if (initResetTime<0) initResetTime=0;
        if (initResetTime>16) initResetTime=16;
        altered=true;
      }
      popWarningColor();
      
      ImGui::Text(_L("- 0 disables envelope reset. not recommended!\n- 1 may trigger SID envelope bugs.\n- values that are too high may result in notes being skipped.##sgsc"));

      if (ImGui::Checkbox(_L("Disable 1Exy env update (compatibility)##sgsc"),&no1EUpdate)) {
        altered=true;
      }

      if (ImGui::Checkbox(_L("Relative duty and cutoff macros are coarse (compatibility)##sgsc"),&multiplyRel)) {
        altered=true;
      }


      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("keyPriority",keyPriority);
          flags.set("no1EUpdate",no1EUpdate);
          flags.set("multiplyRel",multiplyRel);
          flags.set("testAttack",testAttack);
          flags.set("testDecay",testDecay);
          flags.set("testSustain",testSustain);
          flags.set("testRelease",testRelease);
          flags.set("initResetTime",initResetTime);
        });
      }
      break;
    }
    case DIV_SYSTEM_YM2610:
    case DIV_SYSTEM_YM2610_EXT:
    case DIV_SYSTEM_YM2610_CSM:
    case DIV_SYSTEM_YM2610_FULL:
    case DIV_SYSTEM_YM2610_FULL_EXT:
    case DIV_SYSTEM_YM2610B:
    case DIV_SYSTEM_YM2610B_EXT:
    case DIV_SYSTEM_YM2610B_CSM: {
      int clockSel=flags.getInt("clockSel",0);
      bool noExtMacros=flags.getBool("noExtMacros",false);
      bool fbAllOps=flags.getBool("fbAllOps",false);
      int ssgVol=flags.getInt("ssgVol",128);
      int fmVol=flags.getInt("fmVol",256);

      ImGui::Indent();
      if (ImGui::RadioButton("8MHz (Neo Geo MVS)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("8.06MHz (Neo Geo AES)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Unindent();

      if (type==DIV_SYSTEM_YM2610_EXT || type==DIV_SYSTEM_YM2610_FULL_EXT || type==DIV_SYSTEM_YM2610B_EXT || type==DIV_SYSTEM_YM2610_CSM || type==DIV_SYSTEM_YM2610B_CSM) {
        if (ImGui::Checkbox(_L("Disable ExtCh FM macros (compatibility)##sgsc1"),&noExtMacros)) {
          altered=true;
        }
        if (ImGui::Checkbox(_L("Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc1"),&fbAllOps)) {
          altered=true;
        }
      }

      if (CWSliderInt(_L("SSG Volume##sgsc0"),&ssgVol,0,256)) {
        if (ssgVol<0) ssgVol=0;
        if (ssgVol>256) ssgVol=256;
        altered=true;
      } rightClickable

      if (CWSliderInt(_L("FM/ADPCM Volume##sgsc0"),&fmVol,0,256)) {
        if (fmVol<0) fmVol=0;
        if (fmVol>256) fmVol=256;
        altered=true;
      } rightClickable

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("noExtMacros",noExtMacros);
          flags.set("fbAllOps",fbAllOps);
          flags.set("ssgVol",ssgVol);
          flags.set("fmVol",fmVol);
        });
      }
      break;
    }
    case DIV_SYSTEM_AY8910:
    case DIV_SYSTEM_AY8930: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool halfClock=flags.getBool("halfClock",false);
      bool stereo=flags.getBool("stereo",false);
      int stereoSep=flags.getInt("stereoSep",0);

      ImGui::Text(_L("Clock rate:##sgsc3"));
      ImGui::Indent();
      if (ImGui::RadioButton("1.79MHz (ZX Spectrum NTSC/MSX)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.77MHz (ZX Spectrum PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("0.83MHz (Pre-divided Sunsoft 5B on PAL)##sgsc"),clockSel==8)) {
        clockSel=8;
        altered=true;
      }
      if (ImGui::RadioButton(_L("0.89MHz (Pre-divided Sunsoft 5B)##sgsc"),clockSel==6)) {
        clockSel=6;
        altered=true;
      }
      if (ImGui::RadioButton("1MHz (Amstrad CPC)",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      if (ImGui::RadioButton("1.10MHz (Gamate/VIC-20 PAL)",clockSel==9)) {
        clockSel=9;
        altered=true;
      }
      if (ImGui::RadioButton("1.25MHz (Mag Max)",clockSel==13)) {
        clockSel=13;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz (Vectrex)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("1.536MHz (Kyugo)",clockSel==14)) {
        clockSel=14;
        altered=true;
      }
      if (ImGui::RadioButton("1.67MHz (?)",clockSel==7)) {
        clockSel=7;
        altered=true;
      }
      if (ImGui::RadioButton("1.75MHz (ZX Spectrum 48K)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz (Atari ST/Sharp X1)",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("2^21Hz (Game Boy)",clockSel==10)) {
        clockSel=10;
        altered=true;
      }
      if (ImGui::RadioButton("3.58MHz (Darky)",clockSel==11)) {
        clockSel=11;
        altered=true;
      }
      if (ImGui::RadioButton("3.6MHz (Darky)",clockSel==12)) {
        clockSel=12;
        altered=true;
      }
      ImGui::Unindent();
      if (type==DIV_SYSTEM_AY8910) {
        ImGui::Text(_L("Chip type:##sgsc2"));
        ImGui::Indent();
        if (ImGui::RadioButton("AY-3-8910",chipType==0)) {
          chipType=0;
          altered=true;
        }
        if (ImGui::RadioButton("YM2149(F)",chipType==1)) {
          chipType=1;
          altered=true;
        }
        if (ImGui::RadioButton("Sunsoft 5B",chipType==2)) {
          chipType=2;
          altered=true;
        }
        if (ImGui::RadioButton("AY-3-8914",chipType==3)) {
          chipType=3;
          altered=true;
        }
        ImGui::Unindent();
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("note: AY-3-8914 is not supported by the VGM format!##sgsc"));
        }
      }
      ImGui::BeginDisabled(type==DIV_SYSTEM_AY8910 && chipType==2);
      if (ImGui::Checkbox(_L("Stereo##_AY_STEREO"),&stereo)) {
        altered=true;
      }
      if (stereo) {
        int sep=256-(stereoSep&255);
        if (CWSliderInt(_L("Separation##sgsc"),&sep,1,256)) {
          if (sep<1) sep=1;
          if (sep>256) sep=256;
          stereoSep=256-sep;
          altered=true;
        }
      }
      ImGui::EndDisabled();
      ImGui::BeginDisabled(type==DIV_SYSTEM_AY8910 && chipType!=1);
      if (ImGui::Checkbox(_L("Half Clock divider##_AY_CLKSEL"),&halfClock)) {
        altered=true;
      }
      ImGui::EndDisabled();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          if (type==DIV_SYSTEM_AY8910) {
            flags.set("chipType",chipType);
          }
          flags.set("halfClock",halfClock);
          flags.set("stereo",stereo);
          flags.set("stereoSep",stereoSep);
        });
      }
      break;
    }
    case DIV_SYSTEM_SAA1099: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Indent();
      if (ImGui::RadioButton("SAM Coupé (8MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("NTSC (7.15MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (7.09MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_AMIGA: {
      bool clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      int chipMem=flags.getInt("chipMem",21);
      int stereoSep=flags.getInt("stereoSep",0);
      bool bypassLimits=flags.getBool("bypassLimits",false);

      ImGui::Text(_L("Stereo separation:##sgsc"));
      if (CWSliderInt("##StereoSep",&stereoSep,0,127)) {
        if (stereoSep<0) stereoSep=0;
        if (stereoSep>127) stereoSep=127;
        altered=true;
      } rightClickable

      ImGui::Text(_L("Model:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton("Amiga 500 (OCS)",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("Amiga 1200 (AGA)",chipType==1)) {
        chipType=1;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Chip memory:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("2MB (ECS/AGA max)##sgsc"),chipMem==21)) {
        chipMem=21;
        altered=true;
        mustRender=true;
      }
      if (ImGui::RadioButton(_L("1MB##sgsc"),chipMem==20)) {
        chipMem=20;
        altered=true;
        mustRender=true;
      }
      if (ImGui::RadioButton(_L("512KB (OCS max)##sgsc"),chipMem==19)) {
        chipMem=19;
        altered=true;
        mustRender=true;
      }
      if (ImGui::RadioButton(_L("256KB##sgsc"),chipMem==18)) {
        chipMem=18;
        altered=true;
        mustRender=true;
      }
      ImGui::Unindent();


      if (ImGui::Checkbox("PAL",&clockSel)) {
        altered=true;
      }
      if (ImGui::Checkbox(_L("Bypass frequency limits##sgsc"),&bypassLimits)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("chipType",chipType);
          flags.set("chipMem",chipMem);
          flags.set("stereoSep",stereoSep);
          flags.set("bypassLimits",bypassLimits);
        });
      }
      break;
    }
    case DIV_SYSTEM_TIA: {
      bool clockSel=flags.getInt("clockSel",0);
      int mixingType=flags.getInt("mixingType",0);

      ImGui::Text(_L("Mixing mode:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Mono##sgsc"),mixingType==0)) {
        mixingType=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Mono (no distortion)##sgsc"),mixingType==1)) {
        mixingType=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Stereo##sgsc0"),mixingType==2)) {
        mixingType=2;
        altered=true;
      }
      ImGui::Unindent();

      if (ImGui::Checkbox("PAL",&clockSel)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("mixingType",mixingType);
        });
      }
      break;
    }
    case DIV_SYSTEM_PCSPKR: {
      int clockSel=flags.getInt("clockSel",0);
      int speakerType=flags.getInt("speakerType",0);
      bool resetPhase=flags.getBool("resetPhase",false);

      ImGui::Text(_L("Clock rate:##sgsc4"));
      ImGui::Indent();
      if (ImGui::RadioButton("1.19MHz (PC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.99MHz (PC-98)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("2.46MHz (PC-98)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Speaker type:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Unfiltered##sgsc"),speakerType==0)) {
        speakerType=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Cone##sgsc"),speakerType==1)) {
        speakerType=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Piezo##sgsc"),speakerType==2)) {
        speakerType=2;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Use system beeper (Linux only!)##sgsc"),speakerType==3)) {
        speakerType=3;
        altered=true;
      }
      ImGui::Unindent();

      if (ImGui::Checkbox(_L("Reset phase on frequency change##sgsc"),&resetPhase)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("speakerType",speakerType);
          flags.set("resetPhase",resetPhase);
        });
      }
      break;
    }
    case DIV_SYSTEM_QSOUND: {
      int echoDelay=flags.getInt("echoDelay",0);
      int echoFeedback=flags.getInt("echoFeedback",0)&255;

      ImGui::Text(_L("Echo delay:##sgsc1"));
      int echoBufSize1=2725-echoDelay;
      if (CWSliderInt("##EchoBufSize",&echoBufSize1,0,2725)) {
        if (echoBufSize1<0) echoBufSize1=0;
        if (echoBufSize1>2725) echoBufSize1=2725;
        echoDelay=2725-echoBufSize1;
        altered=true;
      } rightClickable
      ImGui::Text(_L("Echo feedback:##sgsc1"));
      if (CWSliderInt("##EchoFeedback",&echoFeedback,0,255)) {
        if (echoFeedback<0) echoFeedback=0;
        if (echoFeedback>255) echoFeedback=255;
        altered=true;
      } rightClickable

      if (altered) {
        e->lockSave([&]() {
          flags.set("echoDelay",echoDelay);
          flags.set("echoFeedback",echoFeedback);
        });
      }

      supportsCustomRate=false;
      break;
    }
    case DIV_SYSTEM_X1_010: {
      int clockSel=flags.getInt("clockSel",0);
      bool stereo=flags.getBool("stereo",false);
      bool isBanked=flags.getBool("isBanked",false);

      ImGui::Text(_L("Clock rate:##sgsc5"));
      ImGui::Indent();
      if (ImGui::RadioButton("16MHz (Seta 1)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("16.67MHz (Seta 2)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("14.32MHz (NTSC)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();

      if (ImGui::Checkbox(_L("Stereo##sgsc1"),&stereo)) {
        altered=true;
      }

      if (ImGui::Checkbox(_L("Bankswitched (Seta 2)##sgsc"),&isBanked)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("stereo",stereo);
          flags.set("isBanked",isBanked);
        });
      }
      break;
    }
    case DIV_SYSTEM_N163: {
      int clockSel=flags.getInt("clockSel",0);
      int channels=flags.getInt("channels",0)+1;
      bool multiplex=flags.getBool("multiplex",false);
      bool lenCompensate=flags.getBool("lenCompensate",false);

      ImGui::Text(_L("Clock rate:##sgsc6"));
      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (1.79MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (1.67MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("Dendy (1.77MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Initial channel limit:##sgsc0"));
      if (CWSliderInt("##N163_InitialChannelLimit",&channels,1,8)) {
        if (channels<1) channels=1;
        if (channels>8) channels=8;
        altered=true;
      } rightClickable
      if (ImGui::Checkbox(_L("Disable hissing##sgsc"),&multiplex)) {
        altered=true;
      }
      if (ImGui::Checkbox(_L("Scale frequency to wave length##sgsc"),&lenCompensate)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("channels",channels-1);
          flags.set("multiplex",multiplex);
          flags.set("lenCompensate",lenCompensate);
        });
      }
      break;
    }
    case DIV_SYSTEM_ES5506: {
      int channels=flags.getInt("channels",0x1f)+1;
      int volScale=flags.getInt("volScale",4095);
      ImGui::Text(_L("Initial channel limit:##sgsc1"));
      if (CWSliderInt("##OTTO_InitialChannelLimit",&channels,5,32)) {
        if (channels<5) channels=5;
        if (channels>32) channels=32;
        altered=true;
      } rightClickable

      ImGui::Text(_L("Volume scale:##sgsc0"));

      if (CWSliderInt("##VolScaleO",&volScale,0,4095)) {
        if (volScale<0) volScale=0;
        if (volScale>4095) volScale=4095;
        altered=true;
      } rightClickable

      if (altered) {
        e->lockSave([&]() {
          flags.set("channels",channels-1);
          flags.set("volScale",volScale);
        });
      }
      break;
    }
    case DIV_SYSTEM_YM2203:
    case DIV_SYSTEM_YM2203_EXT:
    case DIV_SYSTEM_YM2203_CSM: {
      int clockSel=flags.getInt("clockSel",0);
      int prescale=flags.getInt("prescale",0);
      bool noExtMacros=flags.getBool("noExtMacros",false);
      bool fbAllOps=flags.getBool("fbAllOps",false);
      int ssgVol=flags.getInt("ssgVol",128);
      int fmVol=flags.getInt("fmVol",256);

      ImGui::Text(_L("Clock rate:##sgsc7"));
      ImGui::Indent();
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("3.54MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3.9936MHz (PC-88/PC-98)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Output rate:##sgsc0"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("FM: clock / 72, SSG: clock / 16##sgsc0"),prescale==0)) {
        prescale=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("FM: clock / 36, SSG: clock / 8##sgsc"),prescale==1)) {
        prescale=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("FM: clock / 24, SSG: clock / 4##sgsc"),prescale==2)) {
        prescale=2;
        altered=true;
      }
      ImGui::Unindent();

      if (CWSliderInt(_L("SSG Volume##sgsc1"),&ssgVol,0,256)) {
        if (ssgVol<0) ssgVol=0;
        if (ssgVol>256) ssgVol=256;
        altered=true;
      } rightClickable

      if (CWSliderInt(_L("FM Volume##sgsc"),&fmVol,0,256)) {
        if (fmVol<0) fmVol=0;
        if (fmVol>256) fmVol=256;
        altered=true;
      } rightClickable

      if (type==DIV_SYSTEM_YM2203_EXT || type==DIV_SYSTEM_YM2203_CSM) {
        if (ImGui::Checkbox(_L("Disable ExtCh FM macros (compatibility)##sgsc2"),&noExtMacros)) {
          altered=true;
        }
        if (ImGui::Checkbox(_L("Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc2"),&fbAllOps)) {
          altered=true;
        }
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("prescale",prescale);
          flags.set("noExtMacros",noExtMacros);
          flags.set("fbAllOps",fbAllOps);
          flags.set("ssgVol",ssgVol);
          flags.set("fmVol",fmVol);
        });
      }
      break;
    }
    case DIV_SYSTEM_YM2608:
    case DIV_SYSTEM_YM2608_EXT:
    case DIV_SYSTEM_YM2608_CSM: {
      int clockSel=flags.getInt("clockSel",0);
      int prescale=flags.getInt("prescale",0);
      bool noExtMacros=flags.getBool("noExtMacros",false);
      bool fbAllOps=flags.getBool("fbAllOps",false);
      int ssgVol=flags.getInt("ssgVol",128);
      int fmVol=flags.getInt("fmVol",256);

      ImGui::Text(_L("Clock rate:##sgsc8"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("8MHz (Arcade)##sgsc"),clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("7.987MHz (PC-88/PC-98)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Output rate:##sgsc1"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("FM: clock / 144, SSG: clock / 32##sgsc"),prescale==0)) {
        prescale=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("FM: clock / 72, SSG: clock / 16##sgsc1"),prescale==1)) {
        prescale=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("FM: clock / 48, SSG: clock / 8##sgsc"),prescale==2)) {
        prescale=2;
        altered=true;
      }
      ImGui::Unindent();

      if (CWSliderInt(_L("SSG Volume##sgsc2"),&ssgVol,0,256)) {
        if (ssgVol<0) ssgVol=0;
        if (ssgVol>256) ssgVol=256;
        altered=true;
      } rightClickable

      if (CWSliderInt(_L("FM/ADPCM Volume##sgsc1"),&fmVol,0,256)) {
        if (fmVol<0) fmVol=0;
        if (fmVol>256) fmVol=256;
        altered=true;
      } rightClickable

      if (type==DIV_SYSTEM_YM2608_EXT || type==DIV_SYSTEM_YM2608_CSM) {
        if (ImGui::Checkbox(_L("Disable ExtCh FM macros (compatibility)##sgsc3"),&noExtMacros)) {
          altered=true;
        }
        if (ImGui::Checkbox(_L("Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc3"),&fbAllOps)) {
          altered=true;
        }
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("prescale",prescale);
          flags.set("noExtMacros",noExtMacros);
          flags.set("fbAllOps",fbAllOps);
          flags.set("ssgVol",ssgVol);
          flags.set("fmVol",fmVol);
        });
      }
      break;
    }
    case DIV_SYSTEM_RF5C68: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);

      ImGui::Text(_L("Clock rate:##sgsc9"));
      ImGui::Indent();
      if (ImGui::RadioButton("8MHz (FM Towns)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("10MHz (Sega System 18)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("12.5MHz (Sega CD/System 32)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Chip type:##sgsc3"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("RF5C68 (10-bit output)##sgsc"),chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("RF5C164 (16-bit output)##sgsc"),chipType==1)) {
        chipType=1;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("chipType",chipType);
        });
      }
      break;
    }
    case DIV_SYSTEM_MSM6258: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text(_L("Clock rate:##sgsc10"));
      ImGui::Indent();
      if (ImGui::RadioButton("4MHz",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("4.096MHz",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("8MHz (X68000)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("8.192MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      ImGui::Unindent();
      
      int chipClock=flags.getInt("customClock",0);
      if (!chipClock) {
        switch (clockSel) {
          case 0:
            chipClock=4000000;
            break;
          case 1:
            chipClock=4096000;
            break;
          case 2:
            chipClock=8000000;
            break;
          case 3:
            chipClock=8192000;
            break;
        }
      }

      ImGui::Text(_L("Sample rate table:##sgsc"));
      if (ImGui::BeginTable("6258Rate",3)) {
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        ImGui::TableNextColumn();
        ImGui::Text(_L("divider \\ clock##sgsc"));
        ImGui::TableNextColumn();
        ImGui::Text(_L("full##sgsc"));
        ImGui::TableNextColumn();
        ImGui::Text(_L("half##sgsc"));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg,ImGui::GetColorU32(ImGuiCol_TableHeaderBg));
        ImGui::Text("/512");
        ImGui::TableNextColumn();
        ImGui::Text("%dHz",chipClock/512);
        ImGui::TableNextColumn();
        ImGui::Text("%dHz",chipClock/1024);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg,ImGui::GetColorU32(ImGuiCol_TableHeaderBg));
        ImGui::Text("/768");
        ImGui::TableNextColumn();
        ImGui::Text("%dHz",chipClock/768);
        ImGui::TableNextColumn();
        ImGui::Text("%dHz",chipClock/1536);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg,ImGui::GetColorU32(ImGuiCol_TableHeaderBg));
        ImGui::Text("/1024");
        ImGui::TableNextColumn();
        ImGui::Text("%dHz",chipClock/1024);
        ImGui::TableNextColumn();
        ImGui::Text("%dHz",chipClock/2048);

        ImGui::EndTable();
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_MSM6295: {
      int clockSel=flags.getInt("clockSel",0);
      bool rateSel=flags.getBool("rateSel",false);

      ImGui::Text(_L("Clock rate:##sgsc11"));
      ImGui::Indent();
      if (ImGui::RadioButton("0.875MHz",clockSel==10)) {
        clockSel=10;
        altered=true;
      }
      if (ImGui::RadioButton("0.89MHz",clockSel==7)) {
        clockSel=7;
        altered=true;
      }
      if (ImGui::RadioButton("0.9375MHz",clockSel==11)) {
        clockSel=11;
        altered=true;
      }
      if (ImGui::RadioButton("1MHz",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.02MHz",clockSel==6)) {
        clockSel=6;
        altered=true;
      }
      if (ImGui::RadioButton("1.056MHz",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("1.193MHz (Atari)",clockSel==14)) {
        clockSel=14;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz",clockSel==12)) {
        clockSel=12;
        altered=true;
      }
      if (ImGui::RadioButton("1.79MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz",clockSel==8)) {
        clockSel=8;
        altered=true;
      }
      if (ImGui::RadioButton("2.112MHz",clockSel==9)) {
        clockSel=9;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz",clockSel==13)) {
        clockSel=13;
        altered=true;
      }
      if (ImGui::RadioButton("3.58MHz",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("4.224MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      ImGui::Unindent();
      ImGui::Text(_L("Output rate:##sgsc2"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("clock / 132##sgsc"),rateSel==0)) {
        rateSel=false;
        altered=true;
      }
      if (ImGui::RadioButton(_L("clock / 165##sgsc"),rateSel==1)) {
        rateSel=true;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("rateSel",rateSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_SCC:
    case DIV_SYSTEM_SCC_PLUS: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text(_L("Clock rate:##sgsc12"));
      ImGui::Indent();
      if (ImGui::RadioButton("1.79MHz (NTSC/MSX)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.77MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("1.5MHz (Arcade)##sgsc"),clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPL:
    case DIV_SYSTEM_OPL_DRUMS:
    case DIV_SYSTEM_OPL2:
    case DIV_SYSTEM_OPL2_DRUMS:
    case DIV_SYSTEM_Y8950:
    case DIV_SYSTEM_Y8950_DRUMS: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text(_L("Clock rate:##sgsc13"));
      ImGui::Indent();
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("3.54MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3.9936MHz (PC-88/PC-98)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("3.5MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPL3:
    case DIV_SYSTEM_OPL3_DRUMS: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool compatPan=flags.getBool("compatPan",false);

      ImGui::Text(_L("Clock rate:##sgsc14"));
      ImGui::Indent();
      if (ImGui::RadioButton("14.32MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("14.19MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("14MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("16MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("15MHz",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("33.8688MHz (OPL3-L)",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      ImGui::Text(_L("Chip type:##sgsc4"));
      if (ImGui::RadioButton("OPL3 (YMF262)",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("OPL3-L (YMF289B)",chipType==1)) {
        chipType=1;
        altered=true;
      }
      ImGui::Unindent();

      if (ImGui::Checkbox(_L("Compatible panning (0800)##sgsc"),&compatPan)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("chipType",chipType);
          flags.set("compatPan",compatPan);
        });
      }
      break;
    }
    case DIV_SYSTEM_YMZ280B: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text(_L("Clock rate:##sgsc15"));
      ImGui::Indent();
      if (ImGui::RadioButton("16.9344MHz",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("14.32MHz (NTSC)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("14.19MHz (PAL)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("16MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("16.67MHz",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("14MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_PCM_DAC: {
      // default to 44100Hz 16-bit stereo
      int sampRate=flags.getInt("rate",44100);
      int bitDepth=flags.getInt("outDepth",15)+1;
      int interpolation=flags.getInt("interpolation",0);
      bool stereo=flags.getBool("stereo",false);

      ImGui::Text(_L("Output rate:##sgsc3"));
      if (CWSliderInt("##SampRate",&sampRate,1000,96000)) {
        if (sampRate<1000) sampRate=1000;
        if (sampRate>96000) sampRate=96000;
        altered=true;
      } rightClickable
      ImGui::Text(_L("Output bit depth:##sgsc"));
      if (CWSliderInt("##BitDepth",&bitDepth,1,16)) {
        if (bitDepth<1) bitDepth=1;
        if (bitDepth>16) bitDepth=16;
        altered=true;
      } rightClickable
      if (ImGui::Checkbox(_L("Stereo##sgsc2"),&stereo)) {
        altered=true;
      }

      ImGui::Text(_L("Interpolation:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("None##sgsc"),interpolation==0)) {
        interpolation=0;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Linear##sgsc"),interpolation==1)) {
        interpolation=1;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Cubic##sgsc"),interpolation==2)) {
        interpolation=2;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Sinc##sgsc"),interpolation==3)) {
        interpolation=3;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("rate",sampRate);
          flags.set("outDepth",bitDepth-1);
          flags.set("stereo",stereo);
          flags.set("interpolation",interpolation);
        });
      }
      break;
    }
    case DIV_SYSTEM_SNES: {
      char temp[64];
      int vsL=127-(flags.getInt("volScaleL",0)&127);
      int vsR=127-(flags.getInt("volScaleR",0)&127);
      bool echo=flags.getBool("echo",false);
      int echoVolL=flags.getInt("echoVolL",127);
      int echoVolR=flags.getInt("echoVolR",127);
      int echoDelay=flags.getInt("echoDelay",0)&15;
      int echoFeedback=flags.getInt("echoFeedback",0);
      int echoMask=flags.getInt("echoMask",0);

      int echoFilter[8];
      echoFilter[0]=flags.getInt("echoFilter0",127);
      echoFilter[1]=flags.getInt("echoFilter1",0);
      echoFilter[2]=flags.getInt("echoFilter2",0);
      echoFilter[3]=flags.getInt("echoFilter3",0);
      echoFilter[4]=flags.getInt("echoFilter4",0);
      echoFilter[5]=flags.getInt("echoFilter5",0);
      echoFilter[6]=flags.getInt("echoFilter6",0);
      echoFilter[7]=flags.getInt("echoFilter7",0);

      ImGui::Text(_L("Volume scale:##sgsc1"));
      if (CWSliderInt(_L("Left##VolScaleL"),&vsL,0,127)) {
        if (vsL<0) vsL=0;
        if (vsL>127) vsL=127;
        altered=true;
      } rightClickable
      if (CWSliderInt(_L("Right##VolScaleL"),&vsR,0,127)) {
        if (vsR<0) vsR=0;
        if (vsR>127) vsR=127;
        altered=true;
      } rightClickable

      if (ImGui::Checkbox(_L("Enable echo##sgsc1"),&echo)) {
        altered=true;
      }
      
      ImGui::Text(_L("Initial echo state:##sgsc"));
      for (int i=0; i<8; i++) {
        bool echoChan=(bool)(echoMask&(1<<i));
        snprintf(temp,63,"%d##EON%d",i+1,i);
        if (ImGui::Checkbox(temp,&echoChan)) {
          echoMask&=~(1<<i);
          if (echoChan) {
            echoMask|=1<<i;
          }
          altered=true;
        }
        if (i<7) {
          if (fromMenu) {
            ImGui::SameLine();
          } else {
            sameLineMaybe();
          }
        }
      }

      if (CWSliderInt(_L("Delay##EchoDelay"),&echoDelay,0,15)) {
        if (echoDelay<0) echoDelay=0;
        if (echoDelay>15) echoDelay=15;
        altered=true;
      } rightClickable

      if (CWSliderInt(_L("Feedback##EchoFeedback"),&echoFeedback,-128,127)) {
        if (echoFeedback<-128) echoFeedback=-128;
        if (echoFeedback>127) echoFeedback=127;
        altered=true;
      } rightClickable

      ImGui::Text(_L("Echo volume:##sgsc1"));
      if (CWSliderInt(_L("Left##EchoVolL"),&echoVolL,-128,127)) {
        if (echoVolL<-128) echoVolL=-128;
        if (echoVolL>127) echoVolL=127;
        altered=true;
      } rightClickable
      if (CWSliderInt(_L("Right##EchoVolL"),&echoVolR,-128,127)) {
        if (echoVolR<-128) echoVolR=-128;
        if (echoVolR>127) echoVolR=127;
        altered=true;
      } rightClickable

      ImGui::Text(_L("Echo filter:##sgsc"));
      for (int i=0; i<8; i++) {
        snprintf(temp,63,"%d##FIR%d",i+1,i);
        if (CWSliderInt(temp,&echoFilter[i],-128,127)) {
          if (echoFilter[i]<-128) echoFilter[i]=-128;
          if (echoFilter[i]>127) echoFilter[i]=127;
          altered=true;
        } rightClickable
      }

      if (ImGui::Button(snesFilterHex?_L("Hex##SNESFHex"):_L("Dec##SNESFHex"))) {
        snesFilterHex=!snesFilterHex;
      }
      ImGui::SameLine();
      ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x); // wavetable text input size found here
      if (ImGui::InputText("##MMLWave",&mmlStringSNES[sysPos])) {
        int actualData[256];
        int discardIt=0;
        memset(actualData,0,256*sizeof(int));
        decodeMMLStrW(mmlStringSNES[sysPos],actualData,discardIt,snesFilterHex?0:-128,snesFilterHex?255:127,snesFilterHex);
        if (snesFilterHex) {
          for (int i=0; i<8; i++) {
            if (actualData[i]>=128) actualData[i]-=256;
          }
        }
        memcpy(echoFilter,actualData,8*sizeof(int));
        altered=true;
      }
      if (!ImGui::IsItemActive()) {
        int actualData[8];
        for (int i=0; i<8; i++) {
          if (echoFilter[i]<0 && snesFilterHex) {
            actualData[i]=echoFilter[i]+256;
          } else {
            actualData[i]=echoFilter[i];
          }
        }
        encodeMMLStr(mmlStringSNES[sysPos],actualData,8,-1,-1,snesFilterHex);
      }

      int filterSum=(
        echoFilter[0]+
        echoFilter[1]+
        echoFilter[2]+
        echoFilter[3]+
        echoFilter[4]+
        echoFilter[5]+
        echoFilter[6]+
        echoFilter[7]
      );

      ImGui::PushStyleColor(ImGuiCol_Text,(filterSum<-128 || filterSum>127)?uiColors[GUI_COLOR_LOGLEVEL_WARNING]:uiColors[GUI_COLOR_TEXT]);
      ImGui::Text(_L("sum: %d##sgsc"),filterSum);
      ImGui::PopStyleColor();

      if (altered) {
        e->lockSave([&]() {
          flags.set("volScaleL",127-vsL);
          flags.set("volScaleR",127-vsR);
          flags.set("echo",echo);
          flags.set("echoVolL",echoVolL);
          flags.set("echoVolR",echoVolR);
          flags.set("echoDelay",echoDelay);
          flags.set("echoFeedback",echoFeedback);
          flags.set("echoFilter0",echoFilter[0]);
          flags.set("echoFilter1",echoFilter[1]);
          flags.set("echoFilter2",echoFilter[2]);
          flags.set("echoFilter3",echoFilter[3]);
          flags.set("echoFilter4",echoFilter[4]);
          flags.set("echoFilter5",echoFilter[5]);
          flags.set("echoFilter6",echoFilter[6]);
          flags.set("echoFilter7",echoFilter[7]);
          flags.set("echoMask",echoMask);
        });
      }

      supportsCustomRate=false;

      break;
    }
    case DIV_SYSTEM_MSM5232: {
      int detune=flags.getInt("detune",0);
      int vibSpeed=flags.getInt("vibSpeed",0);
      float vibDepth=flags.getFloat("vibDepth",0.0f);
      bool groupEnv[2];
      int groupVol[8];
      float capValue[8];
      char temp[64];
      groupEnv[0]=flags.getBool("groupEnv0",true);
      groupEnv[1]=flags.getBool("groupEnv1",true);
      groupVol[0]=flags.getInt("partVolume0",255);
      groupVol[1]=flags.getInt("partVolume1",255);
      groupVol[2]=flags.getInt("partVolume2",255);
      groupVol[3]=flags.getInt("partVolume3",255);
      groupVol[4]=flags.getInt("partVolume4",255);
      groupVol[5]=flags.getInt("partVolume5",255);
      groupVol[6]=flags.getInt("partVolume6",255);
      groupVol[7]=flags.getInt("partVolume7",255);
      capValue[0]=flags.getFloat("capValue0",390.0f);
      capValue[1]=flags.getFloat("capValue1",390.0f);
      capValue[2]=flags.getFloat("capValue2",390.0f);
      capValue[3]=flags.getFloat("capValue3",390.0f);
      capValue[4]=flags.getFloat("capValue4",390.0f);
      capValue[5]=flags.getFloat("capValue5",390.0f);
      capValue[6]=flags.getFloat("capValue6",390.0f);
      capValue[7]=flags.getFloat("capValue7",390.0f);

      if (CWSliderInt(_L("Detune##sgsc"),&detune,-127,127)) {
        if (detune<-127) detune=-127;
        if (detune>127) detune=127;
        altered=true;
      } rightClickable

      ImGui::Text(_L("Capacitor values (nF):##sgsc"));
       for (int i=0; i<8; i++) {
        snprintf(temp,63,"%d##CAPV%d",i+1,i);
        if (CWSliderFloat(temp,&capValue[i],1.0f,1000.0f)) {
          if (capValue[i]<0) capValue[i]=0;
          if (capValue[i]>1000) capValue[i]=1000;
          altered=true;
        } rightClickable
      }
      
      ImGui::Text(_L("Initial part volume (channel 1-4):##sgsc"));
      for (int i=0; i<4; i++) {
        snprintf(temp,63,"%d'##GRPV%d",2<<i,i);
        if (CWSliderInt(temp,&groupVol[i],0,255)) {
          if (groupVol[i]<0) groupVol[i]=0;
          if (groupVol[i]>255) groupVol[i]=255;
          altered=true;
        } rightClickable
      }

      ImGui::Text(_L("Initial part volume (channel 5-8):##sgsc"));
      for (int i=4; i<8; i++) {
        snprintf(temp,63,"%d'##GRPV%d",2<<(i-4),i);
        if (CWSliderInt(temp,&groupVol[i],0,255)) {
          if (groupVol[i]<0) groupVol[i]=0;
          if (groupVol[i]>255) groupVol[i]=255;
          altered=true;
        } rightClickable
      }

      ImGui::Text(_L("Envelope mode (channel 1-4):##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Capacitor (attack/decay)##EM00"),groupEnv[0])) {
        groupEnv[0]=true;
        altered=true;
      }
      if (ImGui::RadioButton(_L("External (volume macro)##EM01"),!groupEnv[0])) {
        groupEnv[0]=false;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Envelope mode (channel 5-8):##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Capacitor (attack/decay)##EM10"),groupEnv[1])) {
        groupEnv[1]=true;
        altered=true;
      }
      if (ImGui::RadioButton(_L("External (volume macro)##EM11"),!groupEnv[1])) {
        groupEnv[1]=false;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Global vibrato:##sgsc"));

      if (CWSliderInt(_L("Speed##sgsc"),&vibSpeed,0,256)) {
        if (vibSpeed<0) vibSpeed=0;
        if (vibSpeed>256) vibSpeed=256;
        altered=true;
      } rightClickable
      if (CWSliderFloat(_L("Depth##sgsc"),&vibDepth,0.0f,256.0f)) {
        if (vibDepth<0) vibDepth=0;
        if (vibDepth>256) vibDepth=256;
        altered=true;
      } rightClickable

      if (altered) {
        flags.set("detune",detune);
        flags.set("vibSpeed",vibSpeed);
        flags.set("vibDepth",vibDepth);

        flags.set("capValue0",capValue[0]);
        flags.set("capValue1",capValue[1]);
        flags.set("capValue2",capValue[2]);
        flags.set("capValue3",capValue[3]);
        flags.set("capValue4",capValue[4]);
        flags.set("capValue5",capValue[5]);
        flags.set("capValue6",capValue[6]);
        flags.set("capValue7",capValue[7]);

        flags.set("partVolume0",groupVol[0]);
        flags.set("partVolume1",groupVol[1]);
        flags.set("partVolume2",groupVol[2]);
        flags.set("partVolume3",groupVol[3]);
        flags.set("partVolume4",groupVol[4]);
        flags.set("partVolume5",groupVol[5]);
        flags.set("partVolume6",groupVol[6]);
        flags.set("partVolume7",groupVol[7]);

        flags.set("groupEnv0",groupEnv[0]);
        flags.set("groupEnv1",groupEnv[1]);
      }
      break;
    }
    case DIV_SYSTEM_T6W28: {
      bool noEasyNoise=flags.getBool("noEasyNoise",false);

      if (ImGui::Checkbox(_L("Disable easy period to note mapping on upper octaves##sgsc1"),&noEasyNoise)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("noEasyNoise",noEasyNoise);
        });
      }
      break;
    }
    case DIV_SYSTEM_K007232: {
      bool stereo=flags.getBool("stereo",false);

      if (ImGui::Checkbox(_L("Stereo##sgsc3"),&stereo)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("stereo",stereo);
        });
      }
      break;
    }
    case DIV_SYSTEM_NAMCO:
    case DIV_SYSTEM_NAMCO_15XX: {
      bool romMode=flags.getBool("romMode",false);

      ImGui::Text(_L("Waveform storage mode:##sgsc0"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("RAM##sgsc"),!romMode)) {
        romMode=false;
        altered=true;
      }
      if (ImGui::RadioButton(_L("ROM (up to 8 waves)##sgsc"),romMode)) {
        romMode=true;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("romMode",romMode);
        });
      }
      break;
    }
    case DIV_SYSTEM_NAMCO_CUS30: {
      bool newNoise=flags.getBool("newNoise",true);

      if (InvCheckbox(_L("Compatible noise frequencies##sgsc"),&newNoise)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("newNoise",newNoise);
        });
      }
      break;
    }
    case DIV_SYSTEM_SEGAPCM:
    case DIV_SYSTEM_SEGAPCM_COMPAT: {
      bool oldSlides=flags.getBool("oldSlides",false);

      if (ImGui::Checkbox(_L("Legacy slides and pitch (compatibility)##sgsc"),&oldSlides)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("oldSlides",oldSlides);
        });
      }
      break;
    }
    case DIV_SYSTEM_SM8521:/*  {
      bool noAntiClick=flags.getBool("noAntiClick",false);

      if (ImGui::Checkbox("Disable anti-click",&noAntiClick)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("noAntiClick",noAntiClick);
        });
      }
      break;
    }*/
    case DIV_SYSTEM_K053260: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text(_L("Clock rate:##sgsc16"));
      ImGui::Indent();
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_TED: {
      int clockSel=flags.getInt("clockSel",0);
      bool keyPriority=flags.getBool("keyPriority",true);

      ImGui::Text(_L("Clock rate:##sgsc17"));

      ImGui::Indent();
      if (ImGui::RadioButton("NTSC (1.79MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (1.77MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Unindent();

      ImGui::Text(_L("Global parameter priority:##sgsc1"));

      ImGui::Indent();
      if (ImGui::RadioButton(_L("Left to right##sgsc1"),!keyPriority)) {
        keyPriority=false;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Last used channel##sgsc1"),keyPriority)) {
        keyPriority=true;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("keyPriority",keyPriority);
        });
      }
      break;
    }
    case DIV_SYSTEM_C140: {
      int bankType=flags.getInt("bankType",0);

      ImGui::Text(_L("Banking style:##sgsc"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Namco System 2 (2MB)##sgsc"),bankType==0)) {
        bankType=0;
        altered=true;
        mustRender=true;
      }
      if (ImGui::RadioButton(_L("Namco System 21 (4MB)##sgsc"),bankType==1)) {
        bankType=1;
        altered=true;
        mustRender=true;
      }
      if (ImGui::RadioButton(_L("Raw (16MB; no VGM export!)##sgsc"),bankType==2)) {
        bankType=2;
        altered=true;
        mustRender=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("bankType",bankType);
        });
      }
      break;
    }
    case DIV_SYSTEM_VBOY: {
      bool romMode=flags.getBool("romMode",false);

      ImGui::Text(_L("Waveform storage mode:##sgsc1"));
      ImGui::Indent();
      if (ImGui::RadioButton(_L("Dynamic (unconfirmed)##sgsc"),!romMode)) {
        romMode=false;
        altered=true;
      }
      if (ImGui::RadioButton(_L("Static (up to 5 waves)##sgsc"),romMode)) {
        romMode=true;
        altered=true;
      }
      ImGui::Unindent();

      if (altered) {
        e->lockSave([&]() {
          flags.set("romMode",romMode);
        });
      }
      break;
    }
    case DIV_SYSTEM_SFX_BEEPER_QUADTONE: {
      bool sysPal=flags.getInt("clockSel",0);
      bool noHiss=flags.getBool("noHiss",false);
      if (ImGui::Checkbox("PAL",&sysPal)) {
        altered=true;
      }
      if (ImGui::Checkbox("Disable hissing",&noHiss)) {
        altered=true;
      }
      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)sysPal);
          flags.set("noHiss",noHiss);
        });
      }
      break;
    }
    case DIV_SYSTEM_SWAN:
    case DIV_SYSTEM_BUBSYS_WSG:
    case DIV_SYSTEM_PET:
    case DIV_SYSTEM_GA20:
    case DIV_SYSTEM_PV1000:
    case DIV_SYSTEM_VERA:
    case DIV_SYSTEM_C219:
      break;
    case DIV_SYSTEM_YMU759:
    case DIV_SYSTEM_ESFM:
      supportsCustomRate=false;
      ImGui::Text(_L("nothing to configure##sgsc"));
      break;
    case DIV_SYSTEM_ES5503:
    {
      bool mono = flags.getBool("monoOutput", false);

      if (ImGui::Checkbox(_L("Downmix chip output to mono##sgsc"), &mono)) {
        altered = true;
      }

      int reserved = flags.getInt("reserveBlocks",0);

      if(rerender_es5503)
      {
        e->renderSamples(-1); //hack! it needs rerendering two times...
        rerender_es5503 = false;
      }

      ImGui::TextUnformatted(_L("Reserved blocks for wavetables:##sgsc"));
      if(CWSliderInt("",&reserved,0,32))
      {
        altered = true;
        rerender_es5503 = true;
      }

      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Reserve this many blocks 256 bytes each in sample memory.\nEach block holds one wavetable (is used for one wavetable channel),\nso reserve as many as you need.##sgsc"));
      }

      if (altered) {
        e->lockSave([&]() {
            flags.set("monoOutput", mono);
            flags.set("reserveBlocks", reserved);
        });

        e->renderSamples(-1); //hack! it needs rerendering two times...
      }
      break;
    }
    default: {
      bool sysPal=flags.getInt("clockSel",0);

      if (ImGui::Checkbox("PAL",&sysPal)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)sysPal);
        });
      }
      break;
    }
  }

  if (supportsCustomRate) {
    ImGui::Separator();
    int customClock=flags.getInt("customClock",0);
    bool usingCustomClock=customClock>=MIN_CUSTOM_CLOCK;

    if (ImGui::Checkbox(_L("Custom clock rate##sgsc"),&usingCustomClock)) {
      if (usingCustomClock) {
        customClock=MIN_CUSTOM_CLOCK;
      } else {
        customClock=0;
      }
      altered=true;
    }
    ImGui::Indent();
    if (ImGui::InputInt("Hz",&customClock,100,10000)) {
      if (customClock<MIN_CUSTOM_CLOCK) customClock=0;
      if (customClock>MAX_CUSTOM_CLOCK) customClock=MAX_CUSTOM_CLOCK;
      altered=true;
    }
    ImGui::Unindent();

    if (altered) {
      e->lockSave([&]() {
        flags.set("customClock",customClock);
      });
    }
  }

  if (altered) {
    if (chan>=0) {
      e->updateSysFlags(chan,restart,mustRender);
      if (e->song.autoSystem) {
        autoDetectSystem();
      }
      updateWindowTitle();
    }
    MARK_MODIFIED;
  }

  return altered;
}
