#include <init.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <core.h>
#include <stdio.h>
#include <type.h>

static char** TRASHED_FILES;
static u64 TRASHED_FILES_LEN;

bool init_trash_dir(void) {
  const char* const home_dir = getenv("HOME");
  if (home_dir == NULL) 
    panic("Unable to get HOME path");

  char trash_dir_path[strlen(home_dir) + 16];
  strcpy(trash_dir_path, home_dir);
  strcat(trash_dir_path, "/.trm");

  DIR* trash_dir = opendir(trash_dir_path);
  if (trash_dir == NULL) {
    printf("warning, trash dir not found!\n");

    if (mkdir(trash_dir_path, 0755) != 0) {
      perror("mkdir");
      panic("Unable to create trash dir");
    }

    trash_dir = opendir(trash_dir_path);
    if (trash_dir == NULL) 
      panic("Unable to open trash dir");
  }

  TRASHED_FILES = (char**) malloc(sizeof(char*) * 16);
  TRASHED_FILES_LEN = 0;
  u64 trashed_files_cap = 16;

  struct dirent* entry;
  while((entry = readdir(trash_dir)) != NULL) {
    if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) 
      continue;
    if (strcmp("trm.cat", entry->d_name) == 0)
      continue;
  
    TRASHED_FILES[TRASHED_FILES_LEN] = (char*) malloc(strlen(entry->d_name) + 1);
    strcpy(TRASHED_FILES[TRASHED_FILES_LEN++], entry->d_name);
    --trashed_files_cap;

    if (trashed_files_cap <= 1) {
      trashed_files_cap += 16;
      TRASHED_FILES = (char**) realloc(TRASHED_FILES, trashed_files_cap);
    }
  }

  closedir(trash_dir);
  return true;
}

bool init_trash_cat(void) {

  return true;
}

char** get_trashed_files(u64* trashed_files_len) {
  if (trashed_files_len == NULL)
    panic("null ptr");

  *trashed_files_len = TRASHED_FILES_LEN;
  return TRASHED_FILES;
}
