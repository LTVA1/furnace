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

#define _USE_MATH_DEFINES
#include "gui.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <math.h>
#include "../ta-log.h"
#include "IconsFontAwesome4.h"
#include "furIcons.h"
#include "misc/cpp/imgui_stdlib.h"
#include <fmt/printf.h>
#include "guiConst.h"
#include "sampleUtil.h"
#include "util.h"

const double timeDivisors[10]={
  1000.0, 500.0, 200.0, 100.0, 50.0, 20.0, 10.0, 5.0, 2.0, 1.0
};

const double timeMultipliers[13]={
  1.0, 2.0, 5.0, 10.0, 20.0, 30.0,
  60.0, 2*60.0, 5*60.0, 10*60.0, 20*60.0, 30*60.0,
  3600.0
};

#define CENTER_TEXT(text) \
  ImGui::SetCursorPosX(ImGui::GetCursorPosX()+0.5*(ImGui::GetContentRegionAvail().x-ImGui::CalcTextSize(text).x));

#define SAMPLE_WARN(_x,_text) \
  if (_x.find(_text)==String::npos) { \
    if (!_x.empty()) _x+='\n'; \
    _x+=_text; \
  }

#define MAX_RATE(_name,_x) \
   if (e->isPreviewingSample()) { \
     if ((int)e->getSamplePreviewRate()>(int)(_x)) { \
       SAMPLE_WARN(warnRate,fmt::sprintf(_L("%s: maximum sample rate is %d##sgse"),_name,(int)(_x))); \
     } \
   }

#define MIN_RATE(_name,_x) \
   if (e->isPreviewingSample()) { \
     if ((int)e->getSamplePreviewRate()<(int)(_x)) { \
       SAMPLE_WARN(warnRate,fmt::sprintf(_L("%s: minimum sample rate is %d##sgse"),_name,(int)(_x))); \
     } \
   }

#define EXACT_RATE(_name,_x) \
   if (e->isPreviewingSample()) { \
     if ((int)e->getSamplePreviewRate()!=(int)(_x)) { \
       SAMPLE_WARN(warnRate,fmt::sprintf(_L("%s: sample rate must be %d##sgse"),_name,(int)(_x))); \
     } \
   }

