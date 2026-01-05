#include <header.h>
#include <stdlib.h>
#include <core.h>

void freeEntry(trash_entry_t *entry) {
  if (entry == NULL)
    goto null_ptr;
  if (entry->curr_name == NULL)
    goto null_ptr;
  if (entry->og_name == NULL)
    goto null_ptr;
  if (entry->og_path == NULL)
    goto null_ptr;

  free(entry->curr_name);
  free(entry->og_name);
  free(entry->og_path);

  free(entry);
  return;
null_ptr:
  panic("null ptr");
}

trash_entry_t* readentry(FILE* file) {
  if (file == NULL)
    panic("null ptr");

  const char* const err_entry_header = "Invalid entry read!";
  trash_entry_t* entry = (trash_entry_t*) malloc(sizeof(trash_entry_t) + 1);

  _FREAD(&entry->magic_start, sizeof(u16), 1, file);
  _FREAD(&entry->curr_name_len, sizeof(u16), 1, file);
  _FREAD(&entry->og_name_len, sizeof(u16), 1, file);
  _FREAD(&entry->og_path_len, sizeof(u16), 1, file);

  if (entry->magic_start != ENTRY_START)
    panic(err_entry_header);

  if (entry->curr_name_len < 1)
    panic(err_entry_header);
  if (entry->og_name_len < 1)
    panic(err_entry_header);
  if (entry->og_path_len < 1)
    panic(err_entry_header);

  entry->curr_name = (char*) malloc(entry->curr_name_len + 1);
  entry->og_name = (char*) malloc(entry->og_name_len + 1);
  entry->og_path = (char*) malloc(entry->og_path_len + 1);

  _FREAD(entry->curr_name, sizeof(char), entry->curr_name_len, file);
  _FREAD(entry->og_name, sizeof(char), entry->og_name_len, file);
  _FREAD(entry->og_path, sizeof(char), entry->og_path_len, file);

  _FREAD(&entry->magic_end, sizeof(u16), 1, file);
  if (entry->magic_end != ENTRY_END)
    panic(err_entry_header);
    
  return entry;
}

void writeEntry(trash_entry_t *entry, FILE *file) {
  panic("todo");
  return;
}
