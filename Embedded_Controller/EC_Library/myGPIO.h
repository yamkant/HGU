#include "stm32f411xe.h"

#ifndef __MY_GPIO_H
#define __MY_GPIO_H

#define INPUT  0x00
#define OUTPUT 0x01
#define AF  	 0x02
#define ANALOG 0x03

#define HIGH 1
#define LOW  0

#define LED_PIN 	5
#define BUTTON_PIN 13

void GPIO_init(GPIO_TypeDef *Port, int Pin, int mode);
void GPIO_write(GPIO_TypeDef *Port, int Pin, int Output);
int  GPIO_read(GPIO_TypeDef *Port, int Pin);
void LED_init(void);
void LED_toggle(void);
void LED_off(void);
void LED_on(void);

// 7-segment
void SevenSegment_init(void);
void SevenSegment_on(int num);
#endif
