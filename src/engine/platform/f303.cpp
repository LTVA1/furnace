/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2025 tildearrow and contributors
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

#include "f303.h"
#include "../engine.h"
#include "IconsFontAwesome4.h"
#include <math.h>
#include "../../ta-log.h"

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }

#define CHIP_FREQBASE (524288 / 2 / 2 / 2 / 2 / 2)
#define CHIP_DIVIDER 1

#define CURRENT_FREQ_IN_HZ() ((double)chipClock / pow(2.0, (double)SID3_ACC_BITS) * (double)chan[i].freq)
#define c_5_FREQ() (parent->song.tuning / pow(2, (12.0 * 9.0 + 9.0) / 12.0))
#define FREQ_FOR_NOTE(note) (c_5_FREQ() * pow(2, (double)note / 12.0))

void DivPlatformF303::acquire(short** buf, size_t len) 
{
  while (!writes.empty()) 
  {
    QueuedWrite w=writes.front();

    switch(w.addr & 0xff)
    {
      case WRITE_SAMPLE_OFF:
      {
        f303->chan[((w.addr >> 8) & 0xFF)].sample_start_addr = w.val;
        break;
      }
      case WRITE_SAMPLE_LEN:
      {
        f303->chan[((w.addr >> 8) & 0xFF)].sample_length = w.val;
        break;
      }
      case WRITE_FREQ:
      {
        if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
        {
          f303->chan[((w.addr >> 8) & 0xFF)].freq = w.val;
        }
        else //noise chan
        {
          f303->noise.freq = w.val;
        }
        break;
      }
      case WRITE_WAVETABLE_MODE:
      {
        f303->chan[((w.addr >> 8) & 0xFF)].use_wavetable = w.val;
        break;
      }
      case WRITE_SAMPLE_LOOP:
      {
        f303->chan[((w.addr >> 8) & 0xFF)].sample_loop = w.val;
        break;
      }
      case WRITE_VOLUME:
      {
        if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
        {
          f303->chan[((w.addr >> 8) & 0xFF)].volume = w.val;
        }
        else //noise chan
        {
          f303->noise.volume = w.val;
        }
        break;
      }
      case WRITE_PAN_RIGHT:
      {
        if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
        {
          f303->chan[((w.addr >> 8) & 0xFF)].pan_right = w.val;
        }
        else //noise chan
        {
          f303->noise.pan_right = w.val;
        }
        break;
      }
      case WRITE_PAN_LEFT:
      {
        if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
        {
          f303->chan[((w.addr >> 8) & 0xFF)].pan_left = w.val;
        }
        else //noise chan
        {
          f303->noise.pan_left = w.val;
        }
        break;
      }
      case WRITE_ACC:
      {
        if(((w.addr >> 8) & 0xFF) < F303_NUM_CHANNELS - 1)
        {
          f303->chan[((w.addr >> 8) & 0xFF)].acc = w.val;
        }
        else //noise chan
        {
          f303->noise.acc = w.val;
        }
        break;
      }
      case WRITE_NOISE_LFSR_BITS:
      {
        if(((w.addr >> 8) & 0xFF) == F303_NUM_CHANNELS - 1)
        {
          f303->noise.lfsr_taps = w.val;
        }
        break;
      }
      case WRITE_NOISE_LFSR_VALUE:
      {
        if(((w.addr >> 8) & 0xFF) == F303_NUM_CHANNELS - 1)
        {
          f303->noise.lfsr = w.val;
        }
        break;
      }
      default: break;
    }

    writes.pop();
  }

  for (int i=0; i<F303_NUM_CHANNELS; i++) 
  {
    oscBuf[i]->begin(len);
  }

  for (size_t i=0; i<len; i++) 
  {
    f303_clock(f303);

    buf[0][i]=f303->output_l;
    buf[1][i]=f303->output_r;

    for(int j = 0; j < F303_NUM_CHANNELS - 1; j++)
    {
      oscBuf[j]->putSample(i, f303->chan[j].muted ? 0 : (f303->chan[j].chan_output * 127));
    }

    oscBuf[F303_NUM_CHANNELS - 1]->putSample(i,f303->noise.muted ? 0 : (f303->noise.chan_output * 127));
  }

  for (int i=0; i<F303_NUM_CHANNELS; i++) {
    oscBuf[i]->end(len);
  }
}

