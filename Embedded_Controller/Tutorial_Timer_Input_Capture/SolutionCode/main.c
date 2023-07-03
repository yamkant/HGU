#include <stdio.h>
#include <math.h>
#include "myRCC.h"
#include "mySysTick.h"
#include "myGPIO.h"
#include "myPWM.h"
#include "myUART.h"
#include "myTIM.h"

extern uint32_t timeInterval;

int main(void){
	
	RCC_PLL_init(); // Clock: TIM1 & TIM2 -> 84MHz
	SysTick_init();
	UART2_init(9600, POL);
	
	// Trigger Generation (PA8)--------------------------------
	TIM_t trig;
	GPIO_init(GPIOA, 8, AF);
	PWM_init(&trig, GPIOA, 8); 
	PWM_period_ms(&trig, 50);				// 50[ms]
	PWM_pulsewidth_ms(&trig, 0.01);	// 10[us]
	
	// Echo Reception (PB10)-----------------------------------
	TIM_t echo;
	GPIO_init(GPIOB, 10, AF);
	
	TIM_period_us(2, 1);						// TIM2, 1us
	CAP_init(&echo, GPIOB, 10); 
	//	CAP_setup(&echo, FIRST, RISE);		// CC3 is mapped on TI3, configured as rising edge
	//	CAP_setup(&echo, SECOND, FALL);		// CC4 is mapped on TI3, configured as falling edge	
	NVIC_SetPriority(TIM2_IRQn, 2);
	NVIC_EnableIRQ(TIM2_IRQn);

	float distance = 0;
	while(1){
		distance = (float) timeInterval/58; 
		printf("%.3f cm\r\n", distance);
		delay(500);
	}
}




//#include <stdio.h>
//#include <math.h>
//#include "stm32f4xx.h"
//#include "EC_SysClk.h"
//#include "EC_SysTimer.h"
//#include "EC_GPIO.h"
//#include "EC_UART.h"
//#include "EC_ADC.h"

//uint32_t currentValue = 0;
//uint32_t lastValue = 0;
//uint32_t overflowCount = 0;
//uint32_t timeInterval = 0;

//int main(void){
//	
//	//SysClk_Init(); // APB2(TIM1): 84MHz, APB1(TIM2): 42MHz
//	SysTick_Init();
//	UART2_Init(9600, POL);

//	// SysClk_HSI_Init();-------------------------------------------------------------------
//	// Enable High Speed Internal Clock (HSI = 16 MHz)
//  RCC->CR |= ((uint32_t)RCC_CR_HSION);
//	
//  // wait until HSI is ready
//  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
//	
//  // Select HSI as system clock source 
//  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
//  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;     // 01: HSI16 oscillator used as system clock

//  // Wait till HSI is used as system clock source 
//  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI ) {;}
//  
//	// GPIO configuration ---------------------------------------------------------------------
//	// PA8(Trig), PB10(Echo)
//  // Enable the clock to GPIO Port A & B 
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 	
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
//	
//			
//	// Set the mode of the pins to alternate function mode
//	// MODE: 10 - Alternate function mode
//	GPIOA->MODER &= ~(3 << (2 * 8)); // clear bits
//	GPIOA->MODER |= (2 << (2 * 8));
//	GPIOB->MODER &= ~(3 << (2 * 10)); // clear bits
//	GPIOB->MODER |= (2 << (2 * 10));
//	
//		
//	// Set alternative function 1(TIM1/TIM2) on PB0 and PA1	
//	GPIOA->AFR[1] |= (1 << (4 * (8 - 8)));
//	GPIOB->AFR[1] |= (1 << (4 * (10- 8)));	
//	
//		
//	// No pull-up & No pull-down
//	GPIOB->PUPDR &= ~(3<<(2*0));
//	GPIOA->PUPDR &= ~(3<<(2*1));
//	// High speed
//	GPIOA->OSPEEDR |= 3 << (2*0);		
//	
//	// TIM configuration -------------------------------------------------------------------------
//	// Enable timer 1 and 2
//	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // trigger(output compare) - APB2: 84MHz
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	// echo(input capture)		 - APB1: 42MHz
//		
//	// PA8 (TIM1_CH1): Trigger Signal
//	TIM1->PSC = 83;																			// Timer counter clock: 1MHz(1us)
//	TIM1->CR1 |= TIM_CR1_ARPE; 													// Enable auto reload
//	TIM1->CR1 &= ~TIM_CR1_DIR;													// Upcounting
//	TIM1->ARR = 0xFFFF;  																// Set auto reload register to maximum (count up to 65535 ?)
//	TIM1->CCR1 = 10;																		// channel 1 compare value(10us duty)
//	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // channel 1 ouput compare mode (PWM mode 1 - 110)
//	TIM1->CCER |= TIM_CCER_CC1E; 												// channel 1 capture/compare output enable
//	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;											// Output Compare 1 preload enable 
//	TIM1->BDTR |= TIM_BDTR_OSSR;												// enable output even at inactive condition? (310p)
//	TIM1->BDTR |= TIM_BDTR_MOE;													// mode output enable (@ TIM_CCER_CC1E = 1)
//	TIM1->EGR |= TIM_EGR_UG;														// Reinitialize the counter and generates an update of the registers ---> not necessary ?! 
//	//TIM1->SR &= ~TIM_SR_UIF;														// No update occured 
//	TIM1->DIER |= TIM_DIER_UIE;													// Update interrupt enable
//	TIM1->CR1 |= TIM_CR1_CEN;														// Counter enable! 

