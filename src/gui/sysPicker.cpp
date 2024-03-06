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
#include "guiConst.h"
#include <imgui.h>

#define RESTRICT_CHIP_SHOW_BEGIN if(
#define RESTRICT_CHIP_SHOW_SYSTEM(sys) curSysSection[j] != (sys) &&
#define RESTRICT_CHIP_SHOW_HEADER_END(sys) curSysSection[j] != (sys)) \
{

#define RESTRICT_CHIP_SHOW_END \
}

#define FIRST_SYSTEM_COLLAPSIBLE_BEGIN(sys) \
if((DivSystem)curSysSection[j] == (sys)) \
{ \
  if (ImGui::TreeNode(_L(e->getSystemName((DivSystem)curSysSection[j])))) {

#define SYSTEM_COLLAPSIBLE_BEGIN(sys) \
else if((DivSystem)curSysSection[j] == (sys)) \
{ \
  if (ImGui::TreeNode(_L(e->getSystemName((DivSystem)curSysSection[j])))) {


#define SYSTEM_IN_COLLAPSIBLE(sys) \
    if (ImGui::Selectable(_L(e->getSystemName(sys)),false,0,ImVec2(500.0f*dpiScale,0.0f))) ret=(sys); \
    if (ImGui::IsItemHovered()) { \
      hoveredSys=(sys); \
    } 

#define SYSTEM_COLLAPSIBLE_END(sys) \
    ImGui::TreePop(); \
  } \
  if (ImGui::IsItemHovered() && hoveredSys != (sys)) { \
    hoveredSys=(DivSystem)curSysSection[j]; \
  } \
} 

DivSystem FurnaceGUI::systemPicker(bool full_width) {
  DivSystem ret=DIV_SYSTEM_NULL;
  DivSystem hoveredSys=DIV_SYSTEM_NULL;
  bool reissueSearch=false;
  if (curSysSection==NULL) {
    curSysSection=availableSystems;
  }

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  if (ImGui::InputTextWithHint("##SysSearch",settings.language == DIV_LANG_ENGLISH ? "Search..." : _L("Search...##sgsp"),&sysSearchQuery)) reissueSearch=true;
  if (ImGui::BeginTabBar("SysCats")) {
    for (int i=0; chipCategories[i]; i++) {
      if (ImGui::BeginTabItem(_L(chipCategoryNames[i]))) {
        if (ImGui::IsItemActive()) {
          reissueSearch=true;
        }
        curSysSection=chipCategories[i];
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }
  if (reissueSearch) {
    String lowerCase=sysSearchQuery;
    for (char& i: lowerCase) {
      if (i>='A' && i<='Z') i+='a'-'A';
    }

    sysSearchResults.clear();
    for (int j=0; curSysSection[j]; j++) {
      String lowerCase1=_L(e->getSystemName((DivSystem)curSysSection[j]));
      for (char& i: lowerCase1) {
        if (i>='A' && i<='Z') i+='a'-'A';
      }

      if (lowerCase1.find(lowerCase)!=String::npos) {
        sysSearchResults.push_back((DivSystem)curSysSection[j]);
      }
    }
  }

  float real_full_width = ImGui::GetContentRegionAvail().x;

  if (ImGui::BeginTable("SysList",1,ImGuiTableFlags_ScrollY,ImVec2(full_width ? ImGui::GetContentRegionAvail().x : 500.0f*dpiScale,200.0f*dpiScale))) {
    if (sysSearchQuery.empty()) {
      // display chip list
      
      for (int j=0; curSysSection[j]; j++) {
        RESTRICT_CHIP_SHOW_BEGIN
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2612_EXT) //which chips are not shown in "All chips" tab
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2612_DUALPCM) //a hack to still show them in search results
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2612_CSM)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2612_DUALPCM)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2612_DUALPCM_EXT)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2610_EXT)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2610_FULL)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2610_FULL_EXT)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2610_CSM)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2610B_EXT)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2610B_CSM)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2203_EXT)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2203_CSM)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2608_EXT)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_YM2608_CSM)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_OPLL_DRUMS)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_OPL_DRUMS)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_OPL2_DRUMS)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_OPL3_DRUMS)
        RESTRICT_CHIP_SHOW_SYSTEM(DIV_SYSTEM_Y8950_DRUMS)
        RESTRICT_CHIP_SHOW_HEADER_END(DIV_SYSTEM_Y8950_DRUMS)

          ImGui::TableNextRow();
          ImGui::TableNextColumn();

          FIRST_SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_YM2612);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2612);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2612_EXT);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2612_CSM);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2612_DUALPCM);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2612_DUALPCM_EXT);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_YM2612_DUALPCM_EXT)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_YM2610);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610_EXT);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610_FULL);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610_FULL_EXT);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610_CSM);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_YM2610_CSM)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_YM2610B);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610B);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610B_EXT);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2610B_CSM);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_YM2610B_CSM)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_YM2203);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2203);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2203_EXT);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2203_CSM);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_YM2203_CSM)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_YM2608);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2608);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2608_EXT);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_YM2608_CSM);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_YM2608_CSM)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_OPLL);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPLL);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPLL_DRUMS);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_OPLL_DRUMS)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_OPL);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPL);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPL_DRUMS);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_OPL_DRUMS)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_OPL2);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPL2);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPL2_DRUMS);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_OPL2_DRUMS)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_OPL3);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPL3);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_OPL3_DRUMS);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_OPL3_DRUMS)

          SYSTEM_COLLAPSIBLE_BEGIN(DIV_SYSTEM_Y8950);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_Y8950);
          SYSTEM_IN_COLLAPSIBLE(DIV_SYSTEM_Y8950_DRUMS);
          SYSTEM_COLLAPSIBLE_END(DIV_SYSTEM_Y8950_DRUMS)

          else
          {
            if (ImGui::Selectable(_L(e->getSystemName((DivSystem)curSysSection[j])),false,0,ImVec2(full_width ? real_full_width : 500.0f*dpiScale,0.0f))) ret=(DivSystem)curSysSection[j];
            if (ImGui::IsItemHovered()) {
              hoveredSys=(DivSystem)curSysSection[j];
            }
          }

        RESTRICT_CHIP_SHOW_END
      }
    } else {
      // display search results
      for (DivSystem i: sysSearchResults) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::Selectable(_L(e->getSystemName(i)),false,0,ImVec2(full_width ? real_full_width : 500.0f*dpiScale,0.0f))) ret=i;
        if (ImGui::IsItemHovered()) {
          hoveredSys=i;
        }
      }
    }
    ImGui::EndTable();
  }
  ImGui::Separator();
  if (ImGui::BeginChild("SysDesc",ImVec2(0.0f,150.0f*dpiScale),false,ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse)) {
    if (hoveredSys!=DIV_SYSTEM_NULL) {
      const DivSysDef* sysDef=e->getSystemDef(hoveredSys);
      ImGui::TextWrapped("%s",_L(sysDef->description));
    }
  }
  ImGui::EndChild();
  return ret;
}