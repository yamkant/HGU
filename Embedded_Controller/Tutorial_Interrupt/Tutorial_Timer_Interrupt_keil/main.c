#include "stm32f4xx.h"
#include "EC_SysClk.h"
#include "EC_SysTimer.h"
#include "EC_GPIO.h"

int count_ms = 0; //[ms]
int count_s  = 0; //[s]

int main() {
	SysClk_Init(); // Switch System Clock = 84 MHz
	LED_Init();
	TIM2_Int_Init();
	NVIC_EnableIRQ(TIM2_IRQn); 			// 'core_cm4.h'
	NVIC_SetPriority(TIM2_IRQn, 2); // 'core_cm4.h'
	while(1);
}

// TIM2_IRQHanalder: Copy from startup_stm32f411xe.s
void TIM2_IRQHandler(void){
	  if ((TIM2->SR & TIM_SR_UIF) != 0) { //U1F pended;
			count_ms++;
			if(count_ms == 1000) {
				LED_Toggle();
				count_s++;
				count_ms = 0;
			}			
			TIM2->SR &= ~TIM_SR_UIF; // Clear UIF flag 
		}
}