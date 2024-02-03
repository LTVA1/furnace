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

void FurnaceGUI::drawInsDAVE(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("DAVE")) 
  {
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(_L("Waveform##sgidave")).x);
    P(CWSliderScalar(_L("Waveform##sgidave"),ImGuiDataType_U8,&ins->dave.mode,&_ZERO,&_FOUR,_L(daveWaves[ins->dave.mode%5])));
    
    ImGui::Checkbox(_L("Highpass filter##sgidave"), &ins->dave.highpass);
    ImGui::Checkbox(_L("Ring modulation##sgidave"), &ins->dave.ring_mod);
    ImGui::Checkbox(_L("Phase reset on new note##sgidave"), &ins->dave.phase_reset_on_start);
    ImGui::Checkbox(_L("Absolute raw frequency macro##sgidave"), &ins->dave.raw_freq_is_abs);
    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_L("Macros##sgidave"))) 
  {
    panMin=0;
    panMax=63;

    int raw_freq_min = -4095;
    int raw_freq_max = 4095;

    if(ins->dave.raw_freq_is_abs)
    {
      raw_freq_min = 0;
    }

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgidave"),ins,DIV_MACRO_VOL,0xff,0,63,96,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgidave"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,0,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgidave"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgidave"),ins,DIV_MACRO_WAVE,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgidave"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgidave"),ins,DIV_MACRO_PAN_RIGHT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgidave"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Special##sgidave"),ins,DIV_MACRO_DUTY,0xff,0,2,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,daveBits));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Raw Frequency##sgidave"),ins,DIV_MACRO_EX1,0xff,raw_freq_min,raw_freq_max,256,uiColors[GUI_COLOR_MACRO_OTHER]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}