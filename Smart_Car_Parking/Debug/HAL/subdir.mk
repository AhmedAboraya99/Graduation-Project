################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Servo_Motor.c \
../HAL/keypad.c \
../HAL/lcd.c 

OBJS += \
./HAL/Servo_Motor.o \
./HAL/keypad.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/Servo_Motor.d \
./HAL/keypad.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Servo_Motor.o: ../HAL/Servo_Motor.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"HAL/Servo_Motor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/keypad.o: ../HAL/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"HAL/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/lcd.o: ../HAL/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"HAL/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

