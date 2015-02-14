################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/misc.c \
../lib/src/stm32f4xx_adc.c \
../lib/src/stm32f4xx_can.c \
../lib/src/stm32f4xx_crc.c \
../lib/src/stm32f4xx_cryp.c \
../lib/src/stm32f4xx_cryp_aes.c \
../lib/src/stm32f4xx_cryp_des.c \
../lib/src/stm32f4xx_cryp_tdes.c \
../lib/src/stm32f4xx_dac.c \
../lib/src/stm32f4xx_dbgmcu.c \
../lib/src/stm32f4xx_dcmi.c \
../lib/src/stm32f4xx_dma.c \
../lib/src/stm32f4xx_dma2d.c \
../lib/src/stm32f4xx_exti.c \
../lib/src/stm32f4xx_flash.c \
../lib/src/stm32f4xx_flash_ramfunc.c \
../lib/src/stm32f4xx_fsmc.c \
../lib/src/stm32f4xx_gpio.c \
../lib/src/stm32f4xx_hash.c \
../lib/src/stm32f4xx_hash_md5.c \
../lib/src/stm32f4xx_hash_sha1.c \
../lib/src/stm32f4xx_i2c.c \
../lib/src/stm32f4xx_iwdg.c \
../lib/src/stm32f4xx_ltdc.c \
../lib/src/stm32f4xx_pwr.c \
../lib/src/stm32f4xx_rcc.c \
../lib/src/stm32f4xx_rng.c \
../lib/src/stm32f4xx_rtc.c \
../lib/src/stm32f4xx_sai.c \
../lib/src/stm32f4xx_sdio.c \
../lib/src/stm32f4xx_spi.c \
../lib/src/stm32f4xx_syscfg.c \
../lib/src/stm32f4xx_tim.c \
../lib/src/stm32f4xx_usart.c \
../lib/src/stm32f4xx_wwdg.c 

OBJS += \
./lib/src/misc.o \
./lib/src/stm32f4xx_adc.o \
./lib/src/stm32f4xx_can.o \
./lib/src/stm32f4xx_crc.o \
./lib/src/stm32f4xx_cryp.o \
./lib/src/stm32f4xx_cryp_aes.o \
./lib/src/stm32f4xx_cryp_des.o \
./lib/src/stm32f4xx_cryp_tdes.o \
./lib/src/stm32f4xx_dac.o \
./lib/src/stm32f4xx_dbgmcu.o \
./lib/src/stm32f4xx_dcmi.o \
./lib/src/stm32f4xx_dma.o \
./lib/src/stm32f4xx_dma2d.o \
./lib/src/stm32f4xx_exti.o \
./lib/src/stm32f4xx_flash.o \
./lib/src/stm32f4xx_flash_ramfunc.o \
./lib/src/stm32f4xx_fsmc.o \
./lib/src/stm32f4xx_gpio.o \
./lib/src/stm32f4xx_hash.o \
./lib/src/stm32f4xx_hash_md5.o \
./lib/src/stm32f4xx_hash_sha1.o \
./lib/src/stm32f4xx_i2c.o \
./lib/src/stm32f4xx_iwdg.o \
./lib/src/stm32f4xx_ltdc.o \
./lib/src/stm32f4xx_pwr.o \
./lib/src/stm32f4xx_rcc.o \
./lib/src/stm32f4xx_rng.o \
./lib/src/stm32f4xx_rtc.o \
./lib/src/stm32f4xx_sai.o \
./lib/src/stm32f4xx_sdio.o \
./lib/src/stm32f4xx_spi.o \
./lib/src/stm32f4xx_syscfg.o \
./lib/src/stm32f4xx_tim.o \
./lib/src/stm32f4xx_usart.o \
./lib/src/stm32f4xx_wwdg.o 

C_DEPS += \
./lib/src/misc.d \
./lib/src/stm32f4xx_adc.d \
./lib/src/stm32f4xx_can.d \
./lib/src/stm32f4xx_crc.d \
./lib/src/stm32f4xx_cryp.d \
./lib/src/stm32f4xx_cryp_aes.d \
./lib/src/stm32f4xx_cryp_des.d \
./lib/src/stm32f4xx_cryp_tdes.d \
./lib/src/stm32f4xx_dac.d \
./lib/src/stm32f4xx_dbgmcu.d \
./lib/src/stm32f4xx_dcmi.d \
./lib/src/stm32f4xx_dma.d \
./lib/src/stm32f4xx_dma2d.d \
./lib/src/stm32f4xx_exti.d \
./lib/src/stm32f4xx_flash.d \
./lib/src/stm32f4xx_flash_ramfunc.d \
./lib/src/stm32f4xx_fsmc.d \
./lib/src/stm32f4xx_gpio.d \
./lib/src/stm32f4xx_hash.d \
./lib/src/stm32f4xx_hash_md5.d \
./lib/src/stm32f4xx_hash_sha1.d \
./lib/src/stm32f4xx_i2c.d \
./lib/src/stm32f4xx_iwdg.d \
./lib/src/stm32f4xx_ltdc.d \
./lib/src/stm32f4xx_pwr.d \
./lib/src/stm32f4xx_rcc.d \
./lib/src/stm32f4xx_rng.d \
./lib/src/stm32f4xx_rtc.d \
./lib/src/stm32f4xx_sai.d \
./lib/src/stm32f4xx_sdio.d \
./lib/src/stm32f4xx_spi.d \
./lib/src/stm32f4xx_syscfg.d \
./lib/src/stm32f4xx_tim.d \
./lib/src/stm32f4xx_usart.d \
./lib/src/stm32f4xx_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o: ../lib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DSTM32F40XX -DARM_MATH_CM4 -DHSE_VALUE=8000000 -D__FPU_PRESENT=1 -D__FPU_USED=1 -I"/home/ichiro/workspace1/cnc/lib/inc" -I"/home/ichiro/workspace1/cnc/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


