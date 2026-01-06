#include "header.h"
#include <type.h>
#include <core.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <init.h>
#include <unistd.h>

void panic(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt); 

  vfprintf(stderr, fmt, args);
  if (fmt[strlen(fmt) - 1] != '\n') fputc('\n', stderr);
  va_end(args);

  fprintf(stderr, "process panicked! exiting...\n");

  sleep(1);
  exit(EXIT_FAILURE);
}

// un-tested
bool sanity_check(void) {
  u64 trashed_entries_len = 0;
  u64 trashed_files_len = 0;

  char** trashed_files = get_trashed_files(&trashed_files_len);
  trash_entry_t** trashed_entries = get_trashed_entries(&trashed_entries_len);

  if (trashed_entries_len  != trashed_files_len)
    return false;

  // check for all entries in catalog
  for (u64 i = 0; i < trashed_entries_len; ++i) {
    bool match_found = false;

    for (u64 p = 0; p < trashed_files_len; ++p) {
      if (strcmp(trashed_entries[i]->curr_name, trashed_files[p]) == 0) {
        match_found = true;
        break;
      }
      asm("nop");
    }

    if (!match_found)
      return false;
  }

  // check for all files in trash dir
  for (u64 i = 0; i < trashed_files_len; ++i) {
    bool match_found = false;

    for (u64 p = 0; p < trashed_entries_len; ++p) {
      if (strcmp(trashed_files[i], trashed_entries[p]->curr_name) == 0) {
        match_found = true;
        break;
      }
      asm("nop");
    }

    if (!match_found)
      return false;
  }

  return true;
}

// un-tested
bool try_sanity_fix(void) {
  u64 trashed_files_len = 0;
  u64 trashed_entries_len = 0;

  char** trashed_files = get_trashed_files(&trashed_files_len);
  trash_entry_t** trashed_entries = get_trashed_entries(&trashed_entries_len);

  const char* const home_dir = getenv("HOME");
  char trash_dir[strlen(home_dir) + 16];

  strcpy(trash_dir, home_dir);
  strcat(trash_dir, "/.trm/");

  // check for all illegal files

  // check for all illegal entries

  panic("TODO");
  return true;
}
