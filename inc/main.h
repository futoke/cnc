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
    PLUS = 0, MINUS = !PLUS
} dir_t;
typedef enum {
    NO_MOTION = 0, ACCEL, STRIGHT, DECEL, MOTION
} motion_state_t;
typedef enum {
    FALLING = 0, RISING = !FALLING
} edge_t;
typedef struct {
    dir_t dir;
    motion_state_t state;
    uint32_t period;
    uint32_t accel_steps;
    uint32_t stright_steps;
    uint32_t decel_steps;
} motion_t;
/* Exported constants --------------------------------------------------------*/
#define STEPS_PER_REV   200
#define MICROSTEPS      16
#define PITCH           5.0
#define TICKS_PER_REV	2000.0
#define BASE_FREQ       42000000ULL
#define ACCELERATION    (1 * ((STEPS_PER_REV * MICROSTEPS) / PITCH)) // mm/s^2
#define BEGIN_PERIOD    (BASE_FREQ * isqrtf(2 / ACCELERATION))

#define CMD_BUFFER      16
/* Exported macro ------------------------------------------------------------*/
//#define STEPS_TO_MM(x) (((x) * PITCH) / ((STEPS_PER_REV) * MICROSTEPS))
#define MM_TO_STEPS(x) ( \
        (uint64_t)( \
                ((x) * ((STEPS_PER_REV * MICROSTEPS) / PITCH)) + 0.5 \
        ) \
)
#define MM_MIN_TO_PERIOD(x) ( \
        (uint64_t)( \
                ((BASE_FREQ * 60) / (MM_TO_STEPS(x))) + 0.5 \
        ) - 1 \
)
//#define MM_MIN_TO_STEPS_SEC(x) ((uint64_t)())
/* Exported functions ------------------------------------------------------- */
float32_t isqrtf(float32_t num);

void motion_init(__IO motion_t *motion);
void motion_goto_pos(__IO motion_t *motion, float32_t rel_position);
void motion_set_vel(__IO motion_t *motion, float32_t velocity);
void motion_step(__IO motion_t *motion);

void tim_conf(void);
/* Exported variables ------------------------------------------------------- */
__IO motion_t y_motion;

#endif /* CNC_MAIN_H */
