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

  // create thread to call init
  if (pthread_create(&init_thread, NULL, init, NULL) != 0) {
    perror("pthread create");
    return EXIT_FAILURE;
  }

  cmdline_t cmd;
  if (!parseCmdline(&cmd, argc, argv)) return EXIT_FAILURE;
  if (checkCmdline(&cmd)) return EXIT_SUCCESS;

  // wait for init thread
  int init_retval;
  if (pthread_join(init_thread, (void*)&init_retval) != 0) {
    perror("pthread join");
    return EXIT_FAILURE;
  }
  if (init_retval != 0) 
    panic("Initialization failed");

  // main logic goes here

  if (!sanity_check()) {
    printf("Error! Sanity check failed\n");
    printf("Try to fix it?[y/N] ");

    char key = (char)getchar();
    switch (key) {
      case 'y':
      case 'Y':
        if (!try_sanity_fix())
          panic("Unable to fix sanity\n");
      case 'n':
      case 'N':
      default:
        printf("Unable to fix sanity\n");
        return EXIT_FAILURE; // leaking memory
    }
  }

  
  fini();
  freeCmdline(&cmd);
  return EXIT_SUCCESS;
}
