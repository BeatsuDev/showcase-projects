const std = @import("std");


const StackError = error {
    StackOverflow,
    StackEmpty
};

pub fn StackHandler(comptime T: type) type {
    return struct {
        pub const Stack = struct {
            stack_array: []T,
            size: usize,
            max: usize,
        };

        pub fn create(comptime size: usize) Stack {
            var stack_array: [size]T = undefined;
            return Stack {
                .stack_array = &stack_array,
                .size = 0,
                .max = size,
            };
        }

        pub fn append(stack: *Stack, value: T) StackError!void {
            if (stack.size == stack.max) return StackError.StackOverflow;

            stack.stack_array[stack.size] = value;
            stack.size += 1;
        }

        pub fn pop(stack: *Stack) StackError!T {
            if (stack.size == 0) return StackError.StackEmpty;

            stack.size -= 1;
            return stack.stack_array[stack.size];
        }
    };
}

