#ifndef _CMD_H
#define _CMD_H
#include <string>
#include <utility>
#include <vector>

enum CmdOpt {
  OptHelp,
  OptVersion,
  OptRestore,
  OptRestoreCurrent,
  OptPrint,
  OptClean,
  OptRemove,
  OptInit,
};

struct Cmdline {
  std::vector<std::string> files;
  std::vector<CmdOpt> opts;

  Cmdline(const int argc, const char **argv);
  ~Cmdline() = default;

  bool contains(CmdOpt opt);
};

bool CheckHelpOrVersion(Cmdline &cmd);

#endif // _CMD_H
