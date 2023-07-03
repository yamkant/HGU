#ifndef __MY_PWM_H
#define __MY_PWM_H
#include "stm32f411xe.h"
#include "myTIM.h"

void PWM_init(TIM_t *PWM_pin, GPIO_TypeDef *port, int pin);
void PWM_period_ms(TIM_t *PWM_pin, float period_ms);
void PWM_pulsewidth_ms(TIM_t *PWM_pin, float pulse_width_ms);

#endif