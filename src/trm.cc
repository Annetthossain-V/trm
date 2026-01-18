#include "cmd.h"
#include "trash_init.h"
#include <print>
#include <stdexcept>

int main(const int argc, const char **argv) {
  try {
    Cmdline cmd(argc, argv);
    if (CheckHelpOrVersion(cmd))
      return 0;

    init_trash_dir(cmd.contains(CmdOpt::OptInit) ? true : false);
    init_trash_cat(cmd.contains(CmdOpt::OptInit) ? true : false);
  } catch (const std::runtime_error &err) {
    std::println("[\x1b[31mError\x1b[0m] {}", err.what());
    std::println("{} failed to complete task", argv[0]);
    return 1;
  }
  return 0;
}
