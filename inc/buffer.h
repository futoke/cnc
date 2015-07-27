/*
 * buffer.h
 *
 *  Created on: 06.02.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_BUFFER_H
#define CNC_BUFFER_H

/* Includes ------------------------------------------------------------------*/
#include  <stdbool.h>
#include "stm32f4xx.h"

/* Exported constants --------------------------------------------------------*/
#define BUFF_SIZE 256
/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint16_t head;
    uint16_t tail;
    uint16_t counter;
    uint8_t buff[BUFF_SIZE];
} fifo_t;
/* Exported macro ------------------------------------------------------------*/
#define BUFF_MASK (BUFF_SIZE - 1)
/* Exported functions ------------------------------------------------------- */
void buff_init(__IO fifo_t *buffer);
void buff_put(__IO fifo_t *buffer, uint8_t ch);
uint8_t buff_get(__IO fifo_t *buffer);
bool buff_empty(__IO fifo_t buffer);
bool buff_full(__IO fifo_t buffer);
/* Exported variables --------------------------------------------------------*/

#endif /* CNC_BUFFER_H */
