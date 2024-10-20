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

void FurnaceGUI::drawInsC64(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("C64")) 
  {
    ImGui::AlignTextToFramePadding();
    ImGui::Text(_("Waveform##sgiC640"));
    ImGui::SameLine();
    pushToggleColors(ins->c64.triOn);
    if (ImGui::Button(_("tri##sgiC64"))) 
    { PARAMETER
      ins->c64.triOn=!ins->c64.triOn;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.sawOn);
    if (ImGui::Button(_("saw##sgiC64"))) 
    { PARAMETER
      ins->c64.sawOn=!ins->c64.sawOn;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.pulseOn);
    if (ImGui::Button(_("pulse##sgiC64"))) 
    { PARAMETER
      ins->c64.pulseOn=!ins->c64.pulseOn;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.noiseOn);
    if (ImGui::Button(_("noise##sgiC64"))) 
    { PARAMETER
      ins->c64.noiseOn=!ins->c64.noiseOn;
    }
    popToggleColors();

    ImVec2 sliderSize=ImVec2(20.0f*dpiScale,128.0*dpiScale);

    if (ImGui::BeginTable("C64EnvParams",5,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      CENTER_TEXT(_("A##sgiC640"));
      ImGui::TextUnformatted(_("A##sgiC641"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("D##sgiC640"));
      ImGui::TextUnformatted(_("D##sgiC641"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("S##sgiC640"));
      ImGui::TextUnformatted(_("S##sgiC641"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("R##sgiC640"));
      ImGui::TextUnformatted(_("R##sgiC641"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("Envelope##sgiC640"));
      ImGui::TextUnformatted(_("Envelope##sgiC641"));

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Attack",sliderSize,ImGuiDataType_U8,&ins->c64.a,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay",sliderSize,ImGuiDataType_U8,&ins->c64.d,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Sustain",sliderSize,ImGuiDataType_U8,&ins->c64.s,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Release",sliderSize,ImGuiDataType_U8,&ins->c64.r,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      drawFMEnv(0,16-ins->c64.a,16-ins->c64.d,15-(ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r),15-(ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r),15-ins->c64.s,0,0,0,15,16,15,ImVec2(ImGui::GetContentRegionAvail().x,sliderSize.y),ins->type); //the (ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r) is used so release part never becomes horizontal (which isn't the case with SID envelope)

      ImGui::EndTable();
    }

    P(CWSliderScalar(_("Duty##sgiC640"),ImGuiDataType_U16,&ins->c64.duty,&_ZERO,&_FOUR_THOUSAND_NINETY_FIVE)); rightClickable
    bool resetDuty=ins->c64.resetDuty;
    if (ImGui::Checkbox(_("Reset duty on new note##sgiC64"),&resetDuty)) 
    { PARAMETER
      ins->c64.resetDuty=resetDuty;
    }

    bool ringMod=ins->c64.ringMod;
    if (ImGui::Checkbox(_("Ring Modulation##sgiC64"),&ringMod)) 
    { PARAMETER
      ins->c64.ringMod=ringMod;
    }
    bool oscSync=ins->c64.oscSync;
    if (ImGui::Checkbox(_("Oscillator Sync##sgiC64"),&oscSync)) 
    { PARAMETER
      ins->c64.oscSync=oscSync;
    }

    P(ImGui::Checkbox(_("Enable filter##sgiC64"),&ins->c64.toFilter));
    P(ImGui::Checkbox(_("Initialize filter##sgiC64"),&ins->c64.initFilter));
    
    P(CWSliderScalar(_("Cutoff##sgiC640"),ImGuiDataType_U16,&ins->c64.cut,&_ZERO,&_TWO_THOUSAND_FORTY_SEVEN)); rightClickable
    P(CWSliderScalar(_("Resonance##sgiC640"),ImGuiDataType_U8,&ins->c64.res,&_ZERO,&_FIFTEEN)); rightClickable

    ImGui::AlignTextToFramePadding();
    ImGui::Text(_("Filter Mode##sgiC640"));
    ImGui::SameLine();
    pushToggleColors(ins->c64.lp);
    if (ImGui::Button(_("low##sgiC64"))) 
    { PARAMETER
      ins->c64.lp=!ins->c64.lp;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.bp);
    if (ImGui::Button(_("band##sgiC64"))) 
    { PARAMETER
      ins->c64.bp=!ins->c64.bp;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.hp);
    if (ImGui::Button(_("high##sgiC64"))) 
    { PARAMETER
      ins->c64.hp=!ins->c64.hp;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.ch3off);
    if (ImGui::Button(_("ch3off##sgiC64"))) 
    { PARAMETER
      ins->c64.ch3off=!ins->c64.ch3off;
    }
    popToggleColors();

    if (ImGui::Checkbox(_("Absolute Cutoff Macro##sgiC64"),&ins->c64.filterIsAbs)) 
    {
      ins->std.get_macro(DIV_MACRO_ALG, true)->vZoom=-1;
      PARAMETER;
    }
    if (ImGui::Checkbox(_("Absolute Duty Macro##sgiC64"),&ins->c64.dutyIsAbs)) 
    {
      ins->std.get_macro(DIV_MACRO_DUTY, true)->vZoom=-1;
      PARAMETER;
    }
    P(ImGui::Checkbox(_("Don't test before new note##sgiC64"),&ins->c64.noTest));
    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_("Macros##sgiC64"))) 
  {
    int dutyMin = 0;
    int dutyMax = 0;

    if (ins->c64.dutyIsAbs)
    {
      dutyMin=0;
      dutyMax=4095;
    }

    else 
    {
      dutyMin=-4095;
      dutyMax=4095;
    }

    int cutoffMin=-2047;
    int cutoffMax=2047;

    if (ins->c64.filterIsAbs) 
    {
      cutoffMin=0;
    }

    macroList.push_back(FurnaceGUIMacroDesc(_("Volume##sgiC64"),ins,DIV_MACRO_VOL,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio##sgiC64"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch##sgiC64"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_("Duty##sgiC641"),ins,DIV_MACRO_DUTY,0xff,dutyMin,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Waveform##sgiC641"),ins,DIV_MACRO_WAVE,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,true,c64ShapeBits,0));

    macroList.push_back(FurnaceGUIMacroDesc(_("Cutoff##sgiC641"),ins,DIV_MACRO_ALG,0xff,cutoffMin,cutoffMax,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Filter Mode##sgiC641"),ins,DIV_MACRO_EX1,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,filtModeBits));
    macroList.push_back(FurnaceGUIMacroDesc(_("Filter Toggle##sgiC64"),ins,DIV_MACRO_EX3,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Resonance##sgiC641"),ins,DIV_MACRO_EX2,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Special##sgiC64"),ins,DIV_MACRO_EX4,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,c64TestGateBits));
    macroList.push_back(FurnaceGUIMacroDesc(_("Attack##sgiC64"),ins,DIV_MACRO_EX5, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Decay##sgiC64"),ins,DIV_MACRO_EX6, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Sustain##sgiC64"),ins,DIV_MACRO_EX7, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Release##sgiC64"),ins,DIV_MACRO_EX8, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}