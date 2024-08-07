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

#include "../../engine/platform/fzt.h"

class FurnaceGUI;

const unsigned short fzt_commands_map[] = 
{
  DivInstrumentFZT::TE_EFFECT_ARPEGGIO,
  DivInstrumentFZT::TE_EFFECT_PORTAMENTO_UP,
  DivInstrumentFZT::TE_EFFECT_PORTAMENTO_DOWN,
  DivInstrumentFZT::TE_EFFECT_VIBRATO,
  DivInstrumentFZT::TE_EFFECT_PWM,
  DivInstrumentFZT::TE_EFFECT_SET_PW,
  DivInstrumentFZT::TE_EFFECT_PW_DOWN,
  DivInstrumentFZT::TE_EFFECT_PW_UP,
  DivInstrumentFZT::TE_EFFECT_SET_CUTOFF,
  DivInstrumentFZT::TE_EFFECT_VOLUME_FADE,
  DivInstrumentFZT::TE_EFFECT_SET_WAVEFORM,
  DivInstrumentFZT::TE_EFFECT_SET_VOLUME,

  DivInstrumentFZT::TE_EFFECT_EXT_TOGGLE_FILTER,
  DivInstrumentFZT::TE_EFFECT_EXT_PORTA_UP,
  DivInstrumentFZT::TE_EFFECT_EXT_PORTA_DN,
  DivInstrumentFZT::TE_EFFECT_EXT_FILTER_MODE,
  //TE_EFFECT_EXT_PATTERN_LOOP = 0x0e60, // e60 = start, e61-e6f = end and indication how many loops you want
  //is not supported in Furnace yet
  DivInstrumentFZT::TE_EFFECT_EXT_RETRIGGER,
  DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_DOWN,
  DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_UP,
  DivInstrumentFZT::TE_EFFECT_EXT_NOTE_CUT,
  DivInstrumentFZT::TE_EFFECT_EXT_PHASE_RESET,

  DivInstrumentFZT::TE_EFFECT_SET_SPEED_PROG_PERIOD,
  DivInstrumentFZT::TE_EFFECT_CUTOFF_UP, // Gxx
  DivInstrumentFZT::TE_EFFECT_CUTOFF_DOWN, // Hxx
  DivInstrumentFZT::TE_EFFECT_SET_RESONANCE, // Ixx
  DivInstrumentFZT::TE_EFFECT_RESONANCE_UP, // Jxx
  DivInstrumentFZT::TE_EFFECT_RESONANCE_DOWN, // Kxx

  DivInstrumentFZT::TE_EFFECT_SET_ATTACK, // Lxx
  DivInstrumentFZT::TE_EFFECT_SET_DECAY, // Mxx
  DivInstrumentFZT::TE_EFFECT_SET_SUSTAIN, // Nxx
  DivInstrumentFZT::TE_EFFECT_SET_RELEASE, // Oxx

  DivInstrumentFZT::TE_EFFECT_SET_RING_MOD_SRC, // Rxx
  DivInstrumentFZT::TE_EFFECT_SET_HARD_SYNC_SRC, // Sxx

  DivInstrumentFZT::TE_EFFECT_PORTA_UP_SEMITONE, // Txx
  DivInstrumentFZT::TE_EFFECT_PORTA_DOWN_SEMITONE, // Uxx
  DivInstrumentFZT::TE_EFFECT_PITCH, //Vxx
  /*
  TE_EFFECT_ = 0x2000, //Wxx
  */
  DivInstrumentFZT::TE_EFFECT_ARPEGGIO_ABS, // Yxx
  DivInstrumentFZT::TE_EFFECT_TRIGGER_RELEASE, // Zxx

  /* These effects work only in instrument program */
  DivInstrumentFZT::TE_PROGRAM_LOOP_BEGIN,
  DivInstrumentFZT::TE_PROGRAM_LOOP_END,
  DivInstrumentFZT::TE_PROGRAM_JUMP,
  DivInstrumentFZT::TE_PROGRAM_NOP,
  DivInstrumentFZT::TE_PROGRAM_END,
  0xffff,
};

