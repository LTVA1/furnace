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

#include "gui.h"
#include "IconsFontAwesome4.h"
#include "misc/cpp/imgui_stdlib.h"
#include "plot_nolerp.h"
#include "guiConst.h"
#include "../ta-log.h"
#include <fmt/printf.h>
#include <imgui.h>
#include <imgui_internal.h>

const char* sampleNote[12]={
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

#define DRAG_SOURCE(_d,_a,_c) \
  if (ImGui::BeginDragDropSource()) { \
    dirToMove=_d; \
    assetToMove=_a; \
    ImGui::SetDragDropPayload(_c,NULL,0,ImGuiCond_Once); \
    ImGui::Button(ICON_FA_ARROWS "##AssetDrag"); \
    ImGui::EndDragDropSource(); \
  }

#define DRAG_TARGET(_d,_a,_type,_c) \
  if (ImGui::BeginDragDropTarget()) { \
    const ImGuiPayload* dragItem=ImGui::AcceptDragDropPayload(_c); \
    if (dragItem!=NULL) { \
      if (dragItem->IsDataType(_c)) { \
        if (assetToMove==-1) { \
          if (dirToMove!=_d && _a==-1) { \
            e->lockEngine([&]() { \
              DivAssetDir val=_type[dirToMove]; \
              _type.erase(_type.begin()+dirToMove); \
              _type.insert(_type.begin()+_d,val); \
            }); \
          } \
        } else { \
          if (dirToMove!=_d || assetToMove!=_a) { \
            logV("%d/%d -> %d/%d",dirToMove,assetToMove,_d,_a); \
            e->lockEngine([&]() { \
              int val=_type[dirToMove].entries[assetToMove]; \
              _type[dirToMove].entries.erase(_type[dirToMove].entries.begin()+assetToMove); \
              _type[_d].entries.insert((_a<0)?(_type[_d].entries.end()):(_type[_d].entries.begin()+_a),val); \
            }); \
          } \
        } \
        dirToMove=-1; \
        assetToMove=-1; \
      } \
    } \
    ImGui::EndDragDropTarget(); \
  }

void FurnaceGUI::insListItem(int i, int dir, int asset) {
  ImGui::PushID(i);
  String name=(settings.insIconsStyle==0)?"":ICON_FA_CIRCLE_O;
  const char* insType=_L("Bug!##sgdl");
  if (i>=0 && i<e->song.insLen) {
    DivInstrument* ins=e->song.ins[i];
    insType=(ins->type>=DIV_INS_MAX)?_L("Unknown##sgdl"):insTypes[ins->type][0];
    const char** insIcon=NULL;

    if (ins->type>=DIV_INS_MAX) {
      ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_INSTR_UNKNOWN]);
      insIcon=insTypes[DIV_INS_MAX];
    } else {
      ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_INSTR_STD+ins->type]);
      insIcon=insTypes[ins->type];
    }
  
    switch (settings.insIconsStyle) {
      case 1:
        name=fmt::sprintf("%s##_INS%d",insIcon[1],i);
        break;
      case 2:
        name=fmt::sprintf("%s##_INS%d",insIcon[2],i);
        break;
      default:
        name=fmt::sprintf("##_INS%d",i);
        break;
    }
  } else {
    ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_TEXT]);
  }
  bool insReleased=ImGui::Selectable(name.c_str(),(i==-1)?(curIns<0 || curIns>=e->song.insLen):(curIns==i));
  bool insPressed=ImGui::IsItemActivated();
  if (insReleased || (!insListDir && insPressed)) {
    curIns=i;
    if (!insReleased || insListDir) {
      wavePreviewInit=true;
      updateFMPreview=true;
    }
    lastAssetType=0;
    if (settings.insFocusesPattern && patternOpen)
      nextWindow=GUI_WINDOW_PATTERN;
  }
  if (wantScrollList && curIns==i) ImGui::SetScrollHereY();
  if (ImGui::IsItemHovered() && i>=0 && !mobileUI) {
    ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_TEXT]);
    ImGui::SetTooltip("%s",insType);
    ImGui::PopStyleColor();
    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
      insEditOpen=true;
      nextWindow=GUI_WINDOW_INS_EDIT;
    }
  }
  if (i>=0) {
    if (insListDir) {
      DRAG_SOURCE(dir,asset,"FUR_INSDIR");
      DRAG_TARGET(dir,asset,e->song.insDir,"FUR_INSDIR");
    }

    if (ImGui::BeginPopupContextItem("InsRightMenu")) {
      curIns=i;
      updateFMPreview=true;
      ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_TEXT]);
      if (ImGui::MenuItem(_L("duplicate##sgdl0"))) {
        doAction(GUI_ACTION_INS_LIST_DUPLICATE);
      }
      if (ImGui::MenuItem(_L("replace...##sgdl0"))) {
        doAction((curIns>=0 && curIns<(int)e->song.ins.size())?GUI_ACTION_INS_LIST_OPEN_REPLACE:GUI_ACTION_INS_LIST_OPEN);
      }
      if (ImGui::MenuItem(_L("save##sgdl0"))) {
        doAction(GUI_ACTION_INS_LIST_SAVE);
      }
      if (ImGui::MenuItem(_L("export (.dmp)##sgdl"))) {
        doAction(GUI_ACTION_INS_LIST_SAVE_DMP);
      }
      if (ImGui::MenuItem(_L("delete##sgdl0"))) {
        doAction(GUI_ACTION_INS_LIST_DELETE);
      }
      ImGui::PopStyleColor();
      ImGui::EndPopup();
    }
  }
  if (i>=0) {
    if (i<(int)e->song.ins.size()) {
      DivInstrument* ins=e->song.ins[i];
      ImGui::SameLine();
      ImGui::TextNoHashHide("%.2X: %s",i,ins->name.c_str());
    } else {
      ImGui::SameLine();
      ImGui::Text(_L("%.2X: <INVALID>##sgdl"),i);
    }
  } else {
    ImGui::SameLine();
    ImGui::Text(_L("- None -##sgdl"));
  }
  ImGui::PopID();
  ImGui::PopStyleColor();
}

