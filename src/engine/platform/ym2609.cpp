/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2026 tildearrow and contributors
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

#include "ym2609.h"
#include "../engine.h"
#include <math.h>
#include "../../ta-log.h"

#define PLEASE_HELP_ME(_targetChan,blk) \
  int boundaryBottom=parent->calcBaseFreq(chipClock,CHIP_FREQBASE,0,false); \
  int boundaryTop=parent->calcBaseFreq(chipClock,CHIP_FREQBASE,12,false); \
  int destFreq=NOTE_FNUM_BLOCK(c.value2,11,blk); \
  int newFreq; \
  bool return2=false; \
  if (_targetChan.portaPause) { \
    if (parent->song.compatFlags.oldOctaveBoundary) { \
      if ((_targetChan.portaPauseFreq&0xf800)>(_targetChan.baseFreq&0xf800)) { \
        _targetChan.baseFreq=((_targetChan.baseFreq&0x7ff)>>1)|(_targetChan.portaPauseFreq&0xf800); \
      } else { \
        _targetChan.baseFreq=((_targetChan.baseFreq&0x7ff)<<1)|(_targetChan.portaPauseFreq&0xf800); \
      } \
      c.value*=2; \
    } else { \
      _targetChan.baseFreq=_targetChan.portaPauseFreq; \
    } \
  } \
  if (destFreq>_targetChan.baseFreq) { \
    newFreq=_targetChan.baseFreq+c.value; \
    if (newFreq>=destFreq) { \
      newFreq=destFreq; \
      return2=true; \
    } \
  } else { \
    newFreq=_targetChan.baseFreq-c.value; \
    if (newFreq<=destFreq) { \
      newFreq=destFreq; \
      return2=true; \
    } \
  } \
  /* check for octave boundary */ \
  /* what the heck! */ \
  if (!_targetChan.portaPause) { \
    if ((newFreq&0x7ff)>boundaryTop && (newFreq&0xf800)<0x3800) { \
      if (parent->song.compatFlags.fbPortaPause) { \
        _targetChan.portaPauseFreq=(boundaryBottom)|((newFreq+0x800)&0xf800); \
        _targetChan.portaPause=true; \
        break; \
      } else { \
        newFreq=((newFreq&0x7ff)>>1)|((newFreq+0x800)&0xf800); \
      } \
    } \
    if ((newFreq&0x7ff)<boundaryBottom && (newFreq&0xf800)>0) { \
      if (parent->song.compatFlags.fbPortaPause) { \
        _targetChan.portaPauseFreq=newFreq=(boundaryTop-1)|((newFreq-0x800)&0xf800); \
        _targetChan.portaPause=true; \
        break; \
      } else { \
        newFreq=((newFreq&0x7ff)<<1)|((newFreq-0x800)&0xf800); \
      } \
    } \
  } \
  _targetChan.portaPause=false; \
  _targetChan.freqChanged=true; \
  _targetChan.baseFreq=newFreq; \
  if (return2) { \
    _targetChan.inPorta=false; \
    return 2; \
  }

#define KVS(x,y) ((chan[x].state.op[y].kvs==2 && isOutput[chan[x].state.alg][y]) || chan[x].state.op[y].kvs==1)

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }
#define immWrite(a,v) ym2609->SetReg(a, v); regPool[a % YM2609_NUM_REGISTERS]=v;
//#define rWrite(a,v) ym2609->SetReg(a, v);
//#define immWrite(a,v) if (!skipRegisterWrites) {writes.push_back(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }
//#define immWrite(a,v) ym2609->SetReg(a, v); regPool[a % YM2609_NUM_REGISTERS]=v;

//TODO: replace with custom clock

#define YM2609_CLOCK 8000000
#define YM2609_DSP_RATE 48000

#define CHIP_FREQBASE fmFreqBase
#define CHIP_DIVIDER fmDivBase

const char** DivPlatformYM2609::getRegisterSheet() {
  return NULL;
}

void DivPlatformYM2609::acquire(short** buf, size_t len) 
{
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) 
  {
    oscBuf[i]->begin(len);
  }

  while (!writes.empty()) 
  {
    QueuedWrite w=writes.front();
    ym2609->SetReg(w.addr, w.val);
    regPool[w.addr % YM2609_NUM_REGISTERS]=w.val;
    writes.pop();
  }

  for(size_t samp = 0; samp < len; samp++)
  {
    output_buf[0][0] = 0;
    output_buf[1][0] = 0;

    ym2609->Mix(output_buf, 1);

    for(int i = 0; i < 6; i++)
    {
      oscBuf[i]->putSample(samp,(ym2609->fm6[0].ch_output[i][0] + ym2609->fm6[0].ch_output[i][1]) / 2);
      oscBuf[i+6]->putSample(samp,(ym2609->fm6[1].ch_output[i][0] + ym2609->fm6[1].ch_output[i][1]) / 2);

      oscBuf[rhythm_offset+i]->putSample(samp,(ym2609->rss_output[i][0] + ym2609->rss_output[i][1]));

      oscBuf[adpcma_offset+i]->putSample(samp,(ym2609->adpcma.chan_output[i][0] + ym2609->adpcma.chan_output[i][1]) / 2);
    }

    for(int i = 0; i < 3; i++)
    {
      oscBuf[psg_offset+i]->putSample(samp,(ym2609->psg2[0].chan_output[i][0] + ym2609->psg2[0].chan_output[i][1]) * 3 / 2);
      oscBuf[psg_offset+3+i]->putSample(samp,(ym2609->psg2[1].chan_output[i][0] + ym2609->psg2[1].chan_output[i][1]) * 3 / 2);
      oscBuf[psg_offset+3*2+i]->putSample(samp,(ym2609->psg2[2].chan_output[i][0] + ym2609->psg2[2].chan_output[i][1]) * 3 / 2);
      oscBuf[psg_offset+3*3+i]->putSample(samp,(ym2609->psg2[3].chan_output[i][0] + ym2609->psg2[3].chan_output[i][1]) * 3 / 2);

      oscBuf[adpcmb_offset+i]->putSample(samp,(ym2609->adpcmb[i].chan_output[0] + ym2609->adpcmb[i].chan_output[0]) / 2);
    }

    buf[0][samp] = output_buf[0][0];
    buf[1][samp] = output_buf[1][0];
  }

  for (int i=0; i<YM2609_NUM_CHANNELS; i++) 
  {
    oscBuf[i]->end(len);
  }
}

double DivPlatformYM2609::NOTE_ADPCMB(int ch, int note) {
  int adpcm_ch = ch - adpcmb_offset;

  if (chan[ch].sample>=0 && chan[ch].sample<parent->song.sampleLen) {
    double clock_divider = (144.0 * 8.0 / 16.0);
    double off=65535.0*(double)(parent->getSample(chan[ch].sample)->centerRate)/parent->getCenterRate();
    return parent->calcBaseFreq((double)chipClock/clock_divider,off,note,false);
  }
  return 0;
}

