#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"

int main() {
  stdio_init_all(); // init standart i/o

  while (!stdio_usb_connected()) { // wait until usb connected
    sleep_ms(100);
  }

  printf("Hello, Pico!\n");

  return 0;
}