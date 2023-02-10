################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_DRIVERS/STM32F103x6_EXTI_Driver.c \
../STM32_F103C6_DRIVERS/STM32F103x6_GPIO_Driver.c \
../STM32_F103C6_DRIVERS/STM32F103x6_RCC_Driver.c \
../STM32_F103C6_DRIVERS/STM32F103x6_SPI_Driver.c \
../STM32_F103C6_DRIVERS/STM32F103x6_UART_Driver.c \
../STM32_F103C6_DRIVERS/Timer.c 

OBJS += \
./STM32_F103C6_DRIVERS/STM32F103x6_EXTI_Driver.o \
./STM32_F103C6_DRIVERS/STM32F103x6_GPIO_Driver.o \
./STM32_F103C6_DRIVERS/STM32F103x6_RCC_Driver.o \
./STM32_F103C6_DRIVERS/STM32F103x6_SPI_Driver.o \
./STM32_F103C6_DRIVERS/STM32F103x6_UART_Driver.o \
./STM32_F103C6_DRIVERS/Timer.o 

C_DEPS += \
./STM32_F103C6_DRIVERS/STM32F103x6_EXTI_Driver.d \
./STM32_F103C6_DRIVERS/STM32F103x6_GPIO_Driver.d \
./STM32_F103C6_DRIVERS/STM32F103x6_RCC_Driver.d \
./STM32_F103C6_DRIVERS/STM32F103x6_SPI_Driver.d \
./STM32_F103C6_DRIVERS/STM32F103x6_UART_Driver.d \
./STM32_F103C6_DRIVERS/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_DRIVERS/STM32F103x6_EXTI_Driver.o: ../STM32_F103C6_DRIVERS/STM32F103x6_EXTI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"STM32_F103C6_DRIVERS/STM32F103x6_EXTI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_DRIVERS/STM32F103x6_GPIO_Driver.o: ../STM32_F103C6_DRIVERS/STM32F103x6_GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"STM32_F103C6_DRIVERS/STM32F103x6_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_DRIVERS/STM32F103x6_RCC_Driver.o: ../STM32_F103C6_DRIVERS/STM32F103x6_RCC_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"STM32_F103C6_DRIVERS/STM32F103x6_RCC_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_DRIVERS/STM32F103x6_SPI_Driver.o: ../STM32_F103C6_DRIVERS/STM32F103x6_SPI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"STM32_F103C6_DRIVERS/STM32F103x6_SPI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_DRIVERS/STM32F103x6_UART_Driver.o: ../STM32_F103C6_DRIVERS/STM32F103x6_UART_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"STM32_F103C6_DRIVERS/STM32F103x6_UART_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_DRIVERS/Timer.o: ../STM32_F103C6_DRIVERS/Timer.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"STM32_F103C6_DRIVERS/Timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

