#include "stm32f4xx.h"
#include "myRCC.h"
#include "myGPIO.h"
#include "mySysTick.h"

// IN1 ~ IN4: PB10, PB4, PB5, PB3
// Full Step: 0b1001, 0b1100, 0b0110, 0b0011
// Half Step: 0b1001, 0b1000, 0b1100, 0b0100, 0b0110, 0b0010, 0b0011, 0b0001

uint8_t full_step[4] = {0b1001, 0b1100, 0b0110, 0b0011};
uint8_t half_step[8] = {0b1001, 0b1000, 0b1100, 0b0100, 0b0110, 0b0010, 0b0011, 0b0001};

void Full_step();
void Half_step();

int main(void){
	RCC_PLL_init();
	
	SysTick_init();
	
	GPIO_init(GPIOB, 10, OUTPUT); // IN1
	GPIO_init(GPIOB, 4, OUTPUT);	// IN2
	GPIO_init(GPIOB, 5, OUTPUT);	// IN3
	GPIO_init(GPIOB, 3, OUTPUT);	// IN4
	int cnt = 0;
	while(1){
		Full_step();
		cnt++;
		if(cnt == 512) break;
		
		//Half_step();
	}
	
}

void Full_step(){
	for(int i = 0; i < 4; i++){
		GPIO_write(GPIOB, 10, (full_step[i] & 0b1000) >> 3);
		GPIO_write(GPIOB,  4, (full_step[i] & 0b0100) >> 2);
		GPIO_write(GPIOB,  5, (full_step[i] & 0b0010) >> 1);
		GPIO_write(GPIOB,  3, (full_step[i] & 0b0001) >> 0);
		delay(2);
	}
}

void Half_step(){
	for(int i = 0; i < 8; i++){
		GPIO_write(GPIOB, 10, (half_step[i] & 0b1000) >> 3);
		GPIO_write(GPIOB,  4, (half_step[i] & 0b0100) >> 2);
		GPIO_write(GPIOB,  5, (half_step[i] & 0b0010) >> 1);
		GPIO_write(GPIOB,  3, (half_step[i] & 0b0001) >> 0);
		delay(1);
	}
}