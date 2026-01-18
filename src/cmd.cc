#include "cmd.h"
#include <cstring>
#include <print>
#include <stdexcept>

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

      else {
        std::println("Argument `{}`", argv[i]);
        throw std::runtime_error("Unknown Argument!");
      }
    }
  }

  return;
}
