#include "trash_init.h"
#include <cstdlib>
#include <filesystem>
#include <print>
#include <string>

namespace fs = std::filesystem;

void init_trash_dir(const bool create) {
  const char *const HomeDir = std::getenv("HOME");
  std::string trash_path(HomeDir);
  trash_path += "/.trm";

  fs::path path(trash_path);
  if (fs::exists(path) && !fs::is_directory(path)) {
    std::println("Trash dir path `{}` is not a dir", trash_path);
    throw std::runtime_error("Not a directory");
  }

  if (!fs::exists(path)) {
    if (!create) {
      std::println("Trash dir `{}` doesn't exist!", trash_path);
      std::println("Run with `--init` to create it");
      throw std::runtime_error("Directory not found!");
    }

    if (!fs::create_directory(path)) {
      std::println("Failed to create trash dir path `{}`", trash_path);
      throw std::runtime_error("Dir creation failed");
    }
  }
  return;
}

void init_trash_cat(const bool create) {
  const char *const HomeDir = std::getenv("HOME");
  std::string TrashCatPath(HomeDir);
  TrashCatPath += "/.trm/trash.cat";

  throw int{2};

  return;
}
