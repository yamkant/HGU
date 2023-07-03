#ifndef __MY_ADC_H
#define __MY_ADC_H
#include "stm32f411xe.h"
#define POL 0
#define INT 1
#define EXT 2

void ADC_init(GPIO_TypeDef *port, int pin, int type);
uint32_t ADC_read();
uint32_t ADC_pinmap(GPIO_TypeDef *port, int pin);

#endif