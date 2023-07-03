#include "stm32f411xe.h"

#ifndef GPIO_HEADER
#define GPIO_HEADER

#define OUTPUT 0x01
#define INPUT  0x00

#define HIGH 1
#define LOW  0


void GPIO_Init(GPIO_TypeDef *Port, int Pin, int mode);
void GPIO_Out(GPIO_TypeDef *Port, int Pin, int Output);
int  GPIO_In(GPIO_TypeDef *Port, int Pin);
void LED_Init();
void LED_Toggle();

#endif