#include "stm32f4xx.h"
#include "myPWM.h"

void PWM_pinmap(PWM_t *PWM_pin){
   GPIO_TypeDef *port = PWM_pin->port;
   int pin = PWM_pin->pin;
   
   if(port == GPIOA) {
      switch(pin){
         case 0 : PWM_pin->timer = TIM2; PWM_pin->ch = 1; break;
         case 1 : PWM_pin->timer = TIM2; PWM_pin->ch = 2; break;
         case 5 : PWM_pin->timer = TIM2; PWM_pin->ch = 1; break;
         case 6 : PWM_pin->timer = TIM3; PWM_pin->ch = 1; break;
         //case 7: PWM_pin->timer = TIM1; PWM_pin->ch = 1N; break;
         case 8 : PWM_pin->timer = TIM1; PWM_pin->ch = 1; break;
         case 9 : PWM_pin->timer = TIM1; PWM_pin->ch = 2; break;
         case 10: PWM_pin->timer = TIM1; PWM_pin->ch = 3; break;
         case 15: PWM_pin->timer = TIM2; PWM_pin->ch = 1; break;
         default: break;
      }         
   }
   else if(port == GPIOB) {
      switch(pin){
         //case 0: PWM_pin->timer = TIM1; PWM_pin->ch = 2N; break;
         //case 1: PWM_pin->timer = TIM1; PWM_pin->ch = 3N; break;
         case 3 : PWM_pin->timer = TIM2; PWM_pin->ch = 2; break;
         case 4 : PWM_pin->timer = TIM3; PWM_pin->ch = 1; break;
         case 5 : PWM_pin->timer = TIM3; PWM_pin->ch = 2; break;
         case 6 : PWM_pin->timer = TIM4; PWM_pin->ch = 1; break;
         case 7 : PWM_pin->timer = TIM4; PWM_pin->ch = 2; break;
         case 8 : PWM_pin->timer = TIM4; PWM_pin->ch = 3; break;
         case 9 : PWM_pin->timer = TIM4; PWM_pin->ch = 3; break;
         case 10: PWM_pin->timer = TIM2; PWM_pin->ch = 3; break;
         
         default: break;
      }
   }
   else if(port == GPIOC) {
      switch(pin){
         case 6 : PWM_pin->timer = TIM3; PWM_pin->ch = 1; break;
         case 7 : PWM_pin->timer = TIM3; PWM_pin->ch = 2; break;
         case 8 : PWM_pin->timer = TIM3; PWM_pin->ch = 3; break;
         case 9 : PWM_pin->timer = TIM3; PWM_pin->ch = 4; break;
         
         default: break;
      }
   }
}

void PWM_init(PWM_t *PWM_pin, GPIO_TypeDef *port, int pin){
      PWM_pin->port = port;
      PWM_pin->pin  = pin;
   
      PWM_pinmap(PWM_pin);
      
      if(port == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;          // Enable GPIOA clock
      else if(port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;     // Enable GPIOB clock
      else if(port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;     // Enable GPIOC cloc   
   
      // Set PA_5 I/O direction as Alternative Function 1
      port->MODER     &= ~(0x03 << (2*pin));               // Clear bits
      port->MODER     |= 0x02 << (2*pin);                  // AlterFunc(10)
   
      //Set I/O output speed value as very high speed
      port->OSPEEDR  &= ~(0x03<<(2*pin));                         // Speed mask
      port->OSPEEDR  |=   0x03<<(2*pin);                          // High speed
      port->PUPDR    &= ~(0x03<<(2*pin));                         // No PUPD(00, reset)
			port->OTYPER   &=  ~(1<<pin) ;                              // Push-Pull(0, reset)
      
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
}


void PWM_period_ms(PWM_t *PWM_pin, int period_ms){
	TIM_TypeDef *TIMx = PWM_pin->timer;
	int CHn = PWM_pin->ch;	
	
 	int ARR_Value = period_ms * 10;          
	if(ARR_Value > 0xFFFF) ARR_Value = 0xFFFF; // maximum ARR value = 65535(16-bit) --> maximum period: 6553.5[ms]

	TIMx->PSC    = 8399;                                // Prescaler = 8399 --> f_cnt = 10kHz
	TIMx->ARR    = ARR_Value - 1 ;                      // Auto-reload: Upcouting (0..ARR), Downcouting (ARR..0)
	
	TIMx->CR1 &= ~TIM_CR1_DIR;                          // Counting direction: 0 = up-counting, 1 = down-counting
	
		
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

// TIMx counter frequency: 10kHz
void PWM_pulsewidth_ms(PWM_t *PWM_pin, int pulse_width_ms){ 
	TIM_TypeDef *TIMx = PWM_pin->timer;
	int CHn = PWM_pin->ch;
	
	switch(CHn){
		case 1: TIMx->CCR1 = pulse_width_ms * 10; break;
		case 2: TIMx->CCR2 = pulse_width_ms * 10; break;
		case 3: TIMx->CCR3 = pulse_width_ms * 10; break;
		case 4: TIMx->CCR4 = pulse_width_ms * 10; break;
		default: break;
	}
}