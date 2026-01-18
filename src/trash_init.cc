#include "trash_init.h"
#include "trmdef.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

  fs::path path(TrashCatPath);
  if (!fs::exists(path) && !create) {
    std::println("Trash Catalog File `{}` Not Found!", TrashCatPath);
    throw std::runtime_error("Unable to find catalog file");
  }
  if (fs::is_directory(path)) {
    std::println("Trash Catalog Path `{}` Is A Directory", TrashCatPath);
    throw std::runtime_error("Expected File, Found Directory");
  }

  if (!fs::exists(path) && create) {
    _file TrashCat = std::fopen(TrashCatPath.c_str(), "wb");
    if (TrashCat.ptr == nullptr) {
      std::println("Failed to create trash catalog `{}`", TrashCatPath);
      throw std::runtime_error("Failed to create file");
    }

    std::uint64_t sig[] = TRASH_CATALOG_SIGNATURE;
    fwrite_checked(&sig, sizeof(std::uint64_t), 4, TrashCat.ptr);
  }

  _file TrashCat = std::fopen(TrashCatPath.c_str(), "rb");
  if (TrashCat.ptr == nullptr) {
    std::println("Failed to open trash catalog file `{}`", TrashCatPath);
    throw std::runtime_error("File not open");
  }

  std::uint64_t sig[4];
  std::uint64_t check_sig[] = TRASH_CATALOG_SIGNATURE;

  fread_checked(&sig, sizeof(std::uint64_t), 4, TrashCat.ptr);
  if (std::memcmp(&sig, &check_sig, sizeof(std::uint64_t) * 4) != 0) {
    std::println("Trash catalog file signature does not match!");
    throw std::runtime_error("Corrupted Catalog file");
  }

  return;
}
