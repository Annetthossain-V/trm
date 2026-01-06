#ifndef HEADER_H
#define HEADER_H
#include <type.h>
#include <stdio.h>

#define GLOBAL_MAGIC 0xA7F3
#define ENTRY_START 0x3C9A
#define ENTRY_END 0xF041

struct entry_date {
  u16 year;
  u8 month;
  u8 day;
  u8 hour;
} __attribute__((packed));
typedef struct entry_date entry_date_t;

struct trm_global_header {
  u16 magic;
  float version;
  u64 total_trashed_files;
  char trash_header[12];
} __attribute__((packed));
typedef struct trm_global_header trm_global_header_t;

struct trash_entry {
  u16 magic_start;

  u16 curr_name_len;
  u16 og_name_len;
  u16 og_path_len;

  char* curr_name;
  char* og_name;
  char* og_path;

  entry_date_t date;

  u16 magic_end;
} __attribute__((packed));
typedef struct trash_entry trash_entry_t;

trash_entry_t* readentry(FILE* file);
void writeEntry(trash_entry_t* entry, FILE* file);
void freeEntry(trash_entry_t* entry);

#endif // HEADER_H
