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

#ifndef _F303_H_
#define _F303_H_

#include "../dispatch.h"
#include "../../fixedQueue.h"
#include "../waveSynth.h"
#include "sound/stm32f303.h"

#define F303_WAVE_CUSTOM 0
#define F303_WAVE_PULSE 1
#define F303_WAVE_TRIANGLE 2
#define F303_WAVE_SAWTOOTH 3

#define WRITE_SAMPLE_OFF 0
#define WRITE_SAMPLE_LEN 1
#define WRITE_FREQ 2
#define WRITE_WAVETABLE_MODE 3
#define WRITE_SAMPLE_LOOP 4
#define WRITE_VOLUME 5
#define WRITE_PAN_LEFT 6
#define WRITE_PAN_RIGHT 7
#define WRITE_ACC 8
#define WRITE_WAVETABLE_NUM 9 /* dummy for export */
#define WRITE_WAVE_TYPE 10 /* dummy for export */
#define WRITE_DUTY 11 /* dummy for export */
#define WRITE_NOISE_LFSR_BITS 12 /* dummy for export */
#define WRITE_NOISE_LFSR_VALUE 13 /* dummy for export */
#define WRITE_FRAME_DELAY 14 /* dummy for export */
#define WRITE_JUMP 15 /* dummy for export */
#define WRITE_END 16

class DivPlatformF303: public DivDispatch 
{
  struct Channel: public SharedChannel<signed short> 
  {
    bool use_wavetable;
    bool pcm;
    int dacSample;
    int wavetable;

    int panRight;
    int panLeft;

    int waveform;

    int duty;

    unsigned int lfsr;
    unsigned int lfsr_bits;

    bool sample_off;
    unsigned int sample_off_val;

    struct PCM {
      bool isNoteMap;
      int index, next;
      int note;
      double freqOffs;
      double nextFreqOffs;
      PCM():
        isNoteMap(false),
        index(-1),
        next(-1),
        note(0),
        freqOffs(1.0),
        nextFreqOffs(1.0) {}
    } pcmm;

    Channel():
      SharedChannel<signed short>(F303_MAX_VOLUME),
      use_wavetable(false),
      pcm(true),
      dacSample(-1),
      wavetable(-1),
      panRight(0xFF),
      panLeft(0xFF),
      waveform(0),
      duty(0x80),
      lfsr(0x3fffffff),
      lfsr_bits( 1 | (1 << 23) | (1 << 25) | (1 << 29)),  //https://docs.amd.com/v/u/en-US/xapp052 for 30 bits: 30, 6, 4, 1; but inverted since our LFSR is moving in different direction
      sample_off(false),
      sample_off_val(0) {}
  };

  

  struct QueuedWrite {
      unsigned int addr;
      unsigned int val;
      QueuedWrite(): addr(0), val(0) {}
      QueuedWrite(unsigned int a, unsigned int v): addr(a), val(v) {}
  };
  FixedQueue<QueuedWrite,512 * 16> writes;
  
  friend void putDispatchChip(void*,int);
  friend void putDispatchChan(void*,int,int);
  void updateWave(int chan);

  public:
    Channel chan[F303_NUM_CHANNELS];
    DivDispatchOscBuffer* oscBuf[F303_NUM_CHANNELS];

    DivWaveSynth ws[F303_NUM_CHANNELS - 1];

    STM32F303* f303;

    bool isMuted[F303_NUM_CHANNELS];

    DivMemoryComposition memCompo;

    unsigned char sampleMem[65536 * 2];
    size_t sampleMemLen;

    unsigned int* sampleOff;
    unsigned int* sampleLen;
    bool* sampleLoaded;


    void acquire(short** buf, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    void reset();
    void forceIns();
    void tick(bool sysTick=true);
    void muteChannel(int ch, bool mute);
    void setFlags(const DivConfig& flags);
    void notifyInsChange(int ins);
    void notifyWaveChange(int wave); 
    float getPostAmp();
    bool getDCOffRequired();
    unsigned short getPan(int chan);
    DivMacroInt* getChanMacroInt(int ch);
    void notifyInsDeletion(void* ins);
    void poke(unsigned int addr, unsigned short val);
    void poke(std::vector<DivRegWrite>& wlist);
    const void* getSampleMem(int index = 0);
    size_t getSampleMemCapacity(int index = 0);
    size_t getSampleMemUsage(int index = 0);
    bool isSampleLoaded(int index, int sample);
    const DivMemoryComposition* getMemCompo(int index);
    void renderSamples(int chipID);
    int init(DivEngine* parent, int channels, int sugRate, const DivConfig& flags);
    int getOutputCount();
    void quit();
    DivPlatformF303();
    ~DivPlatformF303();
};

#endif