void FurnaceGUI::waveListItem(int i, float* wavePreview, int dir, int asset) {
  DivWavetable* wave=e->song.wave[i];
  for (int i=0; i<wave->len; i++) {
    wavePreview[i]=wave->data[i];
  }
  if (wave->len>0) wavePreview[wave->len]=wave->data[wave->len-1];
  ImVec2 curPos=ImGui::GetCursorPos();
  ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,ImVec2(0,0.5f));
  if (ImGui::Selectable(fmt::sprintf(" %d##_WAVE%d\n",i,i).c_str(),curWave==i,0,ImVec2(0,ImGui::GetFrameHeight()))) {
    curWave=i;
    localWaveList = false;
    lastAssetType=1;
  }
  ImGui::PopStyleVar();
  curPos.x+=ImGui::CalcTextSize("2222").x;
  if (wantScrollList && curWave==i) ImGui::SetScrollHereY();
  if (ImGui::IsItemHovered()) {
    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
      waveEditOpen=true;
      localWaveList = false;
      nextWindow=GUI_WINDOW_WAVE_EDIT;
    }
  }
  if (waveListDir || (settings.unifiedDataView && insListDir)) {
    DRAG_SOURCE(dir,asset,"FUR_WAVEDIR");
    DRAG_TARGET(dir,asset,e->song.waveDir,"FUR_WAVEDIR");
  }
  ImGui::SameLine();
  ImGui::SetCursorPos(curPos);
  PlotNoLerp(fmt::sprintf("##_WAVEP%d",i).c_str(),wavePreview,wave->len+1,0,NULL,0,wave->max,ImVec2(ImGui::GetContentRegionAvail().x,ImGui::GetFrameHeight()));
}

void FurnaceGUI::sampleListItem(int i, int dir, int asset) {
  bool memWarning=false;

  ImGui::PushID(i);

  DivSample* sample=e->song.sample[i];
  for (int j=0; j<e->song.systemLen; j++) {
    DivDispatch* dispatch=e->getDispatch(j);
    if (dispatch==NULL) continue;

    for (int k=0; k<DIV_MAX_SAMPLE_TYPE; k++) {
      if (dispatch->getSampleMemCapacity(k)==0) continue;
      if (!dispatch->isSampleLoaded(k,i) && sample->renderOn[k][j]) {
        memWarning=true;
        break;
      }
    }
    if (memWarning) break;
  }
  if (memWarning) ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_SAMPLE_CHIP_WARNING]);
  if (ImGui::Selectable(fmt::sprintf("%d: %s##_SAM%d",i,sample->name,i).c_str(),curSample==i,ImGuiSelectableFlags_NoHashTextHide)) {
    curSample=i;
    samplePos=0;
    updateSampleTex=true;
    lastAssetType=2;
  }
  if (ImGui::IsItemHovered() && !mobileUI) {
    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
      sampleEditOpen=true;
      nextWindow=GUI_WINDOW_SAMPLE_EDIT;
    }
  }
  if (sampleListDir || (settings.unifiedDataView && insListDir)) {
    DRAG_SOURCE(dir,asset,"FUR_SDIR");
    DRAG_TARGET(dir,asset,e->song.sampleDir,"FUR_SDIR");
  }
  if (memWarning) {
    ImGui::SameLine();
    ImGui::Text(ICON_FA_EXCLAMATION_TRIANGLE);
    if (ImGui::IsItemHovered() && !mobileUI) {
      ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_TEXT]);
      ImGui::SetTooltip(_L("out of memory for this sample!##sgdl"));
      ImGui::PopStyleColor();
    }
    ImGui::PopStyleColor();
  }
  if (ImGui::BeginPopupContextItem("SampleRightMenu")) {
    curSample=i;
    samplePos=0;
    updateSampleTex=true;
    lastAssetType=2;
    ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_TEXT]);
    if (ImGui::MenuItem(_L("make instrument##sgdl"))) {
      doAction(GUI_ACTION_SAMPLE_MAKE_INS);
    }
    if (ImGui::MenuItem(_L("make me a drum kit##sgdl"))) {
      doAction(GUI_ACTION_SAMPLE_LIST_MAKE_MAP);
    }
    if (ImGui::MenuItem(_L("duplicate##sgdl1"))) {
      doAction(GUI_ACTION_SAMPLE_LIST_DUPLICATE);
    }
    if (ImGui::MenuItem(_L("replace...##sgdl1"))) {
      doAction((curSample>=0 && curSample<(int)e->song.sample.size())?GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE:GUI_ACTION_SAMPLE_LIST_OPEN);
    }
    if (ImGui::MenuItem(_L("save##sgdl1"))) {
      doAction(GUI_ACTION_SAMPLE_LIST_SAVE);
    }
    if (ImGui::MenuItem(_L("delete##sgdl1"))) {
      doAction(GUI_ACTION_SAMPLE_LIST_DELETE);
    }
    ImGui::PopStyleColor();
    ImGui::EndPopup();
  }
  if (wantScrollList && curSample==i) ImGui::SetScrollHereY();
  ImGui::PopID();
}

