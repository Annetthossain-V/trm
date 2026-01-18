#include "cmd.h"
#include <cstring>
#include <print>
#include <stdexcept>

#define VERSION "2.4"

static const char *const HELP_MSG = "Usage: trm <options> <files>\n\
options:\n\
  <Information>\n\
    --help # prints this message\n\
    --version # prints version info\n\
    --print-trashed # print trashed files\n\
  <Trash>\n\
    --restore # restore given files from trashed files\n\
    --restore-current # restore to current directory instead of the original one\n\
    --clean # delete all trashed files\n\
    --remove # delete given files from trash\n\
    --init # create trash dir and trash catalog if they don't exist";

Cmdline::Cmdline(const int argc, const char **argv) {
  if (argc < 2)
    throw std::runtime_error("Not enough arguments provided!");

  for (auto i = 0; i < argc; ++i) {
    if (argv[i][0] != '-')
      this->files.push_back(argv[i]);
    else {
      if (strcmp(argv[i], "--help") == 0)
        this->opts.push_back(CmdOpt::OptHelp);
      else if (strcmp(argv[i], "--version") == 0)
        this->opts.push_back(CmdOpt::OptVersion);
      else if (strcmp(argv[i], "--restore") == 0)
        this->opts.push_back(CmdOpt::OptRestore);
      else if (strcmp(argv[i], "--restore-current") == 0)
        this->opts.push_back(CmdOpt::OptRestoreCurrent);
      else if (strcmp(argv[i], "--print-trashed") == 0)
        this->opts.push_back(CmdOpt::OptPrint);
      else if (strcmp(argv[i], "--clean") == 0)
        this->opts.push_back(CmdOpt::OptClean);
      else if (strcmp(argv[i], "--remove") == 0)
        this->opts.push_back(CmdOpt::OptRemove);
      else if (strcmp(argv[i], "--init") == 0)
        this->opts.push_back(CmdOpt::OptInit);

      else {
        std::println("Argument `{}`", argv[i]);
        throw std::runtime_error("Unknown Argument!");
      }
    }
  }

  return;
}

bool Cmdline::contains(CmdOpt opt) {
  for (auto _opt : this->opts) {
    if (_opt == opt)
      return true;
  }
  return false;
}

bool CheckHelpOrVersion(Cmdline &cmd) {
  if (cmd.contains(CmdOpt::OptHelp)) {
    std::println("{}", HELP_MSG);
    return true;
  } else if (cmd.contains(CmdOpt::OptVersion)) {
    std::println("trm version {}", VERSION);
    return true;
  }
  return false;
}
