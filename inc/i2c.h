/* i2c.h
 *
 *  Created on: 22.07.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_I2C_H
#define CNC_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void i2c_conf(void);
void i2c_start_trans(I2C_TypeDef* I2Cx, uint8_t trans_dir, uint8_t slave_addr);
void i2c_putch(I2C_TypeDef* I2Cx, uint8_t ch);
uint8_t i2c_getch(I2C_TypeDef* I2Cx);
void i2c_puts(uint8_t *str);
/* Exported variables --------------------------------------------------------*/

#endif /* CNC_I2C_H */
