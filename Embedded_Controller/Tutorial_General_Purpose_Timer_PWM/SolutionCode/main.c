#include "stm32f4xx.h"
#include "myRCC.h"
#include "myPWM.h"
#include "myEXTI.h"

int button_cnt = 0;
float button_state = 0;

int main() {   
	RCC_PLL_init();                         // System Clock = 84MHz
	
	EXTI_init(GPIOC, 13, FALL, 0);
	
	PWM_t pwm;	
	PWM_init(&pwm, GPIOA, 1);
	PWM_period_ms(&pwm, 10);

	while(1) {         
		PWM_pulsewidth_ms(&pwm, button_state);		
	}
}

void EXTI15_10_IRQHandler(){
   if((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13){
      button_cnt++;
      button_cnt = button_cnt % 11;
      button_state = button_cnt*0.2 + 0.5;
      EXTI->PR |= EXTI_PR_PR13;
   }
 }

//#include "stm32f4xx.h"
//#include "myRCC.h"
//#include "myPWM.h"
//#include "myGPIO.h"
//#include "mySysTick.h"
//#include "myEXTI.h"
//#include <stdbool.h>

//int main(void){
//	RCC_PLL_init();
//	SysTick_init();
//	EXTI_init(GPIOC, 13, FALL, 1);
//	
//  PWM_t PA5;
//  PWM_init(&PA5, GPIOA, 5);
//  PWM_period_ms(&PA5, 10);
//	
//	int pw = 0;
//	bool UP = 1;
//	
//	while(1){		
//		if(pw == 10) 			UP = 0;
//		else if(pw == 0) 	UP = 1;
//		
//		if(UP) pw++;
//		else pw--;
//		
//		PWM_pulsewidth_ms(&PA5, pw);
//		delay(100);
//	}
//}