void DivPlatformYM2609::tick(bool sysTick) 
{
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) 
  {
    chan[i].std.next();

    DivInstrument* ins=parent->getIns(chan[i].ins,DIV_INS_YM2609_FM);
    
    if(sysTick)
    {
      
    }

    bool writePan = false;
    bool doUpdatePSGWave = false;

    if (chan[i].std.vol.had) 
    {
      if (i<psg_offset)
      {
        int inVol=chan[i].std.vol.val;

        chan[i].outVol=VOL_SCALE_LOG_BROKEN(chan[i].vol,MIN(127,inVol),127);

        for (int j=0; j<4; j++) {
          unsigned short baseAddr=chanOffs[i]|opOffs[j];
          DivInstrumentFM::Operator& op=chan[i].state.op[j];
          if (isMuted[i] || !op.enable) {
            //rWrite(baseAddr+ADDR_TL,127);
            rWrite(baseAddr+ADDR_TL,127|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
          } else {
            if (KVS(i,j)) {
              //rWrite(baseAddr+ADDR_TL,127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[i].outVol&0x7f,127));
              rWrite(baseAddr+ADDR_TL,(127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[i].outVol&0x7f,127))|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
            } else {
              //rWrite(baseAddr+ADDR_TL,op.tl);
              rWrite(baseAddr+ADDR_TL,op.tl|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
            }
          }
        }
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;

        chan[i].outVol=MIN(15,chan[i].std.vol.val)-(15-(chan[i].vol&15));
        if (chan[i].outVol<0) chan[i].outVol=0;

        if (isMuted[i]) {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,0|(chan[i].pan << 6));
        } else {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[i].outVol&15)|((chan[i].nextPSGMode.getEnvelope())<<2)|(chan[i].pan << 6));
        }
      }
      if(i >= rhythm_offset && i < adpcma_offset)
      {
        chan[i].outVol=(chan[i].vol*MIN(chan[i].macroVolMul,chan[i].std.vol.val))/chan[i].macroVolMul;
        immWrite(0x18+(i-(rhythm_offset)),isMuted[i]?0:((chan[i].pan<<6)|chan[i].outVol));
      }
      if(i >= adpcma_offset && i < adpcmb_offset)
      {
        chan[i].outVol=(chan[i].vol*MIN(chan[i].macroVolMul,chan[i].std.vol.val))/chan[i].macroVolMul;
        immWrite(0x113,i-adpcma_offset);
        immWrite(0x114,isMuted[i]?0:(chan[i].outVol));
      }
      if(i >= adpcmb_offset && !isMuted[i])
      {
        int adpcm_ch = i - adpcmb_offset;

        chan[i].outVol=(chan[i].vol*MIN(chan[i].macroVolMul,chan[i].std.vol.val))/chan[i].macroVolMul;

        immWrite(adpcmb_offsets[adpcm_ch] + 0xb,chan[i].outVol);
      }
    }
    if (NEW_ARP_STRAT) {
      chan[i].handleArp();
    } else if (chan[i].std.arp.had) {
      if (!chan[i].inPorta) {
        chan[i].baseFreq=NOTE_FNUM_BLOCK(parent->calcArp(chan[i].note,chan[i].std.arp.val),11,chan[i].state.block);
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].std.pitch.had) {
      if (chan[i].std.pitch.mode) {
        chan[i].pitch2+=chan[i].std.pitch.val;
        CLAMP_VAR(chan[i].pitch2,-65535,65535);
      } else {
        chan[i].pitch2=chan[i].std.pitch.val;
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].std.panL.had) 
    {
      if(i < psg_offset)
      {
        if(chan[i].std.panL.val == 0)
        {
          chan[i].pan &= ~(1 << 1);
        }
        else
        {
          chan[i].pan |= (1 << 1);
          chan[i].panLeft = (3 - ((chan[i].std.panL.val - 1) & 3));
        }

        chan[i].freqChanged = true; //to write left soft pan
        writePan = true;
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        if(chan[i].std.panL.val == 0)
        {
          chan[i].pan &= ~(1 << 1);
        }
        else
        {
          chan[i].pan |= (1 << 1);
          chan[i].panLeft = (7 - ((chan[i].std.panL.val - 1) & 7));
        }

        writePan = true;
      }
      if(i >= rhythm_offset && i < adpcma_offset)
      {
        if(chan[i].std.panL.val == 0)
        {
          chan[i].pan &= ~(1 << 1);
        }
        else
        {
          chan[i].pan |= (1 << 1);
          chan[i].panLeft = (7 - ((chan[i].std.panL.val - 1) & 7));
        }

        rWrite(0x12 + i - rhythm_offset, chan[i].panRight | (chan[i].panLeft << 3));
      }
      if(i >= adpcma_offset && i < adpcmb_offset)
      {
        if(chan[i].std.panL.val == 0)
        {
          chan[i].pan &= ~(1 << 1);
        }
        else
        {
          chan[i].pan |= (1 << 1);
          chan[i].panLeft = (3 - ((chan[i].std.panL.val - 1) & 3));
        }

        immWrite(0x115,isMuted[i]?0:(((chan[i].pan & 2) << 6) | ((chan[i].panLeft & 3) << 5) | ((chan[i].pan & 1) << 4) | ((chan[i].panRight & 3) << 2)));
      }
      if(i >= adpcmb_offset)
      {
        int adpcm_ch = i - adpcmb_offset;

        if(chan[i].std.panL.val == 0)
        {
          chan[i].pan &= ~(1 << 1);
        }
        else
        {
          chan[i].pan |= (1 << 1);
          chan[i].panLeft = (3 - ((chan[i].std.panL.val - 1) & 3));
        }

        immWrite(adpcmb_offsets[adpcm_ch] + 0x1,(isMuted[i]?0:(chan[i].pan<<6))|2);
        immWrite(adpcmb_offsets[adpcm_ch] + 0x7,((chan[i].panRight & 3)<<4)|((chan[i].panLeft & 3)<<6));
      }
    }
    if (chan[i].std.panR.had) 
    {
      if(i < psg_offset)
      {
        if(chan[i].std.panR.val == 0)
        {
          chan[i].pan &= ~(1 << 0);
        }
        else
        {
          chan[i].pan |= (1 << 0);
          chan[i].panRight = (3 - ((chan[i].std.panR.val - 1) & 3));
        }

        writePan = true;
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        if(chan[i].std.panR.val == 0)
        {
          chan[i].pan &= ~(1 << 0);
        }
        else
        {
          chan[i].pan |= (1 << 0);
          chan[i].panRight = (7 - ((chan[i].std.panR.val - 1) & 7));
        }

        writePan = true;
      }
      if(i >= rhythm_offset && i < adpcma_offset)
      {
        if(chan[i].std.panR.val == 0)
        {
          chan[i].pan &= ~(1 << 0);
        }
        else
        {
          chan[i].pan |= (1 << 0);
          chan[i].panRight = (7 - ((chan[i].std.panR.val - 1) & 7));
        }

        rWrite(0x12 + i - rhythm_offset, chan[i].panRight | (chan[i].panLeft << 3));
      }
      if(i >= adpcma_offset && i < adpcmb_offset)
      {
        if(chan[i].std.panR.val == 0)
        {
          chan[i].pan &= ~(1 << 0);
        }
        else
        {
          chan[i].pan |= (1 << 0);
          chan[i].panRight = (3 - ((chan[i].std.panR.val - 1) & 3));
        }

        immWrite(0x115,isMuted[i]?0:(((chan[i].pan & 2) << 6) | ((chan[i].panLeft & 3) << 5) | ((chan[i].pan & 1) << 4) | ((chan[i].panRight & 3) << 2)));
      }
      if(i >= adpcmb_offset)
      {
        int adpcm_ch = i - adpcmb_offset;

        if(chan[i].std.panR.val == 0)
        {
          chan[i].pan &= ~(1 << 0);
        }
        else
        {
          chan[i].pan |= (1 << 0);
          chan[i].panRight = (3 - ((chan[i].std.panR.val - 1) & 3));
        }

        immWrite(adpcmb_offsets[adpcm_ch] + 0x1,(isMuted[i]?0:(chan[i].pan<<6))|2);
        immWrite(adpcmb_offsets[adpcm_ch] + 0x7,((chan[i].panRight & 3)<<4)|((chan[i].panLeft & 3)<<6));
      }
    }

    if(writePan)
    {
      if(i < psg_offset)
      {
        rWrite(chanOffs[i]+ADDR_FB_ALG,(chan[i].state.alg&7)|(chan[i].state.fb<<3)|((chan[i].panRight&3)<<6));
        rWrite(chanOffs[i]+ADDR_LRAF,(isMuted[i]?0:(chan[i].pan<<6))|(chan[i].state.fms&7)|((chan[i].state.ams&3)<<4)|(chan[i].state_ym2609fm.alg_construct_switch<<3));
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;

        rWrite(ssg_offsets[ssg_num] + 0xf, chan[i].panRight | (chan[i].panLeft << 3) | (chan_num << 6));
        rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[i].vol&15)|((chan[i].curPSGMode.getEnvelope())<<2)|(chan[i].pan << 6));
      }
      writePan = false;
    }

    if (chan[i].std.duty.had) {
      if(i >= psg_offset && i < rhythm_offset) //noise freq
      {
        int ssg_num = (i - psg_offset) / 3;

        rWrite(ssg_offsets[ssg_num]+0x06,255-chan[i].std.duty.val);
      }
      if(i >= rhythm_offset && i < adpcma_offset) //global RSS volume
      {
        if (globalRSSVolume!=(chan[i].std.duty.val&0x3f)) {
          globalRSSVolume=chan[i].std.duty.val&0x3f;
          immWrite(0x11,globalRSSVolume);
        }
      }
      if(i >= adpcma_offset && i < adpcmb_offset) //global RSS volume
      {
        if (globalADPCMAVolume!=(chan[i].std.duty.val&0x3f)) {
          globalADPCMAVolume=chan[i].std.duty.val&0x3f;
          immWrite(0x112,globalADPCMAVolume);
        }
      }
    }

    if(i >= rhythm_offset && i < adpcma_offset)
    {
      if (!isMuted[i] && (chan[i].std.vol.had || chan[i].std.panL.had || chan[i].std.panR.had)) {
        immWrite(0x18+(i-rhythm_offset),isMuted[i]?0:((chan[i].pan<<6)|chan[i].outVol));
      }
    }

    if (chan[i].std.wave.had) 
    {
      if(i >= psg_offset && i < rhythm_offset)
      {
        int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;

        chan[i].nextPSGMode.val=chan[i].std.wave.val&7;
        if (chan[i].active) {
          chan[i].curPSGMode.val=chan[i].nextPSGMode.val;
        }
        if (isMuted[i]) {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,0|(chan[i].pan << 6));
        } else {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[i].outVol&15)|((chan[i].nextPSGMode.getEnvelope())<<2)|(chan[i].pan << 6));

          rWrite(ssg_offsets[ssg_num]+0x07,
          ~((chan[12+ssg_num*3+0].curPSGMode.getTone())|
           ((chan[12 + ssg_num*3+1].curPSGMode.getTone())<<1)|
           ((chan[12 + ssg_num*3+2].curPSGMode.getTone())<<2)|
           ((chan[12 + ssg_num*3+0].curPSGMode.getNoise())<<2)|
           ((chan[12 + ssg_num*3+1].curPSGMode.getNoise())<<3)|
           ((chan[12 + ssg_num*3+2].curPSGMode.getNoise())<<4)));
        }
      }
    }

    if (chan[i].std.phaseReset.had) {
      if(i >= psg_offset && i < rhythm_offset)
      {
        int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;

        if(chan[i].std.phaseReset.val == 1)
        {
          if (isMuted[i]) {
            rWrite(ssg_offsets[ssg_num]+0x08+chan_num,0|(chan[i].pan << 6));
          } else {
            rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[i].outVol&15)|((chan[i].nextPSGMode.getEnvelope())<<2)|(chan[i].pan << 6)|(1 << 5));
          }
        }
      }
      if(i >= rhythm_offset && i < adpcmb_offset + 3)
      {
        if ((chan[i].std.phaseReset.val==1) && chan[i].active) {
          chan[i].keyOn=true;
        }
      }
    }

    if (chan[i].std.alg.had) {
      if(i < psg_offset)
      {
        chan[i].state.alg=chan[i].std.alg.val;
        rWrite(chanOffs[i]+ADDR_FB_ALG,(chan[i].state.alg&7)|(chan[i].state.fb<<3)|((chan[i].panRight&3)<<6));
        if (!parent->song.compatFlags.algMacroBehavior) for (int j=0; j<4; j++) {
          unsigned short baseAddr=chanOffs[i]|opOffs[j];
          DivInstrumentFM::Operator& op=chan[i].state.op[j];
          if (isMuted[i] || !op.enable) {
            rWrite(baseAddr+ADDR_TL,127|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
          } else {
            if (KVS(i,j)) {
              rWrite(baseAddr+ADDR_TL,(127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[i].outVol&0x7f,127))|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
            } else {
              rWrite(baseAddr+ADDR_TL,op.tl|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
            }
          }
        }
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        chan[i].autoEnvDen=chan[i].std.alg.val;
        chan[i].freqChanged=true;
        if (!chan[i].std.ex3.will) chan[i].autoEnvNum=1;
      }
    }
    if (chan[i].std.fb.had) {
      if(i < psg_offset)
      {
        chan[i].state.fb=chan[i].std.fb.val;
        rWrite(chanOffs[i]+ADDR_FB_ALG,(chan[i].state.alg&7)|(chan[i].state.fb<<3)|((chan[i].panRight&3)<<6));
      }
    }
    if (chan[i].std.fms.had) {
      if(i < psg_offset) //LFO1 FM depth
      {
        chan[i].state_ym2609fm.lfo_fm_depth[0]=chan[i].std.fms.val;
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[0] + 4, chan[i].state_ym2609fm.lfo_fm_depth[0]);
      }
    }
    if (chan[i].std.ams.had) {
      if(i < psg_offset) //LFO1 AM depth
      {
        chan[i].state_ym2609fm.lfo_am_depth[0]=chan[i].std.ams.val;
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[0] + 3, chan[i].state_ym2609fm.lfo_am_depth[0]);
      }
    }
    if (chan[i].std.ex1.had) {
      if(i < psg_offset)
      {
        chan[i].state_ym2609fm.alg_construct_switch=chan[i].std.ex1.val&1;
        rWrite(chanOffs[i]+ADDR_LRAF,(isMuted[i]?0:(chan[i].pan<<6))|(chan[i].state.fms&7)|((chan[i].state.ams&3)<<4)|(chan[i].state_ym2609fm.alg_construct_switch<<3));
      }
      if(i >= psg_offset && i < rhythm_offset) // wavetable index
      {
        int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;
        chan[i].wavetable = chan[i].std.ex1.val;
        chan[i].op_ym2609[0].ws.changeWave1(chan[i].wavetable, true);
        doUpdatePSGWave = true;
      }
    }
    if (chan[i].std.ex2.had) {
      if(i < psg_offset) //LFO2 FM depth
      {
        chan[i].state_ym2609fm.lfo_fm_depth[1]=chan[i].std.ex2.val;
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[1] + 4, chan[i].state_ym2609fm.lfo_fm_depth[1]);
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        int ssg_num = (i - psg_offset) / 3;

        ayEnvMode[ssg_num]=chan[i].std.ex2.val;
        rWrite(ssg_offsets[ssg_num]+0x0d,ayEnvMode[ssg_num]);
      }
    }
    if (chan[i].std.ex3.had) 
    {
      if(i < psg_offset) //LFO1 freq
      {
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[0] + 1, (chan[i].std.ex3.val >> 8) & 0xff);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[0] + 2, chan[i].std.ex3.val & 0xff);
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        chan[i].autoEnvNum=chan[i].std.ex3.val;
        chan[i].freqChanged=true;
        if (!chan[i].std.alg.will) chan[i].autoEnvDen=1;
      }
    }
    if (chan[i].std.ex4.had) {
      if(i < psg_offset)
      {
        chan[i].opMask=chan[i].std.ex4.val&15;
        chan[i].opMaskChanged=true;
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        chan[i].fixedFreq=chan[i].std.ex4.val;
        chan[i].freqChanged=true;
      }
    }
    if (chan[i].std.ex5.had) 
    {
      if(i < psg_offset) //LFO2 freq
      {
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[1] + 1, (chan[i].std.ex5.val >> 8) & 0xff);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[1] + 2, chan[i].std.ex5.val & 0xff);
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        int ssg_num = (i - psg_offset) / 3;

        ayEnvPeriod[ssg_num]=chan[i].std.ex5.val;
        rWrite(ssg_offsets[ssg_num]+0x0b,ayEnvPeriod[ssg_num]);
        rWrite(ssg_offsets[ssg_num]+0x0c,ayEnvPeriod[ssg_num]>>8);
      }
    }
    if (chan[i].std.ex6.had) {
      if(i < psg_offset) //LFO1 shape
      {
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0], (chan[i].std.ex6.val & 0xf) << 4);
        chan[i].lfoShape[0] = (chan[i].std.ex6.val & 0xf);
      }
      if(i >= psg_offset && i < rhythm_offset)
      {
        //int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;

        if(chan[i].std.ex6.val == 10) //custom wavetable
        {
          if(chan[i].wavetable != -1)
          {
            chan[i].duty = 10 + chan_num;
            chan[i].freqChanged = true;
          }
        }
        else
        {
          chan[i].duty = chan[i].std.ex6.val;
          chan[i].freqChanged = true;
        }
      }
    }
    if (chan[i].std.ex7.had) {
      if(i < psg_offset) //LFO2 shape
      {
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[1], (chan[i].std.ex7.val & 0xf) << 4);
        chan[i].lfoShape[1] = (chan[i].std.ex7.val & 0xf);
      }
    }
    if (chan[i].std.ex8.had) {
      if(i < psg_offset) //LFO1 phase reset
      {
        if(chan[i].std.ex8.val)
        {
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0], ((chan[i].lfoShape[0] & 0xf) << 4)|(1 << 3));
        }
      }
    }
    if (chan[i].std.ex9.had) {
      if(i < psg_offset) //LFO2 phase reset
      {
        if(chan[i].std.ex9.val)
        {
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[1], ((chan[i].lfoShape[1] & 0xf) << 4)|(1 << 3));
        }
      }
    }
    if (chan[i].std.ex10.had) {
      if(i < psg_offset) //LFO2 AM depth
      {
        chan[i].state_ym2609fm.lfo_am_depth[1]=chan[i].std.ex10.val;
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
        rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[1] + 3, chan[i].state_ym2609fm.lfo_am_depth[1]);
      }
    }
    if(i < psg_offset)
    {
      for (int j=0; j<4; j++) {
        unsigned short baseAddr=chanOffs[i]|opOffs[j];
        DivInstrumentFM::Operator& op=chan[i].state.op[j];
        DivInstrumentYM2609FM::Operator& op_ym2609=chan[i].state_ym2609fm.op[j];
        DivMacroInt::IntOp& m=chan[i].std.op[j];
        if (m.am.had) {
          op.am=m.am.val;
          rWrite(baseAddr+ADDR_AM_DR,(op.dr&31)|(op.am<<7)|(op.dt2<<5));
        }
        if (m.ar.had) {
          op.ar=m.ar.val;
          rWrite(baseAddr+ADDR_RS_AR,(op.ar&31)|(op.rs<<6));
        }
        if (m.dr.had) {
          op.dr=m.dr.val;
          rWrite(baseAddr+ADDR_AM_DR,(op.dr&31)|(op.am<<7)|(op.dt2<<5));
        }
        if (m.mult.had) {
          op.mult=m.mult.val;
          rWrite(baseAddr+ADDR_MULT_DT,(op.mult&15)|(dtTable[op.dt&7]<<4)|((chan[i].op_ym2609[j].wave_type & 1) << 7));
        }
        if (m.rr.had) {
          op.rr=m.rr.val;
          rWrite(baseAddr+ADDR_SL_RR,(op.rr&15)|(op.sl<<4));
        }
        if (m.sl.had) {
          op.sl=m.sl.val;
          rWrite(baseAddr+ADDR_SL_RR,(op.rr&15)|(op.sl<<4));
        }
        if (m.tl.had) {
          op.tl=m.tl.val;
          if (isMuted[i] || !op.enable) {
            rWrite(baseAddr+ADDR_TL,127|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
          } else {
            if (KVS(i,j)) {
              rWrite(baseAddr+ADDR_TL,(127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[i].outVol&0x7f,127))|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
            } else {
              rWrite(baseAddr+ADDR_TL,op.tl|(((chan[i].op_ym2609[j].wave_type >> 1) & 1) << 7));
            }
          }
        }
        if (m.rs.had) {
          op.rs=m.rs.val;
          rWrite(baseAddr+ADDR_RS_AR,(op.ar&31)|(op.rs<<6));
        }
        if (m.dt.had) {
          op.dt=m.dt.val;
          rWrite(baseAddr+ADDR_MULT_DT,(op.mult&15)|(dtTable[op.dt&7]<<4)|((chan[i].op_ym2609[j].wave_type & 1) << 7));
        }
        if (m.d2r.had) {
          op.d2r=m.d2r.val;
          rWrite(baseAddr+ADDR_DT2_D2R,(op.d2r&31)|(op_ym2609.feedback<<5));
        }
        if (m.dt2.had) {
          op.dt2=m.dt2.val;
          rWrite(baseAddr+ADDR_AM_DR,(op.dr&31)|(op.am<<7)|(op.dt2<<5));
        }
        if (m.ssg.had) {
          op.ssgEnv=m.ssg.val;
          rWrite(baseAddr+ADDR_SSG,(op.ssgEnv&15)|(op_ym2609.alg_link<<4));
        }
        if (m.egt.had) {
          op_ym2609.alg_link=m.egt.val;
          rWrite(baseAddr+ADDR_SSG,(op.ssgEnv&15)|(op_ym2609.alg_link<<4));
        }
        if(j != 0)
        {
          if (m.ksl.had) {
            op_ym2609.feedback=m.ksl.val;
            rWrite(baseAddr+ADDR_DT2_D2R,(op.d2r&31)|(op_ym2609.feedback<<5));
          }
        }
        if (m.dvb.had) {
          op.dvb=m.dvb.val & 0xf;
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xa + orderedOps[j], (op.dvb & 0xf) | ((op.dam & 0x7) << 4));
        }
        if (m.dam.had) {
          op.dam=m.dam.val & 7;
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);
          rWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xa + orderedOps[j], (op.dvb & 0xf) | ((op.dam & 0x7) << 4));
        }
      }
    }

    if(i >= psg_offset && i < rhythm_offset)
    {
      if (chan[i].active) 
      {
        if (chan[i].op_ym2609[0].ws.tick()) 
        {
          doUpdatePSGWave = true;
        }
      }

      if(doUpdatePSGWave && chan[i].wavetable != -1)
      {
        //updateWave();
        int ssg_num = (i - psg_offset) / 3;
        int chan_num = (i - psg_offset) % 3;

        immWrite(ssg_offsets[ssg_num]+0x0d,ayEnvMode[ssg_num]|(chan_num << 4)|(1 << 7 /*reset wave counter*/));

        for(int j = 0; j < 64; j++)
        {
          immWrite(ssg_offsets[ssg_num]+0x0e,chan[i].op_ym2609[0].ws.output[j] & 0xff);
        }

        doUpdatePSGWave = false;
      }
    }
  }

  for (int i=0; i<psg_offset; i++) {
    if ((i==2 || i==8) && extMode) continue;
    if (chan[i].keyOff) {
      rWrite(((i > 5) ? 0x228 : 0x28),0x00|konOffs[i % 6]);
      chan[i].keyOff=false;
    }
  }
    
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) 
  {
    if(i < psg_offset) //FM
    {
      if (chan[i].freqChanged) 
      {
        if (parent->song.compatFlags.linearPitch) 
        {
          chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,2,chan[i].pitch2,chipClock,CHIP_FREQBASE,11,chan[i].state.block);
        } 
        else 
        {
          int fNum=parent->calcFreq(chan[i].baseFreq&0x7ff,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,2,chan[i].pitch2,chipClock,CHIP_FREQBASE,11);
          int block=(chan[i].baseFreq&0xf800)>>11;
          if (fNum<0) fNum=0;
          if (fNum>2047) {
            while (block<7) {
              fNum>>=1;
              block++;
            }
            if (fNum>2047) fNum=2047;
          }
          chan[i].freq=(block<<11)|fNum;
        }
        if (chan[i].freq>0x3fff) chan[i].freq=0x3fff;
        //if (i<6) {
          rWrite(chanOffs[i]+ADDR_FREQH,((chan[i].freq>>8)&0x3f)|((chan[i].panLeft&3)<<6));
          rWrite(chanOffs[i]+ADDR_FREQ,chan[i].freq&0xff);
        //}
        chan[i].freqChanged=false;
      }

      if ((chan[i].keyOn || chan[i].opMaskChanged)) {
        if (i<6) {
          rWrite(0x28,(chan[i].opMask<<4)|konOffs[i]);
        }
        else if(i < psg_offset)
        {
          rWrite(0x228,(chan[i].opMask<<4)|konOffs[i-6]);
        }
        chan[i].opMaskChanged=false;
        chan[i].keyOn=false;
      }
    }

    if(i >= psg_offset && i < rhythm_offset) //SSG
    {
      int ssg_num = (i - psg_offset) / 3;
      int chan_num = (i - psg_offset) % 3;
      if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) {
        chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,true,0,chan[i].pitch2,chipClock,32);

        if (chan[i].freq<0) chan[i].freq=0;
        if (chan[i].freq>4095) chan[i].freq=4095;
        if (chan[i].fixedFreq>4095) chan[i].fixedFreq=4095;
        if (chan[i].keyOn) 
        {
          chan[i].curPSGMode.val=chan[i].nextPSGMode.val;

          rWrite(ssg_offsets[ssg_num]+0x07,
          ~((chan[12+ssg_num*3+0].curPSGMode.getTone())|
           ((chan[12 + ssg_num*3+1].curPSGMode.getTone())<<1)|
           ((chan[12 + ssg_num*3+2].curPSGMode.getTone())<<2)|
           ((chan[12 + ssg_num*3+0].curPSGMode.getNoise())<<2)|
           ((chan[12 + ssg_num*3+1].curPSGMode.getNoise())<<3)|
           ((chan[12 + ssg_num*3+2].curPSGMode.getNoise())<<4)));
        }
        if (chan[i].keyOff) {
          chan[i].curPSGMode.val=0;
          //chan[i].vol=0;
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,0|(chan[i].pan << 6));

          rWrite(ssg_offsets[ssg_num]+0x07,
          ~((chan[12+ssg_num*3+0].curPSGMode.getTone())|
           ((chan[12 + ssg_num*3+1].curPSGMode.getTone())<<1)|
           ((chan[12 + ssg_num*3+2].curPSGMode.getTone())<<2)|
           ((chan[12 + ssg_num*3+0].curPSGMode.getNoise())<<2)|
           ((chan[12 + ssg_num*3+1].curPSGMode.getNoise())<<3)|
           ((chan[12 + ssg_num*3+2].curPSGMode.getNoise())<<4)));
        }
        if (chan[i].fixedFreq>0) {
          rWrite(ssg_offsets[ssg_num]+((chan_num)<<1),chan[i].fixedFreq&0xff);
          rWrite(ssg_offsets[ssg_num]+1+((chan_num)<<1),(chan[i].fixedFreq>>8)|(chan[i].duty << 4));
        } else {
          rWrite(ssg_offsets[ssg_num]+((chan_num)<<1),chan[i].freq&0xff);
          rWrite(ssg_offsets[ssg_num]+1+((chan_num)<<1),(chan[i].freq>>8)|(chan[i].duty << 4));
        }
        if (chan[i].keyOn) chan[i].keyOn=false;
        if (chan[i].keyOff) chan[i].keyOff=false;
        if (chan[i].freqChanged && chan[i].autoEnvNum>0 && chan[i].autoEnvDen>0) {
          ayEnvPeriod[ssg_num]=(chan[i].freq*chan[i].autoEnvDen/chan[i].autoEnvNum)>>4;
          immWrite(ssg_offsets[ssg_num]+0x0b,ayEnvPeriod[ssg_num]);
          immWrite(ssg_offsets[ssg_num]+0x0c,ayEnvPeriod[ssg_num]>>8);
        }
        chan[i].freqChanged=false;
      }
    }

    if(i >= rhythm_offset && i < adpcma_offset)
    {
      if (chan[i].keyOff) {
        writeRSSOff|=(1<<(i-(rhythm_offset)));
        chan[i].keyOff=false;
      }
      if (chan[i].keyOn) {
        writeRSSOn|=(1<<(i-(rhythm_offset)));
        chan[i].keyOn=false;
      }
    }

    if(i >= adpcmb_offset)
    {
      int adpcm_ch = i - adpcmb_offset;

      if(chan[i].freqChanged)
      {
        if (chan[i].sample>=0 && chan[i].sample<parent->song.sampleLen) {
          double off=65535.0*(double)(parent->getSample(chan[i].sample)->centerRate)/parent->getCenterRate();

          double clock_divider = (144.0 * 8.0 / 16.0);

          chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,4,chan[i].pitch2,(double)chipClock/clock_divider,off);
        } else {
          chan[i].freq=0;
        }
        if (chan[i].freq<0) chan[i].freq=0;
        if (chan[i].freq>65535) chan[i].freq=65535;
        immWrite(adpcmb_offsets[adpcm_ch] + 0x9,chan[i].freq&0xff);
        immWrite(adpcmb_offsets[adpcm_ch] + 0xa,(chan[i].freq>>8)&0xff);
        chan[i].freqChanged = false;
      }

      if (chan[i].keyOn || chan[i].keyOff) {
        immWrite(adpcmb_offsets[adpcm_ch],0x01); // reset
        if (chan[i].active && chan[i].keyOn && !chan[i].keyOff) {
          if (chan[i].sample>=0 && chan[i].sample<parent->song.sampleLen) {
            DivSample* s=parent->getSample(chan[i].sample);
            immWrite(adpcmb_offsets[adpcm_ch],(s->isLoopable())?0x90:0x80); // start/repeat
          }
        }
        chan[i].keyOn=false;
        chan[i].keyOff=false;
      }
    }
  }

  for(int i = rhythm_offset; i < adpcma_offset; i++)
  {
    if (writeRSSOff) {
      immWrite(0x10,0x80|writeRSSOff);
      //hardResetElapsed++;
      writeRSSOff=0;
    }

    if (writeRSSOn) {
      immWrite(0x10,writeRSSOn);
      //hardResetElapsed++;
      writeRSSOn=0;
    }
  }
  for(int i = adpcma_offset; i < adpcmb_offset; i++)
  {
    if (chan[i].keyOff) {
      writeADPCMAOff|=(1<<(i-adpcma_offset));
      chan[i].keyOff=false;
    }
    if (chan[i].keyOn) {
      if (chan[i].sample>=0 && chan[i].sample<parent->song.sampleLen) {
        writeADPCMAOn|=(1<<(i-adpcma_offset));
      }
      chan[i].keyOn=false;
    }
  }
  if (writeADPCMAOff) {
    immWrite(0x111,0x80|writeADPCMAOff);
    writeADPCMAOff=0;
  }

  if (writeADPCMAOn) {
    immWrite(0x111,writeADPCMAOn);
    writeADPCMAOn=0;
  }
}

