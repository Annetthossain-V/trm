const std = @import("std");
const terr = @import("err.zig");
const err = terr.err;


const VERSION: f16 = 2.2;
const HELP: []const u8 = 
  \\Usage: trm <files> <options>
  \\options:
  \\ --help # prints this message
  \\ --version # prints version info
  \\ --restore # restore all given files from trash
  \\ --restore-current # restore all given files from trash to current directory
  \\ --print-trashed # print all trashed files
;

pub const cmdopt = enum {
  Help,
  Version,
  Restore,
  RestoreCurrent,
  PrintTrashed,
};

pub const cmdline = struct {
  files: std.ArrayList([]const u8),
  opts: std.ArrayList(cmdopt),
  allocator: std.mem.Allocator,

  pub fn new(allocator: std.mem.Allocator) cmdline {
    return .{
      .files = std.ArrayList([]const u8).initCapacity(allocator, 0) catch unreachable,
      .opts = std.ArrayList(cmdopt).initCapacity(allocator, 0) catch unreachable,
      .allocator = allocator,
    };
  }

  pub fn deinit(self: *cmdline) void {
    for (self.files.items) |item| {
      self.allocator.free(item);
    }

    self.files.deinit(self.allocator);
    self.opts.deinit(self.allocator);
  }

  pub fn addFile(self: *cmdline, str: []const u8) void {
    const owned = self.allocator.dupe(u8, str) catch unreachable;
    self.files.append(self.allocator, owned) catch unreachable;
  }

  pub fn contains(self: *cmdline, opt: cmdopt) bool {
    for (self.opts.items) |_opt| {
      if (_opt == opt) return true;
    }
    return false;
  }
};

pub fn parseCmdline(alloc: std.mem.Allocator) err!cmdline {
  var cmd: cmdline = cmdline.new(alloc);

  const args = std.process.argsAlloc(alloc) catch return err.CmdlineFailed;
  defer std.process.argsFree(alloc, args);

  for (args[1..]) |arg| {
    if (arg[0] != '-') {
      cmd.addFile(arg);
    } 
    else {
      if (std.mem.eql(u8, arg, "--version")) {
        cmd.opts.append(alloc, cmdopt.Version) catch unreachable;
      }
      else if (std.mem.eql(u8, arg, "--help")) {
        cmd.opts.append(alloc, cmdopt.Help) catch unreachable;
      }
      else if (std.mem.eql(u8, arg, "--restore")) {
        cmd.opts.append(alloc, cmdopt.Restore) catch unreachable;
      }
      else if (std.mem.eql(u8, arg, "--restore-current")) {
        cmd.opts.append(alloc, cmdopt.RestoreCurrent) catch unreachable;
      }
      else if (std.mem.eql(u8, arg, "--print-trashed")) {
        cmd.opts.append(alloc, cmdopt.PrintTrashed) catch unreachable;
      }

      else {
        std.debug.print("Unknown flag `{s}`\n", .{arg});
        return err.CmdlineFailed;
      }
    }
  }
 
  if (cmd.files.items.len < 1) cmd.opts.append(alloc, cmdopt.Help) catch unreachable;
  return cmd;
}

pub fn checkCmd(cmd: *cmdline) bool {
  if (cmd.contains(cmdopt.Version)) {
    std.debug.print("version {}\n", .{VERSION});
    return true;
  }
  else if (cmd.contains(cmdopt.PrintTrashed)) {
    return undefined;
  }
  else if (cmd.contains(cmdopt.Help)) {
    std.debug.print("{s}", .{HELP});
    return true;
  }
  return false;
}