//	// PB10 (TIM2_CH3): Input Capture
//	TIM2->PSC = 83;;//41																								// Timer counter clock: 1MHz(1us)
//	TIM2->CR1 |= TIM_CR1_ARPE;																		// Enable auto reload
//	TIM2->ARR = 0xFFFF;																						// Set auto reload register to maximum (count up to 65535 ?)
//	TIM2->CCMR2|= TIM_CCMR2_CC3S_0; 															// Capture/Compare Selection: CC3 is mapped on TI3 
//	TIM2->CCER = TIM_CCER_CC3NP | TIM_CCER_CC3P | TIM_CCER_CC3E;	// Capture both rigsing & falling edges, and Capture enabled
//	TIM2->DIER |= TIM_DIER_CC3IE; 																// Interrupt enabled
//	TIM2->DIER |= TIM_DIER_CC3DE; 																// DMA request enabled
//	TIM2->CR1 |= TIM_CR1_CEN;																			// Counter enable
//	TIM2->DIER |= TIM_DIER_UIE;																		// Update interrupt enable
//	TIM2->EGR |= TIM_EGR_UG;																			// Reinitialize the counter and generates an update of the registers ---> not necessary ?!
//	//TIM2->SR &= ~TIM_SR_UIF;																			// No update occured 
//	TIM2->CCMR2 &= ~TIM_CCMR2_IC3F;																// No filter
//	//TIM2->CCMR1 |= TIM_CCMR1_IC1F_0 | TIM_CCMR1_IC1F_1;
//	
//	//Set priority for TIM2 - Input Capture
//	NVIC_SetPriority(TIM2_IRQn, 2);
//	NVIC_EnableIRQ(TIM2_IRQn);
//	
//	float distance = 0;

//	while(1){
//		distance = (float) timeInterval/58; // Divide the number of microseconds by 58 to get [cm]
//		printf("%.3f cm\r\n", distance);
//		delay(500);
//	}
//}


//void TIM2_IRQHandler(void){
//	if(TIM2->SR & TIM_SR_UIF){ // update interrupt flag
//		overflowCount++;
//		TIM2->SR &= ~TIM_SR_UIF; // clear by writing 0
//	}
//	if((TIM2->SR & TIM_SR_CC3IF) != 0){ // Capture/compare 3 interrupt flag
//		currentValue = (TIM2->CCR3) ;//+ (uint32_t)0xFFFF * overflowCount;
//		timeInterval = currentValue - lastValue;		
//		lastValue = currentValue;
//		overflowCount = 0;

//		TIM2->SR &= ~TIM_SR_CC3IF;	// it is also cleared by reading TIM2->CCR2
//		TIM2->SR &= ~TIM_SR_CC3OF;	// clear overcapture flag
//	}
//}