void DivPlatformYM2609::commitState(int ch, DivInstrument* ins) {
  if (chan[ch].insChanged) 
  {
    chan[ch].state=ins->fm;
    chan[ch].state_ym2609fm=ins->ym2609.ym2609fm;

    chan[ch].opMask=
      (chan[ch].state.op[0].enable?1:0)|
      (chan[ch].state.op[2].enable?2:0)|
      (chan[ch].state.op[1].enable?4:0)|
      (chan[ch].state.op[3].enable?8:0);
  }

  rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + 0xe, ch % 6);
  
  for (int i=0; i<4; i++) 
  {
    unsigned short baseAddr=chanOffs[ch]|opOffs[i];
    DivInstrumentFM::Operator& op=chan[ch].state.op[i];
    DivInstrumentYM2609FM::Operator& op_ym2609=chan[ch].state_ym2609fm.op[i];
    if (isMuted[ch] || !op.enable) {
      if (chan[ch].insChanged) {
        rWrite(baseAddr+ADDR_TL,127|(((chan[ch].op_ym2609[i].wave_type >> 1) & 1) << 7));
      }
    } else {
      if (KVS(ch,i)) {
        if (!chan[ch].active || chan[ch].insChanged) {
          rWrite(baseAddr+ADDR_TL,(127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[ch].outVol&0x7f,127))|(((chan[ch].op_ym2609[i].wave_type >> 1) & 1) << 7));
        }
      } else {
        if (chan[ch].insChanged) {
          rWrite(baseAddr+ADDR_TL,op.tl|(((chan[ch].op_ym2609[i].wave_type >> 1) & 1) << 7));
        }
      }
    }
    if (chan[ch].insChanged) {
      rWrite(baseAddr+ADDR_MULT_DT,(op.mult&15)|(dtTable[op.dt&7]<<4)|((chan[ch].op_ym2609[i].wave_type & 1) << 7));
      rWrite(baseAddr+ADDR_RS_AR,(op.ar&31)|(op.rs<<6)|((op_ym2609.phase_reset & 1) << 5));
      rWrite(baseAddr+ADDR_AM_DR,(op.dr&31)|(op.am<<7)|(op.dt2<<5));

      /*if(i != 0)
      {
        rWrite(baseAddr+ADDR_DT2_D2R,(op.d2r&31)|(op_ym2609.feedback<<5));
      }
      else
      {
        rWrite(baseAddr+ADDR_DT2_D2R,(op.d2r&31));
      }*/

      rWrite(baseAddr+ADDR_DT2_D2R,(op.d2r&31)|(op_ym2609.feedback<<5));
      
      rWrite(baseAddr+ADDR_SL_RR,(op.rr&15)|(op.sl<<4));
      rWrite(baseAddr+ADDR_SSG,(op.ssgEnv&15)|(op_ym2609.alg_link<<4));

      rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + 0xa + i, (chan[ch].state.op[orderedOps[i]].dvb & 0xf) | ((chan[ch].state.op[orderedOps[i]].dam & 0x7) << 4));
    }
  }
  if (chan[ch].insChanged) {
    rWrite(chanOffs[ch]+ADDR_FB_ALG,(chan[ch].state.alg&7)|(chan[ch].state.fb<<3)|((chan[ch].panRight&3)<<6));
    rWrite(chanOffs[ch]+ADDR_LRAF,(isMuted[ch]?0:(chan[ch].pan<<6))|(chan[ch].state.fms&7)|((chan[ch].state.ams&3)<<4)|(chan[ch].state_ym2609fm.alg_construct_switch<<3));
    chan[ch].freqChanged = true; //to write left soft pan

    //LFO...
    //rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + 0xe, ch % 6);
    rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + LFOSettings_ofsets[0] + 3, chan[ch].state_ym2609fm.lfo_am_depth[0]);
    rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + LFOSettings_ofsets[0] + 4, chan[ch].state_ym2609fm.lfo_fm_depth[0]);
    rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + LFOSettings_ofsets[1] + 3, chan[ch].state_ym2609fm.lfo_am_depth[1]);
    rWrite(LFOBase_ofsets[ch > 5 ? 1 : 0] + LFOSettings_ofsets[1] + 4, chan[ch].state_ym2609fm.lfo_fm_depth[1]);
  }
}

