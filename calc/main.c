#include "include/calc_input.h"
#include "include/calc_output.h"
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"

void setup(void) {
  stdio_init_all();

  while(!stdio_usb_connected()) {
    sleep_ms(100);
  }

  printf("Connection to Pico established\n");
  // print welcome message
  print_welcome();
}

int main(void) {
  setup();

  char user_input[USER_INPUT_MAX_SIZE];

  // main loop
  while(1) {
    // get user input from serial console
    printf("> ");
    fflush(stdout); // ensures > appears immediately, even if stdout is buffered
    if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
      printf("Input error, try again\n");
      continue;
    }
    // validate input length
    bool newline = false;
    for (uint8_t i = 0; user_input[i] != '\0'; i++) {
      if (user_input[i] == '\n') {
        newline = true;
        break;
      }
    }
    if (!newline) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF); // discard remaining input if line was too long
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
