const std = @import("std");
const LinkedListStringHashSet = @import("hash_set.zig").LinkedListStringHashSet;

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    const line_count = try getLineCount("navn.txt");
    try stdout.print("Lines: {d}\n", .{line_count});

    // Round to nearest power of two
    var hash_set_size = line_count;
    var n: usize = 0;
    while (hash_set_size != 1) : (hash_set_size = hash_set_size >> 1) n += 1;
    for (0..n) |_| {
        hash_set_size = hash_set_size << 1;
    }
    hash_set_size = hash_set_size << 1;
    try stdout.print("Hash set size: {d}\n", .{hash_set_size});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();
    var student_set = try LinkedListStringHashSet.init(&allocator, hash_set_size);

    const file = try std.fs.cwd().openFile("navn.txt", .{});
    defer file.close();

    var buffered_reader = std.io.bufferedReader(file.reader());
    const file_reader = buffered_reader.reader();

    try stdout.print("Adding students to hash set\n", .{});
    var buffer: [128]u8 = undefined;
    while (try file_reader.readUntilDelimiterOrEof(&buffer, '\n')) |name| {
        const duped_name = try allocator.dupe(u8, name);
        try student_set.add(duped_name);
    }
    try stdout.print("Finished adding students to hash set. Entries: {}\n", .{student_set.entries});
    try stdout.print("Load factor: {d}\n", .{student_set.loadFactor()});
    const i_exist = student_set.contains("Eric Bieszczad-Stie");
    try stdout.print("Eric Bieszczad-Stie exists? {}\n", .{i_exist});
    try stdout.print("Collisions: {d}\n", .{student_set.collisions});
    const collision_factor = @as(f32, @floatFromInt(student_set.collisions)) / @as(f32, @floatFromInt(student_set.capacity));
    try stdout.print("Collision factor: {d}\n", .{collision_factor});
}

pub fn getLineCount(file_name: []const u8) !usize {
    var line_counter: usize = 0;
    const file = try std.fs.cwd().openFile(file_name, .{});
    defer file.close();

    var buffered_reader = std.io.bufferedReader(file.reader());
    const file_reader = buffered_reader.reader();

    var buffer: [1024*1024]u8 = undefined;
    while (try file_reader.read(&buffer) > 0) {
        for (buffer) |char| {
            if (char == '\n') line_counter += 1;
        }
    }

    return line_counter;
}

