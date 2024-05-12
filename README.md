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

## Software Requirements

- `avr-gcc` (compiler).
- `avrdude` (uploader).
- `make`.
- [optinal] `bear` for development.

## Hardware Requirements

- Arduino Uno or equivalent.
- 12 LEDs.
- 12 resistors that are about 200-300 ohms.
- 1k resistor (pull-down).
- 1 Switch button.
- Jumpers for the connections.

## ASCII schematics

This is the schematics for the ATMega328P pins.
The pins in parenthesis are what the Arduino Pins are aliased to.
The information in brackets is what you need to connect to those pins.

```
                             +-\/-+
                       PC6  1|    |28  PC5 (AI 5)
                 (D 0) PD0  2|    |27  PC4 (AI 4)
                 (D 1) PD1  3|    |26  PC3 (AI 3)
[LED + resistor] (D 2) PD2  4|    |25  PC2 (AI 2)
[LED + resistor] (D 3) PD3  5|    |24  PC1 (AI 1)
[LED + resistor] (D 4) PD4  6|    |23  PC0 (AI 0) [Buttom + pulldown 1k Ohm]
[+ protoboard]         VCC  7|    |22  GND
[ground protoboard]    GND  8|    |21  AREF
                       PB6  9|    |20  AVCC
                       PB7 10|    |19  PB5 (D 13) [LED + resistor]
[LED + resistor] (D 5) PD5 11|    |18  PB4 (D 12) [LED + resistor]
[LED + resistor] (D 6) PD6 12|    |17  PB3 (D 11) [LED + resistor]
[LED + resistor] (D 7) PD7 13|    |16  PB2 (D 10) [LED + resistor]
[LED + resistor] (D 8) PB0 14|    |15  PB1 (D 9)  [LED + resistor]
                             +----+
```

## Commands

- `make` compiles the code to `elf` format.
- `make upload` compiles **and** uploads the code to the arduino.
- `make clean` removes build folder.
- `make compile_commands.json` creates a compile_commands.json file for clang.
