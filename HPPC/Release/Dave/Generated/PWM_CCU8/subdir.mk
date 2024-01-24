################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/PWM_CCU8/pwm_ccu8.c \
../Dave/Generated/PWM_CCU8/pwm_ccu8_conf.c 

OBJS += \
./Dave/Generated/PWM_CCU8/pwm_ccu8.o \
./Dave/Generated/PWM_CCU8/pwm_ccu8_conf.o 

C_DEPS += \
./Dave/Generated/PWM_CCU8/pwm_ccu8.d \
./Dave/Generated/PWM_CCU8/pwm_ccu8_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/PWM_CCU8/%.o: ../Dave/Generated/PWM_CCU8/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1301_T016x0032 -D__FPU_PRESENT -DARM_MATH_CM4 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1300_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu99 -ffast-math -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

