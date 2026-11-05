#include "calc.h"
#include <calc_input.h>
#include <stdint.h>
#include <stdbool.h>

int64_t add(void) {
  int64_t res;
  // built-in overflow check
  if (__builtin_add_overflow(parsed.arg1, parsed.arg2, &res))
    return (parsed.arg2 > 0) ? INT64_MAX : INT64_MIN;
  return res;
}

int64_t subtruct(void) {
  int64_t res;
  // built-in overflow check
  if (__builtin_sub_overflow(parsed.arg1, parsed.arg2, &res))
    return (parsed.arg2 < 0) ? INT64_MAX : INT64_MIN;
  return res;
}

int64_t multiply(void) {
  int64_t res;
  // built-in overflow check
  if (__builtin_mul_overflow(parsed.arg1, parsed.arg2, &res))
    return ((parsed.arg1 < 0) != (parsed.arg2 < 0)) ? INT64_MIN : INT64_MAX;
  return res;
}

int64_t divide(void) {
  // Division by zero
  if (parsed.arg2 == 0) return 0;
  // overflow check
  if (parsed.arg1 == INT64_MIN && parsed.arg2 == -1) return INT64_MAX;
  return parsed.arg1 / parsed.arg2;
}

int64_t module(void) {
  return parsed.arg1 % parsed.arg2;
}