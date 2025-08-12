#include "stm32f303.h"

STM32F303* f303_create()
{
    STM32F303* f303 = (STM32F303*)malloc(sizeof(STM32F303));

    memset(f303, 0, sizeof(STM32F303));

    f303_reset(f303);

    return f303;
}

void f303_reset(STM32F303* stm)
{
    bool muted[F303_NUM_CHANNELS - 1];
    bool noise_muted;

    for(int i = 0; i < F303_NUM_CHANNELS - 1; i++)
    {
        muted[i] = stm->chan[i].muted;
    }

    noise_muted = stm->noise.muted;

    memset(stm, 0, sizeof(STM32F303));

    for(int i = 0; i < F303_NUM_CHANNELS - 1; i++)
    {
        stm->chan[i].muted = muted[i];
    }

    stm->noise.muted = noise_muted;

    stm->noise.lfsr = 0x3fffffff;
    stm->noise.lfsr_taps = 1 | (1 << 23) | (1 << 25) | (1 << 29); //https://docs.amd.com/v/u/en-US/xapp052 for 30 bits: 30, 6, 4, 1; but inverted since our LFSR is moving in different direction
}

void f303_clock(STM32F303* stm)
{
    stm->output_l = 0;
    stm->output_r = 0;

    for(int i = 0; i < F303_NUM_CHANNELS - 1; i++)
    {
        stm->chan[i].acc += stm->chan[i].freq;

        if(stm->chan[i].use_wavetable)
        {
            stm->chan[i].chan_output = ((int)stm->chan[i].wavetable[stm->chan[i].acc >> (32 - 8)] - 128) * (int)stm->chan[i].volume / 256;
        }
        else
        {
            if(stm->chan[i].sample_start_addr + (stm->chan[i].acc >> 14) < stm->sample_mem_size) //this condition is emulation-only
            {   
                stm->chan[i].chan_output = ((int)stm->sample_mem[stm->chan[i].sample_start_addr + (stm->chan[i].acc >> 14)] - 128) * (int)stm->chan[i].volume / 256;
            }
        }

        if(!stm->chan[i].use_wavetable)
        {
            if(stm->chan[i].acc > (stm->chan[i].sample_length << 14))
            {
                if(stm->chan[i].sample_loop)
                {
                    stm->chan[i].acc = 0;
                }
                else
                {
                    stm->chan[i].freq = 0;

                    stm->chan[i].chan_output = 0;
                }
            }
        }

        if(!stm->chan[i].muted && stm->chan[i].freq > 0)
        {
            stm->output_l += (int)(((int)stm->chan[i].chan_output) * (int)stm->chan[i].pan_left / 256) * 32;
            stm->output_r += (int)(((int)stm->chan[i].chan_output) * (int)stm->chan[i].pan_right / 256) * 32;
        }
    }

    //noise
    uint32_t prev_acc = stm->noise.acc;

    stm->noise.acc += stm->noise.freq;

    if((stm->noise.acc & (1 << 27)) != (prev_acc & (1 << 27)))
    {
        uint32_t feedback = stm->noise.lfsr & 1;
        stm->noise.lfsr >>= 1;

        if (feedback) 
        {
            stm->noise.lfsr ^= stm->noise.lfsr_taps;
        }
    }

    stm->noise.chan_output = ((stm->noise.lfsr & 1) ? 255 : 0 - 128) * (int)stm->noise.volume / 256;

    if(!stm->noise.muted && stm->noise.freq > 0)
    {
        stm->output_l += (int)(((int)stm->noise.chan_output) * (int)stm->noise.pan_left / 256) * 32;
        stm->output_r += (int)(((int)stm->noise.chan_output) * (int)stm->noise.pan_right / 256) * 32;
    }
}

void f303_set_is_muted(STM32F303* stm, uint8_t ch, bool mute)
{
    if(ch < F303_NUM_CHANNELS - 1)
    {
        stm->chan[ch].muted = mute;
    }
    else
    {
        stm->noise.muted = mute;
    }
}

void f303_set_sample_mem(STM32F303* stm, uint8_t* sample_mem, uint32_t sample_mem_size)
{
    stm->sample_mem = sample_mem;
    stm->sample_mem_size = sample_mem_size;
}

void f303_free(STM32F303* stm)
{
    free(stm);
}