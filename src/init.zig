const std = @import("std");
const errors = @import("err.zig");

pub fn init_trash_dir(alloc: std.mem.Allocator) errors.err!void {
  const home_dir = std.process.getEnvVarOwned(alloc, "HOME") catch return errors.err.InitFailed;
  defer alloc.free(home_dir);



  return;
}

pub fn init_trash_cat() errors.err!void {
  return;
}
