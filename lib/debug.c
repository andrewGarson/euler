#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "debug.h"

static LOG_LEVEL level = NONE;

void log_set_level(LOG_LEVEL _level) {
  level = _level;
};

int log_get_level() {
  return level;
}

void log_info(const char *format, ...) {
  va_list args;
  va_start(args, format);

  if(level >= INFO) {
    vprintf(format, args);
  }

  va_end(args);
}

void log_debug(const char *format, ...) {
  va_list args;
  va_start(args, format);

  if(level >= DEBUG) {
    vprintf(format, args);
  }

  va_end(args);
}

double time_func(TimeWrapper *func) {
  clock_t t;
  t = clock();

  (*func)();

  t = clock() - t;
  return ((double)t)/CLOCKS_PER_SEC;
}

void wait_for_user(const char *format, ...){
  va_list args;
  va_start(args, format);
  vprintf(format, args);

  getchar();

  va_end(args);
}

