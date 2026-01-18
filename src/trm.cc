#include "cmd.h"
#include <exception>
#include <print>
#include <stdexcept>

int main(const int argc, const char **argv) {
  try {
    Cmdline cmd(argc, argv);

  } catch (const std::runtime_error &err) {
    std::println("[\x1b[31mError\x1b[0m] {}", err.what());
    std::println("{} failed to complete task", argv[0]);
    return 1;
  }
  return 0;
}
