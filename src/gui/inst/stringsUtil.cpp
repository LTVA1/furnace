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

#include "stringsUtil.h"

const char* ssgEnvTypes[8]={
  "Down Down Down##sgistru", "Down.##sgistru", "Down Up Down Up##sgistru", "Down UP##sgistru", "Up Up Up##sgistru", "Up.##sgistru", "Up Down Up Down##sgistru", "Up DOWN##sgistru"
};

const char* EngFmParamNames[3][32]={
  {"Algorithm", "Feedback", "LFO > Freq", "LFO > Amp", "Attack", "Decay", "Decay 2", "Release", "Sustain", "Level", "EnvScale", "Multiplier", "Detune", "Detune 2", "SSG-EG", "AM", "AM Depth", "Vibrato Depth", "Sustained", "Sustained", "Level Scaling", "Sustain", "Vibrato", "Waveform", "Scale Rate", "OP2 Half Sine", "OP1 Half Sine", "EnvShift", "Reverb", "Fine", "LFO2 > Freq", "LFO2 > Amp"},
  {"ALG", "FB", "FMS/PMS", "AMS", "AR", "DR", "SR", "RR", "SL", "TL", "KS", "MULT", "DT", "DT2", "SSG-EG", "AM", "AMD", "FMD", "EGT", "EGT", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine", "FMS/PMS2", "AMS2"},
  {"ALG", "FB", "FMS/PMS", "AMS", "AR", "DR", "D2R", "RR", "SL", "TL", "RS", "MULT", "DT", "DT2", "SSG-EG", "AM", "DAM", "DVB", "EGT", "EGS", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine", "FMS/PMS2", "AMS2"}
};

const char* fmParamNames[3][32]={
  {"Algorithm##sgistru", "Feedback##sgistru", "LFO > Freq##sgistru", "LFO > Amp##sgistru", "Attack##sgistru", "Decay##sgistru", "Decay 2##sgistru", "Release##sgistru", "Sustain##sgistru0", "Level##sgistru", "EnvScale##sgistru", "Multiplier##sgistru", "Detune##sgistru0", "Detune 2##sgistru", "SSG-EG##sgistru", "AM", "AM Depth##sgistru", "Vibrato Depth##sgistru", "Sustained##sgistru0", "Sustained##sgistru1", "Level Scaling##sgistru", "Sustain##sgistru1", "Vibrato##sgistru", "Waveform##sgistru", "Scale Rate##sgistru", "OP2 Half Sine##sgistru", "OP1 Half Sine##sgistru", "EnvShift##sgistru", "Reverb##sgistru", "Fine##sgistru0", "LFO2 > Freq##sgistru", "LFO2 > Amp##sgistru"},
  {"ALG", "FB", "FMS/PMS", "AMS", "AR", "DR", "SR", "RR", "SL", "TL", "KS", "MULT", "DT", "DT2", "SSG-EG", "AM", "AMD", "FMD", "EGT", "EGT", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine##sgistru1", "FMS/PMS2", "AMS2"},
  {"ALG", "FB", "FMS/PMS", "AMS", "AR", "DR", "D2R", "RR", "SL", "TL", "RS", "MULT", "DT", "DT2", "SSG-EG", "AM", "DAM", "DVB", "EGT", "EGS", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine##sgistru2", "FMS/PMS2", "AMS2"}
};

const char* esfmParamLongNames[9]={
  "OP4 Noise Mode##sgistru0", "Envelope Delay##sgistru", "Output Level##sgistru0", "Modulation Input Level##sgistru", "Left Output##sgistru", "Right Output##sgistru", "Coarse Tune (semitones)##sgistru", "Detune##sgistru1", "Fixed Frequency Mode##sgistru"
};

const char* EngEsfmParamLongNames[9]={
  "OP4 Noise Mode", "Envelope Delay", "Output Level", "Modulation Input Level", "Left Output", "Right Output", "Coarse Tune (semitones)", "Detune", "Fixed Frequency Mode"
};

const char* esfmParamNames[9]={
  "OP4 Noise Mode##sgistru1", "Env. Delay##sgistru", "Output Level##sgistru1", "ModInput##sgistru", "Left##sgistru", "Right##sgistru", "Tune##sgistru", "Detune##sgistru2", "Fixed##sgistru0"
};

const char* esfmParamShortNames[9]={
  "NOI", "DL", "OL", "MI", "L", "R", "CT", "DT", "FIX"
};

const char* fmParamShortNames[3][32]={
  {"ALG", "FB", "FMS", "AMS", "A", "D", "D2", "R", "S", "TL", "RS", "ML", "DT", "DT2", "SSG", "AM", "DAM", "DVB", "SUS", "SUS", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine##sgistru3", "FMS2", "AMS2"},
  {"ALG", "FB", "FMS", "AMS", "A", "D", "SR", "R", "S", "TL", "KS", "ML", "DT", "DT2", "SSG", "AM", "AMD", "FMD", "EGT", "EGT", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine##sgistru4", "FMS2", "AMS2"},
  {"ALG", "FB", "FMS", "AMS", "A", "D", "D2", "R", "S", "TL", "RS", "ML", "DT", "DT2", "SSG", "AM", "DAM", "DVB", "EGT", "EGS", "KSL", "SUS", "VIB", "WS", "KSR", "DC", "DM", "EGS", "REV", "Fine##sgistru5", "FMS2", "AMS2"}
};

const char* opllVariants[4]={
  "OPLL",
  "YMF281",
  "YM2423",
  "VRC7"
};

const char* opllInsNames[4][17]={
  /* YM2413 */ {
    "User##sgistru0",
    "1. Violin##sgistru",
    "2. Guitar##sgistru0",
    "3. Piano##sgistru0",
    "4. Flute##sgistru0",
    "5. Clarinet##sgistru0",
    "6. Oboe##sgistru",
    "7. Trumpet##sgistru0",
    "8. Organ##sgistru",
    "9. Horn##sgistru",
    "10. Synth##sgistru",
    "11. Harpsichord##sgistru",
    "12. Vibraphone##sgistru0",
    "13. Synth Bass##sgistru",
    "14. Acoustic Bass##sgistru",
    "15. Electric Guitar##sgistru",
    "Drums##sgistru0"
  },
  /* YMF281 */ {
    "User##sgistru1",
    "1. Electric String##sgistru",
    "2. Bow wow##sgistru",
    "3. Electric Guitar##sgistru0",
    "4. Organ##sgistru",
    "5. Clarinet##sgistru1",
    "6. Saxophone##sgistru",
    "7. Trumpet##sgistru1",
    "8. Street Organ##sgistru",
    "9. Synth Brass##sgistru",
    "10. Electric Piano##sgistru",
    "11. Bass##sgistru",
    "12. Vibraphone##sgistru1",
    "13. Chime##sgistru",
    "14. Tom Tom II##sgistru",
    "15. Noise##sgistru",
    "Drums##sgistru1"
  },
  /* YM2423 */ {
    "User##sgistru2",
    "1. Strings##sgistru",
    "2. Guitar##sgistru1",
    "3. Electric Guitar##sgistru1",
    "4. Electric Piano##sgistru",
    "5. Flute##sgistru",
    "6. Marimba##sgistru",
    "7. Trumpet##sgistru2",
    "8. Harmonica##sgistru",
    "9. Tuba##sgistru",
    "10. Synth Brass##sgistru",
    "11. Short Saw##sgistru",
    "12. Vibraphone##sgistru2",
    "13. Electric Guitar 2##sgistru",
    "14. Synth Bass##sgistru",
    "15. Sitar##sgistru",
    "Drums##sgistru2"
  },
  // stolen from FamiTracker
  /* VRC7 */ {
    "User##sgistru3",
    "1. Bell##sgistru",
    "2. Guitar##sgistru2",
    "3. Piano##sgistru1",
    "4. Flute##sgistru1",
    "5. Clarinet##sgistru2",
    "6. Rattling Bell##sgistru",
    "7. Trumpet##sgistru3",
    "8. Reed Organ##sgistru",
    "9. Soft Bell##sgistru",
    "10. Xylophone##sgistru",
    "11. Vibraphone##sgistru",
    "12. Brass##sgistru",
    "13. Bass Guitar##sgistru",
    "14. Synth##sgistru",
    "15. Chorus##sgistru",
    "Drums##sgistru3"
  }
};

const char* oplWaveforms[8]={
  "Sine##sgistru0", "Half Sine##sgistru0", "Absolute Sine##sgistru0", "Quarter Sine##sgistru", "Squished Sine##sgistru0", "Squished AbsSine##sgistru0", "Square##sgistru0", "Derived Square##sgistru0"
};

const char* oplWaveformsStandard[8]={
  "Sine##sgistru1", "Half Sine##sgistru1", "Absolute Sine##sgistru1", "Pulse Sine##sgistru", "Sine (Even Periods)##sgistru", "AbsSine (Even Periods)##sgistru", "Square##sgistru1", "Derived Square##sgistru1"
};

const char* opzWaveforms[8]={
  "Sine##sgistru2", "Triangle##sgistru", "Cut Sine##sgistru", "Cut Triangle##sgistru", "Squished Sine##sgistru1", "Squished Triangle##sgistru", "Squished AbsSine##sgistru1", "Squished AbsTriangle##sgistru"
};

const char* oplDrumNames[4]={
  "Snare##sgistru0", "Tom##sgistru", "Top##sgistru0", "HiHat##sgistru0"
};

const char* esfmNoiseModeNames[4]={
  "Normal##sgistru", "Snare##sgistru1", "HiHat##sgistru1", "Top##sgistru1"
};

const char* esfmNoiseModeDescriptions[4]={
  "Noise disabled##sgistru", "Square + noise##sgistru", "Ringmod from OP3 + noise##sgistru", "Ringmod from OP3 + double pitch ModInput\nWARNING - has emulation issues, subject to change##sgistru"
};

const bool opIsOutput[8][4]={
  {false,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {false,true,false,true},
  {false,true,true,true},
  {false,true,true,true},
  {true,true,true,true}
};

const bool opIsOutputOPL[4][4]={
  {false,false,false,true},
  {true,false,false,true},
  {false,true,false,true},
  {true,false,true,true}
};

const char* fmOperatorBits[5]={
  "op1##sgistru", "op2##sgistru", "op3##sgistru", "op4##sgistru", NULL
};

const char* c64ShapeBits[5]={
  "triangle##sgistru", "saw##sgistru", "pulse##sgistru", "noise##sgistru0", NULL
};

const char* ayShapeBits[4]={
  "tone##sgistru", "noise##sgistru1", "envelope##sgistru", NULL
};

const char* ayEnvBits[4]={
  "hold##sgistru", "alternate##sgistru", "direction##sgistru0", "enable##sgistru0"
};

const char* ssgEnvBits[5]={
  "0", "1", "2", "enabled##sgistru0", NULL
};

const char* saaEnvBits[9]={
  "mirror##sgistru", "loop##sgistru0", "cut##sgistru", "direction##sgistru1", "resolution##sgistru", "fixed##sgistru1", "N/A##sgistru","enabled##sgistru1", NULL
};

const char* snesModeBits[6]={
  "noise##sgistru2", "echo##sgistru", "pitch mod##sgistru", "invert right##sgistru", "invert left##sgistru", NULL
};

const char* filtModeBits[5]={
  "low##sgistru", "band##sgistru", "high##sgistru", "ch3off##sgistru", NULL
};

const char* c64TestGateBits[5]={
  "gate##sgistru", "sync##sgistru", "ring##sgistru", "test##sgistru", NULL
};

const char* pokeyCtlBits[9]={
  "15KHz##sgistru", "filter 2+4##sgistru", "filter 1+3##sgistru", "16-bit 3+4##sgistru", "16-bit 1+2##sgistru", "high3##sgistru", "high1##sgistru", "poly9##sgistru", NULL
};

const char* mikeyFeedbackBits[11] = {
  "0", "1", "2", "3", "4", "5", "7", "10", "11", "int##sgistru", NULL
};

const char* msm5232ControlBits[7]={
  "16'", "8'", "4'", "2'", "sustain##sgistru2", NULL
};

const char* tedControlBits[3]={
  "square##sgistru2", "noise##sgistru3", NULL
};

const char* c219ControlBits[4]={
  "noise##sgistru4", "invert##sgistru", "surround##sgistru", NULL
};

const char* x1_010EnvBits[8]={
  "enable##sgistru1", "oneshot##sgistru", "split L/R##sgistru", "HinvR##sgistru", "VinvR##sgistru", "HinvL##sgistru", "VinvL##sgistru", NULL
};

/*const char* n163UpdateBits[8]={
  "now", "every waveform changed", NULL
};*/

const char* suControlBits[5]={
  "ring mod##sgistru", "low pass##sgistru", "high pass##sgistru", "band pass##sgistru", NULL
};

const char* es5506FilterModes[4]={
  "HP/K2, HP/K2##sgistru", "HP/K2, LP/K1##sgistru", "LP/K2, LP/K2##sgistru", "LP/K2, LP/K1##sgistru",
};

const char* panBits[5]={
  "right##sgistru", "left##sgistru", "rear right##sgistru", "rear left##sgistru", NULL
};

const char* powerNoiseControlBits[3]={
  "enable tap B##sgistru", "AM with slope##sgistru", NULL
};

const char* powerNoiseSlopeControlBits[7]={
  "invert B##sgistru", "invert A##sgistru", "reset B##sgistru", "reset A##sgistru", "clip B##sgistru", "clip A##sgistru", NULL
};

const char* oneBit[2]={
  "on##sgistru", NULL
};

const char* es5506EnvelopeModes[3]={
  "k1 slowdown##sgistru", "k2 slowdown##sgistru", NULL
};

const char* es5506ControlModes[3]={
  "pause##sgistru", "reverse##sgistru", NULL
};

const int orderedOps[4]={
  0, 2, 1, 3
};

const char* singleWSEffects[7]={
  "None##sgistru",
  "Invert##sgistru",
  "Add##sgistru",
  "Subtract##sgistru",
  "Average##sgistru",
  "Phase##sgistru",
  "Chorus##sgistru"
};

const char* dualWSEffects[9]={
  "None (dual)##sgistru",
  "Wipe##sgistru",
  "Fade##sgistru",
  "Fade (ping-pong)##sgistru",
  "Overlay##sgistru",
  "Negative Overlay##sgistru",
  "Slide##sgistru",
  "Mix Chorus##sgistru",
  "Phase Modulation##sgistru"
};

const char* gbHWSeqCmdTypes[6+1]={
  "Envelope##sgistru",
  "Sweep##sgistru",
  "Wait##sgistru0",
  "Wait for Release##sgistru0",
  "Loop##sgistru1",
  "Loop until Release##sgistru0",
  NULL
};

const char* suHWSeqCmdTypes[7+1]={
  "Volume Sweep##sgistru",
  "Frequency Sweep##sgistru",
  "Cutoff Sweep##sgistru",
  "Wait##sgistru1",
  "Wait for Release##sgistru1",
  "Loop##sgistru2",
  "Loop until Release##sgistru1",
  NULL
};

const char* snesGainModes[5]={
  "Direct##sgistru",
  "Decrease (linear)##sgistru",
  "Decrease (logarithmic)##sgistru",
  "Increase (linear)##sgistru",
  "Increase (bent line)##sgistru"
};

const int detuneMap[2][8]={
  {-3, -2, -1, 0, 1, 2, 3, 4},
  { 7,  6,  5, 0, 1, 2, 3, 4}
};

const int detuneUnmap[2][11]={
  {0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0},
  {0, 0, 0, 3, 4, 5, 6, 7, 2, 1, 0}
};

const int kslMap[4]={
  0, 2, 1, 3
};

// do not change these!
// anything other than a checkbox will look ugly!
//
// if you really need to, and have a good rationale (and by good I mean a VERY
// good one), please tell me and we'll sort it out.
const char* macroAbsoluteMode="Fixed##sgistru2";
const char* macroRelativeMode="Relative##sgistru";
const char* macroQSoundMode="QSound##sgistru";
const char* macroDummyMode="Bug##sgistru";