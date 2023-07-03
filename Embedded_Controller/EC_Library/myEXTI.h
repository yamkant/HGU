#include "stm32f411xe.h"

#ifndef __MY_EXTI_H
#define __MY_EXTI_H

#define FALL 0
#define RISE 1
#define BOTH 2

void EXTI_init(GPIO_TypeDef *Port, int Pin, int trig,int priority);
void EXTI13_IRQFunction();
#endif