void FurnaceGUI::drawInsList(bool asChild) {
  if (nextWindow==GUI_WINDOW_INS_LIST) {
    insListOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!insListOpen && !asChild) return;
  bool began=false;
  if (asChild) {
    began=ImGui::BeginChild("Instruments");
  } else {
    began=ImGui::Begin("Instruments",&insListOpen,globalWinFlags,_L("Instruments###Instruments"));
  }
  if (began) {
    if (settings.unifiedDataView) settings.horizontalDataView=0;
    if (ImGui::Button(ICON_FA_PLUS "##InsAdd")) {
      if (settings.unifiedDataView) {
        switch (lastAssetType) {
          case 0:
            doAction(GUI_ACTION_INS_LIST_ADD);
            break;
          case 1:
            doAction(GUI_ACTION_WAVE_LIST_ADD);
            break;
          case 2:
            doAction(GUI_ACTION_SAMPLE_LIST_ADD);
            break;
        }
      } else {
        doAction(GUI_ACTION_INS_LIST_ADD);
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Add##sgdl0"));
    }
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
      makeInsTypeList=e->getPossibleInsTypes();
      displayInsTypeList=true;
      displayInsTypeListMakeInsSample=-1;
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILES_O "##InsClone")) {
      if (settings.unifiedDataView) {
        switch (lastAssetType) {
          case 0:
            doAction(GUI_ACTION_INS_LIST_DUPLICATE);
            break;
          case 1:
            doAction(GUI_ACTION_WAVE_LIST_DUPLICATE);
            break;
          case 2:
            doAction(GUI_ACTION_SAMPLE_LIST_DUPLICATE);
            break;
        }
      } else {
        doAction(GUI_ACTION_INS_LIST_DUPLICATE);
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Duplicate##sgdl2"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FOLDER_OPEN "##InsLoad")) {
      if (settings.unifiedDataView) {
        switch (lastAssetType) {
          case 0:
            doAction(GUI_ACTION_INS_LIST_OPEN);
            break;
          case 1:
            doAction(GUI_ACTION_WAVE_LIST_OPEN);
            break;
          case 2:
            doAction(GUI_ACTION_SAMPLE_LIST_OPEN);
            break;
        }
      } else {
        doAction(GUI_ACTION_INS_LIST_OPEN);
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Open##sgdl0"));
    }
    if (ImGui::BeginPopupContextItem("InsOpenOpt")) {
      if (settings.unifiedDataView) {
        if (ImGui::MenuItem(_L("replace instrument...##sgdl"))) {
          doAction((curIns>=0 && curIns<(int)e->song.ins.size())?GUI_ACTION_INS_LIST_OPEN_REPLACE:GUI_ACTION_INS_LIST_OPEN);
        }
        if (ImGui::MenuItem(_L("load instrument from TX81Z##sgdl"))) {
          doAction(GUI_ACTION_TX81Z_REQUEST);
        }

        ImGui::Separator();

        if (ImGui::MenuItem(_L("replace wavetable...##sgdl"))) {
          doAction((curWave>=0 && curWave<(int)e->song.wave.size())?GUI_ACTION_WAVE_LIST_OPEN_REPLACE:GUI_ACTION_WAVE_LIST_OPEN);
        }

        ImGui::Separator();

        if (ImGui::MenuItem(_L("replace sample...##sgdl"))) {
          doAction((curSample>=0 && curSample<(int)e->song.sample.size())?GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE:GUI_ACTION_SAMPLE_LIST_OPEN);
        }
        if (ImGui::MenuItem(_L("import raw sample...##sgdl"))) {
          doAction(GUI_ACTION_SAMPLE_LIST_OPEN_RAW);
        }
        if (ImGui::MenuItem(_L("import raw sample (replace)...##sgdl"))) {
          doAction((curSample>=0 && curSample<(int)e->song.sample.size())?GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE_RAW:GUI_ACTION_SAMPLE_LIST_OPEN_RAW);
        }
      } else {
        if (ImGui::MenuItem(_L("replace...##sgdl2"))) {
          doAction((curIns>=0 && curIns<(int)e->song.ins.size())?GUI_ACTION_INS_LIST_OPEN_REPLACE:GUI_ACTION_INS_LIST_OPEN);
        }
        ImGui::Separator();
        if (ImGui::MenuItem(_L("load from TX81Z##sgdl"))) {
          doAction(GUI_ACTION_TX81Z_REQUEST);
        }
      }
      ImGui::EndPopup();
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Open (insert; right-click to replace)##sgdl"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FLOPPY_O "##InsSave")) {
      if (settings.unifiedDataView) {
        switch (lastAssetType) {
          case 0:
            doAction(GUI_ACTION_INS_LIST_SAVE);
            break;
          case 1:
            doAction(GUI_ACTION_WAVE_LIST_SAVE);
            break;
          case 2:
            doAction(GUI_ACTION_SAMPLE_LIST_SAVE);
            break;
        }
      } else {
        doAction(GUI_ACTION_INS_LIST_SAVE);
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Save##sgdl2"));
    }
    if (ImGui::BeginPopupContextItem("InsSaveFormats",ImGuiMouseButton_Right)) {
      if (settings.unifiedDataView) {
        if (ImGui::MenuItem(_L("save instrument as .dmp...##sgdl"))) {
          doAction(GUI_ACTION_INS_LIST_SAVE_DMP);
        }

        ImGui::Separator();

        if (ImGui::MenuItem(_L("save wavetable as .dmw...##sgdl"))) {
          doAction(GUI_ACTION_WAVE_LIST_SAVE_DMW);
        }
        if (ImGui::MenuItem(_L("save raw wavetable...##sgdl"))) {
          doAction(GUI_ACTION_WAVE_LIST_SAVE_RAW);
        }

        ImGui::Separator();

        if (ImGui::MenuItem(_L("save raw sample...##sgdl"))) {
          doAction(GUI_ACTION_SAMPLE_LIST_SAVE_RAW);
        }
      } else {
        if (ImGui::MenuItem(_L("save as .dmp...##sgdl"))) {
          doAction(GUI_ACTION_INS_LIST_SAVE_DMP);
        }
      }
      ImGui::EndPopup();
    }
    ImGui::SameLine();
    pushToggleColors(insListDir);
    if (ImGui::Button(ICON_FA_SITEMAP "##DirMode")) {
      doAction(GUI_ACTION_INS_LIST_DIR_VIEW);
    }
    popToggleColors();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Toggle folders/standard view##sgdl0"));
    }
    if (!insListDir) {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_ARROW_UP "##InsUp")) {
        if (settings.unifiedDataView) {
          switch (lastAssetType) {
            case 0:
              doAction(GUI_ACTION_INS_LIST_MOVE_UP);
              break;
            case 1:
              doAction(GUI_ACTION_WAVE_LIST_MOVE_UP);
              break;
            case 2:
              doAction(GUI_ACTION_SAMPLE_LIST_MOVE_UP);
              break;
          }
        } else {
          doAction(GUI_ACTION_INS_LIST_MOVE_UP);
        }
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Move up##sgdl0"));
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_ARROW_DOWN "##InsDown")) {
        if (settings.unifiedDataView) {
          switch (lastAssetType) {
            case 0:
              doAction(GUI_ACTION_INS_LIST_MOVE_DOWN);
              break;
            case 1:
              doAction(GUI_ACTION_WAVE_LIST_MOVE_DOWN);
              break;
            case 2:
              doAction(GUI_ACTION_SAMPLE_LIST_MOVE_DOWN);
              break;
          }
        } else {
          doAction(GUI_ACTION_INS_LIST_MOVE_DOWN);
        }
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Move down##sgdl0"));
      }
    } else {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_FOLDER "##InsFolder")) {
        folderString="";
      }
      if (ImGui::BeginPopupContextItem("NewInsFolder",ImGuiMouseButton_Left)) {
        ImGui::InputText("##FolderName",&folderString);
        ImGui::SameLine();
        ImGui::BeginDisabled(folderString.empty());
        if (ImGui::Button(_L("Create##sgdl0"))) {
          if (settings.unifiedDataView) {
            switch (lastAssetType) {
              case 0:
                e->lockEngine([this]() {
                  e->song.insDir.push_back(DivAssetDir(folderString));
                });
                break;
              case 1:
                e->lockEngine([this]() {
                  e->song.waveDir.push_back(DivAssetDir(folderString));
                });
                break;
              case 2:
                e->lockEngine([this]() {
                  e->song.sampleDir.push_back(DivAssetDir(folderString));
                });
                break;
            }
          } else {
            e->lockEngine([this]() {
              e->song.insDir.push_back(DivAssetDir(folderString));
            });
          }
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndDisabled();
        ImGui::EndPopup();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("New folder##sgdl0"));
      }
    }
    if (lastAssetType==2) {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_VOLUME_UP "##PreviewSampleL")) {
        doAction(GUI_ACTION_SAMPLE_LIST_PREVIEW);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Preview (right click to stop)##sgdl0"));
      }
      if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        doAction(GUI_ACTION_SAMPLE_LIST_STOP_PREVIEW);
      }
    }
    ImGui::SameLine();
    pushDestColor();
    if (ImGui::Button(ICON_FA_TIMES "##InsDelete")) {
      if (settings.unifiedDataView) {
        switch (lastAssetType) {
          case 0:
            doAction(GUI_ACTION_INS_LIST_DELETE);
            break;
          case 1:
            doAction(GUI_ACTION_WAVE_LIST_DELETE);
            break;
          case 2:
            doAction(GUI_ACTION_SAMPLE_LIST_DELETE);
            break;
        }
      } else {
        doAction(GUI_ACTION_INS_LIST_DELETE);
      }
    }
    popDestColor();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Delete##sgdl2"));
    }
    ImGui::Separator();
    int availableRows=ImGui::GetContentRegionAvail().y/ImGui::GetFrameHeight();
    if (availableRows<1) availableRows=1;
    int columns=settings.horizontalDataView?(int)(ceil((double)(e->song.ins.size()+1)/(double)availableRows)):1;
    if (columns<1) columns=1;
    if (columns>64) columns=64;
    if (insListDir) columns=1;
    if (ImGui::BeginTable("InsListScroll",columns,(settings.horizontalDataView?ImGuiTableFlags_ScrollX:0)|ImGuiTableFlags_ScrollY)) {
      if (settings.unifiedDataView) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::Selectable(ICON_FA_TASKS "##Instruments",lastAssetType==0)) {
          lastAssetType=0;
        }
        ImGui::SameLine();
        ImGui::Text(_L("Instruments##sgdl"));
        ImGui::Indent();
      }

      if (settings.horizontalDataView && !insListDir) {
        ImGui::TableNextRow();
      }

      if (insListDir) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        insListItem(-1,-1,-1);
        int dirIndex=0;
        int dirToDelete=-1;
        for (DivAssetDir& i: e->song.insDir) {
          String nodeName=fmt::sprintf("%s %s##_ADI%d",i.name.empty()?ICON_FA_FOLDER_O:ICON_FA_FOLDER,i.name.empty()?_L("<uncategorized>##sgdl0"):i.name,i.name.empty()?-1:dirIndex);
          String popupID=fmt::sprintf("DirRightMenu%d",dirIndex);
          bool treeNode=ImGui::TreeNodeEx(nodeName.c_str(),ImGuiTreeNodeFlags_SpanAvailWidth|(i.name.empty()?ImGuiTreeNodeFlags_DefaultOpen:0));
          DRAG_SOURCE(dirIndex,-1,"FUR_INSDIR");
          DRAG_TARGET(dirIndex,-1,e->song.insDir,"FUR_INSDIR");
          if (ImGui::BeginPopupContextItem(popupID.c_str())) {
            if (ImGui::MenuItem(_L("rename...##sgdl0"))) {
              editStr(&i.name);
            }
            if (ImGui::MenuItem(_L("delete##sgdl3"))) {
              dirToDelete=dirIndex;
            }
            ImGui::EndPopup();
          }
          if (treeNode) {
            int assetIndex=0;
            for (int j: i.entries) {
              insListItem(j,dirIndex,assetIndex);
              assetIndex++;
            }
            ImGui::TreePop();
          }
          dirIndex++;
        }
        if (dirToDelete!=-1) {
          e->lockEngine([this,dirToDelete]() {
            e->song.insDir.erase(e->song.insDir.begin()+dirToDelete);
            e->checkAssetDir(e->song.insDir,e->song.ins.size());
          });
        }
      } else {
        int curRow=0;
        for (int i=-1; i<(int)e->song.ins.size(); i++) {
          if (!settings.horizontalDataView) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
          } else if (curRow==0) {
            ImGui::TableNextColumn();
          }
          insListItem(i,-1,-1);
          if (settings.horizontalDataView) {
            if (++curRow>=availableRows) curRow=0;
          }
        }
      }

      if (settings.unifiedDataView) {
        ImGui::Unindent();

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::Selectable(ICON_FA_AREA_CHART "##Wavetables",lastAssetType==1)) {
          lastAssetType=1;
        }
        ImGui::SameLine();
        ImGui::Text(_L("Wavetables##sgdl"));
        ImGui::Indent();
        actualWaveList();
        ImGui::Unindent();

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::Selectable(ICON_FA_VOLUME_UP "##Samples",lastAssetType==2)) {
          lastAssetType=2;
        }
        ImGui::SameLine();
        ImGui::Text(_L("Samples##sgdl"));
        ImGui::Indent();
        actualSampleList();
        ImGui::Unindent();
      }

      ImGui::EndTable();
    }
  }
  if (asChild) {
    ImGui::EndChild();
  } else {
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_INS_LIST;
    ImGui::End();
  }
}

