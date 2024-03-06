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
#include "misc/cpp/imgui_stdlib.h"
#include "IconsFontAwesome4.h"
#include <fmt/printf.h>
#include <imgui.h>

static const char* chan_type_names[DIV_CH_MAX] = {
  "FM",
  "Pulse",
  "Noise",
  "Wave",
  "PCM",
  "FM"
};

#define SHOW_HOVER_INFO \
if (ImGui::IsItemHovered()) { \
  if (ImGui::BeginTooltip()) { \
    DivSystem chip=e->song.system[i]; \
    const DivSysDef* sysDef=e->getSystemDef(chip); \
    ImGui::PushTextWrapPos(MIN(scrW*dpiScale,400.0f*dpiScale)); \
    ImGui::Text("%s",_L(sysDef->description)); \
    int num_chans[DIV_CH_MAX + 1] = { 0 }; \
    for(int ch = 0; ch < e->getChannelCount(chip); ch++) \
    { \
      if(sysDef->chanTypes[ch] == (int)DIV_CH_OP) \
      { \
        num_chans[DIV_CH_FM]++; \
      } \
      else \
      { \
        num_chans[sysDef->chanTypes[ch]]++; \
      } \
    } \
    String chan_number_info; \
    for(int ch = 0; ch < (int)DIV_CH_MAX; ch++) \
    { \
      if(num_chans[ch] > 0 && ch != DIV_CH_OP) \
      { \
        chan_number_info += fmt::sprintf((ch == (int)DIV_CH_MAX - 1) ? "%d×%s" : "%d×%s, ", num_chans[ch], chan_type_names[ch]); \
      } \
    } \
    if(chan_number_info[chan_number_info.length() - 1] == ' ') \
    { \
      chan_number_info.pop_back(); \
      chan_number_info.pop_back(); \
    } \
    ImGui::Text("\n%s",chan_number_info.c_str()); \
    ImGui::PopTextWrapPos(); \
    ImGui::EndTooltip(); \
  } \
} \

