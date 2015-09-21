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
typedef enum {
    CW = 0, CCW = !CW
} dir_t;
/* Exported constants --------------------------------------------------------*/
#define STEPS_PER_REV	    400
#define MICROSTEPS          16
#define PITCH               5.0
#define TICKS_PER_REV	    2000.0
/* Exported macro ------------------------------------------------------------*/
#define MICROSTEPS_TO_MM(x) (((x) * PITCH) / (STEPS_PER_REV * MICROSTEPS))
/* Exported functions ------------------------------------------------------- */
float32_t isqrtf(float32_t num);
void tim_conf(void);
/* Exported variables ------------------------------------------------------- */
__IO uint32_t y_steps;
// dir_t y_dir = CW;

#endif /* CNC_MAIN_H */
