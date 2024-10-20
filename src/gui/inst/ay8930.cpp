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

void FurnaceGUI::drawInsAY8930(DivInstrument* ins)
{
  insTabSample(ins);

  if (ImGui::BeginTabItem(_("Macros##sgi8930"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_("Volume##sgi8930"),ins,DIV_MACRO_VOL,0xff,0,31,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio##sgi8930"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch##sgi8930"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));

    if(!ins->amiga.useSample)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_("Noise Freq##sgi8930"),ins,DIV_MACRO_DUTY,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_("Waveform##sgi8930"),ins,DIV_MACRO_WAVE,0xff,0,3,64,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,true,ayShapeBits));
    }

    macroList.push_back(FurnaceGUIMacroDesc(_("Raw Period##sgi8930"),ins,DIV_MACRO_EX4,0xff,0,0xffff,256,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Raw Envelope Period##sgi8930"),ins,DIV_MACRO_EX5,0xff,0,0xffff,256,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Phase Reset##sgi8930"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_("Duty##sgi8930"),ins,DIV_MACRO_EX1,0xff,0,8,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Envelope##sgi8930"),ins,DIV_MACRO_EX2,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,ayEnvBits));

    macroList.push_back(FurnaceGUIMacroDesc(_("AutoEnv Num##sgi8930"),ins,DIV_MACRO_EX3, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("AutoEnv Den##sgi8930"),ins,DIV_MACRO_ALG,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Noise AND Mask##sgi8930"),ins,DIV_MACRO_FB, 0xff,0,8,96,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Noise OR Mask##sgi8930"),ins,DIV_MACRO_FMS, 0xff,0,8,96,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}