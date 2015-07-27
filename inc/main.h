/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_MAIN_H
#define CNC_MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "usart.h"
#include "buffer.h"
#include "encoder.h"
#include "interval.h"
#include "lcd.h"
#include "cmd.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define STEPS_PER_REV	200
#define TICKS_PER_REV	2000.0
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */

#endif /* CNC_MAIN_H */
