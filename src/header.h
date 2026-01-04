#ifndef HEADER_H
#define HEADER_H
#include <type.h>

#define GLOBAL_MAGIC 0xA7F3
#define ENTRY_START 0x3C9A
#define ENTRY_END 0xF041

struct trm_global_header {
  u16 magic;
  float version;
  u64 total_trashed_files;
  char trash_header[16];
} __attribute__((packed));
typedef struct trm_global_header trm_global_header_t;

struct trash_entry {
  u16 magic_start;

  u16 magic_end;
} __attribute__((packed));
typedef struct trash_entry trash_entry_t;

#endif // HEADER_H
