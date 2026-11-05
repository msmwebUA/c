// Pico integer calculator

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "include/calc_input.h"
#include "include/calc_output.h"

#define USER_INPUT_MAX_SIZE 26


void setup(void) {
  while(!stdio_usb_connected()) {
    sleep_ms(100);
  }
  printf("Connection to Pico established\n");
  // print welcome message
  print_welcome();
}

uint8_t main(void) {
  setup();

  char user_input[USER_INPUT_MAX_SIZE];

  // main loop
  while(1) {
    // get user input from serial console
    // scanf("%25s", user_input);
    if (fgets(user_input, sizeof(user_input) - 1, stdin) == NULL) {
      printf("Empty input, try again\n");
      continue;
    } else {
      uint8_t input_len = remove_whitespaces(user_input); // remove all whitespaces, returns new len
      if (input_len > 0) {
        // parse input
        if (parse_input(user_input, input_len)){
          if (!execute_command()) {
            return 0; // exit when q pressed
          }
        } else {
          printf("Invalid command, try again\n");
          continue;
        }
      } else {
        printf("Empty input, try again\n");
        continue;
      }
    }
  }
  return 0;
}
