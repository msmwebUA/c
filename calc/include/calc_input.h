#ifndef CALC_INPUT_H
#define CALC_INPUT_H

#define USER_INPUT_MAX_SIZE 26

char user_input[USER_INPUT_MAX_SIZE];

typedef struct {
  char command;
  int64_t arg1;
  int64_t arg2;
} ParsedInput;

extern ParsedInput parsed; // var initialized in calc_input.c file, 'extern' tells to compiler "dont create another instance, var exists somewhere else" 

uint8_t remove_whitespaces(char *user_input);
bool is_valid_command(const char command);
bool is_valid_operator(const char operator);
bool parse_input(const char *user_input, const uint8_t input_len);
bool parse_int64(const char *str, int64_t *result);
bool parse_operation(const char *str);
uint8_t slice_str(const char *source, uint8_t index_from, uint8_t index_to, char *result, uint8_t max_result_size);
uint8_t len_str(const char *str);

#endif