################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader_cfg.c \
../Bootloader_prg.c \
../DIO.c \
../Fuses.c \
../MCAL.c \
../UART.c \
../WDG.c \
../main.c 

OBJS += \
./Bootloader_cfg.o \
./Bootloader_prg.o \
./DIO.o \
./Fuses.o \
./MCAL.o \
./UART.o \
./WDG.o \
./main.o 

C_DEPS += \
./Bootloader_cfg.d \
./Bootloader_prg.d \
./DIO.d \
./Fuses.d \
./MCAL.d \
./UART.d \
./WDG.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


