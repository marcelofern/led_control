#include "../include/usart.h"
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

FILE uartout = FDEV_SETUP_STREAM(usart_transmit, NULL, _FDEV_SETUP_WRITE);

int usart_transmit(char data, struct __file *stream) {
  /* Transmit 8bits worth of data via USART.
   *
   * Waits until UCSR0A is ready to receive data,
   * and then pushes to register UDR0.
   *
   * More details are in section 19.6.1 of the ATmega328p datasheet.
   */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

void usart_init() {
  /* Initialises USART communication.
   *
   * - Use Asynchronous normal mode.
   * - Enable transmitter only.
   * - Use 8-bit characters for communication.
   *
   * More details are in section 19 of the ATMega328p datasheet.
   */
  uint16_t ubrr = UBRR_VALUE;
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)(ubrr);
  UCSR0B = 1 << TXEN0;
  UCSR0C = 3 << UCSZ00;
  stdout = &uartout;
}
