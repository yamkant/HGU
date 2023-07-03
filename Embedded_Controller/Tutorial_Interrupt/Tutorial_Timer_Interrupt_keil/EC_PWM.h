#include "stm32f411xe.h"

#ifndef __EC_PWM_H
#define __EC_PWM_H

void PWM_Init(GPIO_TypeDef *Port, int Pin);
void PWM_Period(int period_ms);
void PWM_PulseWidth(int pulse_width_ms);
#endif