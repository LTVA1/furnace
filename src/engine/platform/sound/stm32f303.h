#ifndef STM32F303_H_
#define STM32F303_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define F303_NUM_CHANNELS 7 /* six wavetable/sample and one noise */
#define F303_MAX_VOLUME 255

typedef struct
{
    uint32_t acc;
    uint32_t freq;
    uint32_t sample_start_addr;
    uint32_t sample_length;
    bool use_wavetable;
    bool sample_loop;
    uint8_t volume;

    uint8_t wavetable[256];

    uint8_t pan_left;
	uint8_t pan_right;

    bool muted; //emulation-only
    uint16_t chan_output; //emulation-only
} Chan_state;

typedef struct
{
    uint32_t acc;
    uint32_t freq;
    uint8_t volume;

    uint8_t pan_left;
	uint8_t pan_right;

    bool muted; //emulation-only
    uint16_t chan_output; //emulation-only
} Noise_chan_state;

typedef struct
{
    Chan_state chan[F303_NUM_CHANNELS - 1];
    Noise_chan_state noise;

    int16_t output_l;
    int16_t output_r;

    uint8_t* sample_mem;
    uint32_t sample_mem_size;
} STM32F303;

STM32F303* f303_create();
void f303_reset(STM32F303* stm);
void f303_clock(STM32F303* stm);
void f303_set_is_muted(STM32F303* stm, uint8_t ch, bool mute);
void f303_set_sample_mem(STM32F303* stm, uint8_t* sample_mem, uint32_t sample_mem_size);
void f303_free(STM32F303* stm);

#ifdef __cplusplus
};
#endif
#endif /* STM32F303_H_ */
