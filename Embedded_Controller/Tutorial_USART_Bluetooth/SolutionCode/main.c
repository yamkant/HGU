#include <stdio.h>
#include "stm32f4xx.h"
#include "myRCC.h"
#include "mySysTick.h"
#include "myUART.h"
#include <math.h>
#include <stdbool.h>


uint8_t rxByte;  

int main(void){
	RCC_PLL_init(); 
	SysTick_init();
	
	BT_init(9600);
	
	UART2_init(9600, INT);
	
	BT_write((uint8_t *) "Hello Bluetooth\r\n", 17);
	printf("Hello Nucleo\r\n");
	
  while(1){}
}

void USART1_IRQHandler(){
	if(USART1->SR & USART_SR_RXNE) { // Received data
		rxByte = BT_read();
		BT_write(&rxByte, 1);
	}
}

//void USART2_IRQHandler(){
//	if(USART2->SR & USART_SR_RXNE) { // Received data                         
//		rxByte = USART2->DR; // clear RXNE
//		printf("%c", rxByte);
//	} 
//	
//}

/*
//USART_write(USART2, (uint8_t *)"HI\r\n", 4);
rxByte = USART_read(USART2);

//printf("%c\r\n", rxByte);      
if (rxByte == 'H' || rxByte == 'h'){
	 LED_on();
	 //printf("%c\r\n", rxByte);
	 printf("LED is ON\r\n");
	 //USART_write(USART2, (uint8_t *)"LED is on\r\n", 11);
}
else if (rxByte == 'L' || rxByte == 'l'){
	 LED_off();
	 //printf("%c\r\n", rxByte);
	 //USART_write(USART2, (uint8_t *)"LED is off\r\n", 12);
	 printf("LED is OFF\r\n");
}*/