//0-11:FM 12-23:SSG 24-26:ADPCM 27-32:Rhythm 33-38:ADPCM-A
static int get_dsp_chan_index(int ch)
{
  if(ch < 12 + 12) return ch; //fm, psg
  if(ch >= 12 + 12 + 6 + 6) return (ch - (12 + 12 + 6 + 6) + 24); //adpcm-b
  if(ch >= 12 + 12 && ch < 12 + 12 + 6) return (ch - (12 + 12) + 27); //rhythm
  if(ch >= 12 + 12 + 6 && ch < 12 + 12 + 6 + 6) return (ch - (12 + 12 + 6) + 33); //adpcm-a

  return 0;
}

//0-11:SSG 12-23:FM 24-29:Rhythm 30-35:ADPCM-A 36-38:ADPCM-B
static int get_phase_inv_chan_index(int ch)
{
  if(ch < 12) return ch + 12; //fm
  if(ch >= 12 && ch < 12 + 12) return (ch - 12); //psg
  if(ch >= 12 + 12 && ch < 12 + 12 + 6 + 6 + 3) return ch; //rhythm, ADPCM-A, ADPCM-B

  return 0;
}

int DivPlatformYM2609::dispatch(DivCommand c) {
  if (c.chan>YM2609_NUM_CHANNELS - 1) return 0;

  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_FM);

      if(ins->ym2609.ym2609dsp.enable)
      {
        DivInstrumentYM2609DSP& dsp = ins->ym2609.ym2609dsp;

        if (dsp.phase_inv_right != chan[c.chan].state_ym2609dsp.phase_inv_right || chan[c.chan].state_ym2609dsp.phase_inv_left != dsp.phase_inv_left)
        {
          int phase_inv_chan = get_phase_inv_chan_index(c.chan);
          int our_base_chan = c.chan - c.chan % 3;

          chan[c.chan].state_ym2609dsp.phase_inv_left = dsp.phase_inv_left;
          chan[c.chan].state_ym2609dsp.phase_inv_right = dsp.phase_inv_right;

          rWrite(0xCC + phase_inv_chan / 3, ((chan[our_base_chan].state_ym2609dsp.phase_inv_left ? 1 : 0) << 1) | (chan[our_base_chan].state_ym2609dsp.phase_inv_right ? 1 : 0) |
            ((chan[our_base_chan + 1].state_ym2609dsp.phase_inv_left ? 1 : 0) << 3) | ((chan[our_base_chan + 1].state_ym2609dsp.phase_inv_right ? 1 : 0) << 2) |
            ((chan[our_base_chan + 2].state_ym2609dsp.phase_inv_left ? 1 : 0) << 5) | ((chan[our_base_chan + 2].state_ym2609dsp.phase_inv_right ? 1 : 0) << 4));
        }
        
        if(dsp.enable)
        {
          //rWrite(0x323, get_dsp_chan_index(c.chan) | (dsp.reset_all ? 0x80 : 0));
          rWrite(0x323, get_dsp_chan_index(c.chan));

          chan[c.chan].state_ym2609dsp.lpf_on = dsp.lpf_on;
          chan[c.chan].state_ym2609dsp.hpf_on = dsp.hpf_on;
          chan[c.chan].state_ym2609dsp.distortion_enable = dsp.distortion_enable;
          chan[c.chan].state_ym2609dsp.chorus_enable = dsp.chorus_enable;
          chan[c.chan].state_ym2609dsp.ins_compressor_on = dsp.ins_compressor_on;

          if(dsp.lpf_on)
          {
            rWrite(0x3c0, 1);

            if(dsp.lpf_init)
            {
              rWrite(0x3c1, dsp.lpf_cutoff);
              rWrite(0x3c2, dsp.lpf_q);

              chan[c.chan].state_ym2609dsp.lpf_cutoff = dsp.lpf_cutoff;
              chan[c.chan].state_ym2609dsp.lpf_q = dsp.lpf_q;
            }
          }
          else
          {
            rWrite(0x3c0, 0);
          }

          if(dsp.hpf_on)
          {
            rWrite(0x3c3, 1);

            if(dsp.hpf_init)
            {
              rWrite(0x3c4, dsp.hpf_cutoff);
              rWrite(0x3c5, dsp.hpf_q);

              chan[c.chan].state_ym2609dsp.hpf_cutoff = dsp.hpf_cutoff;
              chan[c.chan].state_ym2609dsp.hpf_q = dsp.hpf_q;
            }
          }
          else
          {
            rWrite(0x3c3, 0);
          }

          if(dsp.distortion_enable)
          {
            rWrite(0x325, 0x80 | (dsp.distortion_output_level));
            rWrite(0x326, dsp.distortion_gain);
            rWrite(0x327, dsp.distortion_cutoff);

            chan[c.chan].state_ym2609dsp.distortion_output_level = dsp.distortion_output_level;
            chan[c.chan].state_ym2609dsp.distortion_gain = dsp.distortion_gain;
            chan[c.chan].state_ym2609dsp.distortion_cutoff = dsp.distortion_cutoff;
          }
          else
          {
            rWrite(0x325, chan[c.chan].state_ym2609dsp.distortion_output_level);
          }

          if(dsp.chorus_enable)
          {
            rWrite(0x328, 0x80 | (dsp.chorus_mixlevel));
            rWrite(0x329, dsp.chorus_rate);
            rWrite(0x32A, dsp.chorus_depth);
            rWrite(0x32B, dsp.chorus_feedback);

            chan[c.chan].state_ym2609dsp.chorus_mixlevel = dsp.chorus_mixlevel;
            chan[c.chan].state_ym2609dsp.chorus_rate = dsp.chorus_rate;
            chan[c.chan].state_ym2609dsp.chorus_depth = dsp.chorus_depth;
            chan[c.chan].state_ym2609dsp.chorus_feedback = dsp.chorus_feedback;
          }
          else
          {
            rWrite(0x328, chan[c.chan].state_ym2609dsp.chorus_mixlevel);
          }

          if(dsp.ins_compressor_on)
          {
            rWrite(0x3C6, chan[c.chan].state_ym2609dsp.ins_compressor_volume | 0x80);
            rWrite(0x3C7, chan[c.chan].state_ym2609dsp.ins_compressor_threshold);
            rWrite(0x3C8, chan[c.chan].state_ym2609dsp.ins_compressor_ratio);
            rWrite(0x3C9, chan[c.chan].state_ym2609dsp.ins_compressor_env_freq);
            rWrite(0x3CA, chan[c.chan].state_ym2609dsp.ins_compressor_env_q);
            rWrite(0x3CB, chan[c.chan].state_ym2609dsp.ins_compressor_gain_freq);
            rWrite(0x3CC, chan[c.chan].state_ym2609dsp.ins_compressor_gain_q);

            chan[c.chan].state_ym2609dsp.ins_compressor_volume = dsp.ins_compressor_volume;
            chan[c.chan].state_ym2609dsp.ins_compressor_threshold = dsp.ins_compressor_threshold;
            chan[c.chan].state_ym2609dsp.ins_compressor_ratio = dsp.ins_compressor_ratio;
            chan[c.chan].state_ym2609dsp.ins_compressor_env_freq = dsp.ins_compressor_env_freq;
            chan[c.chan].state_ym2609dsp.ins_compressor_env_q = dsp.ins_compressor_env_q;
            chan[c.chan].state_ym2609dsp.ins_compressor_gain_freq = dsp.ins_compressor_gain_freq;
            chan[c.chan].state_ym2609dsp.ins_compressor_gain_q = dsp.ins_compressor_gain_q;
          }
          else
          {
            rWrite(0x3C6, chan[c.chan].state_ym2609dsp.ins_compressor_volume);
          }
        }
      }

      if(ins->ym2609.ym2609dsp.enable_global)
      {
        DivInstrumentYM2609DSP& dsp = ins->ym2609.ym2609dsp;

        if(dsp.eq_on)
        {
          if(dsp.eq_low_on)
          {
            rWrite(0xC0, 1);
            rWrite(0xC1, dsp.eq_low_freq);
            rWrite(0xC2, dsp.eq_low_gain);
            rWrite(0xC3, dsp.eq_low_q);

            chan[c.chan].state_ym2609dsp.eq_low_freq = dsp.eq_low_freq;
            chan[c.chan].state_ym2609dsp.eq_low_gain = dsp.eq_low_gain;
            chan[c.chan].state_ym2609dsp.eq_low_q = dsp.eq_low_q;
          }
          else
          {
            rWrite(0xC0, 0);
          }

          if(dsp.eq_mid_on)
          {
            rWrite(0xC4, 1);
            rWrite(0xC5, dsp.eq_mid_freq);
            rWrite(0xC6, dsp.eq_mid_gain);
            rWrite(0xC7, dsp.eq_mid_q);

            chan[c.chan].state_ym2609dsp.eq_mid_freq = dsp.eq_mid_freq;
            chan[c.chan].state_ym2609dsp.eq_mid_gain = dsp.eq_mid_gain;
            chan[c.chan].state_ym2609dsp.eq_mid_q = dsp.eq_mid_q;
          }
          else
          {
            rWrite(0xC4, 0);
          }

          if(dsp.eq_high_on)
          {
            rWrite(0xC8, 1);
            rWrite(0xC9, dsp.eq_high_freq);
            rWrite(0xCA, dsp.eq_high_gain);
            rWrite(0xCB, dsp.eq_high_q);

            chan[c.chan].state_ym2609dsp.eq_high_freq = dsp.eq_high_freq;
            chan[c.chan].state_ym2609dsp.eq_high_gain = dsp.eq_high_gain;
            chan[c.chan].state_ym2609dsp.eq_high_q = dsp.eq_high_q;
          }
          else
          {
            rWrite(0xC8, 0);
          }
        }
        else
        {
          rWrite(0xC0, 0);
          rWrite(0xC4, 0);
          rWrite(0xC8, 0);
        }

        if(dsp.compressor_on)
        {
          chan[c.chan].state_ym2609dsp.compressor_volume = dsp.compressor_volume;
          chan[c.chan].state_ym2609dsp.compressor_threshold = dsp.compressor_threshold;
          chan[c.chan].state_ym2609dsp.compressor_ratio = dsp.compressor_ratio;
          chan[c.chan].state_ym2609dsp.compressor_env_freq = dsp.compressor_env_freq;
          chan[c.chan].state_ym2609dsp.compressor_env_q = dsp.compressor_env_q;
          chan[c.chan].state_ym2609dsp.compressor_gain_freq = dsp.compressor_gain_freq;
          chan[c.chan].state_ym2609dsp.compressor_gain_q = dsp.compressor_gain_q;
          
          rWrite(0x1C0, chan[c.chan].state_ym2609dsp.compressor_volume | 0x80);
          rWrite(0x1C1, chan[c.chan].state_ym2609dsp.compressor_threshold);
          rWrite(0x1C2, chan[c.chan].state_ym2609dsp.compressor_ratio);
          rWrite(0x1C3, chan[c.chan].state_ym2609dsp.compressor_env_freq);
          rWrite(0x1C4, chan[c.chan].state_ym2609dsp.compressor_env_q);
          rWrite(0x1C5, chan[c.chan].state_ym2609dsp.compressor_gain_freq);
          rWrite(0x1C6, chan[c.chan].state_ym2609dsp.compressor_gain_q);
        }
        else
        {
          rWrite(0x1C0, chan[c.chan].state_ym2609dsp.compressor_volume);
        }
      }

      if(c.chan < psg_offset) //FM
      {
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_FM);

        chan[c.chan].macroInit(ins);
        if (!chan[c.chan].std.vol.will) {
          chan[c.chan].outVol=chan[c.chan].vol;
        }

        commitState(c.chan,ins);
        chan[c.chan].insChanged=false;

        int reg_shift = (c.chan) > 5 ? 0x200 : 0;
        double log2 = log(2.0);

        for(int i = 0; i < 4; i++)
        {
          if(ins->ym2609.ym2609fm.op[i].custom_wave)
          {
            chan[c.chan].op_ym2609[i].ws.init(NULL,1024,8191,false);
            chan[c.chan].op_ym2609[i].ws.changeWave1(ins->ym2609.ym2609fm.op[i].custom_wave_index, true);

            //set wave channel and wave type
            immWrite(reg_shift+0x2B,((c.chan&0xf) << 4)|(i&3));

            for(int j = 0; j < 1024; j++)
            {
              uint16_t val = chan[c.chan].op_ym2609[i].ws.output[j & 1023];
              uint16_t val_abs = val > 4095 ? val : (((int)val - 4096) * -1 + 4096);
              double qqq = -256 * log(((float)val_abs / 4096.0f - 1.0f)) / log2;
              uint32_t sssss = (uint32_t)((int)(floor(qqq + 0.5)) + 1);

              uint16_t final = val > 4095 ? sssss * 2 : (sssss * 2 + 1);

              if(val == 4096) final = 0x1800; //otherwise spikes to max or min amp on this value...

              immWrite(reg_shift+0x2C, final & 0xff);
              immWrite(reg_shift+0x2C,(final >> 8) & 0x1F);
            }
          }
          else
          {
            //reset to sine wave
            rWrite(reg_shift+0x2B,((c.chan&0xf) << 4)|(i&3)|0b100);
          }
        }

        if (!chan[c.chan].std.vol.will) {
          chan[c.chan].outVol=chan[c.chan].vol;
        }

        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].baseFreq=NOTE_FNUM_BLOCK(c.value,11,chan[c.chan].state.block);
          chan[c.chan].portaPause=false;
          chan[c.chan].freqChanged=true;
          chan[c.chan].note=c.value;
        }

        chan[c.chan].active=true;
        chan[c.chan].keyOn=true;

        break;
      }
      if(c.chan >= psg_offset && c.chan < rhythm_offset) //SSG
      {
        int chan_num = (c.chan - 12) % 3;
        int ssg_num = (c.chan - 12) / 3;
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_SSG);

        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].sampleNote=DIV_NOTE_NULL;
          chan[c.chan].sampleNoteDelta=0;
          chan[c.chan].baseFreq=NOTE_PERIODIC(c.value);
          chan[c.chan].freqChanged=true;
          chan[c.chan].note=c.value;
        }
        chan[c.chan].fixedFreq=0;
        chan[c.chan].active=true;
        chan[c.chan].keyOn=true;
        chan[c.chan].macroInit(ins);

        chan[c.chan].op_ym2609[0].ws.init(ins,64,255,false);

        if (!parent->song.compatFlags.brokenOutVol && !chan[c.chan].std.vol.will) {
          chan[c.chan].outVol=chan[c.chan].vol;
        }

        if (isMuted[c.chan]) {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,0|(chan[c.chan].pan << 6));
        } else {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[c.chan].vol&15)|((chan[c.chan].nextPSGMode.getEnvelope())<<2)|(chan[c.chan].pan << 6));
        }

        rWrite(ssg_offsets[ssg_num]+0x07,
          ~((chan[12+ssg_num*3+0].curPSGMode.getTone())|
           ((chan[12+ssg_num*3+1].curPSGMode.getTone())<<1)|
           ((chan[12+ssg_num*3+2].curPSGMode.getTone())<<2)|
           ((chan[12+ssg_num*3+0].curPSGMode.getNoise())<<2)|
           ((chan[12+ssg_num*3+1].curPSGMode.getNoise())<<3)|
           ((chan[12+ssg_num*3+2].curPSGMode.getNoise())<<4)));
        break;
      }
      if(c.chan >= rhythm_offset && c.chan < adpcma_offset) //RSS
      {
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_RSS);
        chan[c.chan].macroVolMul = 31;
        //chan[c.chan].macroVolMul=(ins->type==DIV_INS_AMIGA)?64:31;
        //if (skipRegisterWrites) break;
        chan[c.chan].outVol = 0;
        
        chan[c.chan].macroInit(ins);
        if (!chan[c.chan].std.vol.will) 
        {
          chan[c.chan].outVol=chan[c.chan].vol;
          immWrite(0x18+(c.chan-(rhythm_offset)),isMuted[c.chan]?0:((chan[c.chan].pan<<6)|chan[c.chan].outVol));
        }
        chan[c.chan].active=true;
        chan[c.chan].keyOn=true;
        break;
      }
      if(c.chan >= adpcma_offset && c.chan < adpcmb_offset) //ADPCM-A
      {
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_ADPCM_A);
        chan[c.chan].macroVolMul=31;
        if (skipRegisterWrites) break;
        chan[c.chan].macroInit(ins);
        if (!chan[c.chan].std.vol.will) {
          chan[c.chan].outVol=chan[c.chan].vol;
        }
        if (c.value!=DIV_NOTE_NULL) chan[c.chan].sample=ins->amiga.getSample(c.value);

        if(!sampleLoaded[0][chan[c.chan].sample]) break;

        immWrite(0x113,c.chan-adpcma_offset);

        if (chan[c.chan].sample>=0 && chan[c.chan].sample<parent->song.sampleLen) 
        {
          DivSample* s=parent->getSample(chan[c.chan].sample);
          immWrite(0x116,(sampleOffA[chan[c.chan].sample]>>8)&0xff);
          immWrite(0x116,sampleOffA[chan[c.chan].sample]>>16);
          int end=sampleOffA[chan[c.chan].sample]+s->lengthA-1;
          immWrite(0x117,(end>>8)&0xff);
          immWrite(0x117,end>>16);
          immWrite(0x114,isMuted[c.chan]?0:(chan[c.chan].outVol));
          immWrite(0x115,isMuted[c.chan]?0:(((chan[c.chan].pan & 2) << 6) | ((chan[c.chan].panLeft & 3) << 5) | ((chan[c.chan].pan & 1) << 4) | ((chan[c.chan].panRight & 3) << 2)));
          if (c.value!=DIV_NOTE_NULL) {
            chan[c.chan].note=c.value;
            chan[c.chan].baseFreq=NOTE_ADPCMB(c.chan, chan[c.chan].note);
            chan[c.chan].freqChanged=true;
          }
          chan[c.chan].active=true;
          chan[c.chan].keyOn=true;
        } else {
          writeADPCMAOff|=(1<<(c.chan-adpcma_offset));
          /*immWrite(0x110+c.chan-adpcma_offset,0);
          immWrite(0x118+c.chan-adpcma_offset,0);
          immWrite(0x120+c.chan-adpcma_offset,0);
          immWrite(0x128+c.chan-adpcma_offset,0);*/
          break;
        }
        break;
      }
      if(c.chan >= adpcmb_offset) // ADPCM-B
      {
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_ADPCM_B);
        int adpcm_ch = c.chan - adpcmb_offset;
        int addr_bit_shift = adpcm_ch == 0 ? 5 : 8;

        chan[c.chan].macroVolMul=255;
        if (skipRegisterWrites) break;
        chan[c.chan].macroInit(ins);
        if (!chan[c.chan].std.vol.will) {
          chan[c.chan].outVol=chan[c.chan].vol;
          immWrite(adpcmb_offsets[adpcm_ch] + 0xb,chan[c.chan].outVol);
        }
        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].sample=ins->amiga.getSample(c.value);
          chan[c.chan].sampleNote=c.value;
          c.value=ins->amiga.getFreq(c.value);
          chan[c.chan].sampleNoteDelta=c.value-chan[c.chan].sampleNote;
        }

        if(!sampleLoaded[1 + adpcm_ch][chan[c.chan].sample]) break;

        if (chan[c.chan].sample>=0 && chan[c.chan].sample<parent->song.sampleLen) {
          DivSample* s=parent->getSample(chan[c.chan].sample);
          immWrite(adpcmb_offsets[adpcm_ch] + 0x2,(sampleOffB[adpcm_ch][chan[c.chan].sample]>>addr_bit_shift)&0xff);
          immWrite(adpcmb_offsets[adpcm_ch] + 0x3,sampleOffB[adpcm_ch][chan[c.chan].sample]>>(addr_bit_shift + 8));
          int end=sampleOffB[adpcm_ch][chan[c.chan].sample]+s->lengthB-1;
          immWrite(adpcmb_offsets[adpcm_ch] + 0x4,(end>>addr_bit_shift)&0xff);
          immWrite(adpcmb_offsets[adpcm_ch] + 0x5,end>>(addr_bit_shift + 8));
          immWrite(adpcmb_offsets[adpcm_ch] + 0x1,(isMuted[c.chan]?0:(chan[c.chan].pan<<6))|2);

          if(!isMuted[c.chan])
          {
            immWrite(adpcmb_offsets[adpcm_ch] + 0x7,((chan[c.chan].panRight & 3)<<4)|((chan[c.chan].panLeft & 3)<<6));
          }

          if (c.value!=DIV_NOTE_NULL) {
            chan[c.chan].note=c.value;
            chan[c.chan].baseFreq=NOTE_ADPCMB(c.chan, chan[c.chan].note);
            chan[c.chan].freqChanged=true;
          }
          chan[c.chan].active=true;
          chan[c.chan].keyOn=true;
        } else {
          immWrite(adpcmb_offsets[adpcm_ch],0x01); // reset
          immWrite(adpcmb_offsets[adpcm_ch] + 0x2,0);
          immWrite(adpcmb_offsets[adpcm_ch] + 0x3,0);
          immWrite(adpcmb_offsets[adpcm_ch] + 0x4,0);
          immWrite(adpcmb_offsets[adpcm_ch] + 0x5,0);
          break;
        }
        break;
      }
    }
    case DIV_CMD_NOTE_OFF:
      if(c.chan < psg_offset || (c.chan >= rhythm_offset && c.chan < adpcmb_offset))
      {
        chan[c.chan].active=false;
        chan[c.chan].keyOff=true;
        chan[c.chan].keyOn=false;
      }
      if(c.chan >= psg_offset && c.chan < rhythm_offset) //SSG
      {
        chan[c.chan].active=false;
        chan[c.chan].keyOff=true;
        chan[c.chan].macroInit(NULL);
      }
      break;
    case DIV_CMD_NOTE_OFF_ENV:
      if(c.chan < psg_offset || (c.chan >= rhythm_offset && c.chan < adpcmb_offset))
      { 
        chan[c.chan].active=false;
        chan[c.chan].keyOff=true;
        chan[c.chan].keyOn=false;
        chan[c.chan].std.release();
      }
      if(c.chan >= psg_offset && c.chan < rhythm_offset) //SSG
      {
        chan[c.chan].std.release();
      }
      break;
    case DIV_CMD_ENV_RELEASE:
      chan[c.chan].std.release();
      break;
    case DIV_CMD_INSTRUMENT:
      if (chan[c.chan].ins!=c.value || c.value2==1) {
        chan[c.chan].insChanged=true;
        chan[c.chan].ins=c.value;
      }
      break;
    case DIV_CMD_VOLUME:
      chan[c.chan].vol=c.value;
      if (!chan[c.chan].std.vol.has) {
        chan[c.chan].outVol=c.value;
      }
      if (c.chan < psg_offset)
      {
        for (int i=0; i<4; i++) 
        {
          unsigned short baseAddr=chanOffs[c.chan]|opOffs[i];
          DivInstrumentFM::Operator& op=chan[c.chan].state.op[i];
          if (isMuted[c.chan] || !op.enable) {
            rWrite(baseAddr+ADDR_TL,127|(((chan[c.chan].op_ym2609[i].wave_type >> 1) & 1) << 7));
          } else {
            if (KVS(c.chan,i)) {
              rWrite(baseAddr+ADDR_TL,(127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[c.chan].outVol&0x7f,127))|(((chan[c.chan].op_ym2609[i].wave_type >> 1) & 1) << 7));
            } else {
              rWrite(baseAddr+ADDR_TL,op.tl|(((chan[c.chan].op_ym2609[i].wave_type >> 1) & 1) << 7));
            }
          }
        }
      }
      if (c.chan >= psg_offset && c.chan < rhythm_offset)
      {
        int chan_num = (c.chan - 12) % 3;
        int ssg_num = (c.chan - 12) / 3;

        if (isMuted[c.chan]) {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,0|(chan[c.chan].pan << 6));
          break;
        } else {
          rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[c.chan].outVol&15)|((chan[c.chan].nextPSGMode.getEnvelope())<<2)|(chan[c.chan].pan << 6));
          break;
        }
      }
      if(c.chan >= rhythm_offset && c.chan < adpcma_offset)
      {
        immWrite(0x18+(c.chan-(rhythm_offset)),isMuted[c.chan]?0:((chan[c.chan].pan<<6)|chan[c.chan].outVol));
        break;
      }
      if(c.chan >= adpcma_offset && c.chan < adpcmb_offset) // ADPCM-A
      { 
        immWrite(0x113,c.chan-adpcma_offset);
        immWrite(0x114,isMuted[c.chan]?0:(chan[c.chan].outVol));
        break;
      }
      if(c.chan >= adpcmb_offset && !isMuted[c.chan])
      {
        immWrite(adpcmb_offsets[c.chan-adpcmb_offset] + 0xb,chan[c.chan].outVol);
        break;
      }
      break;
    case DIV_CMD_GET_VOLUME:
      if (chan[c.chan].std.vol.has) {
        return chan[c.chan].vol;
      }
      return chan[c.chan].outVol;
      break;
    case DIV_CMD_PITCH:
      chan[c.chan].pitch=c.value;
      chan[c.chan].freqChanged=true;
      break;
    case DIV_CMD_NOTE_PORTA: {
      if(c.chan < psg_offset) //FM
      {
        if (parent->song.compatFlags.linearPitch) {
          int destFreq=NOTE_FREQUENCY(c.value2+chan[c.chan].sampleNoteDelta);
          bool return2=false;
          if (destFreq>chan[c.chan].baseFreq) {
            chan[c.chan].baseFreq+=c.value;
            if (chan[c.chan].baseFreq>=destFreq) {
              chan[c.chan].baseFreq=destFreq;
              return2=true;
            }
          } else {
            chan[c.chan].baseFreq-=c.value;
            if (chan[c.chan].baseFreq<=destFreq) {
              chan[c.chan].baseFreq=destFreq;
              return2=true;
            }
          }
          chan[c.chan].freqChanged=true;
          if (return2) {
            chan[c.chan].inPorta=false;
            return 2;
          }
          break;
        }
        PLEASE_HELP_ME(chan[c.chan],chan[c.chan].state.block);
      }
      else if(c.chan >= psg_offset && c.chan < rhythm_offset) //PSG
      {
        int destFreq=NOTE_PERIODIC(c.value2+chan[c.chan].sampleNoteDelta);
        bool return2=false;
        if (destFreq>chan[c.chan].baseFreq) {
          chan[c.chan].baseFreq+=c.value;
          if (chan[c.chan].baseFreq>=destFreq) {
            chan[c.chan].baseFreq=destFreq;
            return2=true;
          }
        } else {
          chan[c.chan].baseFreq-=c.value;
          if (chan[c.chan].baseFreq<=destFreq) {
            chan[c.chan].baseFreq=destFreq;
            return2=true;
          }
        }
        chan[c.chan].freqChanged=true;
        if (return2) {
          chan[c.chan].inPorta=false;
          return 2;
        }
      }
      if (c.chan>=adpcmb_offset) 
      { // ADPCM-B
        int destFreq=NOTE_ADPCMB(c.chan, c.value2+chan[c.chan].sampleNoteDelta);
        bool return2=false;
        if (destFreq>chan[c.chan].baseFreq) {
          chan[c.chan].baseFreq+=c.value;
          if (chan[c.chan].baseFreq>=destFreq) {
            chan[c.chan].baseFreq=destFreq;
            return2=true;
          }
        } else {
          chan[c.chan].baseFreq-=c.value;
          if (chan[c.chan].baseFreq<=destFreq) {
            chan[c.chan].baseFreq=destFreq;
            return2=true;
          }
        }
        chan[c.chan].freqChanged=true;
        if (return2) {
          chan[c.chan].inPorta=false;
          return 2;
        }
        break;
      }
      break;
    }
    case DIV_CMD_LEGATO:
      if(c.chan < psg_offset) //FM
      {
        if (chan[c.chan].insChanged) {
          DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_FM);
          commitState(c.chan,ins);
          chan[c.chan].insChanged=false;
        }
        chan[c.chan].baseFreq=NOTE_FNUM_BLOCK(c.value,11,chan[c.chan].state.block);
        chan[c.chan].note=c.value;
        chan[c.chan].freqChanged=true;
        break;
      }
      else if((c.chan >= psg_offset && c.chan < rhythm_offset)) //PSG
      {
        chan[c.chan].baseFreq=NOTE_PERIODIC(c.value);
        chan[c.chan].freqChanged=true;
        break;
      }
      if(c.chan >= adpcmb_offset) //ADPCM-B
      {
        chan[c.chan].baseFreq=NOTE_ADPCMB(c.chan, c.value+chan[c.chan].sampleNoteDelta);
        chan[c.chan].freqChanged=true;
        break;
      }
      break;
    case DIV_CMD_PRE_PORTA:
      if(c.chan < psg_offset) //FM
      {
        if (chan[c.chan].active && c.value2) {
          if (parent->song.compatFlags.resetMacroOnPorta || parent->song.compatFlags.preNoteNoEffect) {
            chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_YM2609_FM));
            chan[c.chan].keyOn=true;
          }
        }
        if (!chan[c.chan].inPorta && c.value && !parent->song.compatFlags.brokenPortaArp && chan[c.chan].std.arp.will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=NOTE_FREQUENCY(chan[c.chan].note);
      }
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_FM_LFO: {
      if (c.chan>=psg_offset) break;
      //lfoValue[c.chan > 5 ? 1 : 0]=(c.value&7)|((c.value>>4)<<3);
      //rWrite(c.chan > 5 ? 0x200 : 0 + 0x22,lfoValue[c.chan > 5 ? 1 : 0]);
      break;
    }
    case DIV_CMD_GET_VOLMAX:
      if (c.chan>(11+12+6+6)) return 255; //adpcm-b
      if (c.chan>(11+12+6)) return 31; //adpcm-a
      if (c.chan>(11+12)) return 31; //rhythm
      if (c.chan>11) return 15; //psg
      return 127; //fm
      break;
    case DIV_CMD_WAVE:
      
      break;
    case DIV_CMD_MACRO_OFF:
      chan[c.chan].std.mask(c.value,true);
      break;
    case DIV_CMD_MACRO_ON:
      chan[c.chan].std.mask(c.value,false);
      break;
    case DIV_CMD_MACRO_RESTART:
      chan[c.chan].std.restart(c.value);
      break;
    default:
      break;
  }
  return 1;
}

