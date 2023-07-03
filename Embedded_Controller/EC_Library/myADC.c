#include "stm32f411xe.h"
#include "mySysTick.h"
#include "myADC.h"
#include "myGPIO.h"
#include <stdint.h>
uint32_t result;

//******************************************************************************************
// ZHU: STM32L4x6xx Errata sheet
// When the delay between two consecutive ADC conversions is higher than 1 ms the result of 
// the second conversion might be incorrect. The same issue occurs when the delay between the 
// calibration and the first conversion is higher than 1 ms.
// Workaround
// When the delay between two ADC conversions is higher than the above limit, perform two ADC 
// consecutive conversions in single, scan or continuous mode: the first is a dummy conversion 
// of any ADC channel. This conversion should not be taken into account by the application.


void ADC_init(GPIO_TypeDef *port, int pin, int type){
	
	RCC->APB2ENR  |= RCC_APB2ENR_ADC1EN; // Enable the clock of ADC
	
	int CHn = ADC_pinmap(port, pin);		// ADC Channel <->Port/Pin mapping
	
	// ADC_Common_Configuration();--------------------------------------------------------------
	
	ADC1_COMMON->CCR |= ADC_CCR_TSVREFE;		// to read embedded temperature sensor(?)
	ADC1_COMMON->CCR &= ~ADC_CCR_ADCPRE;		// 0000: PCLK2 divided by 2	(42MHz)
	
	ADC1->CR1 &= ~ADC_CR1_RES;     	// 00: 12-bit resolution
	ADC1->CR1 |= ADC_CR1_SCAN;			// 1: Scan mode enable 
	ADC1->CR2 &= ~ADC_CR2_ALIGN;   	// 0: Right alignment
	ADC1->CR2 |= ADC_CR2_CONT;      // Enable Continuous conversion mode		
	
	//************************************************************************************
	ADC1->CR2 &= ~ADC_CR2_CONT;     // Discontinuous conversion mode		
	
	// Specify the channel number of the 1st conversion in regular sequence.
	// If you want to use multi-channel, this part should be modified. 
	ADC1->SQR1 &= ~ADC_SQR1_L; // 0000: 1 conversion in the regular channel conversion sequence
	
	ADC1->SQR3 &= ~ADC_SQR3_SQ1;				 // SQ1 clear bits
	ADC1->SQR3 |= (CHn & ADC_SQR3_SQ1); // Choose the channel to convert firstly
	
	// ADC Sample Time
	// Software is allowed to write these bits only when ADSTART=0 and JADSTART=0	!!
	// Sample time selection--------------------------------------------------------------------
	// 4: 84 ADC clock cycles @42MHz = 2us(?)
	if(CHn < 10) ADC1->SMPR2  |= 4U << (3* CHn); 
	else				 ADC1->SMPR1  |= 4U << (3* (CHn - 10)); 
	
	
	if(type == EXT) {
		ADC1->CR2 &= ~ADC_CR2_EXTSEL; 
		ADC1->CR2 |= ADC_CR2_EXTSEL_3; // 8<<24; // TIM3 TRGO event
		ADC1->CR2 &= ~ADC_CR2_EXTEN;
		ADC1->CR2 |= ADC_CR2_EXTEN; // trigger detection rising edge
		
	}
	
	// ADC complete interrupt enable
	if(type == INT || type == EXT){
		ADC1->CR1 |= ADC_CR1_EOCIE;	// Enable interrupt (EOC: End of Conversion)	
	  NVIC_SetPriority(ADC_IRQn, 1); 	// Set Priority to 1
	  NVIC_EnableIRQ(ADC_IRQn);      	// Enable interrupt form ACD1 peripheral				
	}
	
	// Enable ADC-------------------------------------------------------------------------------
	ADC1->CR2 |= ADC_CR2_ADON; 
	ADC1->CR2 |= ADC_CR2_SWSTART;
}


uint32_t ADC_read(){
	// SWSTART bit should always be set when continuous mode is disabled! // ADC1->CR2 |= ADC_CR2_SWSTART;
	ADC1->CR2 |= ADC_CR2_SWSTART; // discontinuous mode
	while ( (ADC1->SR & ADC_SR_EOC) == !ADC_SR_EOC);
	return ADC1->DR;
}


uint32_t ADC_pinmap(GPIO_TypeDef *Port, int Pin){
	if(Port == GPIOA){
		if(Pin == 0) 			return 0;
		else if(Pin == 1) return 1;
		else if(Pin == 4) return 4;
		else if(Pin == 5) return 5;
		else if(Pin == 6) return 6;
		else if(Pin == 7) return 7;
		else 							while(1);
	}
	else if(Port == GPIOB){
		if(Pin == 0) 			return 8;
		else if(Pin == 1)	return 9;
		else 							while(1);
	}
	else if(Port == GPIOC){
		if(Pin == 0)			return 10;
		else if(Pin == 1)	return 11;
		else if(Pin == 2)	return 12;
		else if(Pin == 3)	return 13;
		else if(Pin == 4)	return 14;
		else if(Pin == 5)	return 15;
		else							while(1);
	}
}