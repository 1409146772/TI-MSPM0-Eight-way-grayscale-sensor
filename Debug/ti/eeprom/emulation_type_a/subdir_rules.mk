################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ti/eeprom/emulation_type_a/%.o: ../ti/eeprom/emulation_type_a/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/MCU/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/LuZIyu/workspace_ccstheia/8-channel grayscale sensor" -I"C:/Users/LuZIyu/workspace_ccstheia/8-channel grayscale sensor/Debug" -I"D:/MCU/CCS/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"D:/MCU/CCS/mspm0_sdk_2_05_01_00/source" -I"C:/Users/LuZIyu/workspace_ccstheia/8-channel grayscale sensor/ti/eeprom/emulation_type_b" -gdwarf-3 -MMD -MP -MF"ti/eeprom/emulation_type_a/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


