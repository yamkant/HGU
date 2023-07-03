#include "stm32f4xx.h"
#include "EC_SysClk.h"
#include "EC_GPIO.h"
#include "EC_EXTI.h"


int main(void) {
	
	SysClk_Init(); 
	LED_Init();
	EXTI_Init(GPIOC, 13, FALL, 0); // EXTI_Init(PORT, PIN, TRIGGER, PRIORITY)
	
	while(1);
}

// Copy from 'startup_stm32f411xe.s'
void EXTI15_10_IRQHandler(void) {  
	if ((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13) {
		LED_Toggle();
		EXTI->PR |= EXTI_PR_PR13; // cleared by writing '1'
	}
}

