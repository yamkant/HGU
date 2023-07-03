#include "myTIM.h"
#include "myPWM.h"
#include "myGPIO.h"
uint32_t beg = 0;
uint32_t end = 0;
uint32_t ovf_cnt = 0;
uint32_t timeInterval = 0;
float distance = 0.0;

void TIM_pinmap(TIM_t *timer_pin){
   GPIO_TypeDef *port = timer_pin->port;
   int pin = timer_pin->pin;
   
   if(port == GPIOA) {
      switch(pin){
         case 0 : timer_pin->timer = TIM2; timer_pin->ch = 1; break;
         case 1 : timer_pin->timer = TIM2; timer_pin->ch = 2; break;
         case 5 : timer_pin->timer = TIM2; timer_pin->ch = 1; break;
         case 6 : timer_pin->timer = TIM3; timer_pin->ch = 1; break;
         //case 7: timer_pin->timer = TIM1; timer_pin->ch = 1N; break;
         case 8 : timer_pin->timer = TIM1; timer_pin->ch = 1; break;
         case 9 : timer_pin->timer = TIM1; timer_pin->ch = 2; break;
         case 10: timer_pin->timer = TIM1; timer_pin->ch = 3; break;
         case 15: timer_pin->timer = TIM2; timer_pin->ch = 1; break;
         default: break;
      }         
   }
   else if(port == GPIOB) {
      switch(pin){
         //case 0: timer_pin->timer = TIM1; timer_pin->ch = 2N; break;
         //case 1: timer_pin->timer = TIM1; timer_pin->ch = 3N; break;
         case 3 : timer_pin->timer = TIM2; timer_pin->ch = 2; break;
         case 4 : timer_pin->timer = TIM3; timer_pin->ch = 1; break;
         case 5 : timer_pin->timer = TIM3; timer_pin->ch = 2; break;
         case 6 : timer_pin->timer = TIM4; timer_pin->ch = 1; break;
         case 7 : timer_pin->timer = TIM4; timer_pin->ch = 2; break;
         case 8 : timer_pin->timer = TIM4; timer_pin->ch = 3; break;
         case 9 : timer_pin->timer = TIM4; timer_pin->ch = 3; break;
         case 10: timer_pin->timer = TIM2; timer_pin->ch = 3; break;
         
         default: break;
      }
   }
   else if(port == GPIOC) {
      switch(pin){
         case 6 : timer_pin->timer = TIM3; timer_pin->ch = 1; break;
         case 7 : timer_pin->timer = TIM3; timer_pin->ch = 2; break;
         case 8 : timer_pin->timer = TIM3; timer_pin->ch = 3; break;
         case 9 : timer_pin->timer = TIM3; timer_pin->ch = 4; break;
         
         default: break;
      }
   }
}
void TIM_period_us(uint32_t nTimer, float usec){ // usec < 100
	TIM_TypeDef *TIMx;
	uint32_t prescaler = 0;
	
	switch(nTimer){
		case 1: TIMx = TIM1; RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; break;
		case 2: TIMx = TIM2; RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;break;
		case 3: TIMx = TIM3; RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; break;
		case 4: TIMx = TIM4; RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; break;
		case 9: TIMx = TIM9; RCC->APB2ENR |= RCC_APB2ENR_TIM9EN; break;
		case 11: TIMx = TIM11; RCC->APB2ENR |= RCC_APB2ENR_TIM11EN; break;
	}
	prescaler = (uint32_t)(84*usec) - 1;
	TIMx->PSC = prescaler;							// Timer counter clock: 1MHz(1us)
	TIMx->ARR = 0xFFFF;									// Set auto reload register to maximum (count up to 65535)
	TIMx->CR1 &= ~TIM_CR1_DIR;					// Upcounter	
}

