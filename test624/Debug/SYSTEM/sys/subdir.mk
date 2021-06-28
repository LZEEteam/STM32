################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SYSTEM/sys/sys.c 

OBJS += \
./SYSTEM/sys/sys.o 

C_DEPS += \
./SYSTEM/sys/sys.d 


# Each subdirectory must supply rules for building sources it contributes
SYSTEM/sys/sys.o: ../SYSTEM/sys/sys.c SYSTEM/sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/SYSTEM/sys" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SYSTEM/sys/sys.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

