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

#include "fmEnvUtil.h"
#include "stringsUtil.h"
#include "macroDraw.h"
#include "fmPublicVars.h"
#include "publicVars.h"
#include "fm.h"
#include "../intConst.h"

class FurnaceGUI;

void FurnaceGUI::drawInsES5506(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("ES5506")) 
  {
    if (ImGui::BeginTable("ESParams",2,ImGuiTableFlags_SizingStretchSame)) 
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.0);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.0);
      // filter
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Filter Mode##sgiOTTO0"),ImGuiDataType_U8,&ins->es5506.filter.mode,&_ZERO,&_THREE,_L(es5506FilterModes[ins->es5506.filter.mode&3])));
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Filter K1##sgiOTTO0"),ImGuiDataType_U16,&ins->es5506.filter.k1,&_ZERO,&_SIXTY_FIVE_THOUSAND_FIVE_HUNDRED_THIRTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Filter K2##sgiOTTO0"),ImGuiDataType_U16,&ins->es5506.filter.k2,&_ZERO,&_SIXTY_FIVE_THOUSAND_FIVE_HUNDRED_THIRTY_FIVE)); rightClickable
      // envelope
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Envelope length##sgiOTTO"),ImGuiDataType_U16,&ins->es5506.envelope.ecount,&_ZERO,&_FIVE_HUNDRED_ELEVEN)); rightClickable
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Left Volume Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.lVRamp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Right Volume Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.rVRamp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Filter K1 Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.k1Ramp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("Filter K2 Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.k2Ramp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Checkbox(_L("K1 Ramp Slowdown##sgiOTTO"),&ins->es5506.envelope.k1Slow);
      ImGui::TableNextColumn();
      ImGui::Checkbox(_L("K2 Ramp Slowdown##sgiOTTO"),&ins->es5506.envelope.k2Slow);
      ImGui::EndTable();
    }

    ImGui::EndTabItem();
  }

  insTabSample(ins);

  if (ImGui::BeginTabItem(_L("Macros##sgiOTTO"))) 
  {
    panMin=0;
    panMax=4095;

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiOTTO"),ins,DIV_MACRO_VOL,0xff,0,4095,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiOTTO"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiOTTO"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgiOTTO"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgiOTTO"),ins,DIV_MACRO_PAN_RIGHT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgiOTTO"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter Mode##sgiOTTO1"),ins,DIV_MACRO_DUTY,0xff,0,3,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,&macroHoverES5506FilterMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter K1##sgiOTTO1"),ins,DIV_MACRO_EX1,0xff,((ins->std.get_macro(DIV_MACRO_EX1, true)->mode==1)?(-65535):0),65535,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter K2##sgiOTTO1"),ins,DIV_MACRO_EX2,0xff,((ins->std.get_macro(DIV_MACRO_EX2, true)->mode==1)?(-65535):0),65535,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Outputs##sgiOTTO"),ins,DIV_MACRO_FB, 0xff,0,5,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Control##sgiOTTO"),ins,DIV_MACRO_ALG,0xff,0,2,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,es5506ControlModes));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}