void DivPlatformYM2609::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
  if (ch>=adpcmb_offset) { // ADPCM-B
    immWrite(adpcmb_offsets[ch-adpcmb_offset] + 0x1,(isMuted[ch]?0:(chan[ch].pan<<6))|2);
    return;
  }
  if (ch>=adpcma_offset && ch < adpcmb_offset) { // ADPCM-A
    immWrite(0x113,ch-adpcma_offset);
    immWrite(0x115,isMuted[ch]?0:(((chan[ch].pan & 2) << 6) | ((chan[ch].panLeft & 3) << 5) | ((chan[ch].pan & 1) << 4) | ((chan[ch].panRight & 3) << 2)));
    return;
  }
  if (ch>=rhythm_offset && ch < adpcma_offset) { // RSS
    immWrite(0x18+(ch-(rhythm_offset)),isMuted[ch]?0:((chan[ch].pan<<6)|chan[ch].outVol));
    return;
  }
  if (ch>=psg_offset && ch < rhythm_offset) { // PSG
    int ssg_num = (ch - psg_offset) / 3;
    int chan_num = (ch - psg_offset) % 3;

    if(isMuted[ch])
    {
      rWrite(ssg_offsets[ssg_num]+0x08+chan_num,((chan[ch].nextPSGMode.getEnvelope())<<2));
    }
    else
    {
      rWrite(ssg_offsets[ssg_num]+0x08+chan_num,(chan[ch].outVol&15)|((chan[ch].nextPSGMode.getEnvelope())<<2)|(chan[ch].pan << 6));
    }
    return;
  }
  // FM
  if(ch<psg_offset)
  {
    for (int j=0; j<4; j++) {
      unsigned short baseAddr=chanOffs[ch]|opOffs[j];
      DivInstrumentFM::Operator& op=chan[ch].state.op[j];
      DivInstrumentYM2609FM::Operator& op_ym2609=chan[ch].state_ym2609fm.op[j];
      if (isMuted[ch] || !op.enable) {
        rWrite(baseAddr+ADDR_TL,127|(((chan[ch].op_ym2609[j].wave_type >> 1) & 1) << 7));
      } else {
        if (KVS(ch,j)) {
          rWrite(baseAddr+ADDR_TL,(127-VOL_SCALE_LOG_BROKEN(127-op.tl,chan[ch].outVol&0x7f,127))|(((chan[ch].op_ym2609[j].wave_type >> 1) & 1) << 7));
        } else {
          rWrite(baseAddr+ADDR_TL,op.tl|(((chan[ch].op_ym2609[j].wave_type >> 1) & 1) << 7));
        }
      }
    }
    rWrite(chanOffs[ch]+ADDR_LRAF,(isMuted[ch]?0:(chan[ch].pan<<6))|(chan[ch].state.fms&7)|((chan[ch].state.ams&3)<<4));
  }
}

