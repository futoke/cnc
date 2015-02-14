/*
 * cmd.c
 *
 *  Created on: 09.02.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "cmd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO cmd_t cmd;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void cmd_init(__IO cmd_t *cmd)
{
    cmd->ind = 0;
    cmd->state = NOT_READY;
}

void cmd_add_ch(__IO cmd_t *cmd, uint8_t ch)
{
    if (ch != '\n' && ch != '\r') {
        cmd->text[cmd->ind++] = ch;
    } else {
        cmd->text[cmd->ind++] = '\0';
        cmd->state = READY;
        cmd->ind = 0;
    }
}

void cmd_set_state(__IO cmd_t *cmd, cmd_state_t state)
{
    cmd->state = state;
}

cmd_state_t cmd_get_state(__IO cmd_t *cmd)
{
    return cmd->state;
}
