#include "stm32f4xx.h"
#include "EC_PWM.h"

int Period = 0;


void PWM_Init(GPIO_TypeDef *Port, int Pin){
		RCC->AHB1ENR       |= RCC_AHB1ENR_GPIOAEN;                  // Enable GPIOA clock	  
		// Set PA_5 I/O direction as Alternative Function 1
		Port->MODER  	&= ~(0x03 << (2*Pin));   							// Clear bits
		Port->MODER  	|= 0x02 << (2*Pin);      							// AlterFunc(10)
		Port->AFR[0] 	|= 0x01 << (4*Pin);                   // AF1 = TIM2_CH1N 
		
		//Set I/O output speed value as very high speed
		Port->OSPEEDR  &= ~(0x03<<(2*Pin)); 								// Speed mask
		Port->OSPEEDR  |=   0x03<<(2*Pin); 									// High speed
		
		Port->PUPDR    &= ~(0x03<<(2*Pin));    							// No PUPD(00, reset)
		
	  Port->OTYPER   &=  ~(1<<Pin) ;           						// Push-Pull(0, reset)
	
    RCC->APB1ENR 	 |= RCC_APB1ENR_TIM2EN;              	// Enable TIMER clock
}


void PWM_Period(int period_ms){
		Period = period_ms;
	
		int ARR_Value = period_ms * 10; 			
		if(ARR_Value > 0xFFFF) ARR_Value = 0xFFFF; // maximum ARR value = 65535(16-bit)
					
		TIM2->CR1 &= ~TIM_CR1_DIR;  														// Counting direction: 0 = up-counting, 1 = down-counting
		
    TIM2->PSC 	  	 = 8399;                               	// Prescaler = 8399 --> f_cnt = 10kHz
    TIM2->ARR 	  	 = ARR_Value - 1 ;                      // Auto-reload: Upcouting (0..ARR), Downcouting (ARR..0)
		TIM2->CCMR1 		&= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
    TIM2->CCMR1  	  |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // OC1M = 110 for PWM Mode 1 output on ch1
    TIM2->CCMR1  		|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)

		// Select output polarity
		TIM2->CCER &= ~TIM_CCER_CC1P; 													// select active high
		
    // Enable output for ch1N
		TIM2->CCER |= TIM_CCER_CC1E;
    
    // Main output enable (MOE): 0 = Disable, 1 = Enable
		TIM2->BDTR |= TIM_BDTR_MOE;  

		TIM2->CCR1  = ARR_Value/2;                         // Output Compare Register for channel 1 (default duty ratio = 50%)
		TIM2->CR1  |= TIM_CR1_CEN;                         // Enable counter
}

void PWM_PulseWidth(int pulse_width_ms){
	TIM2->CCR1 = (TIM2->ARR + 1) * pulse_width_ms / Period;
}