#include "stm32f4xx.h"
#include "myRCC.h"
#include "mySysTick.h"
#include "myGPIO.h"
#include "myUART.h"
#include "myADC.h"
extern uint32_t result;

int main(void){
	RCC_PLL_init();
	SysTick_init();
	UART2_init(9600, POL);
	
	// ADC Initialization---------------------------
	GPIO_init(GPIOA,0, ANALOG);
	ADC_init(GPIOA, 0, POL); 
	
	while(1){
		result = ADC_read();
		printf("%f[V]\r\n", (float)(result*3.3/4095));
		delay(500);
	}
}


void ADC_IRQHandler(void){	
	if ((ADC1->SR & ADC_SR_EOC) == ADC_SR_EOC) {
		result = ADC1->DR;
		
		//ADC1->SR &= ~ADC_SR_EOC; // It is cleared by software or by reading the ADC_DR register.
	}
}
