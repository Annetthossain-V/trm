#pragma once
#include <vector>
#include <string>
#include <type.hxx>

enum cmdopt {
  Version,
  Help,
  PrintTrashed,
  Restore,
  RestoreCurrent,
};

class cmdline {
public:
  cmdline(const int argc, const char** argv);
  bool contains(cmdopt opt);
  void info(u32 total_trashed_files, FILE* trash_cat);

  const std::vector<std::string>& get_files() { return files; }
private:
  std::vector<std::string> files;
  std::vector<cmdopt> opts;
};
