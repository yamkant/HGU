#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "myGPIO.h"
// GPIO Mode			 : Input(00), Output(01), AlterFunc(10), Analog(11, reset)
// GPIO Speed			 : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
// GPIO Push-Pull	 : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)

void GPIO_init(GPIO_TypeDef *Port, int Pin, int mode){
	uint32_t Enable_reg = 0x00000000;
	
	if(Port == GPIOA) Enable_reg = RCC_AHB1ENR_GPIOAEN; 
	else if(Port == GPIOB) Enable_reg = RCC_AHB1ENR_GPIOBEN; 
	else if(Port == GPIOC) Enable_reg = RCC_AHB1ENR_GPIOCEN; 
	else if(Port == GPIOD) Enable_reg = RCC_AHB1ENR_GPIODEN; 
	
	if(mode == OUTPUT){
		// Enable the clock to GPIO Port A	
		RCC->AHB1ENR |= Enable_reg; //0x00000001	
		
		Port->MODER &= ~(3UL<<(2*Pin));  	
		Port->MODER |= mode<<(2*Pin);     // PA_5: Output(01)
		
		Port->OSPEEDR &= ~(3UL<<(2*Pin));		
		Port->OSPEEDR |= 2UL<<(2*Pin); // Fast speed 
		 
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

void GPIO_write(GPIO_TypeDef *Port, int Pin, int Output){
	if(Output == HIGH) Port->ODR |= 1 << Pin;
	else if(Output == LOW) Port->ODR &= ~(1 << Pin);
}

int GPIO_read(GPIO_TypeDef *Port, int Pin){
	return ((Port->IDR) & (1UL << Pin)) >> Pin;
}

void SevenSegment_init(){
	GPIO_init(GPIOA, 5, OUTPUT); // a
	GPIO_init(GPIOA, 6, OUTPUT); // b
	GPIO_init(GPIOA, 7, OUTPUT); // c
	GPIO_init(GPIOB, 6, OUTPUT); // d
	GPIO_init(GPIOC, 7, OUTPUT); // e
	GPIO_init(GPIOA, 9, OUTPUT); // f
	GPIO_init(GPIOA, 8, OUTPUT); // g
	GPIO_init(GPIOB, 10, OUTPUT); // dp
}

void SevenSegment_on(int num){
	if(num > 9) num = 0;
	uint8_t ON = 0;

	switch (num){
		case 0: 
			ON = 0b00000011; break;
		case 1:
			ON = 0b10011111;	break;
		case 2:
			ON = 0b00100101;	break;
		case 3:
			ON = 0b00001101;	break;	
		case 4:
			ON = 0b10011001;	break;	
		case 5:
			ON = 0b01001001;	break;			
		case 6:
			ON = 0b01000001;	break;					
		case 7:
			ON = 0b00011011;	break;					
		case 8:
			ON = 0b00000001;	break;
		case 9:
			ON = 0b00001001;	break;
	}	
	GPIO_write(GPIOA, 5, (ON >> 7) & 1);
	GPIO_write(GPIOA, 6, (ON >> 6) & 1);
	GPIO_write(GPIOA, 7, (ON >> 5) & 1);
	GPIO_write(GPIOB, 6, (ON >> 4) & 1);
	GPIO_write(GPIOC, 7, (ON >> 3) & 1);
	GPIO_write(GPIOA, 9, (ON >> 2) & 1);
	GPIO_write(GPIOA, 8, (ON >> 1) & 1);
	GPIO_write(GPIOB, 10, ON & 1);
}
