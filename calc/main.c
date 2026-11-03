// Pico integer calculator

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"

// #include "calc.h"

void setup() {
  while(!stdio_usb_connected()) {
    sleep_ms(100);
  }
  printf("Connection to Pico established");
}

int main() {
  setup();

  // print welcome message (about, i command for info (list commands))

  // main loop
  while(1) {
    // get user input from serial console
  
  
    // validate input (empty input, wrong symbols and commands, missing argument etc)
  
  
    /* parse input
      commands:
        i - show commands
        q - exit
        h - history (last 10 operations), use malloc() and free() dynamic memory
        !x - recalc row from history
      integers and math operation: add, subtract, multiply, divide, module
    */
  
  
    // call helpers (functions for commands and calculations)
  
  
    // show helpers output


  }

  // return 0;

}