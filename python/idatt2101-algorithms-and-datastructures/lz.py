from __future__ import annotations
import argparse


def find_match(window, match_buffer):
    longest_match = (0, 0)
    for match_end in range(1, len(match_buffer) + 1):
        to_match = match_buffer[:match_end]
        pos = window.rfind(to_match)

        if pos == -1:
            return longest_match

        longest_match = (len(to_match), len(window) - pos)
    
    return longest_match


def lz_compress_bytes(input_bytes):
    window_size = 2**16 - 1
    compressed = bytearray()
    cursor = 0

    # i = 0
    # matches = 0
    # max_len = 0
    # max_dis = 0
    while cursor < len(input_bytes):
        window = input_bytes[max(0, cursor - window_size):cursor]
        match_buffer = input_bytes[cursor:cursor+255]
        match_length, match_distance = find_match(window, match_buffer)

        # if match_length > max_len:
        #     max_len = match_length
        
        # if match_distance > max_dis:
        #     max_dis = match_distance

        # if match_length < 3:
        #     i += 1

        # if match_length > 0:
        #     matches += 1


        if match_length > 1:
            compressed.extend(match_distance.to_bytes(2, byteorder='big'))
            compressed.append(match_length)
            cursor += match_length
        else:
            new_data = input_bytes[cursor:cursor+2]
            if len(new_data) == 2:
                compressed.extend(new_data)
                compressed.append(0)
                cursor += 2
            else:
                compressed.extend(b"\x00\x00")
                compressed.append(new_data[0])
                cursor += 1
                

    # print("Matches:", matches)
    # print("Compressed bytes that increase file size by 1 byte or more unnecessarily:\t", i)
    # print("Longest match:   \t", max_len)
    # print("Longest distance:\t", max_dis)

    return bytes(compressed)


def lz_decompress_bytes(compressed):
    decompressed = bytearray()
    cursor = 0

    print(len(compressed), len(compressed) % 3)
    while cursor < len(compressed):
        distance_bytes = compressed[cursor:cursor+2]
        distance = int.from_bytes(distance_bytes, byteorder='big')
        cursor += 2
        length = compressed[cursor]
        cursor += 1

        if distance == 0:
            decompressed.append(length)
        elif length == 0:
            decompressed.extend(distance_bytes)
        else:
            start = len(decompressed) - distance
            decompressed.extend(decompressed[start:start + length])

    return bytes(decompressed)


def lz(input_file_name: str,
       output_file_name: str,
       decompress: bool = False) -> None:
    with open(input_file_name, "rb") as file:
        input_data = file.read(1024**3)

    if decompress:
        output = lz_decompress_bytes(input_data)
    else:
        output = lz_compress_bytes(input_data)

    with open(output_file_name, "wb") as file:
        file.write(output)


if __name__ == "__main__":
    description = "Compresses/decompresses a file using the " \
                  "Lempel-Ziv compression algorithm."
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

    lz(args.input_file_name, args.output_file_name, args.decompress)
