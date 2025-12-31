#include "com.hxx"
#include "struct.hxx"
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <cmdline.hxx>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

void init_trash_dir() {
  const char* home_dir = std::getenv("HOME");
  char* trash_dir = new char[std::strlen(home_dir) + 8];
  
  std::strcpy(trash_dir, home_dir);
  std::strcat(trash_dir, "/.trm");

  struct stat dir;
  if (stat(trash_dir, &dir) != 0) {
    spdlog::warn("Trash dir not found! creating it...");
    if (mkdir(trash_dir, 07755) != 0) 
      throw std::runtime_error("Unable to create trash dir");
  }

  delete[] trash_dir;
  return;
}

FILE* init_trash_cat() {
  const char* home_dir = std::getenv("HOME");
  char* trash_file = new char[std::strlen(home_dir) + 32];

  std::strcpy(trash_file, home_dir);
  std::strcat(trash_file, "/.trm/");
  std::strcat(trash_file, "trm.cat");

  FILE* check_file = std::fopen(trash_file, "rb");
  if (check_file == nullptr) {
    spdlog::warn("Trash catalog file not found! creating it...");
    FILE* create_file = std::fopen(trash_file, "wb");

    make_header(create_file);
    std::fclose(create_file);
  }
  else std::fclose(check_file);

  FILE* file = std::fopen(trash_file, "rwb");
  delete[] trash_file;
  return file;
}

int main(const int argc, const char** argv) {
  try {
    init_trash_dir();
    FILE* trash_file = init_trash_cat();

    cmdline cmd(argc, argv);
    TrashCatHeader* trash_cat_header = read_header(trash_file);
    cmd.info(trash_cat_header->total_trashed_files, trash_file);

    if (cmd.contains(cmdopt::Restore) || cmd.contains(cmdopt::RestoreCurrent)) {
      // restore mode
    } 
    else trash_files(cmd.get_files());

    delete trash_cat_header;
    std::fclose(trash_file);
  } catch (std::runtime_error& err) {
    spdlog::error("{}", err.what());
    return 1;
  }

  return 0;
}
