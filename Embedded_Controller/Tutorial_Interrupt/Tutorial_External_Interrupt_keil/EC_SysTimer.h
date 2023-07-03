#ifndef __EC_SYSTIMER_H
#define __EC_SYSTIMER_H

#include "stm32f4xx.h"

void SysTick_Init(void);
void SysTick_Handler(void);
void delay (uint32_t T);
void TIM2_Int_Init(void);


#endif