#include "stm32f4xx.h"
#include "myRCC.h"
#include "mySysTick.h"

#define LED_PIN  5

int main() {	
		RCC_PLL_init();																					// System Clock = 84MHz
		SysTick_init();
		
		RCC->AHB1ENR    |= RCC_AHB1ENR_GPIOAEN;              		// Enable GPIOA clock	  
	
		GPIOA->MODER  	&= ~(3 << (2*LED_PIN));   							// Clear bits
		GPIOA->MODER  	|= ;      															// Alternate Function
		
		GPIOA->AFR[0] 	 = ;                 										// AF1 at PA5 = TIM2_CH1 (p.150)
		
		GPIOA->OSPEEDR  &= ~(3 <<(2*LED_PIN)); 									// Clear bits
		GPIOA->OSPEEDR  |=  ; 																	// High speed
		
		GPIOA->PUPDR    &= ~(3 <<(2*LED_PIN));    							// No PUPD(00, reset)
		
	  GPIOA->OTYPER   &=  ~(1<<LED_PIN) ;           					// Push-Pull(0, reset)
	
    RCC->APB1ENR 	 	 = ;              											// Enable TIMER clock
					
		TIM2->CR1 			 = ;  																	// Counting direction: 0 = up-counting, 1 = down-counting
		
    TIM2->PSC 	  	 = ;                               			// f_cnt = 1MHz
		
    TIM2->ARR 	  	 = ;                      			   			// Auto-reload: Upcouting (0..ARR)
		
		TIM2->CCMR1 		&= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
    TIM2->CCMR1  	  |= ; 																		// Set OC1M value for PWM Mode 1 output on ch1
    TIM2->CCMR1  		|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)

		TIM2->CCER &= ~TIM_CCER_CC1P; 													// select active high    
		TIM2->CCER |= ;																					// Enable output for CH1    		

		TIM2->CCR1  = ;                        									// Initialize Output Compare Register for channel 1
		
		TIM2->CR1  |= TIM_CR1_CEN;                  						// Enable counter
		
    while(1) {
			// Create the code to change the brightness of LED(use 'delay(100)')		
		}
}
