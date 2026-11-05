#ifndef CALC_OUTPUT_H
#define CALC_OUTPUT_H

void print_welcome(void);
void print_commands(void);
void print_history(void);
void save_history(void);
void clear_history(void);
void recalculate(void);
bool execute_command(void);
bool int_overflow(int64_t num);

#endif