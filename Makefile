#------------------------------------------------------------------------------
# Make file for the GPS speedometer project build.
#
# Use: make [TARGET]
#
# Build Targets:
#      <file>.o - Generate the object file <file>.o of the <file>.c source file.
#      compile-all - Compile all source files without linking them.
#      build - Compile all source files and link them to create a final executable file. 
#      clean - Remove all compiled objects, preprocessed outputs, assembly outputs and executable files.
#
#------------------------------------------------------------------------------
include sources.mk

TARGET = serial

# Architectures Specific Flags
LINKER_FILE = linker_script.ld
CPU = cortex-m4
#ARCH = armv7e-m
SPECS = nosys.specs

# Compiler Flags and Defines
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy
LDFLAGS = -Map=$(TARGET).map -T $(LINKER_FILE)
CFLAGS = $(INCLUDES) -mcpu=$(CPU) -mthumb \
         -Wall -Werror -g -O0 --specs=$(SPECS) -std=c99
SIZE=arm-none-eabi-size

OBJS:=$(SOURCES:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
	
.PHONY: compile-all
compile-all: $(OBJS)


.PHONY: build
build: $(TARGET).bin
	
	
$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	$(SIZE) $(TARGET).elf


$(TARGET).bin: $(TARGET).elf
		$(OC) -O binary $^ $@ 

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).bin  $(TARGET).elf $(TARGET).map
	

