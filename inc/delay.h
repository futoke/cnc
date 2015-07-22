/* delay.h
 *
 *  Created on: 22.07.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_DELAY_H
#define CNC_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
/* Exported variables --------------------------------------------------------*/

#endif /* CNC_DELAY_H */
