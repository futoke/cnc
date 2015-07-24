/*
 * delay.c
 *
 *  Created on: 22.08.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void delay_ms(uint32_t ms)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	__IO uint32_t cnt = (RCC_Clocks.HCLK_Frequency / 10000) * ms;
	while (cnt--)
		;
}

void delay_us(uint32_t us)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	__IO uint32_t cnt = (RCC_Clocks.HCLK_Frequency / 10000000) * us;
	while (cnt--)
		;
}
