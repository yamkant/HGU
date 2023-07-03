#include "stm32f411xe.h"

#ifndef __EC_EXTI
#define __EC_EXTI

#define FALL 0
#define RISE 1
#define BOTH 2

void EXTI_Init(GPIO_TypeDef *Port, int Pin, int trig,int priority);

#endif