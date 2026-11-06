#include "include/calc_input.h"
#include "include/calc_output.h"
#include <stdio.h>
#include <stdint.h>

#ifdef PICO_ON_DEVICE
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"

void setup(void) {
  stdio_init_all();
  
  while(!stdio_usb_connected()) {
    sleep_ms(100);
  }
  
  printf("Connection to Pico established\n");
}
#endif

int main(void) {
  #ifdef PICO_ON_DEVICE
  setup();
  #endif

  // print welcome message
  print_welcome();

  char user_input[USER_INPUT_MAX_SIZE];

  // main loop
  while(1) {
    // get user input from serial console
    printf("> ");
    fflush(stdout); // ensures > appears immediately, even if stdout is buffered

    // custom read input function fixes no-echo and new line char (\r \n) issues on Pico + input validatation
    int16_t n = read_line(user_input, sizeof(user_input));
    if (n < 0) {
      printf("Input too long, try again\n");
      continue;
    }
    
    // parse input
    uint8_t input_len = remove_whitespaces(user_input); // remove all whitespaces, returns new len
    if (input_len > 0) {
      if (parse_input(user_input, input_len)){
        if (!execute_command()) return 0; // exit when q pressed
      } else {
        printf("Invalid command, try again\n");
        continue;
      }
    } else {
      printf("Empty input, try again\n");
      continue;
    }
  }
  return 0;
}
