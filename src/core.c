#include <core.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void panic(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt); 

  vfprintf(stderr, fmt, args);
  if (fmt[strlen(fmt) - 1] != '\n') fputc('\n', stderr);
  va_end(args);

  fprintf(stderr, "process panicked! exiting...\n");
  exit(EXIT_FAILURE);
}
