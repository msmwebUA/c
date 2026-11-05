#ifndef CALC_OUTPUT_H
#define CALC_OUTPUT_H

#define HISTORY_SIZE 10

void print_welcome(void);
void print_commands(void);
void print_history(void);
void save_history(const char *str);
void clear_history(void);
void recalculate(void);
bool execute_command(void);
bool int_overflow(int64_t num);

#endif