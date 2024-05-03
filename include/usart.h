#ifndef USART_H
#define USART_H

#include <stdio.h>

#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

int usart_transmit(char, struct __file *);
void usart_init();
extern FILE uartout;

#endif
