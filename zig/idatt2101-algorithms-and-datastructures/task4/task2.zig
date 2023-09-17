const std = @import("std");
const stack = @import("stack.zig");

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    const invalid1 = try is_valid("invalid1.txt");
    const invalid2 = try is_valid("invalid2.txt");
    const valid = try is_valid("valid.txt");

    try stdout.print("invalid1.txt valid?: {}\n", .{invalid1});
    try stdout.print("invalid2.txt valid?: {}\n", .{invalid2});
    try stdout.print("valid.txt valid?: {}\n", .{valid});
}

fn is_valid(filename: []const u8) !bool {
    const file = try std.fs.cwd().openFile(filename, .{});
    defer file.close();

    var buffered_reader = std.io.bufferedReader(file.reader());
    const file_reader = buffered_reader.reader();
    
    const U8StackHandler = stack.StackHandler(u8); 
    var symbol_stack = U8StackHandler.create(512);

    var buffer: [1024]u8 = undefined;
    var char_count: u32 = 0;
    while (try file_reader.readUntilDelimiterOrEof(&buffer, '\n')) |data| {
        for (data) |char| {
            char_count += 1;

            // Opening bracket
            if (char == '{' or char == '(' or char == '[') {
                try U8StackHandler.append(&symbol_stack, char);
            }

            // Closing bracket
            else if (char == '}' or char == ')' or char == ']') {
                const symbol = U8StackHandler.pop(&symbol_stack) catch return false;

                // Must match to be valid!!
                if (symbol == '(' and char == ')') {
                    continue;
                }
                if (symbol == '{' and char == '}') {
                    continue;
                }
                if (symbol == '[' and char == ']') {
                    continue;
                }
                std.debug.print("Failed in file \"{s}\" at char: {}\n", .{filename, char_count});
                std.debug.print("Expected closing bracket for: {}, but got: {}\n\n", .{symbol, char});
                return false;
            }
        }
    }

    if (symbol_stack.size > 0) return false;
    return true;
}
