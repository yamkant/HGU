#include "stm32f4xx.h"
#include "myRCC.h"
#include "mySysTick.h"
#include "myGPIO.h"
#include "myUART.h"
#include "myADC.h"
#include "myTIM.h"

float read;
int print_flag;
int main(){
	
	RCC_PLL_init();
  SysTick_init();
  UART2_init(9600,POL);	
	TIM3_init(1000); 					// 1sec
	GPIO_init(GPIOA,0,ANALOG);
	ADC_init(GPIOA, 0,EXT); 
	
	while(1){
		if (print_flag == 1){
	  printf("CH1 = %f[V] \r\n", read);   
		print_flag = 0;
	}
 }
	
}

void ADC_IRQHandler(void){
	if( (ADC1->SR & ADC_SR_EOC) != 0){
	  read = (float) ADC_read();
		read = read*3.3/4095;
		print_flag = 1;		
	}
}
