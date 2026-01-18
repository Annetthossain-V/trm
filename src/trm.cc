#include "cmd.h"
#include "trash_init.h"
#include <print>
#include <stdexcept>

int main(const int argc, const char **argv) {
  try {
    Cmdline cmd(argc, argv);
    if (CheckHelpOrVersion(cmd))
      return 0;

    if (cmd.contains(CmdOpt::OptVerbose))
      std::println("\x1b[33mChecking trash dir...\x1b[0m");
    init_trash_dir(cmd.contains(CmdOpt::OptInit) ? true : false);

    if (cmd.contains(CmdOpt::OptVerbose))
      std::println("\x1b[33mChecking trash catalog...\x1b[0m");
    init_trash_cat(cmd.contains(CmdOpt::OptInit) ? true : false);
  } catch (const std::runtime_error &err) {
    std::println("[\x1b[31mError\x1b[0m] {}", err.what());
    std::println("\x1b[31m{}\x1b[0m failed to complete task", argv[0]);
    return 1;
  }
  return 0;
}
