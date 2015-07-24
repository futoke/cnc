/* encoder.h
 *
 *  Created on: 24.07.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_ENCODER_H
#define CNC_ENCODER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM3_Configuration(void);
void encoder_init(void);
/* Exported variables --------------------------------------------------------*/

#endif /* CNC_ENCODER_H */