void FurnaceGUI::drawSampleEdit() {
  if (nextWindow==GUI_WINDOW_SAMPLE_EDIT) {
    sampleEditOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!sampleEditOpen) return;
  if (mobileUI) {
    patWindowPos=(portrait?ImVec2(0.0f,(mobileMenuPos*-0.65*canvasH)):ImVec2((0.16*canvasH)+0.5*canvasW*mobileMenuPos,0.0f));
    patWindowSize=(portrait?ImVec2(canvasW,canvasH-(0.16*canvasW)-(pianoOpen?(0.4*canvasW):0.0f)):ImVec2(canvasW-(0.16*canvasH),canvasH-(pianoOpen?(0.3*canvasH):0.0f)));
    ImGui::SetNextWindowPos(patWindowPos);
    ImGui::SetNextWindowSize(patWindowSize);
  }
  if (ImGui::Begin("Sample Editor",&sampleEditOpen,globalWinFlags|(settings.allowEditDocking?0:ImGuiWindowFlags_NoDocking), _L("Sample Editor###Sample Editor"))) {
    if (curSample<0 || curSample>=(int)e->song.sample.size()) {
      ImGui::SetCursorPosY(ImGui::GetCursorPosY()+(ImGui::GetContentRegionAvail().y-ImGui::GetFrameHeightWithSpacing()*2.0f)*0.5f);
      CENTER_TEXT(_L("no sample selected##sgse"));
      ImGui::Text(_L("no sample selected##sgse"));
      if (ImGui::BeginTable("noAssetCenter",3)) {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.5f);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthStretch,0.5f);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();

        if (e->song.sample.size()>0) {
          if (ImGui::BeginCombo("##SampleSelect",_L("select one...##sgse"))) {
            if (ImGui::BeginTable("SampleSelCombo",1,ImGuiTableFlags_ScrollY)) {
              actualSampleList();
              ImGui::EndTable();
            }
            ImGui::EndCombo();
          }
          ImGui::SameLine();
          ImGui::TextUnformatted(_L("or##sgse0"));
          ImGui::SameLine();
        }
        if (ImGui::Button(_L("Open##sgse0"))) {
          doAction(GUI_ACTION_SAMPLE_LIST_OPEN);
        }
        ImGui::SameLine();
        ImGui::TextUnformatted(_L("or##sgse1"));
        ImGui::SameLine();
        if (ImGui::Button(_L("Create New##sgse"))) {
          doAction(GUI_ACTION_SAMPLE_LIST_ADD);
        }

        ImGui::TableNextColumn();
        ImGui::EndTable();
      }
    } else {
      DivSample* sample=e->song.sample[curSample];
      String sampleType=_L("Invalid##sgse0");
      if (sample->depth<DIV_SAMPLE_DEPTH_MAX) {
        if (sampleDepths[sample->depth]!=NULL) {
          sampleType=_L(sampleDepths[sample->depth]);
        }
      }
      String loopType=_L("Invalid##sgse1");
      if (sample->loopMode<DIV_SAMPLE_LOOP_MAX) {
        if (sampleLoopModes[sample->loopMode]!=NULL) {
          loopType=_L(sampleLoopModes[sample->loopMode]);
        }
      }

      String sampleIndex=fmt::sprintf("%d",curSample);
      ImGui::SetNextItemWidth(72.0f*dpiScale);
      if (ImGui::BeginCombo("##SampleSelect",sampleIndex.c_str())) {
        String name;
        for (size_t i=0; i<e->song.sample.size(); i++) {
          name=fmt::sprintf("%d: %s##_SMPS%d",i,e->song.sample[i]->name,i);
          if (ImGui::Selectable(name.c_str(),curSample==(int)i)) {
            curSample=i;
            sample=e->song.sample[curSample];
            updateSampleTex=true;
          }
        }
        ImGui::EndCombo();
      }

      ImGui::SameLine();

      if (ImGui::Button(ICON_FA_FOLDER_OPEN "##SELoad")) {
        doAction(GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Open##sgse1"));
      }
      if (ImGui::BeginPopupContextItem("SampleEOpenOpt")) {
        if (ImGui::MenuItem(_L("import raw...##sgse"))) {
          doAction((curSample>=0 && curSample<(int)e->song.sample.size())?GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE_RAW:GUI_ACTION_SAMPLE_LIST_OPEN_RAW);
        }
        ImGui::EndPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_FLOPPY_O "##SESave")) {
        doAction(GUI_ACTION_SAMPLE_LIST_SAVE);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Save##sgse"));
      }
      if (ImGui::BeginPopupContextItem("SampleESaveOpt")) {
        if (ImGui::MenuItem(_L("save raw...##sgse"))) {
          doAction(GUI_ACTION_SAMPLE_LIST_SAVE_RAW);
        }
        ImGui::EndPopup();
      }

      ImGui::SameLine();

      ImGui::Text(_L("Name##sgse"));
      ImGui::SameLine();
      ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
      ImGui::PushID(2+curSample);
      if (ImGui::InputText("##SampleName",&sample->name)) {
        MARK_MODIFIED;
      }
      ImGui::PopID();

      ImGui::Separator();

      String warnLoop, warnLoopMode, warnLoopPos;
      String warnLoopStart, warnLoopEnd;
      String warnLength, warnRate;

      bool isChipVisible[DIV_MAX_CHIPS];
      bool isTypeVisible[DIV_MAX_SAMPLE_TYPE];
      bool isMemVisible[DIV_MAX_SAMPLE_TYPE][DIV_MAX_CHIPS];
      bool isMemWarning[DIV_MAX_SAMPLE_TYPE][DIV_MAX_CHIPS];
      memset(isChipVisible,0,DIV_MAX_CHIPS*sizeof(bool));
      memset(isTypeVisible,0,DIV_MAX_SAMPLE_TYPE*sizeof(bool));
      memset(isMemVisible,0,DIV_MAX_CHIPS*DIV_MAX_SAMPLE_TYPE*sizeof(bool));
      memset(isMemWarning,0,DIV_MAX_CHIPS*DIV_MAX_SAMPLE_TYPE*sizeof(bool));

      for (int i=0; i<e->song.systemLen; i++) {
        DivDispatch* dispatch=e->getDispatch(i);

        // warnings
        switch (e->song.system[i]) {
          case DIV_SYSTEM_SNES:
            if (sample->loop) {
              if (sample->loopStart&15) {
                int tryWith=(sample->loopStart+8)&(~15);
                if (tryWith>(int)sample->samples) tryWith-=16;
                String alignHint=fmt::sprintf(_L("SNES: loop start must be a multiple of 16 (try with %d)##sgse"),tryWith);
                SAMPLE_WARN(warnLoopStart,alignHint);
              }
              if (sample->loopEnd&15) {
                int tryWith=(sample->loopEnd+8)&(~15);
                if (tryWith>(int)sample->samples) tryWith-=16;
                String alignHint=fmt::sprintf(_L("SNES: loop end must be a multiple of 16 (try with %d)##sgse"),tryWith);
                SAMPLE_WARN(warnLoopEnd,alignHint);
              }
            }
            if (sample->samples&15) {
              SAMPLE_WARN(warnLength,_L("SNES: sample length will be padded to multiple of 16##sgse"));
            }
            if (dispatch!=NULL) {
              MAX_RATE("SNES",dispatch->chipClock/8.0);
            }
            break;
          case DIV_SYSTEM_QSOUND:
            if (sample->loop) {
              if (sample->loopEnd-sample->loopStart>32767) {
                SAMPLE_WARN(warnLoopPos,_L("QSound: loop cannot be longer than 32767 samples##sgse"));
              }
            }
            if (sample->samples>65535) {
              SAMPLE_WARN(warnLength,_L("QSound: maximum sample length is 65535##sgse"));
            }
            break;
          case DIV_SYSTEM_NES:
            if (sample->loop) {
              if (sample->loopStart!=0 || sample->loopEnd!=(int)(sample->samples)) {
                SAMPLE_WARN(warnLoopPos,_L("NES: loop point ignored on DPCM (may only loop entire sample)##sgse"));
              }
            }
            if (sample->samples>32648) {
              SAMPLE_WARN(warnLength,_L("NES: maximum DPCM sample length is 32648##sgse"));
            }
            break;
          case DIV_SYSTEM_X1_010:
            if (sample->loop) {
              SAMPLE_WARN(warnLoop,_L("X1-010: samples can't loop##sgse"));
            }
            if (sample->samples>131072) {
              SAMPLE_WARN(warnLength,_L("X1-010: maximum sample length is 131072##sgse"));
            }
            break;
          case DIV_SYSTEM_GA20:
            if (sample->loop) {
              SAMPLE_WARN(warnLoop,_L("GA20: samples can't loop##sgse"));
            }
            if (dispatch!=NULL) {
              MIN_RATE("GA20",dispatch->chipClock/1024);
            }
            break;
          case DIV_SYSTEM_YM2608:
          case DIV_SYSTEM_YM2608_EXT:
          case DIV_SYSTEM_YM2608_CSM:
            if (sample->loop) {
              if (sample->loopStart!=0 || sample->loopEnd!=(int)(sample->samples)) {
                SAMPLE_WARN(warnLoopPos,_L("YM2608: loop point ignored on ADPCM (may only loop entire sample)##sgse"));
              }
              if (sample->samples&511) {
                SAMPLE_WARN(warnLength,_L("YM2608: sample length will be padded to multiple of 512##sgse"));
              }
            }
            break;
          case DIV_SYSTEM_YM2610_FULL:
          case DIV_SYSTEM_YM2610_FULL_EXT:
          case DIV_SYSTEM_YM2610_CSM:
          case DIV_SYSTEM_YM2610B:
          case DIV_SYSTEM_YM2610B_EXT:
            if (sample->loop) {
              SAMPLE_WARN(warnLoop,_L("YM2610: ADPCM-A samples can't loop##sgse"));
              if (sample->loopStart!=0 || sample->loopEnd!=(int)(sample->samples)) {
                SAMPLE_WARN(warnLoopPos,_L("YM2610: loop point ignored on ADPCM-B (may only loop entire sample)##sgse"));
              }
              if (sample->samples&511) {
                SAMPLE_WARN(warnLength,_L("YM2610: sample length will be padded to multiple of 512##sgse"));
              }
            }
            if (sample->samples>2097152) {
              SAMPLE_WARN(warnLength,_L("YM2610: maximum ADPCM-A sample length is 2097152##sgse"));
            }
            if (dispatch!=NULL) {
              EXACT_RATE("YM2610 (ADPCM-A)",dispatch->chipClock/432);
            }
            break;
          case DIV_SYSTEM_Y8950:
            if (sample->loop) {
              if (sample->loopStart!=0 || sample->loopEnd!=(int)(sample->samples)) {
                SAMPLE_WARN(warnLoopPos,_L("Y8950: loop point ignored on ADPCM (may only loop entire sample)##sgse"));
              }
              if (sample->samples&511) {
                SAMPLE_WARN(warnLength,_L("Y8950: sample length will be padded to multiple of 512##sgse"));
              }
            }
            break;
          case DIV_SYSTEM_AMIGA:
            if (sample->loop) {
              if (sample->loopStart&1) {
                SAMPLE_WARN(warnLoopStart,_L("Amiga: loop start must be a multiple of 2##sgse"));
              }
              if (sample->loopEnd&1) {
                SAMPLE_WARN(warnLoopEnd,_L("Amiga: loop end must be a multiple of 2##sgse"));
              }
            }
            if (sample->samples>131070) {
              SAMPLE_WARN(warnLength,_L("Amiga: maximum sample length is 131070##sgse"));
            }
            if (dispatch!=NULL) {
              MAX_RATE("Amiga",31250.0);
            }
            break;
          case DIV_SYSTEM_SEGAPCM:
          case DIV_SYSTEM_SEGAPCM_COMPAT:
            if (sample->samples>65280) {
              SAMPLE_WARN(warnLength,_L("SegaPCM: maximum sample length is 65280##sgse"));
            }
            if (dispatch!=NULL) {
              MAX_RATE("SegaPCM",dispatch->chipClock/256);
            }
            break;
          case DIV_SYSTEM_K053260:
            if (sample->loop) {
              if (sample->loopStart!=0 || sample->loopEnd!=(int)(sample->samples)) {
                SAMPLE_WARN(warnLoopPos,_L("K053260: loop point ignored (may only loop entire sample)##sgse"));
              }
            }
            if (sample->samples>65535) {
              SAMPLE_WARN(warnLength,_L("K053260: maximum sample length is 65535##sgse"));
            }
            break;
          case DIV_SYSTEM_C140:
            if (sample->samples>65535) {
              SAMPLE_WARN(warnLength,_L("C140: maximum sample length is 65535##sgse"));
            }
            if (dispatch!=NULL) {
              MAX_RATE("C140",dispatch->rate);
            }
            break;
          case DIV_SYSTEM_C219:
            if (sample->loop) {
              if (sample->loopStart&1) {
                SAMPLE_WARN(warnLoopStart,_L("C219: loop start must be a multiple of 2##sgse"));
              }
              if (sample->loopEnd&1) {
                SAMPLE_WARN(warnLoopEnd,_L("C219: loop end must be a multiple of 2##sgse"));
              }
            }
            if (sample->samples>131072) {
              SAMPLE_WARN(warnLength,_L("C219: maximum sample length is 131072##sgse"));
            }
            if (dispatch!=NULL) {
              MAX_RATE("C219",dispatch->rate);
            }
            break;
          case DIV_SYSTEM_MSM6295:
            if (sample->loop) {
              SAMPLE_WARN(warnLoop,_L("MSM6295: samples can't loop##sgse"));
            }
            if (sample->samples>129024) {
              SAMPLE_WARN(warnLength,"MSM6295: maximum bankswitched sample length is 129024##sgse");
            }
          default:
            break;
        }
        if (e->song.system[i]!=DIV_SYSTEM_PCM_DAC) {
          if (e->song.system[i]==DIV_SYSTEM_ES5506) {
            if (sample->loopMode==DIV_SAMPLE_LOOP_BACKWARD) {
              SAMPLE_WARN(warnLoopMode,_L("ES5506: backward loop mode isn't supported##sgse"));
            }
          } else if (sample->loopMode!=DIV_SAMPLE_LOOP_FORWARD) {
            SAMPLE_WARN(warnLoopMode,_L("backward/ping-pong only supported in Generic PCM DAC\nping-pong also on ES5506##sgse"));
          }
        }

        // chips grid
        if (dispatch==NULL) continue;

        for (int j=0; j<DIV_MAX_SAMPLE_TYPE; j++) {
          if (dispatch->getSampleMemCapacity(j)==0) continue;
          isChipVisible[i]=true;
          isTypeVisible[j]=true;
          isMemVisible[j][i]=true;
          if (!dispatch->isSampleLoaded(j,curSample)) isMemWarning[j][i]=true;
        }
      }

      int selColumns=1;
      for (int i=0; i<DIV_MAX_CHIPS; i++) {
        if (isChipVisible[i]) selColumns++;
      }
      
      int targetRate=sampleCompatRate?sample->rate:sample->centerRate;

      if (ImGui::BeginTable("SampleProps",(selColumns>1)?4:3,ImGuiTableFlags_SizingStretchSame|ImGuiTableFlags_BordersV|ImGuiTableFlags_BordersOuterH)) {
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        ImGui::TableNextColumn();
        if (ImGui::Button(sampleInfo?(ICON_FA_CHEVRON_UP "##SECollapse"):(ICON_FA_CHEVRON_DOWN "##SECollapse"))) {
          sampleInfo=!sampleInfo;
        }
        ImGui::SameLine();
        ImGui::Text(_L("Info##sgse"));
        ImGui::TableNextColumn();
        pushToggleColors(!sampleCompatRate);
        if (ImGui::Button(_L("Rate##sgse0"))) {
          sampleCompatRate=false;
        }
        popToggleColors();
        ImGui::SameLine();
        pushToggleColors(sampleCompatRate);
        if (ImGui::Button(_L("Compat Rate##sgse"))) {
          sampleCompatRate=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("used in DefleMask-compatible sample mode (17xx), in where samples are mapped to an octave.##sgse"));
        }
        popToggleColors();
        ImGui::TableNextColumn();
        bool doLoop=(sample->loop);
        pushWarningColor(!warnLoop.empty());
        String loopCheckboxName=(doLoop && (sample->loopEnd-sample->loopStart)>0)?fmt::sprintf(_L("Loop (length: %d)##Loop"),sample->loopEnd-sample->loopStart):String(_L("Loop##sgse"));
        if (ImGui::Checkbox(loopCheckboxName.c_str(),&doLoop)) { MARK_MODIFIED
          if (doLoop) {
            sample->loop=true;
            if (sample->loopStart<0) {
              sample->loopStart=0;
            }
            if (sample->loopEnd<0) {
              sample->loopEnd=sample->samples;
            }
          } else {
            sample->loop=false;
            /*
            sample->loopStart=-1;
            sample->loopEnd=sample->samples;*/
          }
          updateSampleTex=true;
          if (e->getSampleFormatMask()&(1U<<DIV_SAMPLE_DEPTH_BRR)) {
            e->renderSamplesP(curSample);
          }
        }
        popWarningColor();
        if (ImGui::IsItemHovered() && (!warnLoop.empty() || sample->depth==DIV_SAMPLE_DEPTH_BRR)) {
          if (sample->depth==DIV_SAMPLE_DEPTH_BRR) {
            SAMPLE_WARN(warnLoop,_L("changing the loop in a BRR sample may result in glitches!##sgse0"));
          }
          ImGui::SetTooltip("%s",warnLoop.c_str());
        }

        if (selColumns>1) {
          ImGui::TableNextColumn();
          ImGui::Text(_L("Chips##sgse"));
        }
        
        if (sampleInfo) {
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Type##sgse"));
          ImGui::SameLine();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::BeginCombo("##SampleType",sampleType.c_str())) {
            for (int i=0; i<DIV_SAMPLE_DEPTH_MAX; i++) {
              if (sampleDepths[i]==NULL) continue;
              if (ImGui::Selectable(_L(sampleDepths[i]))) {
                sample->prepareUndo(true);
                e->lockEngine([this,sample,i]() {
                  sample->convert((DivSampleDepth)i);
                  e->renderSamples(curSample);
                });
                updateSampleTex=true;
                MARK_MODIFIED;
              }
            }
            ImGui::EndCombo();
          }

          bool isThereSNES=false;
          for (int i=0; i<e->song.systemLen; i++) {
            if (e->song.system[i]==DIV_SYSTEM_SNES) {
              isThereSNES=true;
              break;
            }
          }
          if (sample->depth==DIV_SAMPLE_DEPTH_BRR || isThereSNES) {
            bool be=sample->brrEmphasis;
            if (ImGui::Checkbox(_L("BRR emphasis##sgse"),&be)) {
              sample->prepareUndo(true);
              sample->brrEmphasis=be;
              e->renderSamplesP(curSample);
              updateSampleTex=true;
              MARK_MODIFIED;
            }
            if (ImGui::IsItemHovered()) {
              if (sample->depth==DIV_SAMPLE_DEPTH_BRR) {
                ImGui::SetTooltip(_L("this is a BRR sample.\nenabling this option will muffle it (only affects non-SNES chips).##sgse"));
              } else {
                ImGui::SetTooltip(_L("enable this option to slightly boost high frequencies\nto compensate for the SNES' Gaussian filter's muffle.##sgse"));
              }
            }
          }
          if (sample->depth!=DIV_SAMPLE_DEPTH_8BIT && e->getSampleFormatMask()&(1L<<DIV_SAMPLE_DEPTH_8BIT)) {
            bool di=sample->dither;
            if (ImGui::Checkbox(_L("8-bit dither##sgse"),&di)) {
              sample->prepareUndo(true);
              sample->dither=di;
              e->renderSamplesP(curSample);
              updateSampleTex=true;
              MARK_MODIFIED;
            }
            if (ImGui::IsItemHovered()) {
              ImGui::SetTooltip(_L("dither the sample when used on a chip that only supports 8-bit samples.##sgse"));
            }
          }

          int sampleNote=round(64.0+(128.0*12.0*log((double)targetRate/8363.0)/log(2.0)));
          int sampleNoteCoarse=60+(sampleNote>>7);
          int sampleNoteFine=(sampleNote&127)-64;

          if (sampleNoteCoarse<0) {
            sampleNoteCoarse=0;
            sampleNoteFine=-64;
          }
          if (sampleNoteCoarse>119) {
            sampleNoteCoarse=119;
            sampleNoteFine=63;
          }

          bool coarseChanged=false;

          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Hz");
          ImGui::SameLine();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::InputInt("##SampleRate",&targetRate,10,200)) { MARK_MODIFIED
            if (targetRate<100) targetRate=100;
            if (targetRate>384000) targetRate=384000;

            if (sampleCompatRate) {
              sample->rate=targetRate;
            } else {
              sample->centerRate=targetRate;
            }
          }
          
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Note##sgse"));
          ImGui::SameLine();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::BeginCombo("##SampleNote",noteNames[sampleNoteCoarse+60])) {
            char temp[1024];
            for (int i=0; i<120; i++) {
              snprintf(temp,1023,"%s##_SRN%d",noteNames[i+60],i);
              if (ImGui::Selectable(temp,i==sampleNoteCoarse)) {
                sampleNoteCoarse=i;
                coarseChanged=true;
              }
              if (i==sampleNoteCoarse) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
          } else if (ImGui::IsItemHovered()) {
            if (wheelY!=0) {
              sampleNoteCoarse-=wheelY;
              if (sampleNoteCoarse<0) {
                sampleNoteCoarse=0;
                sampleNoteFine=-64;
              }
              if (sampleNoteCoarse>119) {
                sampleNoteCoarse=119;
                sampleNoteFine=63;
              }
              coarseChanged=true;
            }
          }

          if (coarseChanged) { MARK_MODIFIED
            sampleNote=((sampleNoteCoarse-60)<<7)+sampleNoteFine;

            targetRate=8363.0*pow(2.0,(double)sampleNote/(128.0*12.0));
            if (targetRate<100) targetRate=100;
            if (targetRate>384000) targetRate=384000;

            if (sampleCompatRate) {
              sample->rate=targetRate;
            } else {
              sample->centerRate=targetRate;
            }
          }

          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Fine##sgse"));
          ImGui::SameLine();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          int prevFine=sampleNoteFine;
          int prevSampleRate=targetRate;
          if (ImGui::InputInt("##SampleFine",&sampleNoteFine,1,10)) { MARK_MODIFIED
            if (sampleNoteFine>63) sampleNoteFine=63;
            if (sampleNoteFine<-64) sampleNoteFine=-64;

            sampleNote=((sampleNoteCoarse-60)<<7)+sampleNoteFine;

            targetRate=round(8363.0*pow(2.0,(double)sampleNote/(128.0*12.0)));

            if (targetRate==prevSampleRate) {
              if (prevFine==sampleNoteFine) {
                // do nothing
              } else if (prevFine>sampleNoteFine) { // coarse incr/decr due to precision loss
                targetRate--;
              } else {
                targetRate++;
              }
            }

            if (targetRate<100) targetRate=100;
            if (targetRate>384000) targetRate=384000;

            if (sampleCompatRate) {
              sample->rate=targetRate;
            } else {
              sample->centerRate=targetRate;
            }
          }

          ImGui::TableNextColumn();
          ImGui::BeginDisabled(!(doLoop || keepLoopAlive));
          keepLoopAlive=false;
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Mode##sgse"));
          ImGui::SameLine();
          pushWarningColor(!warnLoopMode.empty());
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::BeginCombo("##SampleLoopMode",loopType.c_str())) {
            for (int i=0; i<DIV_SAMPLE_LOOP_MAX; i++) {
              if (sampleLoopModes[i]==NULL) continue;
              if (ImGui::Selectable(_L(sampleLoopModes[i]))) {
                sample->prepareUndo(true);
                sample->loopMode=(DivSampleLoopMode)i;
                e->renderSamplesP(curSample);
                updateSampleTex=true;
                MARK_MODIFIED;
              }
            }
            ImGui::EndCombo();
          }
          if (ImGui::IsItemHovered() && !warnLoopMode.empty()) {
            ImGui::SetTooltip("%s",warnLoopMode.c_str());
          }
          popWarningColor();

          pushWarningColor(!warnLoopPos.empty() || !warnLoopStart.empty());
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Start##sgse"));
          ImGui::SameLine();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::InputInt("##LoopStartPosition",&sample->loopStart,1,16)) { MARK_MODIFIED
            if (sample->loopStart<0) {
              sample->loopStart=0;
            }
            if (sample->loopStart>sample->loopEnd) {
              sample->loopStart=sample->loopEnd;
            }
            updateSampleTex=true;
            if (e->getSampleFormatMask()&(1U<<DIV_SAMPLE_DEPTH_BRR)) {
              e->renderSamplesP(curSample);
            }
          }
          if (ImGui::IsItemActive()) {
            keepLoopAlive=true;
          }
          if (ImGui::IsItemHovered() && (!warnLoopPos.empty() || !warnLoopStart.empty() || sample->depth==DIV_SAMPLE_DEPTH_BRR)) {
            if (ImGui::BeginTooltip()) {
              if (sample->depth==DIV_SAMPLE_DEPTH_BRR) {
                ImGui::Text(_L("changing the loop in a BRR sample may result in glitches!##sgse1"));
              }
              if (!warnLoopStart.empty()) {
                ImGui::Text("%s",warnLoopStart.c_str());
              }
              if (!warnLoopPos.empty()) {
                ImGui::Text("%s",warnLoopPos.c_str());
              }
              ImGui::EndTooltip();
            }
          }
          popWarningColor();

          pushWarningColor(!warnLoopPos.empty() || !warnLoopEnd.empty());
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("End##sgse"));
          ImGui::SameLine();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::InputInt("##LoopEndPosition",&sample->loopEnd,1,16)) { MARK_MODIFIED
            if (sample->loopEnd<sample->loopStart) {
              sample->loopEnd=sample->loopStart;
            }
            if (sample->loopEnd>=(int)sample->samples) {
              sample->loopEnd=sample->samples;
            }
            updateSampleTex=true;
            if (e->getSampleFormatMask()&(1U<<DIV_SAMPLE_DEPTH_BRR)) {
              e->renderSamplesP(curSample);
            }
          }
          if (ImGui::IsItemActive()) {
            keepLoopAlive=true;
          }
          if (ImGui::IsItemHovered() && (!warnLoopPos.empty() || !warnLoopEnd.empty() || sample->depth==DIV_SAMPLE_DEPTH_BRR)) {
            if (ImGui::BeginTooltip()) {
              if (sample->depth==DIV_SAMPLE_DEPTH_BRR) {
                ImGui::Text(_L("changing the loop in a BRR sample may result in glitches!##sgse2"));
              }
              if (!warnLoopEnd.empty()) {
                ImGui::Text("%s",warnLoopEnd.c_str());
              }
              if (!warnLoopPos.empty()) {
                ImGui::Text("%s",warnLoopPos.c_str());
              }
              ImGui::EndTooltip();
            }
          }
          popWarningColor();
          ImGui::EndDisabled();

          if (selColumns>1) {
            ImGui::TableNextColumn();
            if (ImGui::BeginTable("SEChipSel",selColumns,ImGuiTableFlags_SizingFixedSame)) {
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              for (int i=0; i<e->song.systemLen; i++) {
                if (!isChipVisible[i]) continue;
                ImGui::TableNextColumn();
                ImGui::Text("%d",i+1);
              }
              char id[1024];
              for (int i=0; i<DIV_MAX_SAMPLE_TYPE; i++) {
                if (!isTypeVisible[i]) continue;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%c",'A'+i);
                for (int j=0; j<e->song.systemLen; j++) {
                  if (!isChipVisible[j]) continue;
                  ImGui::TableNextColumn();

                  if (!isMemVisible[i][j]) continue;
                  snprintf(id,1023,"##_SEC%d_%d",i,j);

                  ImVec4 baseColor=sample->renderOn[i][j]?(isMemWarning[i][j]?uiColors[GUI_COLOR_SAMPLE_CHIP_WARNING]:uiColors[GUI_COLOR_SAMPLE_CHIP_ENABLED]):uiColors[GUI_COLOR_SAMPLE_CHIP_DISABLED];
                  ImVec4 color=baseColor;
                  ImVec4 colorHovered=baseColor;
                  ImVec4 colorActive=baseColor;

                  if (settings.guiColorsBase) {
                    color.x*=0.8f;
                    color.y*=0.8f;
                    color.z*=0.8f;
                    colorHovered.x*=0.65f;
                    colorHovered.y*=0.65f;
                    colorHovered.z*=0.65f;
                    colorActive.x*=0.3f;
                    colorActive.y*=0.3f;
                    colorActive.z*=0.3f;
                  } else {
                    color.x*=0.2f;
                    color.y*=0.2f;
                    color.z*=0.2f;
                    colorHovered.x*=0.4f;
                    colorHovered.y*=0.4f;
                    colorHovered.z*=0.4f;
                  }

                  ImGui::PushStyleColor(ImGuiCol_FrameBg,color);
                  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,colorHovered);
                  ImGui::PushStyleColor(ImGuiCol_FrameBgActive,colorActive);
                  ImGui::PushStyleColor(ImGuiCol_CheckMark,baseColor);

                  if (ImGui::Checkbox(id,&sample->renderOn[i][j])) {
                    e->renderSamplesP(curSample);
                  }

                  ImGui::PopStyleColor(4);

                  if (ImGui::IsItemHovered()) {
                    const char* memName=NULL;
                    size_t capacity=0;
                    size_t usage=0;
                    int totalFree=0;
                    DivDispatch* dispatch=e->getDispatch(j);
                    if (dispatch!=NULL) {
                      memName=dispatch->getSampleMemName(i);
                      capacity=dispatch->getSampleMemCapacity(i);
                      usage=dispatch->getSampleMemUsage(i);
                      if (usage<capacity) {
                        totalFree=capacity-usage;
                      }
                    }
                    String toolText;
                    if (memName==NULL) {
                      toolText=fmt::sprintf(_LP("%s\n%d bytes free##sgse", totalFree),_L(e->getSystemName(e->song.system[j])),totalFree);
                    } else {
                      toolText=fmt::sprintf(_LP("%s (%s)\n%d bytes free##sgse", totalFree),_L(e->getSystemName(e->song.system[j])),memName,totalFree);
                    }

                    if (isMemWarning[i][j] && sample->renderOn[i][j]) {
                      toolText+=_L("\n\nnot enough memory for this sample!##sgse");
                    }

                    ImGui::SetTooltip("%s",toolText.c_str());
                  }
                }
              }
              ImGui::EndTable();
            }
          }
          
        }

        ImGui::EndTable();
      }

      ImGui::Separator();

      pushToggleColors(!sampleDragMode);
      if (ImGui::Button(ICON_FA_I_CURSOR "##SSelect")) {
        sampleDragMode=false;
      }
      popToggleColors();
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Edit mode: Select##sgse"));
      }
      sameLineMaybe();
      pushToggleColors(sampleDragMode);
      if (ImGui::Button(ICON_FA_PENCIL "##SDraw")) {
        sampleDragMode=true;
      }
      popToggleColors();
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Edit mode: Draw##sgse"));
      }
      ImGui::BeginDisabled(sample->depth!=DIV_SAMPLE_DEPTH_8BIT && sample->depth!=DIV_SAMPLE_DEPTH_16BIT);
      sameLineMaybe();
      ImGui::Dummy(ImVec2(4.0*dpiScale,dpiScale));
      sameLineMaybe();
      ImGui::Button(ICON_FUR_SAMPLE_RESIZE "##SResize");
      if (ImGui::IsItemClicked()) {
        resizeSize=sample->samples;
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Resize##sgse0"));
      }
      if (openSampleResizeOpt) {
        openSampleResizeOpt=false;
        ImGui::OpenPopup("SResizeOpt");
      }
      if (ImGui::BeginPopupContextItem("SResizeOpt",ImGuiPopupFlags_MouseButtonLeft)) {
        if (ImGui::InputInt(_L("Samples##sgse0"),&resizeSize,1,64)) {
          if (resizeSize<0) resizeSize=0;
          if (resizeSize>16777215) resizeSize=16777215;
        }
        if (ImGui::Button(_L("Resize##sgse1"))) {
          sample->prepareUndo(true);
          e->lockEngine([this,sample]() {
            if (!sample->resize(resizeSize)) {
              showError(settings.language == DIV_LANG_ENGLISH ? "couldn't resize! make sure your sample is 8 or 16-bit." : _L("couldn't resize! make sure your sample is 8 or 16-bit.##sgse"));
            }
            e->renderSamples(curSample);
          });
          updateSampleTex=true;
          sampleSelStart=-1;
          sampleSelEnd=-1;
          MARK_MODIFIED;
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      } else {
        resizeSize=sample->samples;
      }
      sameLineMaybe();
      ImGui::Button(ICON_FUR_SAMPLE_RESAMPLE "##SResample");
      if (ImGui::IsItemClicked()) {
        resampleTarget=targetRate;
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Resample##sgse0"));
      }
      if (openSampleResampleOpt) {
        openSampleResampleOpt=false;
        ImGui::OpenPopup("SResampleOpt");
      }
      if (ImGui::BeginPopupContextItem("SResampleOpt",ImGuiPopupFlags_MouseButtonLeft)) {
        ImGui::Text(_L("Rate##sgse1"));
        if (ImGui::InputDouble("##SRRate",&resampleTarget,1.0,50.0,"%g")) {
          if (resampleTarget<0) resampleTarget=0;
          if (resampleTarget>96000) resampleTarget=96000;
        }
        ImGui::SameLine();
        if (ImGui::Button("0.5x")) {
          resampleTarget*=0.5;
        }
        ImGui::SameLine();
        if (ImGui::Button("==")) {
          resampleTarget=targetRate;
        }
        ImGui::SameLine();
        if (ImGui::Button("2.0x")) {
          resampleTarget*=2.0;
        }
        double factor=resampleTarget/(double)targetRate;
        if (ImGui::InputDouble(_L("Factor##sgse"),&factor,0.125,0.5,"%g")) {
          resampleTarget=(double)targetRate*factor;
          if (resampleTarget<0) resampleTarget=0;
          if (resampleTarget>96000) resampleTarget=96000;
        }
//        ImGui::Combo(_L("Filter##sgse"),&resampleStrat,resampleStrats,6);
        if (ImGui::BeginCombo(_L("Filter##sgse"),_L(resampleStrats[resampleStrat])))
        {
          int k = 0;
          while(resampleStrats[k])
          {
            if (ImGui::Selectable(_L(resampleStrats[k])))
            {
              resampleStrat = k;
            }
        
            k++;
          }
        
          ImGui::EndCombo();
        }
        if (ImGui::Button(_L("Resample##sgse1"))) {
          sample->prepareUndo(true);
          e->lockEngine([this,sample,targetRate]() {
            if (!sample->resample(targetRate,resampleTarget,resampleStrat)) {
              showError(settings.language == DIV_LANG_ENGLISH ? "couldn't resample! make sure your sample is 8 or 16-bit." : _L("couldn't resample! make sure your sample is 8 or 16-bit.##sgse"));
            }
            e->renderSamples(curSample);
          });
          updateSampleTex=true;
          sampleSelStart=-1;
          sampleSelEnd=-1;
          MARK_MODIFIED;
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      } else {
        resampleTarget=targetRate;
      }
      ImGui::SameLine();
      ImGui::Dummy(ImVec2(4.0*dpiScale,dpiScale));
      sameLineMaybe();
      if (ImGui::Button(ICON_FA_UNDO "##SUndo")) {
        doUndoSample();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Undo##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FA_REPEAT "##SRedo")) {
        doRedoSample();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Redo##sgse"));
      }
      ImGui::SameLine();
      ImGui::Dummy(ImVec2(4.0*dpiScale,dpiScale));
      sameLineMaybe();
      ImGui::Button(ICON_FA_VOLUME_UP "##SAmplify");
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Amplify##sgse"));
      }
      if (openSampleAmplifyOpt) {
        openSampleAmplifyOpt=false;
        ImGui::OpenPopup("SAmplifyOpt");
      }
      if (ImGui::BeginPopupContextItem("SAmplifyOpt",ImGuiPopupFlags_MouseButtonLeft)) {
        ImGui::Text(_L("Volume##sgse"));
        if (ImGui::InputFloat("##SRVolume",&amplifyVol,10.0,50.0,"%g%%")) {
          if (amplifyVol<0) amplifyVol=0;
          if (amplifyVol>10000) amplifyVol=10000;
        }
        ImGui::SameLine();
        ImGui::Text("(%.1fdB)",20.0*log10(amplifyVol/100.0f));
        if (ImGui::Button(_L("Apply##sgse0"))) {
          sample->prepareUndo(true);
          e->lockEngine([this,sample]() {
            SAMPLE_OP_BEGIN;
            float vol=amplifyVol/100.0f;

            if (sample->depth==DIV_SAMPLE_DEPTH_16BIT) {
              for (unsigned int i=start; i<end; i++) {
                float val=sample->data16[i]*vol;
                if (val<-32768) val=-32768;
                if (val>32767) val=32767;
                sample->data16[i]=val;
              }
            } else if (sample->depth==DIV_SAMPLE_DEPTH_8BIT) {
              for (unsigned int i=start; i<end; i++) {
                float val=sample->data8[i]*vol;
                if (val<-128) val=-128;
                if (val>127) val=127;
                sample->data8[i]=val;
              }
            }

            updateSampleTex=true;

            e->renderSamples(curSample);
          });
          MARK_MODIFIED;
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_NORMALIZE "##SNormalize")) {
        doAction(GUI_ACTION_SAMPLE_NORMALIZE);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Normalize##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_FADEIN "##SFadeIn")) {
        doAction(GUI_ACTION_SAMPLE_FADE_IN);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Fade in##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_FADEOUT "##SFadeOut")) {
        doAction(GUI_ACTION_SAMPLE_FADE_OUT);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Fade out##sgse"));
      }
      sameLineMaybe();
      ImGui::Button(ICON_FUR_SAMPLE_INSERT_SILENCE "##SInsertSilence");
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Insert silence##sgse"));
      }
      if (openSampleSilenceOpt) {
        openSampleSilenceOpt=false;
        ImGui::OpenPopup("SSilenceOpt");
      }
      if (ImGui::BeginPopupContextItem("SSilenceOpt",ImGuiPopupFlags_MouseButtonLeft)) {
        if (ImGui::InputInt(_L("Samples##sgse1"),&silenceSize,1,64)) {
          if (silenceSize<0) silenceSize=0;
          if (silenceSize>16777215) silenceSize=16777215;
        }
        if (ImGui::Button(_L("Go##sgse"))) {
          int pos=(sampleSelStart==-1 || sampleSelStart==sampleSelEnd)?sample->samples:sampleSelStart;
          sample->prepareUndo(true);
          e->lockEngine([this,sample,pos]() {
            if (!sample->insert(pos,silenceSize)) {
              showError(settings.language == DIV_LANG_ENGLISH ? "couldn't insert! make sure your sample is 8 or 16-bit." : _L("couldn't insert! make sure your sample is 8 or 16-bit.##sgse"));
            }
            e->renderSamples(curSample);
          });
          updateSampleTex=true;
          sampleSelStart=pos;
          sampleSelEnd=pos+silenceSize;
          MARK_MODIFIED;
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_APPLY_SILENCE "##SSilence")) {
        doAction(GUI_ACTION_SAMPLE_SILENCE);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Apply silence##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FA_TIMES "##SDelete")) {
        doAction(GUI_ACTION_SAMPLE_DELETE);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Delete##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FA_CROP "##STrim")) {
        doAction(GUI_ACTION_SAMPLE_TRIM);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Trim##sgse"));
      }
      ImGui::SameLine();
      ImGui::Dummy(ImVec2(4.0*dpiScale,dpiScale));
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_REVERSE "##SReverse")) {
        doAction(GUI_ACTION_SAMPLE_REVERSE);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Reverse##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_INVERT "##SInvert")) {
        doAction(GUI_ACTION_SAMPLE_INVERT);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Invert##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FUR_SAMPLE_SIGN "##SSign")) {
        doAction(GUI_ACTION_SAMPLE_SIGN);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Signed/unsigned exchange##sgse"));
      }
      sameLineMaybe();
      ImGui::Button(ICON_FUR_SAMPLE_FILTER "##SFilter");
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Apply filter##sgse"));
      }
      if (openSampleFilterOpt) {
        openSampleFilterOpt=false;
        ImGui::OpenPopup("SFilterOpt");
      }
      if (ImGui::BeginPopupContextItem("SFilterOpt",ImGuiPopupFlags_MouseButtonLeft)) {
        float lowP=sampleFilterL*100.0f;
        float bandP=sampleFilterB*100.0f;
        float highP=sampleFilterH*100.0f;
        float resP=sampleFilterRes*100.0f;
        ImGui::Text(_L("Cutoff:##sgse"));
        if (ImGui::InputFloat(_L("From##sgse"),&sampleFilterCutStart,10.0f,1000.0f,"%.0f")) {
          if (sampleFilterCutStart<0.0) sampleFilterCutStart=0.0;
          if (sampleFilterCutStart>sample->rate*0.5) sampleFilterCutStart=sample->rate*0.5;
        }
        if (ImGui::InputFloat(_L("To##sgse"),&sampleFilterCutEnd,10.0f,1000.0f,"%.0f")) {
          if (sampleFilterCutEnd<0.0) sampleFilterCutEnd=0.0;
          if (sampleFilterCutEnd>sample->rate*0.5) sampleFilterCutEnd=sample->rate*0.5;
        }
        ImGui::Separator();
        if (ImGui::SliderFloat(_L("Resonance##sgse"),&resP,0.0f,99.0f,"%.1f%%")) {
          sampleFilterRes=resP/100.0f;
          if (sampleFilterRes<0.0f) sampleFilterRes=0.0f;
          if (sampleFilterRes>0.99f) sampleFilterRes=0.99f;
        }
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Power##sgse"));
        ImGui::SameLine();
        if (ImGui::RadioButton("1x",sampleFilterPower==1)) {
          sampleFilterPower=1;
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("2x",sampleFilterPower==2)) {
          sampleFilterPower=2;
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("3x",sampleFilterPower==3)) {
          sampleFilterPower=3;
        }
        ImGui::Separator();
        if (ImGui::SliderFloat(_L("Low-pass##sgse"),&lowP,0.0f,100.0f,"%.1f%%")) {
          sampleFilterL=lowP/100.0f;
          if (sampleFilterL<0.0f) sampleFilterL=0.0f;
          if (sampleFilterL>1.0f) sampleFilterL=1.0f;
        }
        if (ImGui::SliderFloat(_L("Band-pass##sgse"),&bandP,0.0f,100.0f,"%.1f%%")) {
          sampleFilterB=bandP/100.0f;
          if (sampleFilterB<0.0f) sampleFilterB=0.0f;
          if (sampleFilterB>1.0f) sampleFilterB=1.0f;
        }
        if (ImGui::SliderFloat(_L("High-pass##sgse"),&highP,0.0f,100.0f,"%.1f%%")) {
          sampleFilterH=highP/100.0f;
          if (sampleFilterH<0.0f) sampleFilterH=0.0f;
          if (sampleFilterH>1.0f) sampleFilterH=1.0f;
        }

        if (ImGui::Button(_L("Apply##sgse1"))) {
          sample->prepareUndo(true);
          e->lockEngine([this,sample]() {
            SAMPLE_OP_BEGIN;
            float res=1.0-pow(sampleFilterRes,0.5f);
            float low=0;
            float band=0;
            float high=0;

            double power=(sampleFilterCutStart>sampleFilterCutEnd)?0.5:2.0;

            if (sample->depth==DIV_SAMPLE_DEPTH_16BIT) {
              for (unsigned int i=start; i<end; i++) {
                double freq=sampleFilterCutStart+(sampleFilterCutEnd-sampleFilterCutStart)*pow(double(i-start)/double(end-start),power);
                double cut=sin((freq/double(sample->rate))*M_PI);

                for (int j=0; j<sampleFilterPower; j++) {
                  low=low+cut*band;
                  high=float(sample->data16[i])-low-(res*band);
                  band=cut*high+band;
                }

                float val=low*sampleFilterL+band*sampleFilterB+high*sampleFilterH;
                if (val<-32768) val=-32768;
                if (val>32767) val=32767;
                sample->data16[i]=val;
              }
            } else if (sample->depth==DIV_SAMPLE_DEPTH_8BIT) {
              for (unsigned int i=start; i<end; i++) {
                double freq=sampleFilterCutStart+(sampleFilterCutEnd-sampleFilterCutStart)*pow(double(i-start)/double(end-start),power);
                double cut=sin((freq/double(sample->rate))*M_PI);

                for (int j=0; j<sampleFilterPower; j++) {
                  low=low+cut*band;
                  high=float(sample->data8[i])-low-(res*band);
                  band=cut*high+band;
                }

                float val=low*sampleFilterL+band*sampleFilterB+high*sampleFilterH;
                if (val<-128) val=-128;
                if (val>127) val=127;
                sample->data8[i]=val;
              }
            }

            updateSampleTex=true;

            e->renderSamples(curSample);
          });
          MARK_MODIFIED;
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }
      ImGui::EndDisabled();
      ImGui::SameLine();
      ImGui::Dummy(ImVec2(4.0*dpiScale,dpiScale));
      sameLineMaybe();
      ImGui::Button(ICON_FUR_CROSSFADE "##CrossFade");
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Crossfade loop points##sgse"));
      }
      if (openSampleCrossFadeOpt) {
        openSampleCrossFadeOpt=false;
        ImGui::OpenPopup("SCrossFadeOpt");
      }
      if (ImGui::BeginPopupContextItem("SCrossFadeOpt",ImGuiPopupFlags_MouseButtonLeft)) {
        if (sampleCrossFadeLoopLength>sample->loopStart) sampleCrossFadeLoopLength=sample->loopStart;
        if (sampleCrossFadeLoopLength>(sample->loopEnd-sample->loopStart)) sampleCrossFadeLoopLength=sample->loopEnd-sample->loopStart;
        if (ImGui::SliderInt(_L("Number of samples##sgse"),&sampleCrossFadeLoopLength,0,100000)) {
          if (sampleCrossFadeLoopLength<0) sampleCrossFadeLoopLength=0;
          if (sampleCrossFadeLoopLength>sample->loopStart) sampleCrossFadeLoopLength=sample->loopStart;
          if (sampleCrossFadeLoopLength>(sample->loopEnd-sample->loopStart)) sampleCrossFadeLoopLength=sample->loopEnd-sample->loopStart;
          if (sampleCrossFadeLoopLength>100000) sampleCrossFadeLoopLength=100000;
        }
        if (ImGui::SliderInt(_L("Linear <-> Equal power##sgse"),&sampleCrossFadeLoopLaw,0,100)) {
          if (sampleCrossFadeLoopLaw<0) sampleCrossFadeLoopLaw=0;
          if (sampleCrossFadeLoopLaw>100) sampleCrossFadeLoopLaw=100;
        }
        if (ImGui::Button(_L("Apply##sgse2"))) {
          if (sampleCrossFadeLoopLength>sample->loopStart) {
            showError(settings.language == DIV_LANG_ENGLISH ? "Crossfade: length would go out of bounds. Aborted..." : _L("Crossfade: length would go out of bounds. Aborted...##sgse"));
            ImGui::CloseCurrentPopup();
          } else if (sampleCrossFadeLoopLength>(sample->loopEnd-sample->loopStart)) {
            showError(settings.language == DIV_LANG_ENGLISH ? "Crossfade: length would overflow loopStart. Try a smaller random value." : _L("Crossfade: length would overflow loopStart. Try a smaller random value.##sgse"));
            ImGui::CloseCurrentPopup();
          } else {
            sample->prepareUndo(true);
            e->lockEngine([this,sample] {
              SAMPLE_OP_BEGIN;
              double l=1.0/(double)sampleCrossFadeLoopLength;
              double evar=1.0-sampleCrossFadeLoopLaw/200.0;
              if (sample->depth==DIV_SAMPLE_DEPTH_8BIT) {
                unsigned int crossFadeInput=sample->loopStart-sampleCrossFadeLoopLength;
                unsigned int crossFadeOutput=sample->loopEnd-sampleCrossFadeLoopLength;
                for (int i=0; i<sampleCrossFadeLoopLength; i++) {
                  double f1=pow(i*l,evar);
                  double f2=pow((sampleCrossFadeLoopLength-i)*l,evar);
                  signed char out=(signed char)(((double)sample->data8[crossFadeInput])*f1+((double)sample->data8[crossFadeOutput])*f2);
                  sample->data8[crossFadeOutput]=out;
                  crossFadeInput++;
                  crossFadeOutput++;
                }
              } else if (sample->depth==DIV_SAMPLE_DEPTH_16BIT) {
                unsigned int crossFadeInput=sample->loopStart-sampleCrossFadeLoopLength;
                unsigned int crossFadeOutput=sample->loopEnd-sampleCrossFadeLoopLength;
                for (int i=0; i<sampleCrossFadeLoopLength; i++) {
                  double f1=std::pow(i*l,evar);
                  double f2=std::pow((sampleCrossFadeLoopLength-i)*l,evar);
                  short out=(short)(((double)sample->data16[crossFadeInput])*f1+((double)sample->data16[crossFadeOutput])*f2);
                  sample->data16[crossFadeOutput]=out;
                  crossFadeInput++;
                  crossFadeOutput++;
                }
              }
              updateSampleTex=true;

              e->renderSamples(curSample);
            });
            MARK_MODIFIED;
            ImGui::CloseCurrentPopup();
          }
        }
        ImGui::EndPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_PLAY "##PreviewSample")) {
        e->previewSample(curSample);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Preview sample##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FA_STOP "##StopSample")) {
        e->stopSamplePreview();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Stop sample preview##sgse"));
      }
      sameLineMaybe();
      if (ImGui::Button(ICON_FA_UPLOAD "##MakeIns")) {
        doAction(GUI_ACTION_SAMPLE_MAKE_INS);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Create instrument from sample##sgse"));
      }

      sameLineMaybe(ImGui::CalcTextSize(_L("Zoom##sgse0")).x+150.0f*dpiScale+ImGui::CalcTextSize("100%").x);
      double zoomPercent=100.0/sampleZoom;
      bool checkZoomLimit=false;
      ImGui::AlignTextToFramePadding();
      ImGui::Text(_L("Zoom##sgse1"));
      ImGui::SameLine();
      ImGui::SetNextItemWidth(150.0f*dpiScale);
      if (ImGui::InputDouble("##SZoom",&zoomPercent,zoomPercent/8.0,20.0,"%g%%")) {
        if (zoomPercent>10000.0) zoomPercent=10000.0;
        if (zoomPercent<0.01) zoomPercent=0.01;
        sampleZoom=100.0/zoomPercent;
        sampleZoomAuto=false;
        checkZoomLimit=true;
        updateSampleTex=true;
      }
      ImGui::SameLine();
      if (sampleZoomAuto) {
        ImGui::BeginDisabled(minSampleZoom<1.0);
        if (ImGui::Button("100%")) {
          sampleZoom=1.0;
          sampleZoomAuto=false;
          updateSampleTex=true;
          checkZoomLimit=true;
        }
        ImGui::EndDisabled();
      } else {
        if (ImGui::Button(_L("Auto##sgse"))) {
          sampleZoomAuto=true;
          updateSampleTex=true;
        }
      }

      ImGui::Separator();

      // time
      ImDrawList* dl=ImGui::GetWindowDrawList();
      ImGuiWindow* window=ImGui::GetCurrentWindow();

      ImVec2 size=ImVec2(ImGui::GetContentRegionAvail().x,ImGui::GetFontSize()+2.0*dpiScale);

      ImVec2 minArea=window->DC.CursorPos;
      ImVec2 maxArea=ImVec2(
        minArea.x+size.x,
        minArea.y+size.y
      );
      ImRect rect=ImRect(minArea,maxArea);
      ImGuiStyle& style=ImGui::GetStyle();

      ImGui::ItemSize(size,style.FramePadding.y);
      if (ImGui::ItemAdd(rect,ImGui::GetID("SETime"))) {
        int targetRate=sampleCompatRate?sample->rate:sample->centerRate;
        int curDivisorSel=0;
        int curMultiplierSel=0;
        double divisor=1000.0;
        double multiplier=1.0;
        while ((((double)targetRate/divisor)/sampleZoom)<60.0*dpiScale) {
          if (curDivisorSel>=10) break;
          divisor=timeDivisors[++curDivisorSel];
        }
        if (curDivisorSel>=10) {
          while ((((double)targetRate*multiplier)/sampleZoom)<60.0*dpiScale) {
            if (curMultiplierSel>=13) {
              multiplier+=3600.0;
            } else {
              multiplier=timeMultipliers[++curMultiplierSel];
            }
          }
        }
        double timeStep=multiplier*((double)targetRate/divisor);
        double timeMin=-fmod(samplePos,timeStep);
        double timeMax=size.x*sampleZoom;
        ImU32 color=ImGui::GetColorU32(uiColors[GUI_COLOR_SAMPLE_TIME_FG]);

        dl->AddRectFilled(minArea,maxArea,ImGui::GetColorU32(uiColors[GUI_COLOR_SAMPLE_TIME_BG]));

        for (double i=timeMin; i<timeMax; i+=timeStep) {
          ImVec2 pos=ImVec2(minArea.x+(i/sampleZoom),minArea.y);
          int timeMs=(int)((1000*(samplePos+i))/targetRate);
          String t;
          if (curDivisorSel>=9) {
            if (timeMs>=3600000) {
              t=fmt::sprintf("%d:%02d:%02d",timeMs/3600000,(timeMs/60000)%60,(timeMs/1000)%60);
            } else if (timeMs>=60000) {
              t=fmt::sprintf("%d:%02d.%02d",timeMs/60000,(timeMs/1000)%60,(timeMs%1000)/10);
            } else {
              t=fmt::sprintf("%d.%03d",timeMs/1000,timeMs%1000);
            }
          } else {
            t=fmt::sprintf("%dms",timeMs);
          }
          dl->AddText(pos,color,t.c_str());
        }
      }

      ImVec2 avail=ImGui::GetContentRegionAvail(); // sample view size determined here
      // don't do this. reason: mobile.
      /*if (ImGui::GetContentRegionAvail().y>(ImGui::GetContentRegionAvail().x*0.5f)) {
        avail=ImVec2(ImGui::GetContentRegionAvail().x,ImGui::GetContentRegionAvail().x*0.5f);
      }*/
      avail.y-=ImGui::GetFontSize()+ImGui::GetStyle().ItemSpacing.y+ImGui::GetStyle().ScrollbarSize;
      if (avail.y<1.0) { // Prevents crash
        avail.y=1.0;
      }

      int availX=avail.x;
      int availY=avail.y;

      minSampleZoom=(double)sample->samples/avail.x;

      if (checkZoomLimit) {
        logV("sample: %f min: %f",sampleZoom,minSampleZoom);
        int bounds=((int)sample->samples-round(avail.x*sampleZoom));
        if (bounds<0) bounds=0;
        if (samplePos>bounds) samplePos=bounds;
        if (sampleZoom>minSampleZoom) {
          sampleZoomAuto=true;
        }
      }

      if (sampleZoomAuto) {
        samplePos=0;
        if (sample->samples<1 || avail.x<=0) {
          sampleZoom=1.0;
        } else {
          sampleZoom=minSampleZoom;
        }
        if (sampleZoom!=prevSampleZoom) {
          prevSampleZoom=sampleZoom;
          updateSampleTex=true;
        }
      }

      if (sampleTex==NULL || sampleTexW!=avail.x || sampleTexH!=avail.y) {
        if (sampleTex!=NULL) {
          rend->destroyTexture(sampleTex);
          sampleTex=NULL;
        }
        if (avail.x>=1 && avail.y>=1) {
          logD("recreating sample texture.");
          sampleTex=rend->createTexture(true,avail.x,avail.y);
          sampleTexW=avail.x;
          sampleTexH=avail.y;
          if (sampleTex==NULL) {
            logE("error while creating sample texture! %s",SDL_GetError());
          } else {
            updateSampleTex=true;
          }
        }
      }

      if (sampleTex!=NULL) {
        if (updateSampleTex) {
          unsigned int* dataT=NULL;
          int pitch=0;
          logD("updating sample texture.");
          if (!rend->lockTexture(sampleTex,(void**)&dataT,&pitch)) {
            logE("error while locking sample texture! %s",SDL_GetError());
          } else {
            unsigned int* data=new unsigned int[sampleTexW*sampleTexH];

            ImU32 bgColor=ImGui::GetColorU32(uiColors[GUI_COLOR_SAMPLE_BG]);
            ImU32 bgColorLoop=ImGui::GetColorU32(uiColors[GUI_COLOR_SAMPLE_LOOP]);
            ImU32 lineColor=ImGui::GetColorU32(uiColors[GUI_COLOR_SAMPLE_FG]);
            ImU32 centerLineColor=ImGui::GetColorU32(uiColors[GUI_COLOR_SAMPLE_CENTER]);
            int ij=0;
            for (int i=0; i<availY; i++) {
              for (int j=0; j<availX; j++) {
                int scaledPos=samplePos+(j*sampleZoom);
                if (sample->isLoopable() && (scaledPos>=sample->loopStart && scaledPos<=sample->loopEnd)) {
                  data[ij++]=bgColorLoop;
                } else {
                  data[ij++]=bgColor;
                }
              }
            }
            if (availY>0) {
              for (int i=availX*(availY>>1); i<availX*(1+(availY>>1)); i++) {
                data[i]=centerLineColor;
              }
            }
            unsigned int xCoarse=samplePos;
            unsigned int xFine=0;
            unsigned int xAdvanceCoarse=sampleZoom;
            unsigned int xAdvanceFine=fmod(sampleZoom,1.0)*16777216;
            for (unsigned int i=0; i<(unsigned int)availX; i++) {
              if (xCoarse>=sample->samples) break;
              int y1, y2;
              int candMin=INT_MAX;
              int candMax=INT_MIN;
              int totalAdvance=0;
              if (sample->depth==DIV_SAMPLE_DEPTH_8BIT) {
                if (candMin>sample->data8[xCoarse]) candMin=sample->data8[xCoarse];
                if (candMax<sample->data8[xCoarse]) candMax=sample->data8[xCoarse];
              } else {
                if (candMin>sample->data16[xCoarse]) candMin=sample->data16[xCoarse];
                if (candMax<sample->data16[xCoarse]) candMax=sample->data16[xCoarse];
              }
              xFine+=xAdvanceFine;
              if (xFine>=16777216) {
                xFine-=16777216;
                totalAdvance++;
              }
              totalAdvance+=xAdvanceCoarse;
              if (xCoarse>=sample->samples) break;
              do {
                if (xCoarse>=sample->samples) break;
                if (sample->depth==DIV_SAMPLE_DEPTH_8BIT) {
                  if (candMin>sample->data8[xCoarse]) candMin=sample->data8[xCoarse];
                  if (candMax<sample->data8[xCoarse]) candMax=sample->data8[xCoarse];
                } else {
                  if (candMin>sample->data16[xCoarse]) candMin=sample->data16[xCoarse];
                  if (candMax<sample->data16[xCoarse]) candMax=sample->data16[xCoarse];
                }
                if (totalAdvance>0) xCoarse++;
              } while ((totalAdvance--)>0);
              if (sample->depth==DIV_SAMPLE_DEPTH_8BIT) {
                y1=(((unsigned char)candMin^0x80)*availY)>>8;
                y2=(((unsigned char)candMax^0x80)*availY)>>8;
              } else {
                y1=(((unsigned short)candMin^0x8000)*availY)>>16;
                y2=(((unsigned short)candMax^0x8000)*availY)>>16;
              }
              if (y1>y2) {
                y2^=y1;
                y1^=y2;
                y2^=y1;
              }
              if (y1<0) y1=0;
              if (y1>=availY) y1=availY-1;
              if (y2<0) y2=0;
              if (y2>=availY) y2=availY-1;

              const int s1=i+availX*(availY-y1-1);
              const int s2=i+availX*(availY-y2-1);

              for (int j=s2; j<=s1; j+=availX) {
                data[j]=lineColor;
              }
            }

            if ((pitch>>2)==sampleTexW) {
              memcpy(dataT,data,sampleTexW*sampleTexH*sizeof(unsigned int));
            } else {
              int srcY=0;
              int destY=0;
              for (int i=0; i<sampleTexH; i++) {
                memcpy(&dataT[destY],&data[srcY],sampleTexW*sizeof(unsigned int));
                srcY+=sampleTexW;
                destY+=pitch>>2;
              }
            }
            rend->unlockTexture(sampleTex);
            delete[] data;
          }
          updateSampleTex=false;
        }

        ImGui::ImageButton(rend->getTextureID(sampleTex),avail,ImVec2(0,0),ImVec2(1,1),0);

        ImVec2 rectMin=ImGui::GetItemRectMin();
        ImVec2 rectMax=ImGui::GetItemRectMax();
        ImVec2 rectSize=ImGui::GetItemRectSize();

        unsigned char selectTarget=255;

        if (ImGui::IsItemHovered()) {
          int start=sampleSelStart;
          int end=sampleSelEnd;
          if (start>end) {
            start^=end;
            end^=start;
            start^=end;
          }
          ImVec2 p1=rectMin;
          p1.x+=(start-samplePos)/sampleZoom;

          ImVec2 p2=ImVec2(rectMin.x+(end-samplePos)/sampleZoom,rectMax.y);

          ImVec2 mousePos=ImGui::GetMousePos();
          if (p1.x>=rectMin.x && p1.x<=rectMax.x && fabs(mousePos.x-p1.x)<2.0*dpiScale) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
            selectTarget=0;
          } else if (p2.x>=rectMin.x && p2.x<=rectMax.x && fabs(mousePos.x-p2.x)<2.0*dpiScale) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
            selectTarget=1;
          }
        }

        if (ImGui::IsItemClicked()) {
          nextWindow=GUI_WINDOW_SAMPLE_EDIT;
          if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            sampleDragActive=false;
            sampleSelStart=0;
            sampleSelEnd=sample->samples;
          } else {
            if (sample->samples>0) {
              sampleDragStart=rectMin;
              sampleDragAreaSize=rectSize;
              switch (sample->depth) {
                case DIV_SAMPLE_DEPTH_8BIT:
                  sampleDrag16=false;
                  sampleDragTarget=(void*)sample->data8;
                  break;
                case DIV_SAMPLE_DEPTH_16BIT:
                  sampleDrag16=true;
                  sampleDragTarget=(void*)sample->data16;
                  break;
                default:
                  sampleDrag16=true;
                  sampleDragTarget=NULL;
                  break;
              }
              sampleDragLen=sample->samples;
              sampleDragActive=true;
              if (!sampleDragMode) {
                switch (selectTarget) {
                  case 0:
                    sampleSelStart^=sampleSelEnd;
                    sampleSelEnd^=sampleSelStart;
                    sampleSelStart^=sampleSelEnd;
                    break;
                  case 1:
                    break;
                  default:
                    sampleSelStart=-1;
                    sampleSelEnd=-1;
                    break;
                }
              } else {
                sample->prepareUndo(true);
              }
              processDrags(ImGui::GetMousePos().x,ImGui::GetMousePos().y);
            }
          }
        }

        if (ImGui::IsItemActive()) {
          if (ImGui::GetMousePos().x>rectMax.x) {
            double delta=pow(MAX(1.0,(ImGui::GetMousePos().x-rectMax.x)*0.04),2.0);
            samplePos+=MAX(1.0,sampleZoom*delta);
            int bounds=((int)sample->samples-round(avail.x*sampleZoom));
            if (bounds<0) bounds=0;
            if (samplePos>bounds) samplePos=bounds;
            updateSampleTex=true;
            processDrags(ImGui::GetMousePos().x,ImGui::GetMousePos().y);
            WAKE_UP;
          }
          if (ImGui::GetMousePos().x<rectMin.x) {
            double delta=pow(MAX(1.0,(rectMin.x-ImGui::GetMousePos().x)*0.04),2.0);
            samplePos-=MAX(1.0,sampleZoom*delta);
            if (samplePos<0) samplePos=0;
            updateSampleTex=true;
            processDrags(ImGui::GetMousePos().x,ImGui::GetMousePos().y);
            WAKE_UP;
          }
        }

        if (!sampleDragMode && ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
          ImGui::OpenPopup("SRightClick");
        }

        if (ImGui::BeginPopup("SRightClick",ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_AlwaysAutoResize)) {
          ImGui::BeginDisabled(sample->depth!=DIV_SAMPLE_DEPTH_8BIT && sample->depth!=DIV_SAMPLE_DEPTH_16BIT);
          if (ImGui::MenuItem(_L("cut##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_CUT))) {
            doAction(GUI_ACTION_SAMPLE_CUT);
          }
          ImGui::EndDisabled();
          if (ImGui::MenuItem(_L("copy##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_COPY))) {
            doAction(GUI_ACTION_SAMPLE_COPY);
          }
          ImGui::BeginDisabled(sample->depth!=DIV_SAMPLE_DEPTH_8BIT && sample->depth!=DIV_SAMPLE_DEPTH_16BIT);
          if (ImGui::MenuItem(_L("paste##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_PASTE))) {
            doAction(GUI_ACTION_SAMPLE_PASTE);
          }
          if (ImGui::MenuItem(_L("paste (replace)##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_PASTE_REPLACE))) {
            doAction(GUI_ACTION_SAMPLE_PASTE_REPLACE);
          }
          if (ImGui::MenuItem(_L("paste (mix)##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_PASTE_MIX))) {
            doAction(GUI_ACTION_SAMPLE_PASTE_MIX);
          }
          ImGui::EndDisabled();
          if (ImGui::MenuItem(_L("select all##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_SELECT_ALL))) {
            doAction(GUI_ACTION_SAMPLE_SELECT_ALL);
          }
          ImGui::Separator();
          if (ImGui::MenuItem(_L("set loop to selection##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_SET_LOOP))) {
            doAction(GUI_ACTION_SAMPLE_SET_LOOP);
          }
          if (ImGui::MenuItem(_L("create wavetable from selection##sgse"),BIND_FOR(GUI_ACTION_SAMPLE_CREATE_WAVE))) {
            doAction(GUI_ACTION_SAMPLE_CREATE_WAVE);
          }
          ImGui::EndPopup();
        }

        String statusBar=sampleDragMode?_L("Draw##sgse"):_L("Select##sgse");
        String statusBar2="";
        String statusBar3="";

        if(settings.language == DIV_LANG_ENGLISH)
        {
          statusBar3=fmt::sprintf("%d samples, %d bytes",sample->samples,sample->getCurBufLen());
        }
        else
        {
          String temp1 = fmt::sprintf(_LP("%d samples##sgse", sample->samples), sample->samples);
          String temp2 = fmt::sprintf(_LP("%d bytes##sgse", sample->getCurBufLen()), sample->getCurBufLen());
          statusBar3=fmt::sprintf("%s, %s",temp1,temp2);
        }
        
        bool drawSelection=false;

        if (!sampleDragMode) {
          if (sampleSelStart>=0 && sampleSelEnd>=0) {
            int start=sampleSelStart;
            int end=sampleSelEnd;
            if (start>end) {
              start^=end;
              end^=start;
              start^=end;
            }
            if (start==end) {
              statusBar+=fmt::sprintf(" (%d)",start);
            } else {
              statusBar+=fmt::sprintf(_LP(" (%d-%d: %d samples)##sgse", end-start),start,end,end-start);
            }
            drawSelection=true;
          }
        }

        if (ImGui::IsItemHovered()) {
          if (ctrlWheeling) {
            double zoomPercent=100.0/sampleZoom;
            if (wheelY>0) {
              for (int i=0; i<wheelY; i++) {
                double oldArea=round(rectSize.x*100.0/zoomPercent);
                zoomPercent+=zoomPercent/8.0;
                double increment=fabs(oldArea-(rectSize.x*100.0/zoomPercent))*((ImGui::GetMousePos().x-rectMin.x)/rectSize.x);
                samplePos+=increment;
              }
            } else {
              for (int i=0; i<-wheelY; i++) {
                double oldArea=round(rectSize.x*100.0/zoomPercent);
                zoomPercent-=zoomPercent/8.0;
                double increment=fabs(oldArea-(rectSize.x*100.0/zoomPercent))*((ImGui::GetMousePos().x-rectMin.x)/rectSize.x);
                samplePos-=increment;
                if (samplePos<0) samplePos=0;
              }
            }
            if (zoomPercent>10000.0) zoomPercent=10000.0;
            if (zoomPercent<0.01) zoomPercent=0.01;
            sampleZoom=100.0/zoomPercent;
            sampleZoomAuto=false;
            int bounds=((int)sample->samples-round(rectSize.x*sampleZoom));
            if (bounds<0) bounds=0;
            if (samplePos>bounds) samplePos=bounds;
            updateSampleTex=true;
            if (sampleZoom>minSampleZoom) {
              sampleZoomAuto=true;
            }
          } else {
            if (wheelY!=0) {
              if (!sampleZoomAuto) {
                double scrollAmount=MAX(fabs((double)wheelY*sampleZoom*60.0),1.0);
                if (wheelY>0) {
                  samplePos+=scrollAmount;
                } else {
                  samplePos-=scrollAmount;
                }
                if (samplePos<0) samplePos=0;
                int bounds=((int)sample->samples-round(rectSize.x*sampleZoom));
                if (bounds<0) bounds=0;
                if (samplePos>bounds) samplePos=bounds;
                updateSampleTex=true;
              }
            }
          }

          int posX=-1;
          int posY=0;
          ImVec2 pos=ImGui::GetMousePos();
          pos.x-=rectMin.x;
          pos.y-=rectMin.y;

          if (sampleZoom>0) {
            posX=samplePos+pos.x*sampleZoom;
            if (posX>(int)sample->samples) posX=-1;
          }
          posY=(0.5-pos.y/rectSize.y)*((sample->depth==DIV_SAMPLE_DEPTH_8BIT)?255:65535);
          if (posX>=0) {
            statusBar2=fmt::sprintf("(%d, %d)",posX,posY);
          }
        }

        dl->PushClipRect(rectMin,rectMax);
        if (e->isPreviewingSample() && e->getSamplePreviewSample()==curSample) {
          if (!statusBar2.empty()) {
            statusBar2+=" | ";
          }
          statusBar2+=fmt::sprintf("%.2fHz",e->getSamplePreviewRate());

          int start=sampleSelStart;
          int end=sampleSelEnd;
          if (start>end) {
            start^=end;
            end^=start;
            start^=end;
          }
          ImVec2 p1=rectMin;
          p1.x+=(e->getSamplePreviewPos()-samplePos)/sampleZoom;     
          ImVec4 posColor=uiColors[GUI_COLOR_SAMPLE_NEEDLE];
          ImVec4 posTrail1=posColor;
          ImVec4 posTrail2=posColor;
          posTrail1.w*=0.5f;
          posTrail2.w=0.0f;
          float trailDistance=(e->getSamplePreviewRate()/100.0f)/sampleZoom;

          //if (p1.x<rectMin.x) p1.x=rectMin.x;
          //if (p1.x>rectMax.x) p1.x=rectMax.x;

          ImVec2 p2=p1;
          p2.y=rectMax.y;

          dl->AddRectFilledMultiColor(
            ImVec2(p1.x-trailDistance,p1.y),
            p2,
            ImGui::GetColorU32(posTrail2),
            ImGui::GetColorU32(posTrail1),
            ImGui::GetColorU32(posTrail1),
            ImGui::GetColorU32(posTrail2)
          );
          dl->AddLine(p1,p2,ImGui::GetColorU32(posColor));
        }

        if (e->isRunning()) {
          for (int i=0; i<e->getTotalChannelCount(); i++) {
            DivSamplePos chanPos=e->getSamplePos(i);
            if (chanPos.sample!=curSample) continue;

            int start=sampleSelStart;
            int end=sampleSelEnd;
            if (start>end) {
              start^=end;
              end^=start;
              start^=end;
            }
            ImVec2 p1=rectMin;
            p1.x+=(chanPos.pos-samplePos)/sampleZoom;     
            ImVec4 posColor=uiColors[GUI_COLOR_SAMPLE_NEEDLE_PLAYING];
            ImVec4 posTrail1=posColor;
            ImVec4 posTrail2=posColor;
            posTrail1.w*=0.5f;
            posTrail2.w=0.0f;
            float trailDistance=((float)chanPos.freq/100.0f)/sampleZoom;

            //if (p1.x<rectMin.x) p1.x=rectMin.x;
            //if (p1.x>rectMax.x) p1.x=rectMax.x;

            ImVec2 p2=p1;
            p2.y=rectMax.y;

            dl->AddRectFilledMultiColor(
              ImVec2(p1.x-trailDistance,p1.y),
              p2,
              ImGui::GetColorU32(posTrail2),
              ImGui::GetColorU32(posTrail1),
              ImGui::GetColorU32(posTrail1),
              ImGui::GetColorU32(posTrail2)
            );
            dl->AddLine(p1,p2,ImGui::GetColorU32(posColor));
          }
        }
        dl->PopClipRect();

        if (drawSelection) {
          int start=sampleSelStart;
          int end=sampleSelEnd;
          if (start>end) {
            start^=end;
            end^=start;
            start^=end;
          }
          ImVec2 p1=rectMin;
          p1.x+=(start-samplePos)/sampleZoom;

          ImVec2 p2=ImVec2(rectMin.x+(end-samplePos)/sampleZoom,rectMax.y);
          ImVec4 boundColor=uiColors[GUI_COLOR_SAMPLE_SEL_POINT];
          ImVec4 selColor=uiColors[GUI_COLOR_SAMPLE_SEL];

          if (p1.x<rectMin.x) p1.x=rectMin.x;
          if (p1.x>rectMax.x) p1.x=rectMax.x;

          if (p2.x<rectMin.x) p2.x=rectMin.x;
          if (p2.x>rectMax.x) p2.x=rectMax.x;

          dl->AddRectFilled(p1,p2,ImGui::GetColorU32(selColor));
          dl->AddLine(ImVec2(p1.x,p1.y),ImVec2(p1.x,p2.y),ImGui::GetColorU32(boundColor));
          if (start!=end) {
            dl->AddLine(ImVec2(p2.x,p1.y),ImVec2(p2.x,p2.y),ImGui::GetColorU32(boundColor));
          }
        }

        ImS64 scrollV=samplePos;
        ImS64 availV=round(rectSize.x*sampleZoom);
        ImS64 contentsV=MAX(sample->samples,MAX(availV,1));

        ImGuiID scrollbarID=ImGui::GetID("sampleScroll");
        ImGui::KeepAliveID(scrollbarID);
        if (ImGui::ScrollbarEx(ImRect(ImVec2(rectMin.x,rectMax.y),ImVec2(rectMax.x,rectMax.y+ImGui::GetStyle().ScrollbarSize)),scrollbarID,ImGuiAxis_X,&scrollV,availV,contentsV,0)) {
          if (!sampleZoomAuto && samplePos!=scrollV) {
            samplePos=scrollV;
            updateSampleTex=true;
          }
        }

        if (sample->depth!=DIV_SAMPLE_DEPTH_8BIT && sample->depth!=DIV_SAMPLE_DEPTH_16BIT && sampleDragMode) {
          statusBar=_L("Non-8/16-bit samples cannot be edited without prior conversion.##sgse");
        }
        
        ImGui::SetCursorPosY(ImGui::GetCursorPosY()+ImGui::GetStyle().ScrollbarSize);
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding,ImVec2(0,0));
        if (ImGui::BeginTable("SEStatus",3,ImGuiTableFlags_BordersInnerV)) {
          ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.7);
          ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.3);
          ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed);

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::TextUnformatted(statusBar.c_str());
          ImGui::TableNextColumn();
          if (!warnRate.empty()) {
            ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_WARNING]);
            ImGui::TextUnformatted(statusBar2.c_str());
            ImGui::PopStyleColor();
            if (ImGui::IsItemHovered()) {
              ImGui::SetTooltip("%s",warnRate.c_str());
            }
          } else {
            ImGui::TextUnformatted(statusBar2.c_str());
          }
          ImGui::TableNextColumn();
          if (!warnLength.empty()) {
            ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_WARNING]);
            ImGui::TextUnformatted(statusBar3.c_str());
            ImGui::PopStyleColor();
            if (ImGui::IsItemHovered()) {
              ImGui::SetTooltip("%s",warnLength.c_str());
            }
          } else {
            ImGui::TextUnformatted(statusBar3.c_str());
          }

          ImGui::EndTable();
        }
        ImGui::PopStyleVar();
      }
    }
  }
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_SAMPLE_EDIT;
  ImGui::End();
}

void FurnaceGUI::doUndoSample() {
  if (!sampleEditOpen) return;
  if (curSample<0 || curSample>=(int)e->song.sample.size()) return;
  DivSample* sample=e->song.sample[curSample];
  e->lockEngine([this,sample]() {
    if (sample->undo()==2) {
      e->renderSamples(curSample);
      updateSampleTex=true;
    }
  });
}

void FurnaceGUI::doRedoSample() {
  if (!sampleEditOpen) return;
  if (curSample<0 || curSample>=(int)e->song.sample.size()) return;
  DivSample* sample=e->song.sample[curSample];
  e->lockEngine([this,sample]() {
    if (sample->redo()==2) {
      e->renderSamples(curSample);
      updateSampleTex=true;
    }
  });
}