void DivPlatformF303::updateWave(int chan)
{
  for(int i = 0; i < 256; i++)
  {
    uint8_t val = ws[chan].output[i & 255];
    f303->chan[chan].wavetable[i] = val;
  }
}

size_t DivPlatformF303::getSampleMemUsage(int index) {
  return index == 0 ? sampleMemLen : 0;
}

bool DivPlatformF303::isSampleLoaded(int index, int sample) {
  if (index!=0) return false;
  if (sample<0 || sample>32767) return false;
  return sampleLoaded[sample];
}

const DivMemoryComposition* DivPlatformF303::getMemCompo(int index) {
  if (index!=0) return NULL;
  return &memCompo;
}

const void* DivPlatformF303::getSampleMem(int index) {
  return index == 0 ? sampleMem : NULL;
}

size_t DivPlatformF303::getSampleMemCapacity(int index) {
  return index == 0 ? (65536 * 2) : 0;
}

void DivPlatformF303::renderSamples(int sysID) {
  memset(sampleMem,0,getSampleMemCapacity());
  memset(sampleOff,0,32768*sizeof(unsigned int));
  memset(sampleLen,0,32768*sizeof(unsigned int));
  memset(sampleLoaded,0,32768*sizeof(bool));

  memCompo=DivMemoryComposition();
  memCompo.name="Sample Memory";

  size_t memPos=0;
  for (int i=0; i<parent->song.sampleLen; i++) {
    DivSample* s=parent->song.sample[i];
    if (!s->renderOn[0][sysID]) {
      sampleOff[i]=0;
      continue;
    }

    int length=s->getLoopEndPosition(DIV_SAMPLE_DEPTH_8BIT);
    int actualLength=MIN((int)(getSampleMemCapacity()-memPos),length);
    if (actualLength>0) {
      sampleOff[i]=memPos;
      sampleLen[i]=s->length8;
      memCompo.entries.push_back(DivMemoryEntry(DIV_MEMORY_SAMPLE,"Sample",i,memPos,memPos+actualLength));
      /*for (int j=0; j<actualLength; j++) {
        // convert to signed magnitude
        signed char val=s->data8[j];
        CLAMP_VAR(val,-127,126);
        sampleMem[memPos++]=(val>0)?(val|0x80):(0-val);
      }*/
      // write end of sample marker
      //memset(&sampleMem[memPos],0xff,32);
      //memPos+=32;
      for (int j=0; j<actualLength; j++) {
        int8_t val = s->data8[j];
        sampleMem[memPos] = (uint8_t)((int)s->data8[j] + 0x80);
        memPos++;
      }
    }
    if (actualLength<length) {
      logW("out of PCM memory for sample %d!",i);
      break;
    }
    sampleLoaded[i]=true;
  }
  sampleMemLen=memPos;

  memCompo.used=sampleMemLen;
  memCompo.capacity=getSampleMemCapacity(0);
}

