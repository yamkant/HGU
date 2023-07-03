#include "stm32f411xe.h"

#ifndef __MY_PWM_H
#define __MY_PWM_H

typedef struct{
   GPIO_TypeDef *port;
   int pin;
   TIM_TypeDef *timer;
   int ch;
} PWM_t;

void PWM_pinmap(PWM_t *PWM_pin);
void PWM_init(PWM_t *PWM_pin, GPIO_TypeDef *port, int pin);
void PWM_period_ms(PWM_t *PWM_pin, int period_ms);
void PWM_pulsewidth_ms(PWM_t *PWM_pin, int pulse_width_ms);

#endif