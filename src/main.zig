const std = @import("std");
const cmdline = @import("cmdline.zig");
const init = @import("init.zig");

pub fn main() !u8 {
  var gpa = std.heap.GeneralPurposeAllocator(.{}){};
  defer _ = gpa.deinit();

  var cmd = cmdline.parseCmdline(gpa.allocator()) catch  {
    std.debug.print("Unable to parse command line args!\n", .{});
    return 1; 
  };
  defer cmd.deinit();

  if (cmdline.checkCmd(&cmd)) return 0;
  
  init.init_trash_dir(gpa.allocator()) catch {
    std.debug.print("Unable to initialize trash directory\n", .{});
    return 1;
  };
  init.init_trash_cat() catch {
    std.debug.print("Unable to initialize trash catalog file\n", .{});
    return 1;
  };

  return 0;
}
