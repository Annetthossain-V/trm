#include <cmdline.hxx>
#include <stdexcept>
#include <type.hxx>
#include <cstring>
#include <print>
#include <cstdlib>

const f32 VERSION = 2.1;
const char* HELP = "Usage: trm <options> <files>\n\
options:\n\
  --help # prints this message\n\
  --version # prints version info\n\
  --print-trashed # prints trashed files\n\
  --restore # all files given will be restored from trash\n\
  --restore-current # restore trashed files in current dir instead of their original dir\n\
";

cmdline::cmdline(const int argc, const char** argv) {
  if (argc < 2) {
    this->opts.push_back(cmdopt::Help);
    return;
  }

  for (usize i = 1; i < (usize)argc; ++i) {
    if (argv[i][0] != '-') this->files.push_back(argv[i]);
    else 
    {
      if (strcmp(argv[i], "--version") == 0) this->opts.push_back(cmdopt::Version);
      else if (strcmp(argv[i], "--help") == 0) this->opts.push_back(cmdopt::Help);
      else if (strcmp(argv[i], "--print-trashed") == 0) this->opts.push_back(cmdopt::PrintTrashed);
      else if (strcmp(argv[i], "--restore") == 0) this->opts.push_back(cmdopt::Restore);
      else if (strcmp(argv[i], "--restore-current") == 0) this->opts.push_back(cmdopt::RestoreCurrent);

      else throw std::runtime_error("Unknown cmdline option");
    }
  }

  if (this->files.size() < 1) this->opts.push_back(cmdopt::Help);
}

bool cmdline::contains(cmdopt opt) {
  for (auto& _opt : this->opts)
    if (_opt == opt) return true;
  return false;
}

void cmdline::info(u32 total_trashed_file) {
  if (this->contains(cmdopt::Version)) 
  {
    std::println("version {}", VERSION);
    std::exit(0);
  }
  else if (this->contains(cmdopt::PrintTrashed)) 
  {
    std::println("Total Trashed file `{}`", total_trashed_file);
    std::exit(0);
  }
  else if (this->contains(cmdopt::Help)) 
  {
    std::println("{}", HELP);
    std::exit(0);
  }
  return;
}

