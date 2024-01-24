################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/UART/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/SYSTIMER/subdir.mk
-include Dave/Generated/PWM_CCU8/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/GLOBAL_CCU8/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/GLOBAL_ADC/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC1/subdir.mk
-include Dave/Generated/CLOCK_XMC1/subdir.mk
-include Dave/Generated/ANALOG_IO/subdir.mk
-include Dave/Generated/ADC_MEASUREMENT/subdir.mk
-include Dave/Generated/subdir.mk
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
SECONDARY_FLASH += \
HPPC.hex \

SECONDARY_LIST += \
HPPC.lst \

SECONDARY_SIZE += \
HPPC.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "HPPC.map"

TOOLCHAIN_ROOT=C:/Infineon/Tools/DAVE IDE/4.5.0.202105191637/eclipse/ARM-GCC-49
PROJECT_LOC=F:/HPPC_app/HPPC

# All Target
all: HPPC.elf secondary-outputs

# Tool invocations
HPPC.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -u _printf_float -Wl,-Map,$(MAP_FILE) -mcpu=cortex-m0 -mthumb -o "HPPC.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
HPPC.hex: HPPC.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "HPPC.elf" "HPPC.hex"
	@echo 'Finished building: $@'
	@echo.
HPPC.lst: HPPC.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "HPPC.elf" > "HPPC.lst"
	@echo 'Finished building: $@'
	@echo.
HPPC.siz: HPPC.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "HPPC.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) Dave/Generated/ADC_MEASUREMENT/adc_measurement.o Dave/Generated/ADC_MEASUREMENT/adc_measurement_conf.o Dave/Generated/ANALOG_IO/analog_io.o Dave/Generated/ANALOG_IO/analog_io_conf.o Dave/Generated/CLOCK_XMC1/clock_xmc1.o Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.o Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1.o Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1_conf.o Dave/Generated/DAVE.o Dave/Generated/DIGITAL_IO/digital_io.o Dave/Generated/DIGITAL_IO/digital_io_conf.o Dave/Generated/GLOBAL_ADC/global_adc.o Dave/Generated/GLOBAL_ADC/global_adc_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/GLOBAL_CCU8/global_ccu8.o Dave/Generated/GLOBAL_CCU8/global_ccu8_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/PWM_CCU8/pwm_ccu8.o Dave/Generated/PWM_CCU8/pwm_ccu8_conf.o Dave/Generated/SYSTIMER/systimer.o Dave/Generated/SYSTIMER/systimer_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o Dave/Generated/UART/uart.o Dave/Generated/UART/uart_conf.o EVSELab_System.o Fixed_point_math.o Fridge_300W.o main.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc1_eru.o Libraries/XMCLib/src/xmc1_flash.o Libraries/XMCLib/src/xmc1_gpio.o Libraries/XMCLib/src/xmc1_rtc.o Libraries/XMCLib/src/xmc1_scu.o Libraries/XMCLib/src/xmc_acmp.o Libraries/XMCLib/src/xmc_bccu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_math.o Libraries/XMCLib/src/xmc_pau.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_prng.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usic.o 
	-$(RM) Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Startup/startup_XMC1300.o Startup/system_XMC1300.o  HPPC.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