void DivPlatformYM2609::forceIns() {
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) {
    chan[i].insChanged=true;
    if (chan[i].active) {
      chan[i].keyOn=true;
      chan[i].freqChanged=true;
    }
    chan[i].curPSGMode.val&=~8;
    chan[i].nextPSGMode.val&=~8;
  }

  //rWrite(0x22,lfoValue[0]);
  //rWrite(0x222,lfoValue[1]);

  immWrite(0x11,globalRSSVolume&0x3f);
  immWrite(0x112,globalADPCMAVolume&0x3f);

  for (int i=rhythm_offset; i<adpcma_offset; i++) {
    chan[i].insChanged=true;
    //if (i>(14+isCSM)) { // ADPCM-B
    //  immWrite(0x10b,chan[i].outVol);
    //} else {
      immWrite(0x18+(i-(rhythm_offset)),isMuted[i]?0:((chan[i].pan<<6)|chan[i].outVol));
    //}
  }
}

void DivPlatformYM2609::notifyInsChange(int ins) {
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) {
    if (chan[i].ins==ins) {
      chan[i].insChanged=true;
    }
  }
}

void DivPlatformYM2609::notifyWaveChange(int wave) 
{
  /*if (chan[YM2609_NUM_CHANNELS - 1].wavetable == wave)
  {
    ws.changeWave1(wave, false);
    updateWave();
  }*/
}