void DivPlatformF303::tick(bool sysTick) 
{
  for (int i = 0; i < F303_NUM_CHANNELS; i++)
  {
    bool doUpdateWave = false;

    chan[i].std.next();

    DivInstrument* ins = parent->getIns(chan[i].ins, DIV_INS_F303);

    if (chan[i].std.vol.had && chan[i].outVol != VOL_SCALE_LINEAR(chan[i].vol & 255, MIN(255, chan[i].std.vol.val), 255))
    {
      chan[i].outVol = VOL_SCALE_LINEAR(chan[i].vol & 255, MIN(255, chan[i].std.vol.val), 255);

      rWrite((i << 8) | WRITE_VOLUME, chan[i].outVol);
    }
    if (NEW_ARP_STRAT) 
    {
      chan[i].handleArp();
    }
    else if (chan[i].std.arp.had) 
    {
      if (!chan[i].inPorta) 
      {
        chan[i].baseFreq = NOTE_FREQUENCY(parent->calcArp(chan[i].note, chan[i].std.arp.val));
      }
      chan[i].freqChanged = true;
    }
    if (chan[i].std.pitch.had) 
    {
      if (chan[i].std.pitch.mode) 
      {
        chan[i].pitch2 += chan[i].std.pitch.val;
        CLAMP_VAR(chan[i].pitch2, -65535, 65535);
      }
      else 
      {
        chan[i].pitch2 = chan[i].std.pitch.val;
      }
      chan[i].freqChanged = true;
    }
    if (chan[i].std.wave.had) 
    {
      if(i < F303_NUM_CHANNELS - 1 && !ins->amiga.useSample && chan[i].waveform != (chan[i].std.wave.val & 0x3))
      {
        chan[i].waveform = chan[i].std.wave.val & 0x3;

        rWrite((i << 8) | WRITE_WAVE_TYPE, chan[i].waveform);

        switch(chan[i].waveform)
        {
          case F303_WAVE_CUSTOM:
          {
            doUpdateWave = true;
            break;
          }
          case F303_WAVE_PULSE:
          {
            for(int j = 0; j < 256; j++)
            {
              f303->chan[i].wavetable[j] = j < chan[i].duty ? 0 : 0xFF;
            }
            break;
          }
          case F303_WAVE_SAWTOOTH:
          {
            for(int j = 0; j < 256; j++)
            {
              f303->chan[i].wavetable[j] = j;
            }
            break;
          }
          case F303_WAVE_TRIANGLE:
          {
            for(int j = 0; j < 256; j++)
            {
              f303->chan[i].wavetable[j] = j < 128 ? (j * 2) : ((255 - j) * 2);
            }
            break;
          }
          default: break;
        }
      }
    }
    if (chan[i].std.ex1.had && (chan[i].wavetable != (chan[i].std.ex1.val & 0xff))) 
    {
      if(i < F303_NUM_CHANNELS - 1 && !ins->amiga.useSample && chan[i].waveform == F303_WAVE_CUSTOM && chan[i].wavetable != (chan[i].std.ex1.val & 0xff))
      {
        chan[i].wavetable = chan[i].std.ex1.val & 0xff;
        ws[i].changeWave1(chan[i].wavetable, true);
        rWrite((i << 8) | WRITE_WAVETABLE_NUM, chan[i].wavetable);
        doUpdateWave = true;
      }
    }
    if (chan[i].std.duty.had) 
    {
      if(i < F303_NUM_CHANNELS - 1 && !ins->amiga.useSample && (chan[i].duty != (chan[i].std.duty.val & 0xff)))
      {
        chan[i].duty = chan[i].std.duty.val & 0xff;

        if(chan[i].waveform == F303_WAVE_PULSE)
        {
          rWrite((i << 8) | WRITE_DUTY, chan[i].duty);

          for(int j = 0; j < 256; j++)
          {
            f303->chan[i].wavetable[j] = j < chan[i].duty ? 0 : 0xFF;
          }
        }
      }
    }
    
    if (chan[i].std.panL.had && chan[i].panLeft != chan[i].std.panL.val) 
    {
      rWrite((i << 8) | WRITE_PAN_LEFT, chan[i].std.panL.val);
      chan[i].panLeft = chan[i].std.panL.val;
    }
    if (chan[i].std.panR.had && chan[i].panRight != chan[i].std.panR.val) 
    {
      rWrite((i << 8) | WRITE_PAN_RIGHT, chan[i].std.panR.val);
      chan[i].panRight = chan[i].std.panR.val;
    }

    if (chan[i].std.ex2.had && i == F303_NUM_CHANNELS - 1) 
    {
      if(chan[i].lfsr_bits != chan[i].std.ex2.val)
      {
        chan[i].lfsr_bits = chan[i].std.ex2.val;
        rWrite((i << 8) | WRITE_NOISE_LFSR_BITS, chan[i].lfsr_bits);

        //so that key on doesn't make one redundant write
        f303->noise.lfsr_taps = chan[i].lfsr_bits;
      }
    }

    if (chan[i].std.ex3.had && i == F303_NUM_CHANNELS - 1) 
    {
      chan[i].lfsr = chan[i].std.ex3.val;
      rWrite((i << 8) | WRITE_NOISE_LFSR_VALUE, chan[i].lfsr);
    }

    if (chan[i].std.phaseReset.had && chan[i].std.phaseReset.val == 1) 
    {
      if(i < F303_NUM_CHANNELS - 1)
      {
        rWrite((i << 8) | WRITE_ACC, 0);
      }
      else
      {
        rWrite((i << 8) | WRITE_NOISE_LFSR_VALUE, chan[i].lfsr);
      }
    }

    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff)
    {
      if (chan[i].keyOn)
      {
        DivInstrument* ins = parent->getIns(chan[i].ins, DIV_INS_F303);

        if(i < F303_NUM_CHANNELS - 1)
        {
          if(chan[i].pcm)
          {
            if(f303->chan[i].use_wavetable)
            {
              rWrite((i << 8) | WRITE_WAVETABLE_MODE, 0);
            }
            
            if(!chan[i].sample_off)
            {
              rWrite((i << 8) | WRITE_ACC, 0); //reset accumulator
            }

            DivSample* s=parent->getSample(chan[i].pcmm.next);
            // get frequency offset
            double off=1.0;
            double center=(double)s->centerRate;
            if (center<1) {
              off=1.0;
            } else {
              off=(double)center/parent->getCenterRate();
            }
            chan[i].pcmm.freqOffs=CHIP_FREQBASE*off;
            rWrite((i << 8) | WRITE_SAMPLE_OFF, sampleOff[chan[i].pcmm.next]);
            rWrite((i << 8) | WRITE_SAMPLE_LEN, sampleLen[chan[i].pcmm.next]);

            if (s->isLoopable()) 
            {
              rWrite((i << 8) | WRITE_SAMPLE_LOOP, 1);
            }
            else
            {
              rWrite((i << 8) | WRITE_SAMPLE_LOOP, 0);
            }
          }
          else
          {
            //wavetable
            if(!f303->chan[i].use_wavetable)
            {
              rWrite((i << 8) | WRITE_WAVETABLE_MODE, 1);
            }
          }
        }
        else //noise
        {
          if(f303->noise.lfsr_taps != chan[i].lfsr_bits) //TODO: optimize this? remove this code so user must specify init value in macros?
          {
            rWrite((i << 8) | WRITE_NOISE_LFSR_BITS, chan[i].lfsr_bits);
          }
          
          rWrite((i << 8) | WRITE_NOISE_LFSR_VALUE, chan[i].lfsr);
        }
      }
      if (chan[i].keyOff)
      {
        rWrite((i << 8) | WRITE_VOLUME, 0);
        //chan[i].vol = 0;
        chan[i].outVol = 0;
      }

      if(chan[i].pcm)
      {
        chan[i].freq=CLAMP(parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,2,chan[i].pitch2,chipClock,chan[i].pcmm.freqOffs),0,0x7FFFFFF);
        rWrite((i << 8) | WRITE_FREQ, chan[i].freq);
      }
      else //should also work for noise
      {
        chan[i].freq=CLAMP(parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,2,chan[i].pitch2,chipClock,524288*256),0,0x7FFFFFFF);
        rWrite((i << 8) | WRITE_FREQ, chan[i].freq);
      }
      //rWrite((c.chan << 8) | WRITE_SAMPLE_LEN, sampleLen[chan[c.chan].dacSample]);

      //if (chan[i].freq < 0) chan[i].freq = 0;
      //if (chan[i].freq > 0xffffff) chan[i].freq = 0xffffff;

      if (chan[i].keyOn) chan[i].keyOn = false;
      if (chan[i].keyOff) chan[i].keyOff = false;
      chan[i].freqChanged = false;
      chan[i].sample_off = false;
    }
    if (i < F303_NUM_CHANNELS - 1)
    {
      if ((ws[i].tick() || doUpdateWave) && chan[i].waveform == F303_WAVE_CUSTOM)
      {
        updateWave(i);
        rWrite((i << 8) | WRITE_WAVETABLE_NUM, 0xFFFF); //0xFFFF - signal that a new modified wavetable variant must be pulled from ws memory
      }
    }
  }
}

