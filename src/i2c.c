/*
 * i2c.c
 *
 *  Created on: 22.07.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void i2c_conf(void)
{
    GPIO_InitTypeDef GPIOB_InitStructure;
    I2C_InitTypeDef I2C1_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    I2C1_InitStructure.I2C_ClockSpeed = 100000;
    I2C1_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C1_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    
    I2C1_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C1_InitStructure.I2C_Ack = I2C_Ack_Disable;
    I2C1_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C1_InitStructure);
    
    GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOB_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIOB_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIOB_InitStructure);
    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
    
    I2C_Cmd(I2C1, ENABLE);
}

void i2c_start_trans(I2C_TypeDef* I2Cx, uint8_t trans_dir, uint8_t slave_addr)
{
    // На всякий случай ждем, пока шина осовободится.
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
        ;
    I2C_GenerateSTART(I2Cx, ENABLE);
    
    // Ждем пока поднимется нужный флаг.
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    /* Посылаем адрес подчиненному.
     Возможно тут нужен сдвиг влево,
     http://microtechnics.ru/stm32-ispolzovanie-i2c/#comment-8109 */
    I2C_Send7bitAddress(I2Cx, slave_addr << 1, trans_dir);
    
    if (trans_dir == I2C_Direction_Transmitter) {
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
            ;
    } else if (trans_dir == I2C_Direction_Receiver) {
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
            ;
    }
}

void i2c_write_byte(I2C_TypeDef* I2Cx, uint8_t ch)
{
    I2C_SendData(I2Cx, ch);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
}

uint8_t i2c_read_byte(I2C_TypeDef* I2Cx)
{
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
        ;
    return I2C_ReceiveData(I2Cx);
}