void DivPlatformYM2609::notifyInsDeletion(void* ins) {
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

SharedChannel* DivPlatformYM2609::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformYM2609::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivChannelModeHints DivPlatformYM2609::getModeHints(int ch) {
  DivChannelModeHints ret;
  /*ret.count=1;
  ret.hint[0]=ICON_FA_BELL_SLASH_O;
  ret.type[0]=0;
  if (!chan[ch].gate) {
    ret.type[0]=4;
  }*/

  return ret;
}

DivDispatchOscBuffer* DivPlatformYM2609::getOscBuffer(int ch) {
  return oscBuf[ch];
}

unsigned short DivPlatformYM2609::getPan(int ch) {
  if(ch > psg_offset || ch <= rhythm_offset)
  {
    int pan_right = (chan[ch].pan & 1) ? (3 - chan[ch].panRight + 1) : 0;
    int pan_left = (chan[ch].pan & 2) ? (3 - chan[ch].panLeft + 1) : 0;
    return (pan_left<<8)|pan_right;
  }
  else //SSG
  {
    int pan_right = (chan[ch].pan & 1) ? (7 - chan[ch].panRight + 1) : 0;
    int pan_left = (chan[ch].pan & 2) ? (7 - chan[ch].panLeft + 1) : 0;
    return (pan_left<<8)|pan_right;
  }
}

unsigned char* DivPlatformYM2609::getRegisterPool() {
  return regPool;
}

int DivPlatformYM2609::getRegisterPoolSize() {
  return YM2609_NUM_REGISTERS;
}

float DivPlatformYM2609::getPostAmp() {
  return 1.0f;
}

int get_max_vol(int chan)
{
  if (chan>(11+12+6+6)) return 255; //adpcm-b
  if (chan>(11+12+6)) return 31; //adpcm-a
  if (chan>(11+12)) return 31; //rhythm
  if (chan>11) return 15; //psg
  return 127; //fm
}

void DivPlatformYM2609::reset() {
  while (!writes.empty()) writes.pop();
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) {
    chan[i]=DivPlatformYM2609::Channel();
    chan[i].std.setEngine(parent);
    chan[i].vol=get_max_vol(i);
    chan[i].outVol=get_max_vol(i);

    chan[i].panLeft = 0;
    chan[i].panRight = 0;

    chan[i].duty = 0;
    chan[i].wavetable = -1;

    chan[i].sample = -1;

    chan[i].state = DivInstrumentFM();
    chan[i].state_ym2609fm = DivInstrumentYM2609FM();
    chan[i].state_ym2609dsp = DivInstrumentYM2609DSP();

    for(int j = 0; j < 4; j++)
    {
      chan[i].op_ym2609[j] = DivPlatformYM2609::Channel::Operator_YM2609();

      chan[i].op_ym2609[j].ws.setEngine(parent);
      chan[i].op_ym2609[j].ws.init(NULL,1024,8191,false);

      chan[i].op_ym2609[j].wave_type = j;
    }
  }

  for(int i = 0; i < 4; i++)
  {
    ayEnvMode[i] = 0;
    ayEnvPeriod[i] = 0;
    ayEnvSlideLow[i] = 0;
    ayEnvSlide[i] = 0;
  }

  writeADPCMAOff=0;
  writeADPCMAOn=0;
  globalADPCMAVolume=0x3f;

  writeRSSOff=0;
  writeRSSOn=0;
  globalRSSVolume=0x3f;

  //ym2609->Init(YM2609_CLOCK, YM2609_CLOCK);
  ym2609->Reset();

  //ws.setEngine(parent);
  //ws.init(NULL,256,255,false);

  //sid3_reset(sid3);
  memset(regPool,0,YM2609_NUM_REGISTERS);

  //lfoValue[0]=8;
  //lfoValue[1]=8;

  // LFO
  for(int i = 0; i < 12; i++)
  {
    immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xe, i % 6);

    immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xa, 0);
    immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xb, 0);
    immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xc, 0);
    immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + 0xd, 0);

    for(int j = 0; j < 2; j++)
    {
      immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[j], 0);
      immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[j] + 1, 0);
      immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[j] + 2, 0);
      immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[j] + 3, 0);
      immWrite(LFOBase_ofsets[i > 5 ? 1 : 0] + LFOSettings_ofsets[j] + 4, 0);
    }
  }

  // RSS volume
  immWrite(0x11,globalRSSVolume); //RSS

  // RSS panpot
  for(int i = 0; i < 6; i++)
  {
    immWrite(0x12+i, 0);
  }

  // ADPCM-A volume
  immWrite(0x112,globalADPCMAVolume); //ADPCM-A

  // ADPCM-A panpot
  for(int i = 0; i < 6; i++)
  {
    immWrite(0x113, i);
    immWrite(0x115, 0);
  }

  //DSP reset
  for(int i = 0; i < 39; i++)
  {
    immWrite(0x323, i | 0x80); //reset chorus, reverb, LPF&HPF, channel compressors
  }
  
  //DSP reset
  for(int i = 0; i < 13; i++)
  {
    immWrite(0xCC + i, 0); //reset phase inversion
  }
}

