#include "EC_EXTI.h"

void EXTI_Init(GPIO_TypeDef *Port, int Pin, int trig,int priority){
	int PortEN = 0;
	int EXTI_IRQn = 0;
	int EXTICR_idx = 0;
	int EXTICR_port = 0;

	if(Port == GPIOA) {PortEN = RCC_AHB1ENR_GPIOAEN; EXTICR_port = 0;}
	else if(Port == GPIOB) {PortEN = RCC_AHB1ENR_GPIOBEN; EXTICR_port = 1;}
	else if(Port == GPIOC) {PortEN = RCC_AHB1ENR_GPIOCEN; EXTICR_port = 2;}
	else if(Port == GPIOD) {PortEN = RCC_AHB1ENR_GPIODEN; EXTICR_port = 3;}
	
	if(Pin < 5) EXTI_IRQn = Pin + 6;
	else if(Pin < 10) EXTI_IRQn = EXTI9_5_IRQn;
	else EXTI_IRQn = EXTI15_10_IRQn;
	
	EXTICR_idx = (int) Pin / 4;
	
	
	RCC->AHB1ENR |= PortEN;						// GPIOC clock enable
	
	Port->MODER &= ~3UL << (2 * Pin); // Input(00, reset)
	
	Port->PUPDR &= ~3UL << (2 * Pin); // No pull-up/pull-down
	
	NVIC_EnableIRQ(EXTI_IRQn); 							// EXTI IRQ enable
  NVIC_SetPriority(EXTI_IRQn, priority);  // EXTI priority as 0
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;		// SYSCFG peripheral clock enable
	
	// Connect External Line to the GPIO
	SYSCFG->EXTICR[EXTICR_idx] &= ~(0xF << (4 * (Pin % 4)));    	// Button: PC_13 -> EXTICR3(EXTI13)
	SYSCFG->EXTICR[EXTICR_idx] |=  EXTICR_port << (4 * (Pin % 4));// GPIOC
		
	EXTI->IMR  |= 1 << Pin;     // not masked (i.e., Interrupt enabled)
	
	if(trig == FALL) EXTI->FTSR |= 1 << Pin;    		// Falling trigger enable 
	else if(trig == RISE) EXTI->RTSR |= 1 << Pin;   // Rising trigger enable 
	else if(trig == BOTH) {EXTI->RTSR |= 1 << Pin; 
												 EXTI->FTSR |= 1 << Pin;} // Both falling/rising trigger enable
	
}