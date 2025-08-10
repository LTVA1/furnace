#include "stm32f303.h"

STM32F303* f303_create()
{
    STM32F303* f303 = (STM32F303*)malloc(sizeof(STM32F303));

    memset(f303, 0, sizeof(STM32F303));

    return f303;
}

void f303_reset(STM32F303* stm)
{
    memset(stm, 0, sizeof(STM32F303));
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
            stm->chan[i].chan_output = (int)stm->chan[i].wavetable[stm->chan[i].acc >> (32 - 8)] * stm->chan[i].volume / 256;
        }
        else
        {
            stm->chan[i].chan_output = (int)stm->sample_mem[stm->chan[i].sample_start_addr + (stm->chan[i].acc >> 14)] * stm->chan[i].volume / 256;
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
            stm->output_l += (int)(((int)stm->chan[i].chan_output - 128) * stm->chan[i].pan_left / 256) * 32;
            stm->output_r += (int)(((int)stm->chan[i].chan_output - 128) * stm->chan[i].pan_right / 256) * 32;
        }
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