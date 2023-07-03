#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "EC_GPIO.h"
// GPIO Mode			 : Input(00), Output(01), AlterFunc(10), Analog(11, reset)
// GPIO Speed			 : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
// GPIO Push-Pull	 : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)

void GPIO_Init(GPIO_TypeDef *Port, int Pin, int mode){
	uint32_t Enable_reg = 0x00000000;
	
	if(Port == GPIOA) Enable_reg = RCC_AHB1ENR_GPIOAEN; 
	else if(Port == GPIOB) Enable_reg = RCC_AHB1ENR_GPIOBEN; 
	else if(Port == GPIOC) Enable_reg = RCC_AHB1ENR_GPIOCEN; 
	else if(Port == GPIOD) Enable_reg = RCC_AHB1ENR_GPIODEN; 
	
	if(mode == OUTPUT){
		// Enable the clock to GPIO Port A	
		RCC->AHB1ENR |= Enable_reg; //0x00000001	
		
		Port->MODER &= ~(3UL<<(2*Pin));  	
		Port->MODER |= mode <<(2*Pin);     // PA_5: Output(01)
		
		Port->OSPEEDR &= ~(3UL<<(2*Pin));		
		Port->OSPEEDR |= 2UL<<(2*Pin); 		// Fast speed 
		 
		Port->OTYPER &= ~(1UL<<Pin);      // Push-pull
		
		Port->PUPDR  &= ~(3UL<<(2*Pin));  // No pull-up, no pull-down
	}
	else if(mode == INPUT){
		RCC->AHB1ENR |= Enable_reg; 
		
		Port->MODER &= ~(3UL<<(2*Pin));  	
		Port->MODER |= mode<<(2*Pin); // PC_13: Input(00)
				
		Port->PUPDR  |= 2UL<<(2*Pin);  // Pull-down
	}
}

void GPIO_Out(GPIO_TypeDef *Port, int Pin, int Output){
	Port->ODR = Output << Pin;
}

int GPIO_In(GPIO_TypeDef *Port, int Pin){
	return ((Port->IDR) & (1UL << Pin));
}

void LED_Init(){
	GPIO_Init(GPIOA, 5, OUTPUT);
}

void LED_Toggle(){
	GPIOA->ODR ^= GPIO_ODR_ODR_5;
}