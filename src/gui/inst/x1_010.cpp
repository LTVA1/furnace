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

void FurnaceGUI::drawInsX1_010(DivInstrument* ins)
{
  if(!ins->amiga.useSample)
  {
    insTabWave(ins);
  }
  
  insTabSample(ins);

  if (ImGui::BeginTabItem(_L("Macros##sgiX1"))) 
  {
    panMax=15;

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiX1"),ins,DIV_MACRO_VOL,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiX1"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiX1"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgiX1"),ins,DIV_MACRO_WAVE,0xff,0,WAVE_MACRO_MAX,160,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,false,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgiX1"),ins,DIV_MACRO_PAN_LEFT,0xff,0,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,NULL));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgiX1"),ins,DIV_MACRO_PAN_RIGHT,0xff,0,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));

    if(ins->amiga.useSample)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgiX1"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    }

    if(!ins->amiga.useSample)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_L("Envelope##sgiX1"),ins,DIV_MACRO_EX2,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_L("Envelope Mode##sgiX1"),ins,DIV_MACRO_EX1,0xff,0,7,128,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,x1_010EnvBits));
      macroList.push_back(FurnaceGUIMacroDesc(_L("AutoEnv Num##sgiX1"),ins,DIV_MACRO_EX3,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_L("AutoEnv Den##sgiX1"),ins,DIV_MACRO_ALG,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    }

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}