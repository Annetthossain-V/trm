#ifndef CORE_H
#define CORE_H
#include <stdio.h>
#include <stdbool.h>

void panic(const char* fmt, ...) __attribute__((noreturn));

bool sanity_check(void);
bool try_sanity_fix(void);
  
#define _FWRITE(buff, size, count, file) \
  if (fwrite(buff, size, count, file) != count) \
    panic("fwrite failed!")

#define _FREAD(buff, size, count, file) \
  if (fread(buff, size, count, file) != count) \
    panic("fread failed")

#endif // CORE_H
