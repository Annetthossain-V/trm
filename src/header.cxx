#include <struct.hxx>
#include <cstring>

void make_header(FILE *trash_cat)
{
  TrashCatHeader header = {
    .magic = MAGIC,
    .trash_header = "[Trash Catalog]",
    .version = 2,  
    .total_trashed_files = 0,
  };
  
  FWRITE_MACRO(&header, sizeof(TrashCatHeader), 1, trash_cat);
  return;
}

TrashCatHeader* read_header(FILE* trash_cat) 
{
  TrashCatHeader* trash_header = new TrashCatHeader;

  FREAD_MACRO(&trash_header->magic, sizeof(u16), 1, trash_cat);
  FREAD_MACRO(trash_header->trash_header, sizeof(char), 16, trash_cat);
  FREAD_MACRO(&trash_header->version, sizeof(u8), 1, trash_cat);
  FREAD_MACRO(&trash_header->total_trashed_files, sizeof(u32), 1, trash_cat);

  const char* errm = "Invalid trash catalog header";
  if (trash_header->magic != MAGIC) throw std::runtime_error(errm);
  if (std::strcmp(trash_header->trash_header, "[Trash Catalog]") != 0) throw std::runtime_error(errm);
  if (trash_header->version != 2) throw std::runtime_error(errm);

  return trash_header;
}

void write_item_entry(ItemEntry* entry) {

}

ItemEntry* read_item_entry(FILE* trash_cat) {

}