void CAP_init(TIM_t *cap_pin, GPIO_TypeDef *port, int pin){	
	cap_pin->port = port;
	cap_pin->pin  = pin;
	
	TIM_pinmap(cap_pin);	// Port, Pin --(mapping)--> Timer, Channel
	
	TIM_TypeDef *TIMx = cap_pin->timer;
	int 				CHn 	= cap_pin->ch; 
	
	if(TIMx == TIM1 || TIMx == TIM2)											 port->AFR[pin >> 3] |= 0x01 << (4*(pin % 8)); // TIM1~2
	else if(TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5)  port->AFR[pin >> 3] |= 0x02 << (4*(pin % 8)); // TIM3~5 
	else if(TIMx == TIM9 || TIMx == TIM10|| TIMx == TIM11) port->AFR[pin >> 3] |= 0x03 << (4*(pin % 8)); // TIM9~11 
	
	// Initial Default Setting
	switch(CHn){
		case 1: // CC1 is mapped on TI1, CC2 is mapped on TI1		
			TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_0; 
			TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_1;
		break;
		case 2: // CC1 is mapped on TI2, CC2 is mapped on TI2		
			TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_1; 
			TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_0;
		break;		
		case 3:	// CC3 is mapped on TI3, CC4 is mapped on TI3
			TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_0; 
			TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_1;
		break;
		case 4: // CC3 is mapped on TI4, CC4 is mapped on TI4
			TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_1; 
			TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_0;
		break;
		default: break;
	}
	
	if(CHn == 1 || CHn == 2) {
		TIMx->CCER &= ~(0b1010 << 4*0);	// CC1(Rising)
		TIMx->CCER |=  (0b0010 << 4*1); // CC2(Falling)
		TIMx->CCER |= 1 << (4*0);				// CC1 Capture Enable	
		TIMx->CCER |= 1 << (4*1);				// CC2 Capture Enable
		TIMx->DIER |= (1 << 1)|(1 << 2);// Capture interrupt Enable		
	}
	else if(CHn == 3 || CHn == 4) {
		TIMx->CCER &= ~(0b1010 << 4*2);	// CC3(Rising)
		TIMx->CCER |=  (0b0010 << 4*3); // CC4(Falling)
		TIMx->CCER |= 1 << (4*2);				// CC3 Capture Enable	
		TIMx->CCER |= 1 << (4*3);				// CC4 Capture Enable
		TIMx->DIER |= (1 << 3)|(1 << 4);// Capture interrupt Enable
	}

	TIMx->DIER |= TIM_DIER_UIE;			// Update interrupt enable	
	TIMx->CR1	 |= TIM_CR1_CEN;			// Counter enable
}

void CAP_setup(TIM_t *cap_pin, int ICn_type, int edge_type){
	TIM_TypeDef *TIMx = cap_pin->timer;	// TIMx
	int 				CHn 	= cap_pin->ch;		// Channel n
	int 				ICn 	= 0;
	
	switch(ICn_type){
		case FIRST: 
				switch(CHn){
					case 1: ICn = 1; TIMx->CCMR1 &= ~(TIM_CCMR1_CC1S); TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_0;break; //IC1 is mapped on TI1
					case 2: ICn = 1; TIMx->CCMR1 &= ~(TIM_CCMR1_CC1S); TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_1;break; //IC1 is mapped on TI2
					case 3: ICn = 3; TIMx->CCMR2 &= ~(TIM_CCMR2_CC3S); TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_0;break; //IC3 is mapped on TI3
					case 4: ICn = 3; TIMx->CCMR2 &= ~(TIM_CCMR2_CC3S); TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_1;break; //IC3 is mapped on TI4
					default: break;
				}
		break;
		case SECOND:
				switch(CHn){
					case 1: ICn = 2; TIMx->CCMR1 &= ~(TIM_CCMR1_CC2S); TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_1;break; //IC2 is mapped on TI1
					case 2: ICn = 2; TIMx->CCMR1 &= ~(TIM_CCMR1_CC2S); TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_0;break; //IC2 is mapped on TI2
					case 3: ICn = 4; TIMx->CCMR2 &= ~(TIM_CCMR2_CC4S); TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_1;break; //IC4 is mapped on TI3
					case 4: ICn = 4; TIMx->CCMR2 &= ~(TIM_CCMR2_CC4S); TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_0;break; //IC4 is mapped on TI4
					default: break;
				}
		break;
		default: break;
	}
	
	TIMx->CCER  &= ~(0b1010 << 4*(ICn - 1)); // Clear CCnNP/CCnP bits
	switch(edge_type){
		case RISE: TIMx->CCER &= ~(0b1010 << 4*(ICn - 1)); break; //rising:  00
		case FALL: TIMx->CCER |= 0b0010 << 4*(ICn - 1); 	 break; //falling: 01
		case BOTH: TIMx->CCER |= 0b1010 << 4*(ICn - 1); 	 break; //both:    11
	}
	TIMx->DIER |= 1 << ICn; 					// CCn Interrupt enabled	
	TIMx->CCER |= 1 << (4*(ICn - 1)); //Capture Enable
}

