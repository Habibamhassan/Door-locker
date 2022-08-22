################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_motor.c \
../MCU2.c \
../Timer.c \
../UART.c \
../buzzer.c \
../control.c \
../external_eeprom.c \
../gpio.c \
../timer2_pwm.c \
../twi.c 

OBJS += \
./DC_motor.o \
./MCU2.o \
./Timer.o \
./UART.o \
./buzzer.o \
./control.o \
./external_eeprom.o \
./gpio.o \
./timer2_pwm.o \
./twi.o 

C_DEPS += \
./DC_motor.d \
./MCU2.d \
./Timer.d \
./UART.d \
./buzzer.d \
./control.d \
./external_eeprom.d \
./gpio.d \
./timer2_pwm.d \
./twi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


