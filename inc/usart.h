/* usart.h
 *
 *  Created on: 06.02.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_USART_H
#define CNC_USART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "buffer.h"
#include "cmd.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void usart_conf(void);
void usart_putch(uint8_t ch);
uint8_t usart_getch(void);
void usart_puts(uint8_t *str);
/* Exported variables --------------------------------------------------------*/
extern __IO fifo_t rx_buff, tx_buff;

#endif /* CNC_USART_H */
