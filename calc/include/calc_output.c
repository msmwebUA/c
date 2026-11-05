#include "calc_output.h"
#include "calc_input.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

void print_welcome(void) {
  printf("--- Welcome to Integer Calculation program! ---\n");
  printf("Usage example: input \"x + y\" and press enter to get result (x and y must be positive integers).\n");
  printf("Acceptable actions: add, substruct, multiply, divide and module.\n");
  printf("Use \"i\" command for more details.\n");
  printf("Use \"q\" for exit.\n");
}

void print_commands(void) {
  printf("\"i\" - print info\n");
  printf("\"q\" - exit\n");
  printf("\"h\" - show hostory\n");
  printf("\"c\" - clear history\n");
  printf("\"!x\" - recalculate history row x (x is row number 1..10)\n");
  printf("Acceptable calculation actions: add (+), substruct (-), multiply (*), divide (/) and module (%%).\n");
  printf("Usage example: type x+y and press enter (x and y are positive integers).\n");
  printf("Limits:\n");
  printf("\t- max supported argument is 32 bit unsigned integer (positive 2^32 - 1)\n");
  printf("\t- max supported result is 64 bit signed integer (positive or negative 2^63 - 1))\n");
  printf("\t- user input max length is 21 chars\n");
}

void print_history(void) {
  uint8_t counter = 0;
  printf("History:\n");
  for (int8_t i = HISTORY_SIZE - 1; i >= 0 ; i--) {
    if (history[i] != NULL) {
      counter++;
      printf("%u: %s\n", counter, history[i]);
    }
  }
  if (counter == 0) {
    printf("Sorry, history is empty\n");
  }
}

void recalculate(void) {
  // argument (history row) must be integer from 1 to 10
  if (parsed.arg1 < 1 || parsed.arg1 > HISTORY_SIZE) {
    printf("Row number must be from 1 to 10\n");
    return;
  }
  // get actual size of history
  uint8_t index = 0;
  for (uint8_t i = 0; i < HISTORY_SIZE; i++) {
    if (history[i] != NULL) {
      index++;
    }
  }
  // recalc
  index = index - parsed.arg1;
  if (history[index] != NULL) { // history row exists
    if (parse_operation(history[index])) {
      execute_command();
    }
  } else {
    printf("This history row is empty\n");
  }
}

bool execute_command(void) {
  int64_t res;
  // execute parsed
  switch (parsed.command) {
    // clear history
    case 'c': 
      clear_history();
      break;
    // show history
    case 'h':
      print_history();
      break;
    // print commands
    case 'i': 
      print_commands();
      break;
    // exit
    case 'q':
      return false;
    // show calculated row
    case '!':
      recalculate();
      return true;
    // add
    case '+':
      res = add();
      break;
    // subtruct
    case '-':
      res = subtruct();
      break;
    // multiply
    case '*':
      res = multiply();
      break;
    // divide
    case '/':
      if (parsed.arg2 == 0) {
        printf("Division by zero!\n");
        return true;
      }
      res = divide();
      break;
    // module
    case '%':
      res = module();
      break;
    // otherwize
    default:
      printf("Unknown command\n");
  }

  // return if command is not a math operator
  if (is_valid_command(parsed.command) || parsed.command == '!') {
    parsed.command = '\0';
    return true;
  }

  // print results of math operations
  if (int_overflow(res)) {
    printf("Buffer overflow. Use smaller numbers\n");
  } else {
    printf("Result: %lli\n", res);
  };

  // clear content
  parsed = (ParsedInput){0}; // same as parsed.command = '\0'; parsed.arg1 = 0; parsed.arg2 = 0;
  return true;
}

bool int_overflow(int64_t num) {
  return (num == INT64_MAX || num == INT64_MIN);
}