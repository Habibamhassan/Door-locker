################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCU1.c \
../Timer.c \
../UART.c \
../gpio.c \
../keypad.c \
../lcd.c \
../mcu.c 

OBJS += \
./MCU1.o \
./Timer.o \
./UART.o \
./gpio.o \
./keypad.o \
./lcd.o \
./mcu.o 

C_DEPS += \
./MCU1.d \
./Timer.d \
./UART.d \
./gpio.d \
./keypad.d \
./lcd.d \
./mcu.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


