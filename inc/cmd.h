/*
 * cmd.h
 *
 *  Created on: 09.02.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_CMD_H
#define CNC_CMD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "buffer.h"
#include "usart.h"
/* Exported constants --------------------------------------------------------*/
#define MAX_CMD_LENGTH 256
/* Exported types ------------------------------------------------------------*/
typedef enum {
    NOT_READY = 0, READY = !NOT_READY
} cmd_state_t;
typedef struct {
    uint8_t text[MAX_CMD_LENGTH];
    uint8_t cnt;
    cmd_state_t state;
} cmd_t;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void cmd_init(__IO cmd_t *cmd);
void cmd_add_ch(__IO cmd_t *cmd, uint8_t ch);
void cmd_set_state(__IO cmd_t *cmd, cmd_state_t state);
cmd_state_t cmd_get_state(__IO cmd_t *cmd);
//void cmd_echo(void);
/* Exported variables --------------------------------------------------------*/
extern cmd_t cmd;

#endif /* CNC_CMD_H */
