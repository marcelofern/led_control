#include "../include/rainbow.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define NUM_PERFORMANCES 6

int8_t performance_idx = 0;

void configure_rainbow() {
  /* Configure the following ports as output.
   *
   * PB5 (digital 13 in arduino)
   * PB4 (digital 12 in arduino)
   * PB3 (digital 11 in arduino)
   * PB2 (digital 10 in arduino)
   * PB1 (digital 9 in arduino)
   * PB0 (digital 8 in arduino)
   *
   * PD7 (digital 5 in arduino)
   * PD6 (digital 4 in arduino)
   * PD5 (digital 3 in arduino)
   * PD4 (digital 2 in arduino)
   * PD3 (digital 1 in arduino)
   * PD2 (digital 0 in arduino)
   *
   * After configuration, performs a few blinks
   * to make sure all is good.
   */
  DDRB |= (1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2) | (1 << PB1) |
          (1 << PB0);
  DDRD |= (1 << PD7) | (1 << PD6) | (1 << PD5) | (1 << PD4) | (1 << PD3) |
          (1 << PD2);

  printf("Configuring rainbow.\r\n");
  for (uint8_t i = 0; i < 2; i++) {
    PORTB |= (1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2) | (1 << PB1) |
             (1 << PB0);
    PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5) | (1 << PD4) | (1 << PD3) |
             (1 << PD2);
    _delay_ms(300);
    PORTB &= ~(1 << PB5) & ~(1 << PB4) & ~(1 << PB3) & ~(1 << PB2) &
             ~(1 << PB1) & ~(1 << PB0);
    PORTD &= ~(1 << PD7) & ~(1 << PD6) & ~(1 << PD5) & ~(1 << PD4) &
             ~(1 << PD3) & ~(1 << PD2);
    _delay_ms(300);
  }
}

static void fast_delay(void) { _delay_ms(100); }

static void medium_delay(void) { _delay_ms(250); }

static void slow_delay(void) { _delay_ms(250); }

uint8_t snake_b[] = {0b111000, 0b110000, 0b100000, 0b000000,
                     0b000000, 0b000000, 0b000000, 0b000001,
                     0b000011, 0b000111, 0b001110, 0b011100};
uint8_t snake_d[] = {0b00000000, 0b10000000, 0b11000000, 0b11100000,
                     0b01110000, 0b00111000, 0b00011100, 0b00001100,
                     0b00000100, 0b00000000, 0b00000000, 0b00000000};
uint8_t walking_b[] = {0b100000, 0b010000, 0b001000, 0b000100, 0b000010,
                       0b000001, 0b000010, 0b000100, 0b001000, 0b010000};
uint8_t walking_d[] = {0b00000100, 0b00001000, 0b00010000, 0b00100000,
                       0b01000000, 0b10000000, 0b01000000, 0b00100000,
                       0b00010000, 0b00001000};
uint8_t circle_1_b[] = {0b100000, 0b010000, 0b001000, 0b000100,
                        0b000010, 0b000001, 0b000000, 0b000000,
                        0b000000, 0b000000, 0b000000, 0b000000};
uint8_t circle_1_d[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000,
                        0b00000000, 0b00000000, 0b00000100, 0b00001000,
                        0b00010000, 0b00100000, 0b01000000, 0b10000000};
uint8_t circle_2_b[] = {0b000000, 0b000000, 0b000000, 0b000000,
                        0b000000, 0b000000, 0b000001, 0b000010,
                        0b000100, 0b001000, 0b010000, 0b100000};
uint8_t circle_2_d[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000,
                        0b00001000, 0b00000100, 0b00000000, 0b00000000,
                        0b00000000, 0b00000000, 0b00000000, 0b00000000};
uint8_t zig_zag_b[] = {0b010000, 0b100000, 0b001000, 0b010000, 0b000100,
                       0b001000, 0b000010, 0b000100, 0b000001, 0b100000};
uint8_t zig_zag_d[] = {0b10000000, 0b01000000, 0b01000000, 0b00100000,
                       0b00100000, 0b00010000, 0b00010000, 0b00001000,
                       0b00001000, 0b00000100};
uint8_t to_center_b[] = {0b100001, 0b010010, 0b001100, 0b010010};
uint8_t to_center_d[] = {0b10000100, 0b01001000, 0b00110000, 0b01001000};
uint8_t default_b[] = {0b111111, 0b111111, 0b111111,
                       0b111111, 0b111111, 0b111111};
uint8_t default_d[] = {0b11111100, 0b11111100, 0b11111100,
                       0b11111100, 0b11111100, 0b11111100};

void change_rainbow_performance() {
  uint8_t *port_b = {0};
  uint8_t *port_d = {0};
  uint8_t perf_length = 0;
  void (*delay_func)(void) = {0};
  char *config_name = {0};

  switch (performance_idx) {
  case 0:
    port_b = circle_2_b;
    port_d = circle_2_d;
    delay_func = fast_delay;
    perf_length = sizeof(circle_2_b) / sizeof(circle_2_b[0]);
    config_name = "Circle clockwise";
    break;
  case 1:
    port_b = circle_1_b;
    port_d = circle_1_d;
    delay_func = fast_delay;
    perf_length = sizeof(circle_1_b) / sizeof(circle_1_b[0]);
    config_name = "Circle anticlockwise";
    break;
  case 2:
    port_b = walking_b;
    port_d = walking_d;
    delay_func = slow_delay;
    perf_length = sizeof(walking_b) / sizeof(walking_b[0]);
    config_name = "Walking across";
    break;
  case 3:
    port_b = snake_b;
    port_d = snake_d;
    delay_func = fast_delay;
    perf_length = sizeof(snake_b) / sizeof(snake_b[0]);
    config_name = "Snake 3 LEDs-long";
    break;
  case 4:
    port_b = zig_zag_b;
    port_d = zig_zag_d;
    delay_func = fast_delay;
    perf_length = sizeof(zig_zag_b) / sizeof(zig_zag_b[0]);
    config_name = "Zig Zag";
    break;
  case 5:
    port_b = to_center_b;
    port_d = to_center_d;
    delay_func = slow_delay;
    perf_length = sizeof(to_center_b) / sizeof(to_center_b[0]);
    config_name = "To the center in pairs!";
    break;
  default:
    // error. Keep all LEDS on.
    port_b = default_b;
    port_d = default_d;
    delay_func = medium_delay;
    perf_length = sizeof(default_b) / sizeof(default_b[0]);
    config_name = "Default";
  };

  if (performance_idx == NUM_PERFORMANCES - 1) {
    performance_idx = 0;
  } else {
    performance_idx++;
  }

  printf("Starting: %s...\r\n", config_name);

  while (1) {
    for (uint8_t i = 0; i < perf_length; i++) {
      PORTB = port_b[i];
      PORTD = port_d[i];
      delay_func();
    }
  }
}
