#include "EC_SysTimer.h"

uint32_t msTicks;

void SysTick_Init(void){
   //  SysTick Control and Status Register
   SysTick->CTRL = 0;                      // Disable SysTick IRQ and SysTick Counter
   
   // SysTick Reload Value Register
	 SysTick->LOAD = 84000000/1000 - 1;    // 1ms, Default clock
   
   // SysTick Current Value Register
   SysTick->VAL = 0;

   NVIC_SetPriority(SysTick_IRQn, 1);      // Set Priority to 1
   NVIC_EnableIRQ(SysTick_IRQn);           // Enable EXTI0_1 interrupt in NVIC

   // Enables SysTick exception request
   SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
   
   // Select processor clock
   SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;      
   
   // Enable SysTick IRQ and SysTick Timer
   SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}

// SysTick Interrupt Handler
void SysTick_Handler(void){
   msTicks++;
}
   
// Delay in [ms]
void delay (uint32_t T){
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < T){;}
   
  msTicks = 0;
}


void TIM2_Int_Init(void){
    RCC->APB1ENR	|= RCC_APB1ENR_TIM2EN; // Enable TIMER2 clock
		TIM2->CR1  		&= ~TIM_CR1_DIR;       // Counting direction: 0 = up-counting, 1 = down-counting
    TIM2->PSC 		 = 839;                // timer clock 84MHz/(839 + 1) = 100kHz (0.01ms)
    TIM2->ARR   	 = 100 - 1;            // Auto-reload: Upcouting (0..ARR), Downcouting (ARR..0)
		TIM2->DIER 		|= TIM_DIER_UIE;       // DMA/Interrupt Enable Register: UIE = 1
		TIM2->CR1  		|= TIM_CR1_CEN;        // Enable counter	
}