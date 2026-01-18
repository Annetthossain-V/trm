#ifndef _TRMDEF_H
#define _TRMDEF_H
#include <cstdint>

#define TRASH_CATALOG_SIGNATURE1                                               \
  {0xFFF20AE922, 0xFF87721EFAC, 0x21BCDAE9932C, 0xFFAACB229392}

struct TrashCatalog {
  std::uint64_t _sig1[4];
  char *files_list;
  std::uint32_t files_list_len;
} __attribute__((packed));
typedef struct TrashCatalog TrashCatalog;

#endif // _TRMDEF_H
