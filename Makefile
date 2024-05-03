# Compiler
CC = avr-gcc

# Microcontroller expected by avr-gcc -mmcu flag. (see `man avr-gcc`).
MCU ?= atmega328p

# CPU frequency (in hertz). Must be an unsigned long.
F_CPU ?= 16000000UL

# Arduino USB port (ls /dev/tty*).
USB_PORT ?= /dev/ttyUSB0

# Compiler flags.
CFLAGS = -std=c99 -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall -O3 --param=min-pagesize=0

# Source files.
SRC_DIR = src
SRC_SRCS := $(shell find $(SRC_DIR) -name '*.c')
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, build/src/%.o, $(SRC_SRCS))

# Test source files.
TEST_DIR = tests
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, build/tests/%.o, $(TEST_SRCS))

# Binary executable.
SRC_BIN = build/src/exe.elf
TEST_BIN = build/tests/test_runner

# Compile object files for src.
build/src/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile object files for tests.
build/tests/%.o: $(TEST_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create binary executable for src.
$(SRC_BIN): $(SRC_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $(SRC_BIN)

# Link object files to create test binary executable for tests.
$(TEST_BIN): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_BIN)

# Default target.
all: $(SRC_BIN)

# Upload to board using the arduino bootloader.
upload: $(SRC_BIN)
	avrdude -v -p $(MCU) -c arduino -P $(USB_PORT) -b 115200 -U flash:w:$(SRC_BIN)

# Tests target
tests: $(TEST_BIN)
	$(TEST_BIN)

.PHONY: compile_commands.json clean clean_src clean_tests

# Necessary if using clangd as a Language Server Protocol.
compile_commands.json: clean
	bear --output src/compile_commands.json -- make
	bear --output tests/compile_commands.json -- make tests

clean:
	rm -rf build
