const std = @import("std");
const errors = @import("err.zig");
const c = @cImport({
  @cInclude("sys/types.h");
  @cInclude("sys/stat.h");
  @cInclude("unistd.h");
  @cInclude("dirent.h");
});

pub var trash_files: std.ArrayListAligned(usize, null) = undefined;

pub fn init_trash_dir(alloc: std.mem.Allocator) errors.err!void {
  const home_dir = std.process.getEnvVarOwned(alloc, "HOME") catch return errors.err.InitFailed;
  defer alloc.free(home_dir);

  var trash_dir_path = std.ArrayList(u8).initCapacity(alloc, home_dir.len + 6) catch return errors.err.InitFailed;
  defer trash_dir_path.deinit(alloc);

  trash_dir_path.appendSlice(alloc, "/.trm/") catch return errors.err.InitFailed;

  return;
}

pub fn init_trash_cat() errors.err!void {
  return;
}
