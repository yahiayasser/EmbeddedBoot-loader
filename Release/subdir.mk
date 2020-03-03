################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader.c \
../Bootloader_cfg.c \
../Bootloader_private.c \
../Fuses.c \
../Interrupts.c \
../MCAL.c \
../UART.c \
../WDG.c \
../main.c 

OBJS += \
./Bootloader.o \
./Bootloader_cfg.o \
./Bootloader_private.o \
./Fuses.o \
./Interrupts.o \
./MCAL.o \
./UART.o \
./WDG.o \
./main.o 

C_DEPS += \
./Bootloader.d \
./Bootloader_cfg.d \
./Bootloader_private.d \
./Fuses.d \
./Interrupts.d \
./MCAL.d \
./UART.d \
./WDG.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


