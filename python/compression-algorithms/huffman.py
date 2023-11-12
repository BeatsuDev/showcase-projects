from __future__ import annotations
from collections import Counter
from node import Node
import argparse


def create_huffman_tree(data: bytes) -> Node:
    occurences = list(Counter(data).items())
    occurences.sort(key=lambda x: x[1])

    while len(occurences) > 1:
        node1 = occurences.pop(0)
        node2 = occurences.pop(0)

        if isinstance(node1, tuple) and isinstance(node2, tuple):
            new_node = Node(node1[1] + node2[1], node1[0], node2[0])
        elif isinstance(node1, tuple) and isinstance(node2, Node):
            new_node = Node(node1[1] + node2.value, node1[0], node2)
        elif isinstance(node1, Node) and isinstance(node2, tuple):
            new_node = Node(node1.value + node2[1], node1, node2[0])
        else:
            new_node = Node(node1.value + node2.value, node1, node2)

        i = 0
        while i < len(occurences):
            if isinstance(occurences[i], tuple):
                priority = occurences[i][1]
            else:
                priority = occurences[i].value

            if priority < new_node.value:
                i += 1
            else:
                occurences.insert(i, new_node)
                break
        else:
            occurences.append(new_node)

    return occurences[0]


def huffman_compress_bytes(data: bytes) -> bytes:
    tree_root = create_huffman_tree(data)
    tree_bytes = tree_root.serialize()

    output = len(tree_bytes).to_bytes(3, 'big') + tree_bytes + len(data).to_bytes(4, 'big')
    binary_buffer = ""
    for byte in data:
        node = tree_root

        while True:
            if byte == node.left:
                binary_buffer += "0"
                break

            elif byte == node.right:
                binary_buffer += "1"
                break

            if isinstance(node.left, Node) and byte in node.left:
                binary_buffer += "0"
                node = node.left

            elif isinstance(node.right, Node) and byte in node.right:
                binary_buffer += "1"
                node = node.right

        if len(binary_buffer) > 16:
            output += int(binary_buffer[:16], 2).to_bytes(2, 'big')
            binary_buffer = binary_buffer[16:]

    # Append with zeroes to fill a byte. The length of the data
    # will anyway be determined by a byte at the beginning of the file
    # so the data will be stripped
    binary_buffer += "0" * 16
    output += int(binary_buffer[:16], 2).to_bytes(2, 'big')

    return output


def huffman_decompress_bytes(data: bytes) -> bytes:
    tree_data_size = int.from_bytes(data[:3], 'big')
    tree_data_bytes = data[3: tree_data_size + 3]
    root_node = Node.deserialize(tree_data_bytes)

    data_size_bytes = data[3 + tree_data_size: 3 + tree_data_size + 4]
    data_size = int.from_bytes(data_size_bytes, 'big')
    data_binary = bin(int.from_bytes(data[3 + tree_data_size + 4:], 'big'))[2:]

    if len(data_binary) % 8:
        data_binary = "0" + data_binary

    output = b""
    binary_buffer = ""

    i = 0
    current_node = root_node

    while len(output) < data_size:
        if not binary_buffer:
            binary_buffer = data_binary[i: i+16]
            i += 16

        if not binary_buffer and i > len(data_binary):
            print("No more data to read and the data is not fully reconstructed yet!")
            break

        bit = int(binary_buffer[0])
        binary_buffer = binary_buffer[1:]

        try:
            if isinstance(current_node[bit], Node):
                current_node = current_node[bit]
            else:
                output += current_node[bit].to_bytes(1, 'big')
                current_node = root_node
        except:
            import pdb
            pdb.set_trace()

            print("This should not be happening.")

    return output


def huffman(input_file_name: str,
            output_file_name: str,
            decompress: bool = False) -> None:
    with open(input_file_name, "rb") as file:
        input_data = file.read(1024**3)

    if decompress:
        output = huffman_decompress_bytes(input_data)
    else:
        output = huffman_compress_bytes(input_data)

    with open(output_file_name, "wb") as file:
        file.write(output)


if __name__ == "__main__":
    description = "Compresses/decompresses a file using the " \
                  "Huffman Coding algorithm."
    arg_parser = argparse.ArgumentParser(description=description)
    arg_parser.add_argument("-d", "--decompress", action="store_true")
    arg_parser.add_argument("input_file_name", metavar="input-file")
    arg_parser.add_argument("output_file_name",
                            nargs="?",
                            metavar="output-file",
                            default="output.txt")
    args = arg_parser.parse_args()

    if args.decompress:
        print(f"Decompressing {args.input_file_name}", end=" ")
        print(f"to {args.output_file_name}")
    else:
        print(f"Compressing {args.input_file_name}", end=" ")
        print(f"to {args.output_file_name}")

    huffman(args.input_file_name, args.output_file_name, args.decompress)
