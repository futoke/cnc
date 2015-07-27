/* interval.h
 *
 *  Created on: 27.07.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_INTERVAL_H
#define CNC_INTERVAL_H

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef void (*task_ptr_t)(void);
typedef uint16_t tim_t;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void interval_service(void);
void set_interval_task(task_ptr_t task, tim_t time);
void interval_conf(void);
/* Exported variables --------------------------------------------------------*/

#endif /* CNC_INTERVAL_H */
