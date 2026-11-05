#include "calc_input.h"
#include "calc_output.h"
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
  // recalc command with argument
  if ( input_len > 1 && input_len < 4 && user_input[0] == '!' && parse_int64(user_input + 1, &parsed.arg1) ) { // user_input + 1 gives address of string after '!' char (starts from second char)
    parsed.command = user_input[0];
    return true;
  }
  // math expression
  if (input_len > 3 && parse_operation(user_input)) {
    save_history(user_input);
    return true;
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
  const char *source = str;
  uint8_t occurrences = 0;
  uint8_t oper_index = 0;
  uint8_t length = 0;
  char operator = '\0';
  while(*str) {
    if (is_valid_operator(*str)) {
      operator = *str;
      oper_index = length;
      occurrences++;
    }
    str++;
    length++;
  }
  // one operator in the middle of the string 
  if (occurrences != 1 || oper_index == 0 || oper_index == length - 1) return false;

  char res1[13] = {0};
  char res2[13] = {0};
  
  if (!slice_str(start, 0, oper_index - 1, res1, sizeof(res1)) ||
      !slice_str(start, oper_index + 1, length - 1, res2, sizeof(res2))) {
      return false;
  }
  if (!parse_int64(res1, &parsed.arg1) ||
      !parse_int64(res2, &parsed.arg2)) {
      return false;
  }
  parsed.command = operator;
  return true;
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

void save_history(const char *str) {
  // allocate memory to new string
  char *new_entry_ptr = malloc((len_str(str) + 1));
  if (new_entry_ptr == NULL) return;
  // copy user input to new slot
  char *ptr = new_entry_ptr; // new_entry_ptr leaves untouched and link to first char in string
  while(*str) {
    *ptr++ = *str++;
  }
  *ptr = '\0';
  // remove oldest
  free(history[0]);
  // shift older entries and add new (LIFO)
  for (uint8_t i = 0; i < HISTORY_SIZE - 1; i++) {
    history[i] = history[i + 1];
  }
  history[HISTORY_SIZE - 1] = new_entry_ptr;
}