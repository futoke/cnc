/*
 * interval.c
 *
 *  Created on: 27.08.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "interval.h"
/* Private typedef -----------------------------------------------------------*/
typedef struct {
    task_ptr_t task;
    tim_t time;
    tim_t time_cnt;
} interval_queue_t;
/* Private define ------------------------------------------------------------*/
#define MAX_TASKS					100
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
interval_queue_t interval_queue[MAX_TASKS];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void interval_service(void)
{
    uint8_t i;
    
    for (i = 0; i < MAX_TASKS; i++) {
        if (interval_queue[i].task == NULL) {
            continue;
        }
        if (interval_queue[i].time_cnt) {
            interval_queue[i].time_cnt--;
        } else {
            (interval_queue[i].task)();

            interval_queue[i].time_cnt = interval_queue[i].time;
        }
    }
}

void set_interval_task(task_ptr_t task, tim_t time)
{
    uint8_t i;
    
    for (i = 0; i < MAX_TASKS; i++) {
        if (interval_queue[i].task == NULL) {
            
            interval_queue[i].task = task;
            interval_queue[i].time = time;
            interval_queue[i].time_cnt = time;
            
            return;
        }
    }
}

void interval_conf(void)
{
    uint8_t i;
    
    for (i = 0; i < MAX_TASKS; i++) {
        interval_queue[i].task = NULL;
        interval_queue[i].time = 0;
        interval_queue[i].time_cnt = 0;
    }
    
    // Initialize SysTick timer with 1ms period.
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1)
            ;
    }
}
