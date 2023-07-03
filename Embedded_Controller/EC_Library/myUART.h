#ifndef __MY_UART_H
#define __MY_UART_H

#include "stm32f411xe.h"
#include <stdio.h>

#define POL 0
#define INT 1

typedef struct{
   USART_TypeDef *USARTx;
   GPIO_TypeDef *tx_port;
   GPIO_TypeDef *rx_port;
   
   int tx_pin;               
   int rx_pin;
   
   int baud_rate;   
   int type;
   int mode;
} UART_t;

void UART1_GPIO_init(void);
void UART2_GPIO_init(void);

void BT_init(int baud_rate);
void BT_write(uint8_t *buffer, uint32_t nBytes);
uint8_t BT_read ();

void UART1_init(int baud_rate, int mode);
void UART2_init(int baud_rate, int mode);

void USART_init (USART_TypeDef * USARTx, int baud_rate, int mode);
void USART_write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes);
uint8_t USART_read (USART_TypeDef * USARTx);
void USART_delay(uint32_t us);

void USART_IRQHandler(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t * pRx_counter);

#endif