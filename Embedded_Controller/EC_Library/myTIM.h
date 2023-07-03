#ifndef __MY_TIM_H
#define __MY_TIM_H
#include "stm32f411xe.h"

// ICn selection according to CHn
#define FIRST 1
#define SECOND 2

// Edge Type
#define RISE 0
#define FALL 1
#define BOTH 2

typedef struct{
	GPIO_TypeDef *port;		
	int pin;						
	TIM_TypeDef *timer;	
	int ch;							
}TIM_t;


typedef struct{
	GPIO_TypeDef *port;
	int pin;
	TIM_TypeDef *timer;
	int ch;
	int first;
	int second;
} IC_t;

void TIM_period_us(uint32_t nTimer, float usec);
void CAP_init(TIM_t *cap_pin, GPIO_TypeDef *port, int pin);
void CAP_setup(TIM_t *cap_pin, int ICn_type, int edge_type);
void TIM_pinmap(TIM_t *timer_pin);
void TIM3_init(float msec);
#endif