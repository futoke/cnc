################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/buffer.c \
../src/cmd.c \
../src/main.c \
../src/stm32f4_discovery.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/usart.c 

S_UPPER_SRCS += \
../src/startup_stm32f4xx.S 

OBJS += \
./src/buffer.o \
./src/cmd.o \
./src/main.o \
./src/startup_stm32f4xx.o \
./src/stm32f4_discovery.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/usart.o 

C_DEPS += \
./src/buffer.d \
./src/cmd.d \
./src/main.d \
./src/stm32f4_discovery.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/usart.d 

S_UPPER_DEPS += \
./src/startup_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DSTM32F40XX -DARM_MATH_CM4 -DHSE_VALUE=8000000 -D__FPU_PRESENT=1 -D__FPU_USED=1 -I"/home/ichiro/workspace1/cnc/lib/inc" -I"/home/ichiro/workspace1/cnc/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -x assembler-with-cpp -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DSTM32F40XX -DARM_MATH_CM4 -DHSE_VALUE=8000000 -D__FPU_PRESENT=1 -D__FPU_USED=1 -I"/home/ichiro/workspace1/cnc/lib/inc" -I"/home/ichiro/workspace1/cnc/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


