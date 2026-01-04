#ifndef CMDLINE_H
#define CMDLINE_H
#include <type.h>
#include <stdbool.h>

#define CMDOPT_HELP 0
#define CMDOPT_VERSION 1 
#define CMDOPT_PRINT_TRASHED 2
#define CMDOPT_RESTORE 3
#define CMDOP_RESTORE_CURRENT 4

struct cmdline {
  char** files;
  u8* opts;

  u16 files_len;
  u16 opts_len;
} __attribute__((packed));
typedef struct cmdline cmdline_t;

bool parseCmdline(cmdline_t* cmd);
void freeCmdline(cmdline_t* cmd);

#endif // CMDLINE_H
