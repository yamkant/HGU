#include "stm32f4xx.h"
#include "myRCC.h"
#include "myGPIO.h"
#include "mySysTick.h"
#include "myEXTI.h"

extern int count;

int main(void) {
	RCC_PLL_init();
	SysTick_init();
	
	SevenSegment_init();
	EXTI_init(GPIOC, 13, FALL, 2);
	
	while(1){
		SevenSegment_on(count%10);
	}
}

// Copy from 'startup_stm32f411xe.s'
void EXTI15_10_IRQHandler(void) {  
	if ((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13) {
		count = 0;
		EXTI->PR |= EXTI_PR_PR13; // cleared by writing '1'
	}
}