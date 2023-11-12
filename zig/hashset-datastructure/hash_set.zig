const std = @import("std");
const Allocator = @import("std").mem.Allocator;
const StringLinkedList = @import("linked_list.zig").StringLinkedList;

pub const LinkedListStringHashSet = struct {
    const Self = @This();

    entries: usize,
    capacity: usize,
    set_array: []?*StringLinkedList,
    allocator: *const Allocator,
    collisions: usize,

    pub fn init(allocator: *const Allocator, capacity: usize) !Self {
        var new_set_array = try allocator.alloc(?*StringLinkedList, capacity);
        for (new_set_array) |*item| {
            item.* = null;
        }
        return Self {
            .entries = 0,
            .capacity = capacity,
            .set_array = new_set_array,
            .allocator = allocator,
            .collisions = 0,
        };
    }

    pub fn deinit(self: Self) void {
        for (self.set_array) |list| {
            if (list) |l| {
                l.deinit();
            }
        }
        self.allocator.free(self.set_array);
    }

    pub fn loadFactor(self: Self) f32 {
        if (self.entries == 0) return @floatFromInt(0);
        return @as(f32, @floatFromInt(self.entries)) / @as(f32, @floatFromInt(self.capacity));
    }

    pub fn add(self: *Self, value: []const u8) !void {
        const index = self.hash(value);

        if (self.set_array[index]) |list| {
            std.io.getStdOut().writer().print("Collision at index: {d} when adding name: {s}\n", .{index, value}) catch {};
            self.collisions += 1;
            if (!list.contains(value)) {
                try list.add(value);
                self.entries += 1;
            }
        } else {
            const list = try StringLinkedList.init(self.allocator);
            try list.add(value);
            self.set_array[index] = list;
            self.entries += 1;
        }
    }

    pub fn contains(self: Self, value: []const u8) bool {
        const index = self.hash(value);
        if (self.set_array[index]) |list| {
            return list.contains(value);
        }
        return false;
    }

    pub fn remove(self: *Self, value: []const u8) void {
        const index = self.hash(value);
        if (self.set_array[index]) |list| {
            defer {
                if (list.head == null) {
                    list.deinit(); 
                    self.set_array[index] = null;
                }
            }
            list.remove(value) catch {};
            self.entries -= 1;
        }
        return; 
    }

    pub fn hash(self: Self, value: []const u8) usize {
        var index: usize = 0;
        var i: usize = 0;

        for (value) |char| {
            index += char * i * 7;
            index = index % self.capacity;
            i += 1;
        }
        return index;
    }
};


test "Adding and removing elements from a hashset" {
    const allocator = std.testing.allocator;
    var string_set = try LinkedListStringHashSet.init(&allocator, 8);
    defer string_set.deinit();

    try string_set.add("test");
    try std.testing.expect(string_set.entries == 1);
    try std.testing.expect(string_set.contains("test"));

    string_set.remove("test");
    try std.testing.expect(string_set.entries == 0);
    try std.testing.expect(!string_set.contains("test"));

    try string_set.add("hello");
    try std.testing.expect(string_set.contains("hello"));
    try std.testing.expect(string_set.entries == 1);
    try string_set.add("hello");
    try std.testing.expect(string_set.entries == 1);
}
