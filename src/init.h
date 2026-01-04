#ifndef INIT_H
#define INIT_H
#include <stdbool.h>
#include <type.h>

bool init_trash_dir(void);
bool init_trash_cat(void);

char** get_trashed_files(u64* trashed_files_len);

#endif // INIT_H
