/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_TimeBase
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART_FLAGS (USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE | USART_FLAG_ORE)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t tim5_period;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

uint8_t delay_cycles (uint32_t cycles)
{
	static uint32_t cnt = 0;

	if (cnt++ == cycles) {
		cnt = 0;
		return 1;
	} else {
		return 0;
	}
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    uint8_t ch;
    static uint8_t acc = 0;

    if (!buff_empty(rx_buff)) {
        ch = buff_get(&rx_buff);
        cmd_add_ch(&cmd, ch);
        usart_putch(ch);
    }

	if (acc) {
		if (tim5_period > 1221) {
			if (delay_cycles(8)) {
				TIM_SetCounter(TIM5, 1);
				TIM_SetAutoreload(TIM5, tim5_period);
				tim5_period -= 50;
			}
		} else {
			if (delay_cycles(2000)){
				acc = 0;
			}
		}
	} else {
		if (tim5_period < 10000) {
			if (delay_cycles(8)) {
				TIM_SetCounter(TIM5, 1);
				TIM_SetAutoreload(TIM5, tim5_period);
				tim5_period += 50;
			}
		} else {
			acc = 1;
		}

	}
//    printf("%lu\n", TIM_GetCounter(TIM5));
}

/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
		STM_EVAL_LEDToggle(LED3);

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
    uint8_t ch;

    if(USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET) {
        if ((EVAL_COM1->SR & USART_FLAGS) == 0) {
            ch = (uint8_t)(USART_ReceiveData(EVAL_COM1) & 0xFF);
            buff_put(&rx_buff, ch);
        }  else {
            USART_ReceiveData(EVAL_COM1);
        }
    }

    if (USART_GetITStatus(EVAL_COM1, USART_IT_TXE) == SET) {
        if (!buff_empty(tx_buff)) {
            USART_SendData(EVAL_COM1, buff_get(&tx_buff));
        } else {
            USART_ITConfig(EVAL_COM1, USART_IT_TXE, DISABLE);
        }
    }
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