void FurnaceGUI::drawInsFZT(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("FZT")) 
  {
    if (ImGui::BeginTable("FZTnote",2,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 120.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 98.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text(_("Base note"));
      ImGui::SameLine();
      char tempID[10];
      snprintf(tempID,10,"%s",noteNames[ins->fzt.base_note + 60]);
      ImGui::PushItemWidth(60.0f*dpiScale);
      if (ImGui::BeginCombo("##NN1",tempID)) 
      {
        for (int j=0; j<=MAX_NOTE; j++) 
        {
          snprintf(tempID,10,"%s",noteNames[j + 60]);
          if (ImGui::Selectable(tempID,ins->fzt.base_note==j))
          {
            ins->fzt.base_note=j;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(40.0f*dpiScale);
      ImGui::InputScalar(_("Finetune"),ImGuiDataType_S8,&ins->fzt.finetune,NULL,NULL,"%d");
      ImGui::PopItemWidth();
      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZTslide",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 100.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 45.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 90.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Slide speed"),ImGuiDataType_U8,&ins->fzt.slide_speed,NULL,NULL,"%02X");
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      bool fztSetPw = ins->fzt.flags & TE_SET_PW;
      if (ImGui::Checkbox(_("Set PW"),&fztSetPw)) 
      {
        ins->fzt.flags ^= TE_SET_PW;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Set pulse width on keydown"));
      }
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar("",ImGuiDataType_U8,&ins->fzt.pw,NULL,NULL,"%02X");
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Initial pulse width"));
      }
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      bool fztSetCut = ins->fzt.flags & TE_SET_CUTOFF;
      if (ImGui::Checkbox(_("Set cutoff"),&fztSetCut)) 
      {
        ins->fzt.flags ^= TE_SET_CUTOFF;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Set filter cutoff on keydown"));
      }
      ImGui::EndTable();
    }

    ImGui::AlignTextToFramePadding();
    ImGui::Text(_("Waveform"));
    ImGui::SameLine();
    bool fztNoise = ins->fzt.waveform & SE_WAVEFORM_NOISE;
    pushToggleColors(fztNoise);
    if (ImGui::Button(_("noise"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_NOISE;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztPulse = ins->fzt.waveform & SE_WAVEFORM_PULSE;
    pushToggleColors(fztPulse);
    if (ImGui::Button(_("pulse"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_PULSE;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztTri = ins->fzt.waveform & SE_WAVEFORM_TRIANGLE;
    pushToggleColors(fztTri);
    if (ImGui::Button(_("triangle"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_TRIANGLE;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztSaw = ins->fzt.waveform & SE_WAVEFORM_SAW;
    pushToggleColors(fztSaw);
    if (ImGui::Button(_("saw"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_SAW;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztMetal = ins->fzt.waveform & SE_WAVEFORM_NOISE_METAL;
    pushToggleColors(fztMetal);
    if (ImGui::Button(_("metal"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_NOISE_METAL;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztSine = ins->fzt.waveform & SE_WAVEFORM_SINE;
    pushToggleColors(fztSine);
    if (ImGui::Button(_("sine"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_SINE;
    }
    popToggleColors();

    if (ImGui::BeginTable("FZTfilt",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 100.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 120.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 220.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztSetPw = ins->fzt.sound_engine_flags & SE_ENABLE_FILTER;
      if (ImGui::Checkbox(_("Enable filter"),&fztSetPw)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_FILTER;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Cutoff"),ImGuiDataType_U8,&ins->fzt.filter_cutoff,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Resonance"),ImGuiDataType_U8,&ins->fzt.filter_resonance,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::Text(_("Type"));
      ImGui::SameLine();
      ImGui::PushItemWidth(140.0f*dpiScale);
      char tempID[40];
      snprintf(tempID,40,"%s",_L(fztFilterModes[ins->fzt.filter_type]));
      if (ImGui::BeginCombo("##NNN1",tempID)) 
      {
        for (int j=0; j<8; j++) 
        {
          snprintf(tempID,40,"%s",_L(fztFilterModes[j]));
          if (ImGui::Selectable(tempID,ins->fzt.filter_type==j))
          {
            ins->fzt.filter_type=j;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZThard",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 160.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 130.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 140.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 130.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztRing = ins->fzt.sound_engine_flags & SE_ENABLE_RING_MOD;
      if (ImGui::Checkbox(_("Enable ring modulation"),&fztRing)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_RING_MOD;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Ring mod source"),ImGuiDataType_U8,&ins->fzt.ring_mod,NULL,NULL,"%02X");
      ImGui::PopItemWidth();
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("FF = self-modulation"));
      }

      ImGui::TableNextColumn();

      bool fztSync = ins->fzt.sound_engine_flags & SE_ENABLE_HARD_SYNC;
      if (ImGui::Checkbox(_("Enable hard sync"),&fztSync)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_HARD_SYNC;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Hard sync source"),ImGuiDataType_U8,&ins->fzt.hard_sync,NULL,NULL,"%02X");
      ImGui::PopItemWidth();
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("FF = self-sync"));
      }

      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZTsli",2,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 160.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 160.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztSlRetrig = ins->fzt.flags & TE_RETRIGGER_ON_SLIDE;
      if (ImGui::Checkbox(_("Retrigger on slide"),&fztSlRetrig)) 
      {
        ins->fzt.flags ^= TE_RETRIGGER_ON_SLIDE;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Restart instrument and envelope even if slide command (03xx) is placed with the note."));
      }

      ImGui::TableNextColumn();

      bool fztKeySync = ins->fzt.sound_engine_flags & SE_ENABLE_KEYDOWN_SYNC;
      if (ImGui::Checkbox(_("Sync osc. on keydown"),&fztKeySync)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_KEYDOWN_SYNC;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Reset phase of oscillator each time new note is played.\nDoes not happen when slide (03xx) or legato command is placed."));
      }

      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZTvib",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztVib = ins->fzt.flags & TE_ENABLE_VIBRATO;
      if (ImGui::Checkbox(_("Vibrato"),&fztVib)) 
      {
        ins->fzt.flags ^= TE_ENABLE_VIBRATO;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Speed##spd0"),ImGuiDataType_U8,&ins->fzt.vibrato_speed,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Depth##dp0"),ImGuiDataType_U8,&ins->fzt.vibrato_depth,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Delay##del0"),ImGuiDataType_U8,&ins->fzt.vibrato_delay,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      bool fztPwm = ins->fzt.flags & TE_ENABLE_PWM;
      if (ImGui::Checkbox(_("PWM"),&fztPwm)) 
      {
        ins->fzt.flags ^= TE_ENABLE_PWM;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Speed##spd1"),ImGuiDataType_U8,&ins->fzt.pwm_speed,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Depth##dp1"),ImGuiDataType_U8,&ins->fzt.pwm_depth,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_("Delay##del1"),ImGuiDataType_U8,&ins->fzt.pwm_delay,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::EndTable();
    }

    ImVec2 sliderSize=ImVec2(30.0f*dpiScale,256.0*dpiScale);

    if (ImGui::BeginTable("FZTEnvParams",6,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c5",ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      CENTER_TEXT(_("A"));
      ImGui::TextUnformatted(_("A"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("D"));
      ImGui::TextUnformatted(_("D"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("S"));
      ImGui::TextUnformatted(_("S"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("R"));
      ImGui::TextUnformatted(_("R"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("VOL"));
      ImGui::TextUnformatted(_("VOL"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_("Envelope"));
      ImGui::TextUnformatted(_("Envelope"));

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Attack",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.a,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.d,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Sustain",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.s,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Release",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.r,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Volume",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.volume,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      drawFZTEnv(255-ins->fzt.adsr.volume,(ins->fzt.adsr.a == 0 ? (255) : (256-ins->fzt.adsr.a)),(ins->fzt.adsr.d == 0 ? (255) : (256-ins->fzt.adsr.d)),255-(ins->fzt.adsr.r == 255 ? (ins->fzt.adsr.r - 1) : ins->fzt.adsr.r),255-(ins->fzt.adsr.r == 255 ? (ins->fzt.adsr.r - 1) : ins->fzt.adsr.r),255-ins->fzt.adsr.s,0,0,0,255,256,255,ImVec2(ImGui::GetContentRegionAvail().x,sliderSize.y),ins->type); //the (ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r) is used so release part never becomes horizontal (which isn't the case with SID envelope)

      ImGui::EndTable();
    }

    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_("Instrument program"))) 
  {
    int prper = ins->fzt.program_period;
    ImGui::PushItemWidth(85.0f*dpiScale);
    if(ImGui::InputInt(_("Program period"), &prper))
    {
      if(prper < 1) prper = 1;
      if(prper > 0xff) prper = 0xff;
      ins->fzt.program_period = prper;
    }
    ImGui::PopItemWidth();
    bool fztRestart = ins->fzt.flags & TE_PROG_NO_RESTART;
    if (ImGui::Checkbox(_("Do not restart instrument program on keydown"),&fztRestart)) 
    {
      ins->fzt.flags ^= TE_PROG_NO_RESTART;
    }

    if (ImGui::BeginChild("HWSeqSU",ImGui::GetContentRegionAvail(),true,ImGuiWindowFlags_MenuBar)) 
    {
      ImGui::BeginMenuBar();
      ImGui::Text(_("Instrument program"));
      ImGui::EndMenuBar();

      if (ImGui::BeginTable("HWSeqListFZT",4)) 
      {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 40.0f*dpiScale);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 80.0f*dpiScale);
        ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 40.0f*dpiScale);

        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        ImGui::TableNextColumn();
        ImGui::Text(_("Tick"));
        ImGui::TableNextColumn();
        ImGui::Text(_("Command"));
        ImGui::TableNextColumn();
        ImGui::Text(_("Move/Remove"));
        ImGui::TableNextColumn();
        ImGui::Text(_("Unite"));

        int current_program_step = 0xffff;
        bool in_search = true;

        for(int i = 0; i < e->song.systemLen && in_search; i++)
        {
          if(e->song.system[i] == DIV_SYSTEM_FZT)
          {
            DivPlatformFZT* dispatch = (DivPlatformFZT*)e->getDispatch(i);

            for(int j = 0; j < FZT_NUM_CHANNELS && in_search; j++)
            {
              if(dispatch->chan[j].ins == curIns && ((dispatch->sound_engine->channel[j].flags & SE_ENABLE_GATE) || dispatch->sound_engine->channel[j].adsr.envelope > 0) && e->isRunning())
              {
                current_program_step = dispatch->fztChan[j].program_tick;
                in_search = false;
              }
            }
          }
        }

        for (int i=0; i<FZT_INST_PROG_LEN; i++) 
        {
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          char number[10];
          if(current_program_step == i)
          {
            snprintf(number, 10, "%01X%s",i," >");
          }
          else
          {
            snprintf(number, 10, "%01X",i);
          }
          ImGui::Text(number);
          ImGui::TableNextColumn();
          ImGui::PushID(i);
          if (ins->fzt.program[i].cmd>=DivInstrumentFZT::TE_PROGRAM_END 
            && ins->fzt.program[i].cmd != DivInstrumentFZT::TE_EFFECT_PITCH 
            && ins->fzt.program[i].cmd != DivInstrumentFZT::TE_EFFECT_EXT_PORTA_UP && ins->fzt.program[i].cmd != DivInstrumentFZT::TE_EFFECT_EXT_PORTA_DN
            && ins->fzt.program[i].cmd != DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_UP && ins->fzt.program[i].cmd != DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_DOWN)
          {
            ins->fzt.program[i].cmd=DivInstrumentFZT::TE_PROGRAM_END;
          }
          int cmd=0;
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          while(fzt_commands_map[cmd] != 0xffff)
          {
            if(fzt_commands_map[cmd] == (ins->fzt.program[i].cmd & 0xff00))
            {
              if(fzt_commands_map[cmd] == DivInstrumentFZT::TE_PROGRAM_JUMP)
              {
                if(ins->fzt.program[i].cmd == DivInstrumentFZT::TE_PROGRAM_NOP)
                {
                  cmd = 41;
                  break;
                }
                if(ins->fzt.program[i].cmd == DivInstrumentFZT::TE_PROGRAM_END)
                {
                  cmd = 42;
                  break;
                }
              }
              break;
            }
            cmd++;
          }
          if (ImGui::BeginCombo("##HWSeqCmd",_L(fztCmdTypes[cmd]),ImGuiComboFlags_HeightLarge))
          {
            int j = 0;

            while(fztCmdTypes[j])
            {
              if (ImGui::Selectable(_L(fztCmdTypes[j]), j == cmd))
              {
                if (ins->fzt.program[i].cmd!=fzt_commands_map[j]) 
                {
                  ins->fzt.program[i].cmd=fzt_commands_map[j];
                  ins->fzt.program[i].val=0;

                  if(ins->fzt.program[i].cmd >= 41)
                  {
                    ins->fzt.program[i].unite=false;
                  }
                }
              }

              j++;
            }

            ImGui::EndCombo();
          }


          switch (ins->fzt.program[i].cmd) 
          {
            case DivInstrumentFZT::TE_EFFECT_PORTAMENTO_UP:
            case DivInstrumentFZT::TE_EFFECT_PORTAMENTO_DOWN:
            case DivInstrumentFZT::TE_EFFECT_SET_PW:
            case DivInstrumentFZT::TE_EFFECT_PW_DOWN:
            case DivInstrumentFZT::TE_EFFECT_PW_UP:
            case DivInstrumentFZT::TE_EFFECT_SET_CUTOFF:
            case DivInstrumentFZT::TE_EFFECT_SET_VOLUME:
            case DivInstrumentFZT::TE_EFFECT_SET_SPEED_PROG_PERIOD:
            case DivInstrumentFZT::TE_EFFECT_CUTOFF_UP:
            case DivInstrumentFZT::TE_EFFECT_CUTOFF_DOWN:
            case DivInstrumentFZT::TE_EFFECT_SET_RESONANCE:
            case DivInstrumentFZT::TE_EFFECT_RESONANCE_UP:
            case DivInstrumentFZT::TE_EFFECT_RESONANCE_DOWN:
            case DivInstrumentFZT::TE_EFFECT_SET_ATTACK:
            case DivInstrumentFZT::TE_EFFECT_SET_DECAY:
            case DivInstrumentFZT::TE_EFFECT_SET_SUSTAIN:
            case DivInstrumentFZT::TE_EFFECT_SET_RELEASE:
            case DivInstrumentFZT::TE_EFFECT_PORTA_UP_SEMITONE:
            case DivInstrumentFZT::TE_EFFECT_PORTA_DOWN_SEMITONE:
            case DivInstrumentFZT::TE_EFFECT_PITCH:
            case DivInstrumentFZT::TE_EFFECT_ARPEGGIO_ABS:
            case DivInstrumentFZT::TE_EFFECT_TRIGGER_RELEASE:
            {
              int temp = ins->fzt.program[i].val;
              if(CWSliderInt(_("Value"),&temp,0,0xff,"%02X"))
              {
                ins->fzt.program[i].val = temp;
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_ARPEGGIO:
            {
              bool disabled = (ins->fzt.program[i].val == 0xf0 || ins->fzt.program[i].val == 0xf1);
              ImGui::BeginDisabled(disabled);
              int temp = ins->fzt.program[i].val;
              char buf[6];

              int note = ins->fzt.base_note + 60 + ins->fzt.program[i].val;
              if(note > MAX_NOTE + 60) note = MAX_NOTE + 60;
              int max_note_slider = MAX_NOTE - ins->fzt.base_note;
              
              if(!disabled)
              {
                if(ins->fzt.program[i].val > max_note_slider) ins->fzt.program[i].val = max_note_slider;
                snprintf(buf, 6, "%s", noteNames[note]);
              }
              if(disabled)
              {
                memset(buf,0,6);
              }
              
              if(CWSliderInt(_("Semitones"),&temp,0,max_note_slider, buf))
              {
                ins->fzt.program[i].val = temp;
              }
              ImGui::EndDisabled();

              bool ext1 = ins->fzt.program[i].val == 0xf0;

              if(ImGui::Checkbox(_("First external arpeggio note"), &ext1))
              {
                if(ext1)
                {
                  ins->fzt.program[i].val = 0xf0;
                }
                else
                {
                  ins->fzt.program[i].val = 0;
                }
              }

              bool ext2 = ins->fzt.program[i].val == 0xf1;

              if(ImGui::Checkbox(_("Second external arpeggio note"), &ext2))
              {
                if(ext2)
                {
                  ins->fzt.program[i].val = 0xf1;
                }
                else
                {
                  ins->fzt.program[i].val = 0;
                }
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_VIBRATO:
            case DivInstrumentFZT::TE_EFFECT_PWM:
            {
              int speed = ins->fzt.program[i].val >> 4;
              if(CWSliderInt(_("Speed"),&speed,0,0xf,"%01X"))
              {
                ins->fzt.program[i].val &= 0x0f;
                ins->fzt.program[i].val |= (speed << 4);
              }
              int depth = ins->fzt.program[i].val & 15;
              if(CWSliderInt(_("Depth"),&depth,0,0xf,"%01X"))
              {
                ins->fzt.program[i].val &= 0xf0;
                ins->fzt.program[i].val |= (depth);
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_EXT_TOGGLE_FILTER:
            case DivInstrumentFZT::TE_EFFECT_EXT_PORTA_UP:
            case DivInstrumentFZT::TE_EFFECT_EXT_PORTA_DN:
            case DivInstrumentFZT::TE_EFFECT_EXT_RETRIGGER:
            case DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_DOWN:
            case DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_UP:
            case DivInstrumentFZT::TE_EFFECT_EXT_NOTE_CUT:
            case DivInstrumentFZT::TE_EFFECT_EXT_PHASE_RESET:
            {
              if(ins->fzt.program[i].val > 0xf) ins->fzt.program[i].val = 0xf;
              int temp = ins->fzt.program[i].val;
              if(CWSliderInt(_("Value"),&temp,0,0xf,"%01X"))
              {
                ins->fzt.program[i].val = temp;
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_EXT_FILTER_MODE:
            {
              if(ins->fzt.program[i].val > 7) ins->fzt.program[i].val = 7;
              int temp = ins->fzt.program[i].val;
              char buf[60];
              snprintf(buf, 60, "%s", _L(fztFilterModes[temp]));
              if(CWSliderInt(_("Value"),&temp,0,7,buf))
              {
                ins->fzt.program[i].val = temp;
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_VOLUME_FADE: 
            {
              int speed = ins->fzt.program[i].val >> 4;
              if(CWSliderInt(_("Up"),&speed,0,0xf,"%01X"))
              {
                ins->fzt.program[i].val &= 0x0f;
                ins->fzt.program[i].val |= (speed << 4);
              }
              int depth = ins->fzt.program[i].val & 15;
              if(CWSliderInt(_("Down"),&depth,0,0xf,"%01X"))
              {
                ins->fzt.program[i].val &= 0xf0;
                ins->fzt.program[i].val |= (depth);
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_SET_RING_MOD_SRC:
            case DivInstrumentFZT::TE_EFFECT_SET_HARD_SYNC_SRC:
            {
              if(ins->fzt.program[i].val > FZT_NUM_CHANNELS-1 && ins->fzt.program[i].val != 0xff) ins->fzt.program[i].val = FZT_NUM_CHANNELS-1;
              bool disabled = (ins->fzt.program[i].val == 0xff);

              ImGui::BeginDisabled(disabled);
              int temp = ins->fzt.program[i].val;
              char buf[6];
              
              if(!disabled)
              {
                snprintf(buf, 6, "%01X", ins->fzt.program[i].val);
              }
              if(disabled)
              {
                memset(buf,0,6);
              }
              
              if(CWSliderInt(_("Source channel"),&temp,0,FZT_NUM_CHANNELS-1, buf))
              {
                ins->fzt.program[i].val = temp;
              }
              ImGui::EndDisabled();

              bool ext1 = ins->fzt.program[i].val == 0xff;

              if(ImGui::Checkbox(_("Source is self"), &ext1))
              {
                if(ext1)
                {
                  ins->fzt.program[i].val = 0xff;
                }
                else
                {
                  ins->fzt.program[i].val = 0;
                }
              }
              break;
            }
            case DivInstrumentFZT::TE_EFFECT_SET_WAVEFORM: 
            {
              bool fztNoise = ins->fzt.program[i].val & SE_WAVEFORM_NOISE;
              pushToggleColors(fztNoise);
              if (ImGui::Button(_("noise"))) 
              { PARAMETER
                ins->fzt.program[i].val ^= SE_WAVEFORM_NOISE;
              }
              popToggleColors();
              ImGui::SameLine();
              bool fztPulse = ins->fzt.program[i].val & SE_WAVEFORM_PULSE;
              pushToggleColors(fztPulse);
              if (ImGui::Button(_("pulse"))) 
              { PARAMETER
                ins->fzt.program[i].val ^= SE_WAVEFORM_PULSE;
              }
              popToggleColors();
              ImGui::SameLine();
              bool fztTri = ins->fzt.program[i].val & SE_WAVEFORM_TRIANGLE;
              pushToggleColors(fztTri);
              if (ImGui::Button(_("triangle"))) 
              { PARAMETER
                ins->fzt.program[i].val ^= SE_WAVEFORM_TRIANGLE;
              }
              popToggleColors();
              ImGui::SameLine();
              bool fztSaw = ins->fzt.program[i].val & SE_WAVEFORM_SAW;
              pushToggleColors(fztSaw);
              if (ImGui::Button(_("saw"))) 
              { PARAMETER
                ins->fzt.program[i].val ^= SE_WAVEFORM_SAW;
              }
              popToggleColors();
              ImGui::SameLine();
              bool fztMetal = ins->fzt.program[i].val & SE_WAVEFORM_NOISE_METAL;
              pushToggleColors(fztMetal);
              if (ImGui::Button(_("metal"))) 
              { PARAMETER
                ins->fzt.program[i].val ^= SE_WAVEFORM_NOISE_METAL;
              }
              popToggleColors();
              ImGui::SameLine();
              bool fztSine = ins->fzt.program[i].val & SE_WAVEFORM_SINE;
              pushToggleColors(fztSine);
              if (ImGui::Button(_("sine"))) 
              { PARAMETER
                ins->fzt.program[i].val ^= SE_WAVEFORM_SINE;
              }
              popToggleColors();
              break;
            }
            case DivInstrumentFZT::TE_PROGRAM_LOOP_BEGIN: 
            {
              break;
            }
            case DivInstrumentFZT::TE_PROGRAM_LOOP_END: 
            {
              int temp = ins->fzt.program[i].val;
              if(CWSliderInt(_("Loops"),&temp,0,0xff,"%02X"))
              {
                ins->fzt.program[i].val = temp;
              }
              break;
            }
            case DivInstrumentFZT::TE_PROGRAM_JUMP: 
            {
              int temp = ins->fzt.program[i].val;
              if(CWSliderInt(_("Step to jump to"),&temp,0,0xf,"%02X"))
              {
                ins->fzt.program[i].val = temp;
              }
              break;
            }
            case DivInstrumentFZT::TE_PROGRAM_NOP: 
            {
              ImGui::Text(_("No operation"));
              break;
            }
            case DivInstrumentFZT::TE_PROGRAM_END: 
            {
              ImGui::Text(_("Program end"));
              break;
            }
            default:
              break;
          }
          if(ins->fzt.program[i].cmd < 0x7d00 || ins->fzt.program[i].cmd == 0xE500)
          {
              ImGui::Checkbox(_("Execute next command at the same tick"), &ins->fzt.program[i].unite);
          }
          ImGui::PopID();
          ImGui::TableNextColumn();
          ImGui::PushID(i+512);
          if (ImGui::Button(ICON_FA_CHEVRON_UP "##HWCmdUp")) 
          {
            if (i>0) 
            {
              e->lockEngine([ins,i]() 
              {
                ins->fzt.program[i - 1].cmd^=ins->fzt.program[i].cmd;
                ins->fzt.program[i].cmd^=ins->fzt.program[i - 1].cmd;
                ins->fzt.program[i - 1].cmd^=ins->fzt.program[i].cmd;

                ins->fzt.program[i - 1].val^=ins->fzt.program[i].val;
                ins->fzt.program[i].val^=ins->fzt.program[i - 1].val;
                ins->fzt.program[i - 1].val^=ins->fzt.program[i].val;

                ins->fzt.program[i - 1].unite^=ins->fzt.program[i].unite;
                ins->fzt.program[i].unite^=ins->fzt.program[i - 1].unite;
                ins->fzt.program[i - 1].unite^=ins->fzt.program[i].unite;
              });
            }
            MARK_MODIFIED;
          }
          ImGui::SameLine();
          if (ImGui::Button(ICON_FA_CHEVRON_DOWN "##HWCmdDown")) 
          {
            if (i<FZT_INST_PROG_LEN - 1) 
            {
              e->lockEngine([ins,i]() 
              {
                ins->fzt.program[i + 1].cmd^=ins->fzt.program[i].cmd;
                ins->fzt.program[i].cmd^=ins->fzt.program[i + 1].cmd;
                ins->fzt.program[i + 1].cmd^=ins->fzt.program[i].cmd;

                ins->fzt.program[i + 1].val^=ins->fzt.program[i].val;
                ins->fzt.program[i].val^=ins->fzt.program[i + 1].val;
                ins->fzt.program[i + 1].val^=ins->fzt.program[i].val;

                ins->fzt.program[i + 1].unite^=ins->fzt.program[i].unite;
                ins->fzt.program[i].unite^=ins->fzt.program[i + 1].unite;
                ins->fzt.program[i + 1].unite^=ins->fzt.program[i].unite;
              });
            }
            MARK_MODIFIED;
          }
          ImGui::SameLine();
          pushDestColor();
          if (ImGui::Button(ICON_FA_TIMES "##HWCmdDel")) 
          {
            for (int j=i; j<FZT_INST_PROG_LEN; j++) 
            {
              ins->fzt.program[j].cmd=ins->fzt.program[j+1].cmd;
              ins->fzt.program[j].val=ins->fzt.program[j+1].val;
              ins->fzt.program[j].unite=ins->fzt.program[j+1].unite;
            }
            ins->fzt.program[FZT_INST_PROG_LEN - 1].cmd=DivInstrumentFZT::TE_PROGRAM_NOP;
            ins->fzt.program[FZT_INST_PROG_LEN - 1].val=0;
            ins->fzt.program[FZT_INST_PROG_LEN - 1].unite=false;
          }
          popDestColor();
          ImGui::PopID();

          ImGui::TableNextColumn();

          ImRect rect = ImGui::TableGetCellBgRect(ImGui::GetCurrentTable(), 3);
          ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x,30.0f * dpiScale);
          ImGuiStyle& style=ImGui::GetStyle();

          ImDrawList* dl=ImGui::GetWindowDrawList();
          ImGui::ItemSize(size,style.FramePadding.y);
          ImU32 color=ImGui::GetColorU32(uiColors[GUI_COLOR_FM_ENVELOPE]);
          if (ImGui::ItemAdd(rect,ImGui::GetID("unitee")))
          {
            ImGui::RenderFrame(rect.Min,rect.Max,ImGui::GetColorU32(ImGuiCol_WindowBg),true,style.FrameRounding);

            ImVec2 pos1=ImLerp(rect.Min,rect.Max,ImVec2(0.0,0.3)); //top corner
            ImVec2 pos2=ImLerp(rect.Min,rect.Max,ImVec2(0.7,0.6)); //angle of opening bracket
            ImVec2 pos3=ImLerp(rect.Min,rect.Max,ImVec2(0.7,1.0)); //the bottom end
            ImVec2 pos4=ImLerp(rect.Min,rect.Max,ImVec2(0.7,0.0)); //the top end
            ImVec2 pos5=ImLerp(rect.Min,rect.Max,ImVec2(0.7,0.3)); //angle of closing bracket
            ImVec2 pos6=ImLerp(rect.Min,rect.Max,ImVec2(0.0,0.6)); //bottom corner

            if(i == 0 && ins->fzt.program[i].unite)
            {
              addAALine(dl,pos1,pos2,color,2.0f * dpiScale); //opening bracket
              addAALine(dl,pos2,pos3,color,2.0f * dpiScale);
            }
            if(i > 0)
            {
              if(ins->fzt.program[i].unite && !ins->fzt.program[i-1].unite)
              {
                addAALine(dl,pos1,pos2,color,2.0f * dpiScale); //opening bracket
                addAALine(dl,pos2,pos3,color,2.0f * dpiScale);
              }

              if(!ins->fzt.program[i].unite && ins->fzt.program[i-1].unite)
              {
                addAALine(dl,pos4,pos5,color,2.0f * dpiScale); //closing bracket
                addAALine(dl,pos5,pos6,color,2.0f * dpiScale);
              }

              if(ins->fzt.program[i].unite && ins->fzt.program[i-1].unite)
              {
                addAALine(dl,pos3,pos4,color,2.0f * dpiScale); //mid bracket
              }
            }
          }
        }

        ImGui::EndTable();
      }
    }
    ImGui::EndChild();
    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_("Macros"))) 
  {
    ImGui::Text(_("Warning! Macros are NOT supported by FZT file format! Do not use them if you want to export .fzt file!"));

    macroList.push_back(FurnaceGUIMacroDesc(_("Volume"),ins,DIV_MACRO_VOL,0xff,0,0xff,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_("Duty"),ins,DIV_MACRO_DUTY,0xff,((ins->std.get_macro(DIV_MACRO_DUTY, true)->mode==1)?(-0xfff):0),0xfff,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));

    macroList.push_back(FurnaceGUIMacroDesc(_("Waveform"),ins,DIV_MACRO_WAVE,0xff,0,6,96,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,true,fztShapeBits,0));

    macroList.push_back(FurnaceGUIMacroDesc(_("Cutoff"),ins,DIV_MACRO_ALG,0xff,((ins->std.get_macro(DIV_MACRO_ALG, true)->mode==1)?(-0x7ff):0),0x7ff,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_("Filter Mode"),ins,DIV_MACRO_EX1,0xff,0,7,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Filter Toggle"),ins,DIV_MACRO_EX2,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Resonance"),ins,DIV_MACRO_EX3,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Phase Reset"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Envelope Reset/Key Control"),ins,DIV_MACRO_EX4,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_("Ring mod toggle"),ins,DIV_MACRO_EX5,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Ring mod source"),ins,DIV_MACRO_EX6,0xff,0,FZT_NUM_CHANNELS,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Hard sync toggle"),ins,DIV_MACRO_EX7,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Hard sync source"),ins,DIV_MACRO_EX8,0xff,0,FZT_NUM_CHANNELS,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Attack"),ins,DIV_MACRO_EX9, 0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Decay"),ins,DIV_MACRO_EX10, 0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Sustain"),ins,DIV_MACRO_EX11, 0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Release"),ins,DIV_MACRO_EX12, 0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));


    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}