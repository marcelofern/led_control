#include "../include/interrupt.h"
#include "../include/rainbow.h"
#include "../include/usart.h"
#include <stdio.h>

int main(void) {
  usart_init();
  printf("Running main()...\r\n\n");
  configure_interrupt();
  configure_rainbow();
  while (1)
    ;
  return 0;
}