void TIM3_init(float msec){
	if(msec>100|| msec<0){
		//msec=100;
	}
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; 
	
	TIM3->CR1        &= ~(1<<4); // up counter

  TIM3->CCMR1    &= ~(7<<4);    
  TIM3->CCMR1   |= 6<<4;           //  output compare pwm_1 mode 
	
	
	TIM3->CCER |= 1;         // CC1 Capture enabled    
  TIM3->CCER &= ~(7<<1) ;         // CC1 Capture rising edge  
	TIM3->CCR1 = (10*msec)-1;
	
  TIM3->CR2 &= ~(7<<4); // timer master mode 	OC1REF to TRGO
  TIM3->CR2 |= 4<<4;
	
	TIM3->PSC = 8399 ;   // Timer counter clock: 84Mhz / PSC + 1 = 10Khz
  TIM3-> ARR = (10*msec)-1 ;         // Set auto reload register                         
	
	
	TIM3->CR1  |= 1;                  // Enable counter
}


// Interrupt Handler=======================================================
void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF){// update interrupt flag
		ovf_cnt++;
		TIM2->SR &= ~TIM_SR_UIF;// clear by writing 0
	}
	if((TIM2->SR & TIM_SR_CC3IF) == TIM_SR_CC3IF){ // CC3 interrupt flag (rising edge)
		beg = TIM2->CCR3 + (uint32_t)(0xFFFF * ovf_cnt);
		ovf_cnt = 0;
		TIM2->SR &= ~TIM_SR_CC3IF;	// it is also cleared by reading TIM2->CCR3
		TIM2->SR &= ~TIM_SR_CC3OF;	// clear overcapture flag
	}
	else if((TIM2->SR & TIM_SR_CC4IF) == TIM_SR_CC4IF){ // CC4 interrupt flag (falling edge)
		end = TIM2->CCR4 + (uint32_t)(0xFFFF * ovf_cnt);
		if(end > beg) timeInterval = end - beg;		
		beg = end;
		ovf_cnt = 0;
		TIM2->SR &= ~TIM_SR_CC4IF;	// it is also cleared by reading TIM2->CCR4
	}
}

void TIM4_IRQHandler(void){
	if(TIM4->SR & TIM_SR_UIF){// update interrupt flag
		ovf_cnt++;
		TIM4->SR &= ~TIM_SR_UIF;// clear by writing 0
	}
	if((TIM4->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF){ // CC1 interrupt flag (rising edge)
		beg = TIM4->CCR1;
		ovf_cnt = 0;
		TIM4->SR &= ~TIM_SR_CC1IF;	// it is also cleared by reading TIM2->CCR1
		TIM4->SR &= ~TIM_SR_CC1OF;	// clear overcapture flag
	}
	else if((TIM4->SR & TIM_SR_CC2IF) == TIM_SR_CC2IF){ // CC2 interrupt flag (falling edge)
		end = TIM4->CCR2 + (uint32_t)(0xFFFF * ovf_cnt);
		if(end > beg) timeInterval = end - beg;
		distance = (float) timeInterval / 58;
		beg = end;
		ovf_cnt = 0;
		TIM4->SR &= ~TIM_SR_CC2IF;	// it is also cleared by reading TIM2->CCR2
	}
}