int DivPlatformF303::dispatch(DivCommand c) 
{
  if (c.chan>F303_NUM_CHANNELS - 1) return 0;

  DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_F303);

  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: 
    {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_F303);
      if (c.value!=DIV_NOTE_NULL) 
      {
        chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value);
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;

      if (ins->amiga.useSample)
      {
        chan[c.chan].pcm=true;
      }
      else
      {
        chan[c.chan].pcm=false;
      }

      if (chan[c.chan].pcm && c.chan < F303_NUM_CHANNELS - 1) 
      {
        if (ins->amiga.useSample) 
        {
          if (c.value!=DIV_NOTE_NULL) 
          {
            int sample=ins->amiga.getSample(c.value);
            chan[c.chan].sampleNote=c.value;
            if (sample>=0 && sample<parent->song.sampleLen) 
            {
              chan[c.chan].pcmm.next=ins->amiga.useNoteMap?c.value:sample;
              c.value=ins->amiga.getFreq(c.value);
              chan[c.chan].sampleNoteDelta=c.value-chan[c.chan].sampleNote;
              chan[c.chan].pcmm.note=c.value;
            }
            else 
            {
              chan[c.chan].sampleNoteDelta=0;
            }
          } 
          else 
          {
            int sample=ins->amiga.getSample(chan[c.chan].sampleNote);
            if (sample>=0 && sample<parent->song.sampleLen) 
            {
              chan[c.chan].pcmm.next=ins->amiga.useNoteMap?chan[c.chan].sampleNote:sample;
              c.value=ins->amiga.getFreq(chan[c.chan].sampleNote);
              chan[c.chan].pcmm.note=c.value;
            } 
            else 
            {
              chan[c.chan].sampleNoteDelta=0;
            }
          }

          if (c.value!=DIV_NOTE_NULL) 
          {
            chan[c.chan].baseFreq=NOTE_PERIODIC(c.value);
            chan[c.chan].freqChanged=true;
            chan[c.chan].note=c.value;
          }
          chan[c.chan].active=true;
          chan[c.chan].macroInit(ins);
          if (!parent->song.brokenOutVol && !chan[c.chan].std.vol.will) {
            chan[c.chan].outVol=chan[c.chan].vol;
          }
          chan[c.chan].keyOn=true;
        }
      }

      if (chan[c.chan].insChanged) 
      {
        if(c.chan < F303_NUM_CHANNELS - 1)
        {
          if(!chan[c.chan].pcm)
          {
            ws[c.chan].changeWave1(chan[c.chan].wavetable, false);
            ws[c.chan].init(ins,256,255,chan[c.chan].insChanged);
          }
        }
      }
      chan[c.chan].macroInit(ins);
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      //chan[c.chan].macroInit(NULL);
      break;
    case DIV_CMD_NOTE_OFF_ENV:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].std.release();
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
      if (chan[c.chan].vol!=c.value) {
        chan[c.chan].vol=c.value;
        if (!chan[c.chan].std.vol.has) {
          chan[c.chan].outVol=c.value;
          chan[c.chan].vol=chan[c.chan].outVol;
          rWrite((c.chan << 8) | WRITE_VOLUME, chan[c.chan].vol);
        }
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
      int destFreq=NOTE_FREQUENCY(c.value2);
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
    case DIV_CMD_LEGATO:
      chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value+((HACKY_LEGATO_MESS)?(chan[c.chan].std.arp.val):(0)));
      chan[c.chan].freqChanged=true;
      chan[c.chan].note=c.value;
      break;
    case DIV_CMD_PRE_PORTA:
      if (chan[c.chan].active && c.value2) {
        if (parent->song.resetMacroOnPorta || parent->song.preNoteNoEffect) {
          chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_F303));
          chan[c.chan].keyOn=true;
        }
      }
      if (!chan[c.chan].inPorta && c.value && !parent->song.brokenPortaArp && chan[c.chan].std.arp.will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=NOTE_FREQUENCY(chan[c.chan].note);
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_PANNING: {
      if (!chan[c.chan].std.panL.has && chan[c.chan].panLeft != c.value) 
      {
        chan[c.chan].panLeft = c.value;
        rWrite((c.chan << 8) | WRITE_PAN_LEFT, chan[c.chan].panLeft);
      }
      if (!chan[c.chan].std.panR.has && chan[c.chan].panRight != c.value2) 
      {
        chan[c.chan].panRight = c.value2;
        rWrite((c.chan << 8) | WRITE_PAN_RIGHT, chan[c.chan].panRight);
      }
      break;
    }
    case DIV_CMD_GET_VOLMAX:
      return F303_MAX_VOLUME;
      break;
    case DIV_CMD_WAVE:
      if(c.chan < F303_NUM_CHANNELS - 1 && !ins->amiga.useSample && chan[c.chan].waveform != (c.value & 0x3))
      {
        chan[c.chan].waveform = c.value & 0x3;

        rWrite((c.chan << 8) | WRITE_WAVE_TYPE, chan[c.chan].waveform);

        switch(chan[c.chan].waveform)
        {
          case F303_WAVE_CUSTOM:
          {
            updateWave(c.chan);
            break;
          }
          case F303_WAVE_PULSE:
          {
            for(int j = 0; j < 256; j++)
            {
              f303->chan[c.chan].wavetable[j] = j < chan[c.chan].duty ? 0 : 0xFF;
            }
            break;
          }
          case F303_WAVE_SAWTOOTH:
          {
            for(int j = 0; j < 256; j++)
            {
              f303->chan[c.chan].wavetable[j] = j;
            }
            break;
          }
          case F303_WAVE_TRIANGLE:
          {
            for(int j = 0; j < 256; j++)
            {
              f303->chan[c.chan].wavetable[j] = j < 128 ? (j * 2) : ((255 - j) * 2);
            }
            break;
          }
          default: break;
        }
      }
      break;
    case DIV_CMD_SID3_LFSR_FEEDBACK_BITS:
      if(c.chan == F303_NUM_CHANNELS - 1)
      {
        chan[c.chan].lfsr_bits &= ~(0xffU << (8 * c.value2));
        chan[c.chan].lfsr_bits |= ((c.value & (c.value2 == 3 ? 0x3f : 0xff)) << (8 * c.value2));
        rWrite((c.chan << 8) | WRITE_NOISE_LFSR_BITS, chan[c.chan].lfsr_bits);
      }
      break;
    case DIV_CMD_N163_WAVE_POSITION:
      {
        if(c.chan < F303_NUM_CHANNELS - 1 && !ins->amiga.useSample && chan[c.chan].waveform == F303_WAVE_CUSTOM && chan[c.chan].wavetable != (c.value & 0xff))
        {
          chan[c.chan].wavetable = c.value & 0xff;
          ws[c.chan].changeWave1(chan[c.chan].wavetable, true);
          rWrite((c.chan << 8) | WRITE_WAVETABLE_NUM, chan[c.chan].wavetable);
          //doUpdateWave = true;
          updateWave(c.chan);
        }
      }
      break;
    case DIV_CMD_SAMPLE_POS:
      if(c.chan >= F303_NUM_CHANNELS - 1) break;
      if(!chan[c.chan].pcm) break;
      chan[c.chan].sample_off = true;
      chan[c.chan].sample_off_val = (unsigned int)c.value << 14;
      rWrite((c.chan << 8) | WRITE_ACC, (unsigned int)c.value << 14);
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

void DivPlatformF303::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
  f303_set_is_muted(f303,ch,mute);
}

