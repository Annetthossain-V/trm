#pragma once
#include <type.hxx>
#include <cstdio>
#include <stdexcept>

#define MAGIC 0xA7F3
 
#define ENTRY_START 0x3C9A
#define ENTRY_END 0xF041

#define FREAD_MACRO(ptr, size, count, fp) \
    if (std::fread(ptr, size, count, fp) != count) \
      throw std::runtime_error("read failed")

#define FWRITE_MACRO(ptr, size, count, fp) \
    if (std::fwrite(ptr, size, count, fp) != count) \
      throw std::runtime_error("write failed")

struct TrashCatHeader {
  u16 magic;
  char trash_header[16];
  u8 version;
  u32 total_trashed_files;
} __attribute__((packed));
typedef struct TrashCatHeader TrashCatHeader;

extern TrashCatHeader* read_header(FILE* trash_cat);
void make_header(FILE* trash_cat);

struct ItemEntry {
  u16 entry_start;
  u16 original_name_len;
  u16 new_name_len;
  u16 original_path_len;
  char* orignal_name;
  char* new_name;
  char* original_path;
  u8 is_dir;
  u16 entry_end;
} __attribute__((packed));
typedef struct ItemEntry ItemEntry;
