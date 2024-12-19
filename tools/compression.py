#! /usr/bin/env python3
import sys
from pathlib import Path

def decompress(encoded):
    decoded = bytearray()
    ptr = 4
    done = False
    while not done:
        control = encoded[ptr]
        ptr += 1
        bits = '{:08b}'.format(control)
        for b in bits:
            if b == '0':
                # copy character
                decoded += encoded[ptr:ptr+1]
                ptr += 1
            else:
                b0 = encoded[ptr]
                b1 = encoded[ptr+1]
                ptr += 2
                distance = ((b0 & 0xF0) << 4) + b1
                if distance == 0:
                    done = True
                    break
                length = (b0 & 0xF) + 1
                if length == 1:
                    length += 16 + encoded[ptr]
                    ptr += 1
                for _ in range(length):
                    if distance != 1:
                        decoded += decoded[-distance:-distance+1]
                    else:
                        decoded += decoded[-distance:]
    return decoded

if __name__ == "__main__":
    action = sys.argv[1]
    src_file = sys.argv[2]
    dst_file = sys.argv[3]

    if action == "d":
        src_content = Path(src_file).read_bytes()

        sections = [
            (0x0000000, 0x0001350, False),
            (0x0001350, 0x00116C0, True),
            (0x00116C0, 0x1000000, False),
        ]
        
        dst_content = bytearray()
        for section in sections:
            if section[2]:
                dst_content += decompress(src_content[section[0]:section[1]])
            else:
                dst_content += src_content[section[0]:section[1]]
        Path(dst_file).parent.resolve().mkdir(parents=True, exist_ok=True)
        Path(dst_file).write_bytes(dst_content)
    elif action == "e":
        pass