void FurnaceGUI::drawSysManager() {
  if (nextWindow==GUI_WINDOW_SYS_MANAGER) {
    sysManagerOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!sysManagerOpen) return;
  if (mobileUI) {
    patWindowPos=(portrait?ImVec2(0.0f,(mobileMenuPos*-0.65*canvasH)):ImVec2((0.16*canvasH)+0.5*canvasW*mobileMenuPos,0.0f));
    patWindowSize=(portrait?ImVec2(canvasW,canvasH-(0.16*canvasW)):ImVec2(canvasW-(0.16*canvasH),canvasH));
    ImGui::SetNextWindowPos(patWindowPos);
    ImGui::SetNextWindowSize(patWindowSize);
  } else {
    //ImGui::SetNextWindowSizeConstraints(ImVec2(440.0f*dpiScale,400.0f*dpiScale),ImVec2(canvasW,canvasH));
  }
  if (ImGui::Begin("Chip Manager",&sysManagerOpen,globalWinFlags,_L("Chip Manager###Chip Manager"))) {
    ImGui::Checkbox(_L("Preserve channel order##sgsm"),&preserveChanPos);
    ImGui::SameLine();
    ImGui::Checkbox(_L("Clone channel data##sgsm"),&sysDupCloneChannels);
    //ImGui::SameLine();
    //russian is too long
    ImGui::Checkbox(_L("Clone at end##sgsm"),&sysDupEnd);
    if (ImGui::BeginTable("SystemList",3)) {
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
      ImGui::TableNextColumn();
      ImGui::TableNextColumn();
      ImGui::Text(_L("Name##sgsm"));
      ImGui::TableNextColumn();
      ImGui::Text(_L("Actions##sgsm"));
      for (unsigned char i=0; i<e->song.systemLen; i++) {
        ImGui::PushID(i);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::Button(ICON_FA_ARROWS)) {
        }
        if (ImGui::BeginDragDropSource()) {
          sysToMove=i;
          ImGui::SetDragDropPayload("FUR_SYS",NULL,0,ImGuiCond_Once);
          ImGui::Button(ICON_FA_ARROWS "##SysDrag");
          ImGui::EndDragDropSource();
        } else if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("(drag to swap chips)##sgsm"));
        }
        if (ImGui::BeginDragDropTarget()) {
          const ImGuiPayload* dragItem=ImGui::AcceptDragDropPayload("FUR_SYS");
          if (dragItem!=NULL) {
            if (dragItem->IsDataType("FUR_SYS")) {
              if (sysToMove!=i && sysToMove>=0) {
                e->swapSystem(sysToMove,i,preserveChanPos);
                MARK_MODIFIED;
              }
              sysToMove=-1;
            }
          }
          ImGui::EndDragDropTarget();
        }
        ImGui::TableNextColumn();
        bool collapsed = true;
        if (ImGui::TreeNode(fmt::sprintf("%d. %s##_SYSM%d",i+1,_L(getSystemName(e->song.system[i])),i).c_str())) {
          drawSysConf(i,i,e->song.system[i],e->song.systemFlags[i],true);
          ImGui::TreePop();
          collapsed = false;
        }
        if(settings.showTooltipInChipManager && collapsed)
        {
          SHOW_HOVER_INFO
        }

        ImGui::TableNextColumn();
        ImGui::Button(_L("Change##SysChange"));
        if (ImGui::BeginPopupContextItem("SysPickerC",ImGuiPopupFlags_MouseButtonLeft)) {
          DivSystem picked=systemPicker(false);
          if (picked!=DIV_SYSTEM_NULL) {
            if (e->changeSystem(i,picked,preserveChanPos)) {
              MARK_MODIFIED;
              if (e->song.autoSystem) {
                autoDetectSystem();
              }
              updateWindowTitle();
            } else {
              showError((settings.language == DIV_LANG_ENGLISH ? "cannot remove chip! (" : _L("cannot change chip! (##sggu"))+e->getLastError()+")");
            }
            updateWindowTitle();
            ImGui::CloseCurrentPopup();
          }
          ImGui::EndPopup();
        }
        ImGui::SameLine();
        if(ImGui::Button(_L("Clone##SysDup")))
        {
          if(i == e->song.systemLen - 1) //a simple case: we just copy to the end
          {
            if (!e->cloneSystem(i, true, sysDupCloneChannels)) {
              showError(settings.language == DIV_LANG_ENGLISH ? ("cannot duplicate chip! (") : (_L("cannot duplicate chip! (##sgsm"))+e->getLastError()+")");
            } else {
              MARK_MODIFIED;
            }
            if (e->song.autoSystem) {
              autoDetectSystem();
            }
          }
          else if(e->song.systemLen < DIV_MAX_CHIPS && e->getTotalChannelCount()+e->getChannelCount(e->song.system[i]) <= DIV_MAX_CHANS) //we duplicate the chip that is in the middle or at the beginning of the list. We move all the other chips downward one step
          { //but we do it only if a new chip would fit
            for(int j = e->song.systemLen - 1; j > i; j--)
            {
              if (!e->cloneSystem(j, false, sysDupCloneChannels)) {
                //showError(settings.language == DIV_LANG_ENGLISH ? ("cannot duplicate chip! (") : (_L("cannot duplicate chip! (##sgsm"))+e->getLastError()+")");
              } else {
                MARK_MODIFIED;
              }
            }

            if (!e->cloneSystem(i, true, sysDupCloneChannels)) {
              showError(settings.language == DIV_LANG_ENGLISH ? ("cannot duplicate chip! (") : (_L("cannot duplicate chip! (##sgsm"))+e->getLastError()+")");
            } else {
              MARK_MODIFIED;
            }

            if (e->song.autoSystem) {
              autoDetectSystem();
            }
          }
          else
          {
            if(e->song.systemLen == DIV_MAX_CHIPS)
            {
              showError(fmt::sprintf(settings.language == DIV_LANG_ENGLISH ? "max number of systems is %d" : _L("max number of systems is %d##sgsm"), DIV_MAX_CHIPS));
            }

            if(e->getTotalChannelCount()+e->getChannelCount(e->song.system[i]) >= DIV_MAX_CHANS)
            {
              showError(fmt::sprintf(settings.language == DIV_LANG_ENGLISH ? "max number of total channels is %d" : _L("max number of total channels is %d##sgsm"), DIV_MAX_CHANS));
            }
          }
          
          updateWindowTitle();
        }
        ImGui::SameLine();
        ImGui::BeginDisabled(e->song.systemLen<=1);
        pushDestColor();
        if (ImGui::Button(ICON_FA_TIMES "##SysRemove")) {
          sysToDelete=i;
          showWarning(settings.language == DIV_LANG_ENGLISH ? "Are you sure you want to remove this chip?" : _L("Are you sure you want to remove this chip?##sgsm"),GUI_WARN_SYSTEM_DEL);
        }
        popDestColor();
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("Remove##sgsm"));
        }
        ImGui::EndDisabled();
        ImGui::PopID();
      }
      if (e->song.systemLen<DIV_MAX_CHIPS) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::Button(ICON_FA_PLUS "##SysAdd");
        if (ImGui::BeginPopupContextItem("SysPickerA",ImGuiPopupFlags_MouseButtonLeft)) {
          DivSystem picked=systemPicker(false);
          if (picked!=DIV_SYSTEM_NULL) {
            if (!e->addSystem(picked)) {
              showError(settings.language == DIV_LANG_ENGLISH ? ("cannot add chip! (") : (_L("cannot add chip! (##sgsm"))+e->getLastError()+")");
            } else {
              MARK_MODIFIED;
            }
            if (e->song.autoSystem) {
              autoDetectSystem();
            }
            updateWindowTitle();
            ImGui::CloseCurrentPopup();
          }
          ImGui::EndPopup();
        }
      }
      ImGui::EndTable();
    }
  }
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_SYS_MANAGER;
  ImGui::End();
}
