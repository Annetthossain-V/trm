#ifndef INIT_H
#define INIT_H
#include <header.h>
#include <stdbool.h>
#include <type.h>

bool init_trash_dir(void);
bool init_trash_cat(void);

char** get_trashed_files(u64* trashed_files_len);
trash_entry_t** get_trashed_entries(u64* trashed_entries_len);

void fini(void);

#endif // INIT_H
