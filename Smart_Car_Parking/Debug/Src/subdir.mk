################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/Common" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/HAL/include" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/Second_term_project/Smart_Car_Parking/STM32_F103C6_DRIVERS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

