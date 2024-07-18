################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/HAL/FLASH.c \
../Sources/HAL/HAL_GPIO.c \
../Sources/HAL/HAL_MCG.c \
../Sources/HAL/HAL_PORT.c \
../Sources/HAL/HAL_SIM.c \
../Sources/HAL/HAL_UART0.c 

OBJS += \
./Sources/HAL/FLASH.o \
./Sources/HAL/HAL_GPIO.o \
./Sources/HAL/HAL_MCG.o \
./Sources/HAL/HAL_PORT.o \
./Sources/HAL/HAL_SIM.o \
./Sources/HAL/HAL_UART0.o 

C_DEPS += \
./Sources/HAL/FLASH.d \
./Sources/HAL/HAL_GPIO.d \
./Sources/HAL/HAL_MCG.d \
./Sources/HAL/HAL_PORT.d \
./Sources/HAL/HAL_SIM.d \
./Sources/HAL/HAL_UART0.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HAL/%.o: ../Sources/HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