void FurnaceGUI::drawWaveList(bool asChild) {
  if (nextWindow==GUI_WINDOW_WAVE_LIST) {
    waveListOpen=true;
    if (settings.unifiedDataView) {
      ImGui::SetWindowFocus("Instruments");
    } else {
      ImGui::SetNextWindowFocus();
    }
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (settings.unifiedDataView) return;
  if (!waveListOpen && !asChild) return;
  bool began=false;
  if (asChild) {
    began=ImGui::BeginChild("Wavetables");
  } else {
    began=ImGui::Begin("Wavetables",&waveListOpen,globalWinFlags, _L("Wavetables###Wavetables"));
  }
  if (began) {
    if (ImGui::Button(ICON_FA_PLUS "##WaveAdd")) {
      doAction(GUI_ACTION_WAVE_LIST_ADD);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Add##sgdl1"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILES_O "##WaveClone")) {
      doAction(GUI_ACTION_WAVE_LIST_DUPLICATE);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Duplicate##sgdl3"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FOLDER_OPEN "##WaveLoad")) {
      doAction(GUI_ACTION_WAVE_LIST_OPEN);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Open##sgdl1"));
    }
    if (ImGui::BeginPopupContextItem("WaveOpenOpt")) {
      if (ImGui::MenuItem(_L("replace...##sgdl3"))) {
        doAction((curWave>=0 && curWave<(int)e->song.wave.size())?GUI_ACTION_WAVE_LIST_OPEN_REPLACE:GUI_ACTION_WAVE_LIST_OPEN);
      }
      ImGui::EndPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FLOPPY_O "##WaveSave")) {
      doAction(GUI_ACTION_WAVE_LIST_SAVE);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Save##sgdl3"));
    }
    if (!settings.unifiedDataView) {
      if (ImGui::BeginPopupContextItem("WaveSaveFormats",ImGuiMouseButton_Right)) {
        if (ImGui::MenuItem(_L("save as .dmw...##sgdl"))) {
          doAction(GUI_ACTION_WAVE_LIST_SAVE_DMW);
        }
        if (ImGui::MenuItem(_L("save raw...##sgdl0"))) {
          doAction(GUI_ACTION_WAVE_LIST_SAVE_RAW);
        }
        ImGui::EndPopup();
      }
    }
    ImGui::SameLine();
    pushToggleColors(waveListDir);
    if (ImGui::Button(ICON_FA_SITEMAP "##WaveDirMode")) {
      doAction(GUI_ACTION_WAVE_LIST_DIR_VIEW);
    }
    popToggleColors();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Toggle folders/standard view##sgdl1"));
    }
    if (!waveListDir) {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_ARROW_UP "##WaveUp")) {
        doAction(GUI_ACTION_WAVE_LIST_MOVE_UP);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Move up##sgdl1"));
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_ARROW_DOWN "##WaveDown")) {
        doAction(GUI_ACTION_WAVE_LIST_MOVE_DOWN);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Move down##sgdl1"));
      }
    } else {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_FOLDER "##WaveFolder")) {
        folderString="";
      }
      if (ImGui::BeginPopupContextItem("NewWaveFolder",ImGuiMouseButton_Left)) {
        ImGui::InputText("##FolderName",&folderString);
        ImGui::SameLine();
        ImGui::BeginDisabled(folderString.empty());
        if (ImGui::Button(_L("Create##sgdl1"))) {
          e->lockEngine([this]() {
            e->song.waveDir.push_back(DivAssetDir(folderString));
          });
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndDisabled();
        ImGui::EndPopup();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("New folder##sgdl1"));
      }
    }
    ImGui::SameLine();
    pushDestColor();
    if (ImGui::Button(ICON_FA_TIMES "##WaveDelete")) {
      doAction(GUI_ACTION_WAVE_LIST_DELETE);
    }
    popDestColor();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Delete##sgdl4"));
    }
    ImGui::Separator();
    if (ImGui::BeginTable("WaveListScroll",1,ImGuiTableFlags_ScrollY)) {
      actualWaveList();
      ImGui::EndTable();
    }
  }
  if (asChild) {
    ImGui::EndChild();
  } else {
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_WAVE_LIST;
    ImGui::End();
  }
}

