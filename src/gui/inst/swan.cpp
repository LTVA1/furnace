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

void FurnaceGUI::drawInsSWAN(DivInstrument* ins)
{
  if(!ins->amiga.useSample)
  {
    insTabWave(ins);
  }

  insTabSample(ins);

  if (ImGui::BeginTabItem(_("Macros##sgiSWAN"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_("Volume##sgiSWAN"),ins,DIV_MACRO_VOL,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio##sgiSWAN"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch##sgiSWAN"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));

    if(!ins->amiga.useSample)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_("Noise##sgiSWAN"),ins,DIV_MACRO_DUTY,0xff,0,8,64,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_("Waveform##sgiSWAN"),ins,DIV_MACRO_WAVE,0xff,0,WAVE_MACRO_MAX,160,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,false,NULL,true));
    }

    macroList.push_back(FurnaceGUIMacroDesc(_("Phase Reset##sgiSWAN"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}