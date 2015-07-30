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
    while (1) {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles PendSV_Handler exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

//uint8_t delay_cycles(uint32_t cycles)
//{
//    static uint32_t cnt = 0;
//
//    if (cnt++ == cycles) {
//        cnt = 0;
//        return 1;
//    } else {
//        return 0;
//    }
//}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
//	static uint8_t acc = 0;
//
//    if (acc) {
//		if (tim5_period > 2000) {
//			if (delay_cycles(8)) {
//				TIM_SetCounter(TIM5, 1);
//				TIM_SetAutoreload(TIM5, tim5_period);
//				tim5_period -= 50;
//			}
//		} else {
//			if (delay_cycles(5000)){
//				acc = 0;
//			}
//		}
//	} else {
//		if (tim5_period < 30000) {
//			if (delay_cycles(8)) {
//				TIM_SetCounter(TIM5, 1);
//				TIM_SetAutoreload(TIM5, tim5_period);
//				tim5_period += 50;
//			}
//		} else {
//			acc = 1;
//		}
//	}
    /******************************************************************************/
    interval_service();
}

/**
 * @brief  This function handles TIM3 global interrupt request.
 * @param  None
 * @retval None
 */
void TIM3_IRQHandler(void)
{
}

__IO uint32_t per[] = {17397, 13349, 11254, 9915, 8964, 8243, 7672, 7206, 6816, 6483, 6194, 5941, 5716, 5516, 5335, 5170, 5020, 4883, 4756, 4638, 4529, 4427, 4332, 4243, 4159, 4080, 4005, 3934, 3867, 3803, 3742, 3684, 3628, 3575, 3525, 3476, 3429, 3385, 3341, 3300, 3260, 3221, 3184, 3148, 3113, 3080, 3047, 3015, 2985, 2955, 2926, 2898, 2871, 2845, 2819, 2794, 2769, 2746, 2722, 2700, 2678, 2656, 2635, 2615, 2595, 2575, 2556, 2537, 2519, 2501, 2484, 2466, 2450, 2433, 2417, 2401, 2385, 2370, 2355, 2341, 2326, 2312, 2298, 2285, 2271, 2258, 2245, 2232, 2220, 2207, 2195, 2183, 2172, 2160, 2149, 2138, 2127, 2116, 2105, 2095, 2084, 2074, 2064, 2054, 2045, 2035, 2025, 2016, 2007};

/**
 * @brief  This function handles TIM5 global interrupt request.
 * @param  None
 * @retval None
 */
void TIM5_IRQHandler(void)
{
    static uint32_t cnt = 0;

    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
//        __IO uint32_t res;
        STM_EVAL_LEDToggle(LED3);
        
//        res = (uint32_t)((42000 - 1) * (isqrtf(cnt + 1) - isqrtf(cnt)) + 0.5);

//        res = 42000 * (isqrtf(cnt + 1) - isqrtf(cnt));
//        printf("You enter: %lu", res);

        uint32_t period = 1000000 * (isqrtf(cnt + 1) - isqrtf(cnt));
        TIM_SetCounter(TIM5, 1);
        TIM_SetAutoreload(TIM5, period);

        if (period > 2000) {
            cnt++;
        }

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
    
    if (USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET) {
        if ((EVAL_COM1->SR & USART_FLAGS) == 0) {
            ch = (uint8_t)(USART_ReceiveData(EVAL_COM1) & 0xFF);
            buff_put(&rx_buff, ch);
        } else {
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
 * @brief  This function handles PD0 global interrupt request.
 * @param  None
 * @retval None
 */
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        
        enc_revs_num++;
//    	TIM3->CNT = 0;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