void FurnaceGUI::drawSampleList(bool asChild) {
  if (nextWindow==GUI_WINDOW_SAMPLE_LIST) {
    sampleListOpen=true;
    if (settings.unifiedDataView) {
      ImGui::SetWindowFocus("Instruments");
    } else {
      ImGui::SetNextWindowFocus();
    }
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (settings.unifiedDataView) return;
  if (!sampleListOpen && !asChild) return;
  bool began=false;
  if (asChild) {
    began=ImGui::BeginChild("Samples");
  } else {
    began=ImGui::Begin("Samples",&sampleListOpen,globalWinFlags, _L("Samples###Samples"));
  }
  if (began) {
    if (ImGui::Button(ICON_FA_FILE "##SampleAdd")) {
      doAction(GUI_ACTION_SAMPLE_LIST_ADD);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Add##sgdl2"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILES_O "##SampleClone")) {
      doAction(GUI_ACTION_SAMPLE_LIST_DUPLICATE);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Duplicate##sgdl4"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FOLDER_OPEN "##SampleLoad")) {
      doAction(GUI_ACTION_SAMPLE_LIST_OPEN);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Open##sgdl2"));
    }
    if (mobileUI && ImGui::IsItemActive() && CHECK_LONG_HOLD) {
      ImGui::OpenPopup("SampleOpenOpt");
      NOTIFY_LONG_HOLD;
    }
    if (ImGui::BeginPopupContextItem("SampleOpenOpt")) {
      if (ImGui::MenuItem(_L("replace...##sgdl4"))) {
        doAction((curSample>=0 && curSample<(int)e->song.sample.size())?GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE:GUI_ACTION_SAMPLE_LIST_OPEN);
      }
      ImGui::Separator();
      if (ImGui::MenuItem(_L("import raw...##sgdl"))) {
        doAction(GUI_ACTION_SAMPLE_LIST_OPEN_RAW);
      }
      if (ImGui::MenuItem(_L("import raw (replace)...##sgdl"))) {
        doAction((curSample>=0 && curSample<(int)e->song.sample.size())?GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE_RAW:GUI_ACTION_SAMPLE_LIST_OPEN_RAW);
      }
      ImGui::EndPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FLOPPY_O "##SampleSave")) {
      doAction(GUI_ACTION_SAMPLE_LIST_SAVE);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Save##sgdl4"));
    }
    if (mobileUI && ImGui::IsItemActive() && CHECK_LONG_HOLD) {
      ImGui::OpenPopup("SampleSaveOpt");
      NOTIFY_LONG_HOLD;
    }
    if (ImGui::BeginPopupContextItem("SampleSaveOpt")) {
      if (ImGui::MenuItem(_L("save raw...##sgdl1"))) {
        doAction(GUI_ACTION_SAMPLE_LIST_SAVE_RAW);
      }
      ImGui::EndPopup();
    }
    ImGui::SameLine();
    pushToggleColors(sampleListDir);
    if (ImGui::Button(ICON_FA_SITEMAP "##SampleDirMode")) {
      doAction(GUI_ACTION_SAMPLE_LIST_DIR_VIEW);
    }
    popToggleColors();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Toggle folders/standard view##sgdl2"));
    }
    if (!sampleListDir) {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_ARROW_UP "##SampleUp")) {
        doAction(GUI_ACTION_SAMPLE_LIST_MOVE_UP);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Move up##sgdl2"));
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_ARROW_DOWN "##SampleDown")) {
        doAction(GUI_ACTION_SAMPLE_LIST_MOVE_DOWN);
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("Move down##sgdl2"));
      }
    } else {
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_FOLDER "##SampleFolder")) {
        folderString="";
      }
      if (ImGui::BeginPopupContextItem("NewSampleFolder",ImGuiMouseButton_Left)) {
        ImGui::InputText("##FolderName",&folderString);
        ImGui::SameLine();
        ImGui::BeginDisabled(folderString.empty());
        if (ImGui::Button(_L("Create##sgdl2"))) {
          e->lockEngine([this]() {
            e->song.sampleDir.push_back(DivAssetDir(folderString));
          });
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndDisabled();
        ImGui::EndPopup();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(_L("New folder##sgdl2"));
      }
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_VOLUME_UP "##PreviewSampleL")) {
      doAction(GUI_ACTION_SAMPLE_LIST_PREVIEW);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Preview (right click to stop)##sgdl1"));
    }
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
      doAction(GUI_ACTION_SAMPLE_LIST_STOP_PREVIEW);
    }
    ImGui::SameLine();
    pushDestColor();
    if (ImGui::Button(ICON_FA_TIMES "##SampleDelete")) {
      doAction(GUI_ACTION_SAMPLE_LIST_DELETE);
    }
    popDestColor();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Delete##sgdl7"));
    }
    ImGui::Separator();
    if (ImGui::BeginTable("SampleListScroll",1,ImGuiTableFlags_ScrollY)) {
      actualSampleList();
      ImGui::EndTable();
    }
    ImGui::Unindent();
  }
  if (asChild) {
    ImGui::EndChild();
  } else {
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_SAMPLE_LIST;
    ImGui::End();
  }
}

