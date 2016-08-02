
# The toolchain to use. arm-none-eabi works, but there does exist
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = test.bin

# The name of the assembler listing file to generate.
LIST = test.list

# The name of the map file to generate.
MAP = test.map

# The names of all object files that must be generated. Deduced from the
# assembly code files in source.
OBJECTS := $(patsubst $(SOURCE)%.S,$(BUILD)%.o,$(wildcard $(SOURCE)*.S)) $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))

# Rule to make everything.
all: $(TARGET) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the bin file.
$(TARGET) : $(BUILD)output.elf
	arm-none-eabi-objcopy -O binary "$(BUILD)output.elf" "$(TARGET)"
	arm-none-eabi-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "$(BUILD)output.elf" "$(BUILD)output.hex"
	arm-none-eabi-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "$(BUILD)output.elf" "$(BUILD)output.eep" || exit 0
	arm-none-eabi-objdump -h -S "$(BUILD)output.elf" > "$(MAP)"
	arm-none-eabi-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature  "$(BUILD)output.elf" "$(BUILD)output.srec"
	arm-none-eabi-size "$(BUILD)output.elf"

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS)
	@echo Building target: $@
	# -L ./linkerscripts -Tsam3x8e_flash.ld
	$(ARMGNU)-gcc -o $@  -mthumb -Wl,--start-group -lm  -Wl,--end-group -Wl,--gc-sections -mcpu=cortex-m3 -Tlink.ld $(OBJECTS)
	@echo Finished building target: $@


#Wl,-Map=$(Map)

# Rule to make the object files.
$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	@echo Building file: $<
	$(ARMGNU)-gcc$(QUOTE)  -x c -mthumb -D__SAM3X8E__ -DDEBUG -I "./source/include" -O1 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<

$(BUILD)%.o: $(SOURCE)%.S $(BUILD)
	@echo Building file: $<
	$(ARMGNU)-as -mcpu=cortex-m3 -mfloat-abi=soft -mthumb   -o "$@" "$<"
	@echo Finished building: $<


$(BUILD):
	mkdir $@
