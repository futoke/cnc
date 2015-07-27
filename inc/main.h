/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_MAIN_H
#define CNC_MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <inttypes.h>

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "usart.h"
#include "buffer.h"
#include "encoder.h"
#include "lcd.h"
#include "cmd.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define STEPS_PER_REVOLUTION	200
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */


#define MAX_TIMERS					100

typedef void (*task_ptr_t)(void);
typedef uint16_t ticks_t;
typedef struct {
    task_ptr_t task;
    ticks_t ticks;
    ticks_t ticks_cnt;
} timer_queue_t;

timer_queue_t timer_queue[MAX_TIMERS];

#endif /* CNC_MAIN_H */
