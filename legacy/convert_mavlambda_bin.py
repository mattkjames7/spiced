#!/usr/bin/env python3
"""Convert mavlambda.bin to C++ polynomial coefficient objects."""

import os
import struct
from typing import BinaryIO


CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
SOURCE_PATH = os.path.join(CURRENT_DIR, "mavlambda.bin")
OUTPUT_PATH = os.path.join(CURRENT_DIR, "..", "src", "mavlambda_params.h")


def read_exact(f: BinaryIO, size: int) -> bytes:
    data = f.read(size)
    if len(data) != size:
        raise ValueError(f"Unexpected end of file in {f.name}")
    return data


def read_int(f: BinaryIO) -> int:
    return struct.unpack("<i", read_exact(f, 4))[0]


def read_double_array(f: BinaryIO) -> list[float]:
    length = read_int(f)
    dimensions = read_int(f)
    shape = [read_int(f) for _ in range(dimensions)]
    if dimensions != 1 or shape != [length]:
        raise ValueError(
            f"Expected a one-dimensional array of length {length}, got {shape}"
        )
    return list(struct.unpack(f"<{length}d", read_exact(f, length * 8)))


def format_values(values: list[float]) -> str:
    return "{" + ", ".join(value.hex() for value in values) + "}"


def main() -> None:
    with open(SOURCE_PATH, "rb") as f:
        ps = read_double_array(f)
        pt = read_double_array(f)
        if f.read(1):
            raise ValueError(f"Unexpected trailing data in {SOURCE_PATH}")

    # polynomial() expects coefficients from constant term upwards. The
    # legacy runtime reversed the serialized arrays after loading them.
    header = f"""#pragma once

#include <vector>

struct MavLambdaParams {{
  std::vector<double> ps;
  std::vector<double> pt;
}};

inline const MavLambdaParams mavlambda = {{
  {format_values(list(reversed(ps)))},
  {format_values(list(reversed(pt)))}
}};
"""
    with open(OUTPUT_PATH, "w", encoding="utf-8") as f:
        f.write(header)
    print(f"Saved Mav lambda parameters to {OUTPUT_PATH}")


if __name__ == "__main__":
    main()
