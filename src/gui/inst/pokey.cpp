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

void FurnaceGUI::drawInsPOKEY(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("POKEY")) 
  {
    if(ImGui::Checkbox(_L("16-bit raw period macro##sgiPOKEY"),(bool*)&ins->pokey.raw_freq_macro_mode))
    {
      ins->std.get_macro(DIV_MACRO_EX1, true)->vZoom=-1;
      ins->std.get_macro(DIV_MACRO_EX1, true)->vScroll=-1;
    }
    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_L("Macros##sgiPOKEY"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiPOKEY"),ins,DIV_MACRO_VOL,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiPOKEY"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiPOKEY"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));

    macroList.push_back(FurnaceGUIMacroDesc("AUDCTL",ins,DIV_MACRO_DUTY,0xff,0,8,128,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,pokeyCtlBits));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgiPOKEY"),ins,DIV_MACRO_WAVE,0xff,0,7,64,uiColors[GUI_COLOR_MACRO_WAVE]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Raw Period##sgiPOKEY"),ins,DIV_MACRO_EX1,0xff,0,(ins->pokey.raw_freq_macro_mode ? 65535 : 255),256,uiColors[GUI_COLOR_MACRO_OTHER]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}