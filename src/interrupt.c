#include "../include/rainbow.h"
#include <avr/interrupt.h>
#include <stdio.h>

void configure_interrupt() {
  /*
   * Interrupt that happens when PC0 is "pressed".
   * In arduino, this is analog in A0.
   *
   * 1. Set PC0 as input with pull-up resistor.
   * 2. Activate interrupts in PCINT14..8.
   * 3. But only enable interrupts for PC0.
   * 4. Enable interrupts globally.
   *
   * Note: PCINT8 is another name (special function) for PC0.
   * Note: PCINT8 is part of PCINT1 vector.
   */
  DDRC &= ~(1 << PC0);
  PORTC |= (1 << PC0);
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8);
  sei();
}

static void button_interrupt() {
  printf("\r\nChanging configuration...\r\n");
  // Re-enable interrupts so that another button press during the handling
  // below can happen and change the configuration.
  sei();
  // Clean up all the LEDS
  PORTB &= ~(1 << PB5) & ~(1 << PB4) & ~(1 << PB3) & ~(1 << PB2) & ~(1 << PB1) &
           ~(1 << PB0);
  PORTD &= ~(1 << PD7) & ~(1 << PD6) & ~(1 << PD5) & ~(1 << PD4) & ~(1 << PD3) &
           ~(1 << PD2);
  change_rainbow_performance();
}

ISR(PCINT1_vect) {
  if (!(PINC & (1 << PC0))) {
    button_interrupt();
  }
}
