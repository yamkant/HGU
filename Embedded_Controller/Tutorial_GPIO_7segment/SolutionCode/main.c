#include "stm32f4xx.h"
#include "myLib.h"

int main(void) {
	RCC_HSI_init();	
	
	GPIO_init(GPIOC, 13, INPUT);	
	SevenSegment_init();
	
	long long cnt = 0;
	
	while(1){
		SevenSegment_on(cnt % 10);
		if(GPIO_read(GPIOC,13) == 0) cnt++; 
		for(int i = 0; i < 500000;i++){}
//		cnt ++;
	}
}


//#include "stm32f4xx.h"
//#include "myGPIO.h"
//#include "myRCC.h"

//int main(void) {
//	RCC_HSI_init();	
//	
//	GPIO_init(GPIOA, 5, 1); // a	
//	GPIO_init(GPIOA, 6, 1); // b
//	GPIO_init(GPIOA, 7, 1); // c
//	GPIO_init(GPIOB, 6, 1); // d
//	GPIO_init(GPIOC, 7, 1); // e
//	GPIO_init(GPIOA, 9, 1); // f
//	GPIO_init(GPIOA, 8, 1); // g
//	GPIO_init(GPIOB, 10, 1); // dp	
//		
//	while(1){
//		int ON = 0b00000011;
//		GPIO_write(GPIOA, 5, (ON >> 7) & 1);
//		GPIO_write(GPIOA, 6, (ON >> 6) & 1);
//		GPIO_write(GPIOA, 7, (ON >> 5) & 1);
//		GPIO_write(GPIOB, 6, (ON >> 4) & 1);
//		GPIO_write(GPIOC, 7, (ON >> 3) & 1);
//		GPIO_write(GPIOA, 9, (ON >> 2) & 1);
//		GPIO_write(GPIOA, 8, (ON >> 1) & 1);
//		GPIO_write(GPIOB, 10, ON & 1);					
//	}
//}