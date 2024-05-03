#include "../include/timer.h"
#include <avr/io.h>

void timer0_init() {
  /*
   * Initialise timer 0 with PWM.
   * Frequency: 62.5khz
   *
   * Output:
   *  OC0A: PD6 (duty cycle: 50%) | Arduino D6
   *  OC0B: PD5 (duty cycle: 30%) | Arduino D5
   *
   * A Mode: Fast PWM mode (non-inverting).
   *         COM0A1 = 1
   *         COM0A0 = 0
   *
   * B Mode: Fast PWM mode (non-inverting).
   *         COM0B1 = 1
   *         COM0B0 = 0
   *
   * Wave form: Fast PWM with TOP at 0xFF
   *            WGM01 = WGM00 = 1
   *
   * Pre-scaler: No pre-scaler
   *             CS01 = 0
   *             CS00 = 1
   *
   * Output compare registers:
   *  OCR0A = (256*0.5) = 128.
   *  OCR0B = (256*0.3) = 77.
   */
  DDRD |= (1 << PD5) | (1 << PD6);
  TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS00);
  OCR0A = (256 * 0.5);
  OCR0B = (256 * 0.3);
}

void timer1_init() {
  /*
   * Initialise timer 1 with PWM.
   * Frequency: 1,953khz
   *
   * Output:
   *  OC1A: PB1 (duty cycle: 50%) | Arduino D9
   *  OC1B: PB2 (duty cycle: 25%) | Arduino D10
   *
   * A Mode: Fast PWM mode (non-inverting).
   *         COM1A1 = 1
   *         COM1A0 = 0
   *
   * B Mode: Fast PWM mode (non-inverting).
   *         COM1B1 = 1
   *         COM1B0 = 0
   *
   * Wave form: Fast PWM with TOP at 0x03FF (1023)
   *            WGM10 = WGM11 = WGM12 = 1
   *
   * Pre-scaler: 1/8 (an eighth).
   *             CS11 = 1
   *
   * Output compare registers:
   *  OCR1A = (65536*0.5) = 32768.
   *  OCR1B = (65536*0.25) = 16384.
   */
  DDRB |= (1 << PB1) | (1 << PB2);
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM12) | (1 << WGM11) |
            (1 << WGM10);
  TCCR1B |= (1 << CS11);
  OCR1A = (uint16_t)(65535 * 0.5);
  OCR1B = (uint16_t)(65535 * 0.25);
}

void timer2_init() {
  /*
   * Initialise timer 0 with PWM.
   * Frequency: 488.28hz
   *
   * Output:
   *  OC2A: PB3 (duty cycle: 50%) | Arduino D11
   *  OC2B: PD3 (duty cycle: 30%) | Arduino D3
   *
   * A Mode: Fast PWM mode (non-inverting).
   *         COM2A1 = 1
   *         COM2A0 = 0
   *
   * B Mode: Fast PWM mode (non-inverting).
   *         COM2B1 = 1
   *         COM2B0 = 0
   *
   * Wave form: Fast PWM with TOP at 0xFF
   *            WGM21 = WGM20 = 1
   *
   * Pre-scaler: 1/128
   *             CS22 = 1
   *             CS21 = 0
   *             CS20 = 1
   *
   * Output compare registers:
   *  OCR2A = (256*0.5) = 128.
   *  OCR2B = (256*0.3) = 77.
   */
  DDRD |= (1 << PD3);
  DDRB |= (1 << PB3);

  TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
  TCCR2B |= (1 << CS22) | (1 << CS20);
  OCR2A = (256 * 0.5);
  OCR2B = (256 * 0.3);
}
