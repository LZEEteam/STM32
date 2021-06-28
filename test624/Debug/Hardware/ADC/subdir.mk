################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/ADC/adc_test.c 

OBJS += \
./Hardware/ADC/adc_test.o 

C_DEPS += \
./Hardware/ADC/adc_test.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/ADC/adc_test.o: ../Hardware/ADC/adc_test.c Hardware/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/SYSTEM/sys" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/USMART" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/LCD" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/SYSTEM/delay" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Task" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/KEY" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/IIC" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/24CXX" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/AP3216C" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/PCF8574" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/TOUCH" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/SDRAM" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/ADC" -I"/Users/apeelab1/Documents/STMCUBEPROJECT/test624/test624/Hardware/DAC" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Hardware/ADC/adc_test.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