int DivPlatformYM2609::getOutputCount() {
  return 2;
}

bool DivPlatformYM2609::hasSoftPan(int ch) {
  return true;
}

bool DivPlatformYM2609::getDCOffRequired()
{
  return false;
}

void DivPlatformYM2609::poke(unsigned int addr, unsigned short val) {
  rWrite(addr,val);
}

void DivPlatformYM2609::poke(std::vector<DivRegWrite>& wlist) {
  for (DivRegWrite& i: wlist) rWrite(i.addr,i.val);
}

void DivPlatformYM2609::setFlags(const DivConfig& flags) {
  chipClock=YM2609_CLOCK;
  rate=YM2609_DSP_RATE; //TODO: map somehow?

  clocks_per_sample = (int)ceil((double)chipClock / (double)rate);
  
    // Prescaler flags
  switch (flags.getInt("prescale",0)) {
    case 0x01: // /3
      prescale=0x2e;
      fmFreqBase=9440540.0/2.0;
      fmDivBase=36;
      /*ayDiv=16;
      nukedMult=16;*/
      break;
    case 0x02: // /2
      prescale=0x2f;
      fmFreqBase=9440540.0/3.0;
      fmDivBase=24;
      /*ayDiv=8;
      nukedMult=24;*/
      break;
    default: // /6
      prescale=0x2d;
      fmFreqBase=9440540.0;
      fmDivBase=72;
      /*ayDiv=32;
      nukedMult=8;*/
      break;
  }

  immWrite(0x2d,0xff);
  immWrite(prescale,0xff);

  // enable 6 channel mode
  immWrite(0x29,0x80);

  // enable 6 channel mode
  immWrite(0x229,0x80);
  
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) {
    oscBuf[i]->setRate(rate);
  }
}

void DivPlatformYM2609::getPaired(int ch, std::vector<DivChannelPair>& ret)
{
  
}

const DivMemoryComposition* DivPlatformYM2609::getMemCompo(int index) {
  if (index==0) return &memCompoA;
  if (index==1) return &memCompoB[0];
  if (index==2) return &memCompoB[1];
  if (index==3) return &memCompoB[2];
  return NULL;
}

const void* DivPlatformYM2609::getSampleMem(int index) {
  if(index == 0) return adpcma_buf;
  if(index == 1) return ym2609->get_adpcmb_buf_pointer(0);
  if(index == 2) return ym2609->get_adpcmb_buf_pointer(1);
  if(index == 3) return ym2609->get_adpcmb_buf_pointer(2);
  return NULL;
}

size_t DivPlatformYM2609::getSampleMemCapacity(int index) {
  if(index == 0) return 0x1000000;
  if(index == 1) return 0x40000;
  if(index == 2) return 0x1000000;
  if(index == 3) return 0x1000000;
  return 0;
}

const char* DivPlatformYM2609::getSampleMemName(int index) {
  if(index == 0) return "ADPCM-A";
  if(index == 1) return "ADPCM-B 1";
  if(index == 2) return "ADPCM-B 2";
  if(index == 3) return "ADPCM-B 3";
  return NULL;
}

size_t DivPlatformYM2609::getSampleMemUsage(int index) {
  if(index == 0) return adpcmAMemLen;
  if(index == 1) return adpcmBMemLen[0];
  if(index == 2) return adpcmBMemLen[1];
  if(index == 3) return adpcmBMemLen[2];
  return NULL;
}

bool DivPlatformYM2609::isSampleLoaded(int index, int sample) {
  if (index<0 || index>3) return false;
  if (sample<0 || sample>32767) return false;
  return sampleLoaded[index][sample];
}

void DivPlatformYM2609::renderSamples(int sysID)
{
  memset(adpcma_buf,0,getSampleMemCapacity(0));
  memset(ym2609->get_adpcmb_buf_pointer(0),0,getSampleMemCapacity(1));
  memset(ym2609->get_adpcmb_buf_pointer(1),0,getSampleMemCapacity(2));
  memset(ym2609->get_adpcmb_buf_pointer(2),0,getSampleMemCapacity(3));
  memset(sampleOffA,0,32768*sizeof(unsigned int));
  memset(sampleOffB[0],0,32768*sizeof(unsigned int));
  memset(sampleOffB[1],0,32768*sizeof(unsigned int));
  memset(sampleOffB[2],0,32768*sizeof(unsigned int));
  memset(sampleLoaded[0],0,32768*sizeof(bool));
  memset(sampleLoaded[1],0,32768*sizeof(bool));
  memset(sampleLoaded[2],0,32768*sizeof(bool));
  memset(sampleLoaded[3],0,32768*sizeof(bool));

  memCompoA=DivMemoryComposition();
  memCompoA.name="ADPCM-A";

  memCompoB[0]=DivMemoryComposition();
  memCompoB[0].name="ADPCM-B 1";
  memCompoB[1]=DivMemoryComposition();
  memCompoB[1].name="ADPCM-B 2";
  memCompoB[2]=DivMemoryComposition();
  memCompoB[2].name="ADPCM-B 3";

  size_t memPos=0;
  for (int i=0; i<parent->song.sampleLen; i++) 
  {
    DivSample* s=parent->song.sample[i];
    if (!s->renderOn[0][sysID]) {
      sampleOffA[i]=0;
      continue;
    }

    int paddedLen=(s->lengthA+255)&(~0xff);
    if ((memPos&0xf00000)!=((memPos+paddedLen)&0xf00000)) {
      memPos=(memPos+0xfffff)&0xf00000;
    }
    if (memPos>=getSampleMemCapacity(0)) {
      logW("out of ADPCM-A memory for sample %d!",i);
      break;
    }
    if (memPos+paddedLen>=getSampleMemCapacity(0)) {
      memcpy(adpcma_buf+memPos,s->dataA,getSampleMemCapacity(0)-memPos);
      logW("out of ADPCM-A memory for sample %d!",i);
    } else {
      memcpy(adpcma_buf+memPos,s->dataA,paddedLen);
      sampleLoaded[0][i]=true;
    }
    sampleOffA[i]=memPos;
    memCompoA.entries.push_back(DivMemoryEntry(DIV_MEMORY_SAMPLE,"Sample",i,memPos,memPos+paddedLen));
    memPos+=paddedLen;
  }
  adpcmAMemLen=memPos+256;

  memCompoA.used=adpcmAMemLen;
  memCompoA.capacity=getSampleMemCapacity(0);

  for(int m = 0; m < 3; m++)
  {
    unsigned char* adpcmBMem = ym2609->get_adpcmb_buf_pointer(m);

    memset(adpcmBMem,0,getSampleMemCapacity(1+m));

    memPos=0;
    for (int i=0; i<parent->song.sampleLen; i++) {
      DivSample* s=parent->song.sample[i];
      if (!s->renderOn[1+m][sysID]) {
        sampleOffB[m][i]=0;
        continue;
      }

      int paddedLen=(s->lengthB+255)&(~0xff);
      if ((memPos&0xf00000)!=((memPos+paddedLen)&0xf00000)) {
        memPos=(memPos+0xfffff)&0xf00000;
      }
      if (memPos>=getSampleMemCapacity(1+m)) {
        logW("out of ADPCM-B %d memory for sample %d!",m+1,i);
        break;
      }
      if (memPos+paddedLen>=getSampleMemCapacity(1+m)) {
        memcpy(adpcmBMem+memPos,s->dataB,getSampleMemCapacity(1+m)-memPos);
        logW("out of ADPCM-B %d memory for sample %d!",m+1,i);
      } else {
        memcpy(adpcmBMem+memPos,s->dataB,paddedLen);
        sampleLoaded[1+m][i]=true;
      }
      sampleOffB[m][i]=memPos;
      memCompoB[m].entries.push_back(DivMemoryEntry(DIV_MEMORY_SAMPLE,_("Sample"),i,memPos,memPos+paddedLen));
      memPos+=paddedLen;
    }
    adpcmBMemLen[m]=memPos+256;

    memCompoB[m].used=adpcmBMemLen[m];
    memCompoB[m].capacity=getSampleMemCapacity(1+m);
  }
}

int DivPlatformYM2609::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;
  writeOscBuf=0;

  output_buf = new int*[2];

  output_buf[0] = new int[1];
  output_buf[1] = new int[1];

  adpcma_buf = new uint8_t[0x1000000];
  adpcma_buf_size = 0x1000000;

  sampleOffA=new unsigned int[32768];
  sampleOffB[0]=new unsigned int[32768];
  sampleOffB[1]=new unsigned int[32768];
  sampleOffB[2]=new unsigned int[32768];
  sampleLoaded[0]=new bool[32768];
  sampleLoaded[1]=new bool[32768];
  sampleLoaded[2]=new bool[32768];
  sampleLoaded[3]=new bool[32768];
  
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) 
  {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }

  psg_offset = 12;
  rhythm_offset = 12 + 12;
  adpcma_offset = 12 + 12 + 6;
  adpcmb_offset = 12 + 12 + 6 + 6;

  extMode = false;

  rev = new reverb(YM2609_DSP_RATE * 4, 39);
  dist = new distortion(YM2609_DSP_RATE, 39);
  chor = new chorus(YM2609_DSP_RATE, 39);
  eq = new eq3band(YM2609_DSP_RATE);
  filt = new HPFLPF(YM2609_DSP_RATE * 2, 39); //so that filter doesn't glitch out on highest cutoffs
  reph = new ReversePhase();
  comp = new Compressor(YM2609_DSP_RATE, 39);

  ym2609 = new OPNA2(0, rev, dist, chor, eq, filt, reph, comp);

  ym2609->Init(YM2609_CLOCK, YM2609_DSP_RATE, false, adpcma_buf, adpcma_buf_size);

  setFlags(flags);

  reset();

  return YM2609_NUM_CHANNELS;
}

void DivPlatformYM2609::quit() {
  for (int i=0; i<YM2609_NUM_CHANNELS; i++) 
  {
    delete oscBuf[i];
  }
  if (ym2609!=NULL)
  {
    delete rev;
    delete dist;
    delete chor;
    delete eq;
    delete filt;
    delete reph;
    delete comp;
    delete ym2609;
    ym2609 = NULL;
  }

  delete[] output_buf[0];
  delete[] output_buf[1];
  delete[] output_buf;

  //delete[] adpcma_buf;
  adpcma_buf_size = 0;
}

DivPlatformYM2609::~DivPlatformYM2609() {
  delete[] sampleOffA;
  delete[] sampleOffB[0];
  delete[] sampleOffB[1];
  delete[] sampleOffB[2];
  delete[] sampleLoaded[0];
  delete[] sampleLoaded[1];
  delete[] sampleLoaded[2];
  delete[] sampleLoaded[3];
}
