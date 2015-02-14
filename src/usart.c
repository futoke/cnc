/*
 * usart.c
 *
 *  Created on: 06.02.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO fifo_t rx_buff, tx_buff;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void usart_conf(void)
{
    // Buffers init
    buff_init(&rx_buff);
    buff_init(&tx_buff);
    cmd_init(&cmd);

    // Interrupts init
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* USARTx configured as follows:
     - BaudRate = 115200 baud
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - Hardware flow control disabled (RTS and CTS signals)
     - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = \
            USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);

    NVIC_InitStructure.NVIC_IRQChannel = EVAL_COM1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    STM_EVAL_COMInit(COM1, &USART_InitStructure);
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(EVAL_COM1, USART_IT_RXNE, ENABLE);
}

void usart_putch(uint8_t ch)
{
    while (buff_full(tx_buff))
        ;
    USART_ITConfig(EVAL_COM1, USART_IT_TXE, DISABLE);
    buff_put(&tx_buff, ch);
    USART_ITConfig(EVAL_COM1, USART_IT_TXE, ENABLE);
}

uint8_t usart_getch(void)
{
    while (buff_empty(rx_buff))
        ;
    return buff_get(&rx_buff);
}

void usart_puts(uint8_t *str)
{
  while (*str)
    usart_putch(*str++);
}
