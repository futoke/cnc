/*
 * buffer.c
 *
 *  Created on: 12.02.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "buffer.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void buff_init(__IO fifo_t *buffer)
{
    buffer->counter = 0; // 0 bytes in the buffer
    buffer->head = 0;    // Index points to start
    buffer->tail = 0;    // Index points to start
}


void buff_put(__IO fifo_t *buffer, uint8_t ch)
{
    buffer->buff[BUFF_MASK & (buffer->head++)] = ch;
    buffer->counter++;
}

uint8_t buff_get(__IO fifo_t *buffer)
{
    uint8_t ch;

    ch = buffer->buff[BUFF_MASK & (buffer->tail++)];
    buffer->counter--;

    return ch;
}

bool buff_empty(__IO fifo_t buffer)
{
    return (buffer.counter == 0) ? true : false;
}

bool buff_full(__IO fifo_t buffer)
{
    return (buffer.counter == BUFF_SIZE) ? true : false;
}
