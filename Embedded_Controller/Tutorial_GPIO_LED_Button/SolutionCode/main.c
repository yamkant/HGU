#include "stm32f4xx.h"
#include "myRCC.h"
#include "myGPIO.h"

int main(void) { 
	// Initialiization --------------------------------------------------------
	RCC_HSI_init();
	
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);
	GPIO_init(GPIOA, LED_PIN, OUTPUT);
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		if(GPIO_read(GPIOC, BUTTON_PIN) == 0)	GPIO_write(GPIOA, LED_PIN, HIGH);
		else 																	GPIO_write(GPIOA, LED_PIN, LOW);
	}
}