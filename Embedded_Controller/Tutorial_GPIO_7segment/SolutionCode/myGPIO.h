#include "stm32f411xe.h"

#ifndef GPIO_HEADER
#define GPIO_HEADER

// MODER
#define OUTPUT 0x01
#define INPUT  0x00

// OUTPUT
#define HIGH 1
#define LOW  0

// USER PIN
#define LED_PIN 	 5
#define BUTTON_PIN 13

// General Config
void GPIO_init(GPIO_TypeDef *Port, int Pin, int mode);
void GPIO_write(GPIO_TypeDef *Port, int Pin, int Output);
int  GPIO_read(GPIO_TypeDef *Port, int Pin);

// 7-segment
void SevenSegment_init();
void SevenSegment_on(int num);
#endif