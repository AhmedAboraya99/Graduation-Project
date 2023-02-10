################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32_F103C6_DRIVERS/subdir.mk
-include HAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ECU3Smart_CAR_Parking.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ECU3Smart_CAR_Parking.list \

OBJCOPY_BIN += \
ECU3Smart_CAR_Parking.bin \


# All Target
all: ECU3Smart_CAR_Parking.elf secondary-outputs

# Tool invocations
ECU3Smart_CAR_Parking.elf: $(OBJS) $(USER_OBJS) E:\Work\Embedded\ systems\Diploma\embedded_system_online_diploma\Second_term_project\Smart_Car_Parking\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "ECU3Smart_CAR_Parking.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Work\Embedded systems\Diploma\embedded_system_online_diploma\Second_term_project\Smart_Car_Parking\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ECU3Smart_CAR_Parking.map" -Wl,--gc-sections -static -fcommon --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ECU3Smart_CAR_Parking.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ECU3Smart_CAR_Parking.list"
	@echo 'Finished building: $@'
	@echo ' '

ECU3Smart_CAR_Parking.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ECU3Smart_CAR_Parking.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
