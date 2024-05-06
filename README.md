# LED Control

![demo.mp4](assets/demo.mp4)

This is a project created for studying purposes.

The idea is to use an Arduino (or equivalent board) to control a few LEDs in
a few different configurations.

No code from the Arduino framework is actually used. Instead, the whole code
is compiled directly via `avr-gcc` using the `.c` files in this codebase as
source code.

The only exception is that the bootloader code used is the one embedded in the
arduino flash memory.

## Requirements

- `avr-gcc` (compiler).
- `avrdude` (uploader).
- `make`.
- [optinal] `bear` for development.

## Commands

- `make` compiles the code to `elf` format.
- `make upload` compiles **and** uploads the code to the arduino.
- `make clean` removes build folder.
- `make compile_commands.json` creates a compile_commands.json file for clang.
