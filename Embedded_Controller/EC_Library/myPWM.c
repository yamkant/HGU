#include "stm32f4xx.h"
#include "myPWM.h"

void PWM_init(TIM_t *PWM_pin, GPIO_TypeDef *port, int pin){
	PWM_pin->port = port;
	PWM_pin->pin  = pin;

	TIM_pinmap(PWM_pin);

	TIM_TypeDef *TIMx = PWM_pin->timer;
	int 				CHn 	= PWM_pin->ch;	
      
	if(PWM_pin->timer == TIM1){
		 port->AFR[pin >> 3] |= 0x01 << (4*(pin % 8)); 
		 RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;                 // Enable TIMER clock
	}          
	else if(PWM_pin->timer == TIM2){
		 port->AFR[pin >> 3] |= 0x01 << (4*(pin % 8)); 
		 RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     // Enable GPIOB clock
	}         
	else if(PWM_pin->timer == TIM3){
		 port->AFR[pin >> 3] |= 0x02 << (4*(pin % 8)); 
		 RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     // Enable GPIOC cloc     
	}

 	TIMx->PSC    = 83;          	// f_cnt = 1MHz
	TIMx->CR1 &= ~TIM_CR1_DIR;    // 0 = up-counting
	
	PWM_period_ms(PWM_pin, 1);		// default: 1kHz (1ms)
	
	int ARR_Value = TIMx->ARR + 1;

	if(CHn == 1){
		TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
		TIMx->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // OC1M = 110 for PWM Mode 1 output on ch1
		TIMx->CCMR1	|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)
		TIMx->CCR1  = ARR_Value/2; 													// Output Compare Register for channel 1 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC1P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC1E;												// Enable output for ch1
	}
	else if(CHn == 2){
		TIMx->CCMR1 &= ~TIM_CCMR1_OC2M;                     // Clear ouput compare mode bits for channel 2
		TIMx->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // OC1M = 110 for PWM Mode 1 output on ch2
		TIMx->CCMR1	|= TIM_CCMR1_OC2PE;                     // Output 1 preload enable (make CCR1 value changable)	
		TIMx->CCR2  = ARR_Value/2; 													// Output Compare Register for channel 2 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC2P;                       // select output polarity: active high	
		TIMx->CCER |= TIM_CCER_CC2E;												// Enable output for ch2
	}
	else if(CHn == 3){
		TIMx->CCMR2 &= ~TIM_CCMR2_OC3M;                     // Clear ouput compare mode bits for channel 3
		TIMx->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; // OC1M = 110 for PWM Mode 1 output on ch3
		TIMx->CCMR2	|= TIM_CCMR2_OC3PE;                     // Output 1 preload enable (make CCR1 value changable)	
		TIMx->CCR3  = ARR_Value/2; 													// Output Compare Register for channel 3 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC3P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC3E;												// Enable output for ch3
	}
	else if(CHn == 4){
		TIMx->CCMR2 &= ~TIM_CCMR2_OC4M;                     // Clear ouput compare mode bits for channel 4
		TIMx->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; // OC1M = 110 for PWM Mode 1 output on ch4
		TIMx->CCMR2	|= TIM_CCMR2_OC4PE;                     // Output 1 preload enable (make CCR1 value changable)
		TIMx->CCR4  = ARR_Value/2; 													// Output Compare Register for channel 4 (default duty ratio = 50%)				
		TIMx->CCER &= ~TIM_CCER_CC4P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC4E;												// Enable output for ch4
	}	
	
	if(TIMx == TIM1) TIMx->BDTR |= TIM_BDTR_MOE;					// Main output enable (MOE): 0 = Disable, 1 = Enable	
	TIMx->CR1  |= TIM_CR1_CEN;  													// Enable counter	
	
}


void PWM_period_ms(TIM_t *PWM_pin, float period_ms){
	TIM_TypeDef *TIMx = PWM_pin->timer;
	int CHn = PWM_pin->ch;	

 	int ARR_Value = period_ms * 1000;          // [ms] ´ÜÀ§
	if(ARR_Value > 0xFFFF) ARR_Value = 0xFFFF; // maximum ARR value = 65535(16-bit)

	TIMx->ARR    = ARR_Value - 1 ;             // Auto-reload: Upcouting (0..ARR)
}

// TIMx counter frequency: 1MHz
void PWM_pulsewidth_ms(TIM_t *PWM_pin, float pulse_width_ms){ 
	TIM_TypeDef *TIMx = PWM_pin->timer;
	int CHn = PWM_pin->ch;
	
	switch(CHn){
		case 1: TIMx->CCR1 = (uint32_t)(pulse_width_ms * 1000); break;
		case 2: TIMx->CCR2 = (uint32_t)(pulse_width_ms * 1000); break;
		case 3: TIMx->CCR3 = (uint32_t)(pulse_width_ms * 1000); break;
		case 4: TIMx->CCR4 = (uint32_t)(pulse_width_ms * 1000); break;
		default: break;
	}
}