void FurnaceGUI::actualWaveList() {
  float wavePreview[257];

  if (waveListDir || (settings.unifiedDataView && insListDir)) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    int dirIndex=0;
    int dirToDelete=-1;
    for (DivAssetDir& i: e->song.waveDir) {
      String nodeName=fmt::sprintf("%s %s##_ADW%d",i.name.empty()?ICON_FA_FOLDER_O:ICON_FA_FOLDER,i.name.empty()?_L("<uncategorized>##sgdl1"):i.name,i.name.empty()?-1:dirIndex);
      String popupID=fmt::sprintf("DirRightMenu%d",dirIndex);
      bool treeNode=ImGui::TreeNodeEx(nodeName.c_str(),ImGuiTreeNodeFlags_SpanAvailWidth|(i.name.empty()?ImGuiTreeNodeFlags_DefaultOpen:0));
      DRAG_SOURCE(dirIndex,-1,"FUR_WAVEDIR");
      DRAG_TARGET(dirIndex,-1,e->song.waveDir,"FUR_WAVEDIR");
      if (ImGui::BeginPopupContextItem(popupID.c_str())) {
        if (ImGui::MenuItem(_L("rename...##sgdl1"))) {
          editStr(&i.name);
        }
        if (ImGui::MenuItem(_L("delete##sgdl5"))) {
          dirToDelete=dirIndex;
        }
        ImGui::EndPopup();
      }
      if (treeNode) {
        int assetIndex=0;
        for (int j: i.entries) {
          waveListItem(j,wavePreview,dirIndex,assetIndex);
          assetIndex++;
        }
        ImGui::TreePop();
      }
      dirIndex++;
    }
    if (dirToDelete!=-1) {
      e->lockEngine([this,dirToDelete]() {
        e->song.waveDir.erase(e->song.waveDir.begin()+dirToDelete);
        e->checkAssetDir(e->song.waveDir,e->song.wave.size());
      });
    }
  } else {
    for (int i=0; i<(int)e->song.wave.size(); i++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      waveListItem(i,wavePreview,-1,-1);
    }
  }
}

