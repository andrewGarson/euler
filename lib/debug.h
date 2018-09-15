#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <time.h>

typedef enum{
  NONE, // least logging
  INFO,
  DEBUG // most logging
} LOG_LEVEL;

typedef void (*TimeWrapper)(void);

void log_set_level(LOG_LEVEL level);
int log_get_level();

void log_info(const char *format, ...); 
void log_debug(const char *format, ...);

void wait_for_user(const char *format, ...);

#define TIME_START \
{\
  clock_t start; \
  start = clock(); \
  printf("start: %f\n", (double)start);

#define TIME_END(name) \
  clock_t end; \
  end = clock(); \
  printf("end: %f\n", (double)end); \
  name = ((double)(end - start))/CLOCKS_PER_SEC; \
}

#endif
