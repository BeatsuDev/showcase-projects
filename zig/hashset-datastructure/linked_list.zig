const Allocator = @import("std").mem.Allocator;

pub const StringLinkedList = struct {
    const Self = @This();

    allocator: *const Allocator,
    head: ?*Node = null,

    pub const Node = struct {
        next: ?*Node = null,
        value: []const u8,
    };

    pub fn init(allocator: *const Allocator) !*Self { 
        var list = try allocator.create(Self);
        errdefer allocator.destroy(list);
        list.* = Self {.allocator = allocator, .head = null};
        return list;
    }

    pub fn deinit(list: *Self) void {
        var node = list.head;
        while (node) |current_node| {
            node = current_node.next;
            list.allocator.destroy(current_node);
        }
        list.allocator.destroy(list);
    }

    pub fn debug_print(list: *Self) void {
        var node = list.head;
        while (node) |current_node| {
            node = current_node.next;
        }
    }

    pub fn add(list: *Self, value: []const u8) !void {
        const new_node = try list.allocator.create(Node);
        errdefer list.allocator.destroy(new_node);
        new_node.* = .{.next = list.head, .value=value};
        list.head = new_node;
    }

    pub fn remove(list: *Self, value: []const u8) error {ValueNotFound}!void {
        var previous_node: ?*Node = null;
        var node = list.head;

        while (node) |current_node| {
            if (std.mem.eql(u8, current_node.value, value)) {
                if (previous_node) |prev_node| {
                    prev_node.next = current_node.next;
                } else {
                    list.head = current_node.next;
                }
                list.allocator.destroy(current_node);
                return;
            }
            previous_node = node;
            node = current_node.next;
        }
        return error.ValueNotFound;
    }

    pub fn contains(list: *Self, value: []const u8) bool {
        var node = list.head;
        while (node) |current_node| : (node = current_node.next) {
            if (std.mem.eql(u8, current_node.value, value)) {
                return true;
            }
        }
        return false;
    }
};


const std = @import("std");

test "Test StringLinkedList" {
    var number_list = try StringLinkedList.init(&std.testing.allocator);
    defer number_list.deinit();

    try number_list.add("a");
    try number_list.add("bb");
    try number_list.add("ccc");

    try std.testing.expect(number_list.contains("a"));
    try std.testing.expect(number_list.contains("ccc"));

    if (number_list.head) |head_node| {
        try std.testing.expect(std.mem.eql(u8, head_node.value, "ccc"));
        if (head_node.next) |next_node| {
            if (next_node.next) |next_next_node| {
                try std.testing.expect(std.mem.eql(u8, next_next_node.value, "a"));
            } else {
                try std.testing.expect(false);
            }
        } else {
            try std.testing.expect(false);
        }
    }
    else {
        try std.testing.expect(false);
    }

    try number_list.remove("bb");
    try std.testing.expect(!number_list.contains("bb"));
    if (number_list.head) |head_node| {
        if (head_node.next) |next_node| {
            try std.testing.expect(std.mem.eql(u8, next_node.value, "a"));
        }
    }

    try number_list.remove("ccc");
    if (number_list.head) |head_node| {
        try std.testing.expect(std.mem.eql(u8, head_node.value, "a"));
    }
}
