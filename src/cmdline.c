#include <cmdline.h>
#include <stdlib.h>
#include <stdio.h>
#include <core.h>
#include <string.h>

const float VERSION = 2.4;
const char* const HELP = "Usage: trm <options> <files> \n\
options:\n\
  --version # prints version info\n\
  --help # prints this message\n\
  --print-trashed # print trashed files\n\
  --restore # restore given trashed files\n\
  --restore-current # restore given trashed files to current current dir\n";

void freeCmdline(cmdline_t *cmd) {
  if (cmd == NULL) goto ERR;
  if (cmd->files == NULL) goto ERR;
  if (cmd->opts == NULL) goto ERR;
  
  for (u16 i = 0; i < cmd->files_len; ++i)
    free(cmd->files[i]);

  free(cmd->opts);
  free(cmd->files);

  return;
ERR:
  panic("null ptr");
}

bool parseCmdline(cmdline_t *cmd, const int argc, const char** argv) {
  cmd->files = (char**) malloc(sizeof(char*) * argc);
  cmd->opts = (u8*) malloc(sizeof(u8) * argc);
  cmd->files_len = 0;
  cmd->opts_len = 0;

  if (argc < 2) {
    cmd->opts[cmd->opts_len++] = CMDOPT_HELP;
    return true;
  }

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') 
    {
      cmd->files[cmd->files_len] = (char*) malloc(strlen(argv[i]) + 1);
      strcpy(cmd->files[cmd->files_len++], argv[i]);
    }
    else 
    {
      if (strcmp(argv[i], "--version") == 0)
      {
        cmd->opts[cmd->opts_len++] = CMDOPT_VERSION;
      }
      else if (strcmp(argv[i], "--help") == 0) 
      {
        cmd->opts[cmd->opts_len++] = CMDOPT_HELP;
      }
      else if (strcmp(argv[i], "--print-trashed") == 0)
      {
        cmd->opts[cmd->opts_len++] = CMDOPT_PRINT_TRASHED;
      }
      else if (strcmp(argv[i], "--restore") == 0)
      {
        cmd->opts[cmd->opts_len++] = CMDOPT_RESTORE;
      }
      else if (strcmp(argv[i], "--restore-current") == 0)
      {
        cmd->opts[cmd->opts_len++] = CMDOP_RESTORE_CURRENT;
      }

      else panic("Undefined option `%s`", argv[i]);
    }
  }

  if (cmd->files_len == 0) cmd->opts[cmd->opts_len++] = CMDOPT_HELP;
  return true;
}

bool checkCmdline(cmdline_t *cmd) {
  if (cmd == NULL) panic("null ptr");
  if (cmd->opts == NULL) panic("null ptr");

  bool is_version = false;
  bool is_print_trashed = false;
  bool is_help = false;

  for (u16 i = 0; i < cmd->opts_len; ++i) {
    switch (cmd->opts[i]) {
      case CMDOPT_VERSION:
        is_version = true;
      case CMDOPT_PRINT_TRASHED:
        is_print_trashed = true;
      case CMDOPT_HELP:
        is_help = true;
      default:
        break;
    }
  }

  if (is_version) {
    printf("version %.1f\n", VERSION);
    return true;
  } else if (is_print_trashed) {
    __builtin_unreachable(); // TODO
    return true;
  } else if (is_help) {
    printf("%s", HELP);
    return true;
  }
  return false;
}
