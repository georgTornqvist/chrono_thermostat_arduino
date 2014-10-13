################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include Libraries/idDHT11-master/subdir.mk
-include Libraries/Wire/utility/subdir.mk
-include Libraries/Wire/subdir.mk
-include Libraries/U8glib_ST7920/utility/subdir.mk
-include Libraries/U8glib_ST7920/subdir.mk
-include Libraries/Timer-master/subdir.mk
-include Libraries/Time/subdir.mk
-include Libraries/SPI/subdir.mk
-include Libraries/SD/utility/subdir.mk
-include Libraries/SD/subdir.mk
-include Libraries/DS1307RTC/subdir.mk
-include Libraries/Adafruit-ST7735-Library-master/subdir.mk
-include Libraries/Adafruit-GFX-Library-master/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/georg/SviluppoArduino/chrono_thermostat/Release/arduino.ar \

ELF += \
chrono_thermostat.elf \

EEP += \
chrono_thermostat.eep \

FLASH_IMAGE += \
chrono_thermostat.hex \


# All Target
all: chrono_thermostat

# Tool invocations
chrono_thermostat: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/georg/Sviluppo/arduino-1.5.2/hardware/tools/avr/bin/avr-size" -A "/home/georg/SviluppoArduino/chrono_thermostat/Release/chrono_thermostat.hex"
	@echo 'Finished building target: $@'
	@echo ' '

/home/georg/SviluppoArduino/chrono_thermostat/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/georg/Sviluppo/arduino-1.5.2/hardware/tools/avr/bin/avr-ar" rcs "/home/georg/SviluppoArduino/chrono_thermostat/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

chrono_thermostat.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/georg/Sviluppo/arduino-1.5.2/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p -o "/home/georg/SviluppoArduino/chrono_thermostat/Release/chrono_thermostat.elf"   $(LINK_OBJ) $(AR)  "/home/georg/SviluppoArduino/chrono_thermostat/Release/arduino.ar" "-L/home/georg/SviluppoArduino/chrono_thermostat/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

chrono_thermostat.eep: $(ELF)
	@echo 'Create eeprom image'
	"/home/georg/Sviluppo/arduino-1.5.2/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "/home/georg/SviluppoArduino/chrono_thermostat/Release/chrono_thermostat.elf" "/home/georg/SviluppoArduino/chrono_thermostat/Release/chrono_thermostat.eep"
	@echo 'Finished building: $@'
	@echo ' '

chrono_thermostat.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/home/georg/Sviluppo/arduino-1.5.2/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom "/home/georg/SviluppoArduino/chrono_thermostat/Release/chrono_thermostat.elf" "/home/georg/SviluppoArduino/chrono_thermostat/Release/chrono_thermostat.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) chrono_thermostat
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
