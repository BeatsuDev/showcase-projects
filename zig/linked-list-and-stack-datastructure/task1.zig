const std = @import("std");

const Node = struct {
    value: usize,
    next: *Node,  // next is REQUIRED here. Impossible to not make a circular list!!
};

// Choose values here!
const people: usize = std.math.pow(usize, 10, 4);
const skips: usize = 3;

// Program entry point
pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    var general_purpose_allocator = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = general_purpose_allocator.allocator();

    const head = try create_indexed_circular_list(allocator, people);
    const surviving_node = try solution(head, skips);

    try stdout.print("Josephus survives if he's number {} in the row!\n", .{surviving_node.value});
}

// Creates a circular list of people indexed from 1 to people. Returns the head (number 1)
fn create_indexed_circular_list(allocator: std.mem.Allocator, people_amount: usize) !*Node {
    const head: *Node = try allocator.create(Node);

    head.* = .{ .value = 1, .next = head };
    var previous_node: *Node = head;

    for (2..people_amount+1) |i| {
        const current_node = try allocator.create(Node);        
        previous_node.next = current_node;
        current_node.* = .{ .value = i, .next = head };
        previous_node = current_node;
    }
    return head;
}

// Finds the last person to commit suicide given a circular indexed linked list
fn solution(people_list_head: *Node, people_skips: usize ) !*Node {
    const stdout = std.io.getStdOut().writer();

    var previous_node = people_list_head;
    var current_node = people_list_head.next;
    var iterations: usize = 1;

    // Carry on until the next node is the node itself. That means only one node is left!
    while (!(current_node.next == current_node)) {
        if (iterations % (people_skips+1) == people_skips) {
            try stdout.print("Number {} commited suicide!\n", .{current_node.value});
            previous_node.next = current_node.next;
        } else {
            try stdout.print("Skipping number {}\n", .{current_node.value});
            previous_node = current_node;
        }
        current_node = previous_node.next;
        iterations += 1;
    }

    return current_node;
}