void DivPlatformF303::forceIns() {
  for (int i=0; i<F303_NUM_CHANNELS; i++) {
    chan[i].insChanged=true;
    if (chan[i].active) {
      chan[i].keyOn=true;
      chan[i].freqChanged=true;
    }
    //updateFilter(i);
  }
}

void DivPlatformF303::notifyInsChange(int ins) {
  for (int i=0; i<F303_NUM_CHANNELS; i++) {
    if (chan[i].ins==ins) {
      chan[i].insChanged=true;
    }
  }
}

void DivPlatformF303::notifyWaveChange(int wave) 
{
  if (chan[F303_NUM_CHANNELS - 1].wavetable==wave)
  {
    //ws.changeWave1(wave, false);
    //updateWave();
  }
}

void DivPlatformF303::notifyInsDeletion(void* ins) {
  for (int i=0; i<F303_NUM_CHANNELS; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void* DivPlatformF303::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformF303::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

unsigned short DivPlatformF303::getPan(int ch) {
  return (chan[ch].panLeft<<8)|chan[ch].panRight;
}

DivDispatchOscBuffer* DivPlatformF303::getOscBuffer(int ch) {
  return oscBuf[ch];
}

float DivPlatformF303::getPostAmp() {
  return 1.0f;
}

void DivPlatformF303::reset() 
{
  for (int i=0; i<F303_NUM_CHANNELS; i++) 
  {
    chan[i]=DivPlatformF303::Channel();
    chan[i].std.setEngine(parent);
    chan[i].vol = -1;
    chan[i].outVol = -1;

    chan[i].panLeft = chan[i].panRight = -1;

    chan[i].duty = -1;
    chan[i].waveform = -1;

    chan[i].lfsr = 0x3fffffff;
    chan[i].lfsr_bits = 1 | (1 << 23) | (1 << 25) | (1 << 29); //https://docs.amd.com/v/u/en-US/xapp052 for 30 bits: 30, 6, 4, 1; but inverted since our LFSR is moving in different direction

    chan[i].sample_off = false;
    chan[i].sample_off_val = 0;

    f303_set_is_muted(f303, i, isMuted[i]);
  }
  for (int i=0; i<F303_NUM_CHANNELS - 1; i++) 
  {
    ws[i].setEngine(parent);
    ws[i].init(NULL,256,255,false);
  }

  f303_reset(f303);
  f303_set_sample_mem(f303, sampleMem, getSampleMemCapacity(0));
}

int DivPlatformF303::getOutputCount() {
  return 2;
}

bool DivPlatformF303::getDCOffRequired()
{
  return false;
}

void DivPlatformF303::poke(unsigned int addr, unsigned short val) {
  //rWrite(addr,val);
}

void DivPlatformF303::poke(std::vector<DivRegWrite>& wlist) {
  //for (DivRegWrite& i: wlist) rWrite(i.addr,i.val);
}

void DivPlatformF303::setFlags(const DivConfig& flags) {
  chipClock=48077;
  CHECK_CUSTOM_CLOCK;

  rate=chipClock;

  for (int i=0; i<F303_NUM_CHANNELS; i++) 
  {
    oscBuf[i]->setRate(rate);
  }
}

int DivPlatformF303::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent = p;
  dumpWrites=false;
  skipRegisterWrites=false;
  //writeOscBuf=0;
  
  for (int i=0; i<F303_NUM_CHANNELS; i++) 
  {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }

  f303 = f303_create();

  setFlags(flags);

  reset();

  return F303_NUM_CHANNELS;
}

void DivPlatformF303::quit() {
  for (int i=0; i<F303_NUM_CHANNELS; i++) 
  {
    delete oscBuf[i];
  }
  if (f303!=NULL)
  {
    f303_free(f303);
    f303 = NULL;
  }
}

// initialization of important arrays
DivPlatformF303::DivPlatformF303() {
  sampleOff=new unsigned int[32768];
  sampleLen=new unsigned int[32768];
  sampleLoaded=new bool[32768];
}

DivPlatformF303::~DivPlatformF303() {
  delete[] sampleOff;
  delete[] sampleLen;
  delete[] sampleLoaded;
}
