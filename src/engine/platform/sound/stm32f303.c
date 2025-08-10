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

}

void f303_set_is_muted(STM32F303* stm, uint8_t ch, bool mute)
{

}

void f303_free(STM32F303* stm)
{
    free(stm);
}