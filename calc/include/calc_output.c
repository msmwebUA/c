#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "calc_output.h"
#include "calc_input.h"
#include "calc.h"

void print_welcome(void) {
  printf("--- Welcome to Integer Calculation program! ---\n");
  printf("Usage example: input \"x + y\" and press enter to get result. Max two integers allowed.\n");
  printf("Acceptable actions: add, substruct, multiply, divide and module\n");
  printf("Use \"i\" command for details\n");
  printf("Use \"q\" for exit\n");
}

void print_commands(void) {
  printf("\"i\" - print info\n");
  printf("\"q\" - exit\n");
  printf("\"h\" - show hostory\n");
  printf("\"c\" - clear history\n");
  printf("\"!x\" - recalculate history row x (x is row number 1..10)\n");
  printf("Acceptable calculation actions: add (+), substruct (-), multiply (*), divide (/) and module (%%)\n");
  printf("Usage example: type x+y and press enter (x and y are integers)\n");
  printf("Limits: max supported integer (argument or result) is 64 bit (positive or negative 2^63)\n");
}

void print_history(void) {
  // TODO
}

void save_history(void) {
  // TODO
}

void clear_history(void) {
  // TODO
}

void recalculate(void) {
  // TODO
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
      break;
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
    printf("%lli", res);
  };
  
  // save history
  save_history();

  // clear content
  parsed = (ParsedInput){0}; // same as parsed.command = '\0'; parsed.arg1 = 0; parsed.arg2 = 0;
  return true;
}

bool int_overflow(int64_t num) {
  return (num == INT64_MAX || num == INT64_MIN);
}