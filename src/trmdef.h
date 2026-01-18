#ifndef _TRMDEF_H
#define _TRMDEF_H
#include <cstdint>
#include <cstdio>
#include <stdexcept>

#define TRASH_CATALOG_SIGNATURE                                                \
  {0xFFF20AE922, 0xFF87721EFAC, 0x21BCDAE9932C, 0xFFAACB229392}

static inline void fwrite_checked(void *ptr, size_t size, size_t n,
                                  std::FILE *file) {
  if (std::fwrite(ptr, size, n, file) != n)
    throw std::runtime_error("failed to write to file");
}

static inline void fread_checked(void *ptr, size_t size, size_t n,
                                 std::FILE *file) {
  if (std::fread(ptr, size, n, file) != n)
    throw std::runtime_error("failed to read file");
}

struct _file {
  std::FILE *ptr;

  _file() { ptr = nullptr; }
  _file(std::FILE *fp) { ptr = fp; }
  ~_file() {
    if (ptr != nullptr)
      std::fclose(ptr);
  }
  _file &operator=(std::FILE *fp) {
    ptr = fp;
    return *this;
  }
};

#endif // _TRMDEF_H
