################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/georg/SviluppoArduino/Libraries/DS1307RTC/DS1307RTC.cpp 

CPP_DEPS += \
./Libraries/DS1307RTC/DS1307RTC.cpp.d 

LINK_OBJ += \
./Libraries/DS1307RTC/DS1307RTC.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/DS1307RTC/DS1307RTC.cpp.o: /home/georg/SviluppoArduino/Libraries/DS1307RTC/DS1307RTC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/georg/Sviluppo/arduino-1.5.2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=152    -I"/home/georg/Sviluppo/arduino-1.5.2/hardware/arduino/avr/cores/arduino" -I"/home/georg/Sviluppo/arduino-1.5.2/hardware/arduino/avr/variants/standard" -I"/home/georg/SviluppoArduino/Libraries/DS1307RTC" -I"/home/georg/SviluppoArduino/Libraries/idDHT11-master" -I"/home/georg/SviluppoArduino/Libraries/U8glib_ST7920" -I"/home/georg/SviluppoArduino/Libraries/U8glib_ST7920/utility" -I"/home/georg/Sviluppo/arduino-1.5.2/hardware/arduino/avr/libraries/Wire" -I"/home/georg/Sviluppo/arduino-1.5.2/hardware/arduino/avr/libraries/Wire/utility" -I"/home/georg/SviluppoArduino/Libraries/Time" -I"/home/georg/SviluppoArduino/Libraries/Timer-master" -I"/home/georg/Sviluppo/arduino-1.5.2/libraries/SD" -I"/home/georg/Sviluppo/arduino-1.5.2/libraries/SD/utility" -I"/home/georg/SviluppoArduino/Libraries/Adafruit-GFX-Library-master" -I"/home/georg/SviluppoArduino/Libraries/Adafruit-ST7735-Library-master" -I"/home/georg/Sviluppo/arduino-1.5.2/hardware/arduino/avr/libraries/SPI" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


