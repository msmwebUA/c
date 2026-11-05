#include "calc_input.h"
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

const char commands[] = {
  'c', // clean history
  'h', // history
  'i', // print commands
  'q', // exit
};

const char operators[] = {
  '+',
  '-',
  '*',
  '/',
  '%'
};

ParsedInput parsed = {0}; // init instance with empty values

bool is_valid_command(const char command) {
  for (uint8_t i = 0; i < sizeof(commands); i++) {
    if (commands[i] == command) return true;
  }
  return false;
}

bool is_valid_operator(const char operator) {
  for (uint8_t i = 0; i < sizeof(operators); i++) {
    if (operators[i] == operator) return true;
  }
  return false;
}

bool parse_input(const char *user_input, const uint8_t input_len) {
  // check for single command
  if (input_len == 1 && is_valid_command(user_input[0])) {
    parsed.command = user_input[0];
    return true;
  }
  // char *input = user_input; // this helps to keep pointer to start of user_input unchanged
  // recalc command with argument (integer from 1 to 10)
  if ( input_len > 1 && input_len < 4 && user_input[0] == '!' && parse_int64(user_input + 1, &parsed.arg1) ) { // user_input + 1 gives address of string after '!' char (starts from second char)
    parsed.command = user_input[0];
    return true;
  }
  // math expression
  if (input_len > 3) {
    return parse_operation(user_input);
  }
  // otherwize invalid input
  return false;
}

uint8_t remove_whitespaces(char *user_input) {
  char *source = user_input;
  char *result = user_input;
  uint8_t str_len = 0;
  while (*source) {
    if ( !isspace((unsigned char)*source) ) { // isspace() recognizes: space, tab \t, new line \n, carriage return \r, form feed \f, vertical tab \v
      *result++ = *source; 
      str_len++;
    }
    source++;
  }
  *result = '\0';
  return str_len;
}

bool parse_int64(const char *str, int64_t *result) {
  char *endptr;
  errno = 0;
  long long value = strtoll(str, &endptr, 10);
  // no digits found or unexpected characters
  if (endptr == str || *endptr != '\0') return false;
  // check overflow
  if (errno == ERANGE || value < LLONG_MIN || value > LLONG_MAX) return false;
  *result = (int64_t)value;
  return true;
}

bool parse_operation(const char *str) {
  uint8_t occurrences = 0;
  uint8_t oper_index = 0;
  uint8_t last_index = -1;
  char operator;
  while(*str) {
    last_index++;
    if (is_valid_operator(*str)) {
      operator = *str;
      oper_index = last_index;
      occurrences++;
    }
  }
  // one operator in the middle of the string 
  if (occurrences == 1 && oper_index != 0 && oper_index != last_index) {
    // extract arguments, convert them into integers and set to parsed struct
    char res1[13];
    char res2[13];
    if (slice_str(str, 0, oper_index - 1, res1, sizeof(res1)) && slice_str(str, oper_index + 1, last_index, res2, sizeof(res2))) {
      parsed.command = operator;
      return parse_int64(res1, &parsed.arg1) && parse_int64(res2, &parsed.arg2);
    }
  }
  return false;
}

uint8_t slice_str(const char *source, uint8_t index_from, uint8_t index_to, char *result, uint8_t max_result_size) {
  // validate pointers
  if (source == NULL || result == NULL) return 0;
  // validate indexes (from and to must be inside the string, from cannot be greater than to)
  uint8_t source_len = len_str(source);
  if (index_from >= source_len || index_to >= source_len || index_from > index_to) return 0;
  // validate max result size (sliced portion + 1 (for '\0') must fit inside max_result_size)
  if ((index_to - index_from + 1) >= max_result_size) return 0;
  // copy chars
  uint8_t res_index = 0;
  for (uint8_t i = index_from; i <= index_to && source[i] != '\0'; i++) {
    result[res_index] = source[i];
    res_index++;
  }
  // terminate new string
  result[res_index] = '\0';
  return res_index; // len of spliced part
}

uint8_t len_str(const char *str) {
  if (str == NULL) return 0;
  uint8_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}