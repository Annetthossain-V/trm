#include <cmdline.h>
#include <stdlib.h>
#include <cmdline.h>
#include <core.h>
#include <init.h>
#include <pthread.h>
#include <stdio.h>

static void* init(void* arg) {
  if (!init_trash_dir()) return (void*)1;
  if (!init_trash_cat()) return (void*)1;
  return (void*)0;
}

int main(const int argc, const char** argv) {
  pthread_t init_thread;

  if (pthread_create(&init_thread, NULL, init, NULL) != 0) {
    perror("pthread create");
    return EXIT_FAILURE;
  }

  cmdline_t cmd;
  if (!parseCmdline(&cmd, argc, argv)) return EXIT_FAILURE;
  if (checkCmdline(&cmd)) return EXIT_SUCCESS;

  int init_retval;
  if (pthread_join(init_thread, (void*)&init_retval) != 0) {
    perror("pthread join");
    return EXIT_FAILURE;
  }
  if (init_retval != 0) 
    panic("Initialization failed");

  


  freeCmdline(&cmd);
  return EXIT_SUCCESS;
}
