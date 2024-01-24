################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/CLOCK_XMC1/clock_xmc1.c \
../Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.c 

OBJS += \
./Dave/Generated/CLOCK_XMC1/clock_xmc1.o \
./Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.o 

C_DEPS += \
./Dave/Generated/CLOCK_XMC1/clock_xmc1.d \
./Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/CLOCK_XMC1/%.o: ../Dave/Generated/CLOCK_XMC1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1301_T016x0032 -D__FPU_PRESENT -DARM_MATH_CM4 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1300_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu99 -ffast-math -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