void FurnaceGUI::actualSampleList() {
  if (sampleListDir || (settings.unifiedDataView && insListDir)) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    int dirIndex=0;
    int dirToDelete=-1;
    for (DivAssetDir& i: e->song.sampleDir) {
      String nodeName=fmt::sprintf("%s %s##_ADS%d",i.name.empty()?ICON_FA_FOLDER_O:ICON_FA_FOLDER,i.name.empty()?"<uncategorized>##sgdl2":i.name,i.name.empty()?-1:dirIndex);
      String popupID=fmt::sprintf("DirRightMenu%d",dirIndex);
      bool treeNode=ImGui::TreeNodeEx(nodeName.c_str(),ImGuiTreeNodeFlags_SpanAvailWidth|(i.name.empty()?ImGuiTreeNodeFlags_DefaultOpen:0));
      DRAG_SOURCE(dirIndex,-1,"FUR_SDIR");
      DRAG_TARGET(dirIndex,-1,e->song.sampleDir,"FUR_SDIR");
      if (ImGui::BeginPopupContextItem(popupID.c_str())) {
        if (ImGui::MenuItem(_L("rename...##sgdl2"))) {
          editStr(&i.name);
        }
        if (ImGui::MenuItem(_L("delete##sgdl6"))) {
          dirToDelete=dirIndex;
        }
        ImGui::EndPopup();
      }
      if (treeNode) {
        int assetIndex=0;
        for (int j: i.entries) {
          sampleListItem(j,dirIndex,assetIndex);
          assetIndex++;
        }
        ImGui::TreePop();
      }
      dirIndex++;
    }
    if (dirToDelete!=-1) {
      e->lockEngine([this,dirToDelete]() {
        e->song.sampleDir.erase(e->song.sampleDir.begin()+dirToDelete);
        e->checkAssetDir(e->song.sampleDir,e->song.sample.size());
      });
    }
  } else {
    for (int i=0; i<(int)e->song.sample.size(); i++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      sampleListItem(i,-1,-1);
    }
  }
}
