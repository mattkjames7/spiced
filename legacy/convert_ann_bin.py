#!/usr/bin/env python3
"""Convert the embedded ANN model binaries to C++ parameter objects."""

import os
import struct
from typing import BinaryIO


CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
SRC_DIR = os.path.join(CURRENT_DIR, "..", "src")
OUTPUT_PATH = os.path.join(SRC_DIR, "ann_model_params.h")

MODEL_FILES = {
    "mavhann.bin": "Average hot ion mass",
    "mavcpsann.bin": "Average cold ion mass (plasmasphere)",
    "mavcptann.bin": "Average cold ion mass (plasmatrough)",
    "probann.bin": "Probability of being in the plasmasphere",
    "psann.bin": "Electron density (plasmasphere)",
    "ptann.bin": "Electron density (plasmatrough)",
}


def read_exact(f: BinaryIO, size: int) -> bytes:
    data = f.read(size)
    if len(data) != size:
        raise ValueError(f"Unexpected end of file in {f.name}")
    return data


def read_int(f: BinaryIO) -> int:
    return struct.unpack("<i", read_exact(f, 4))[0]


def read_array(f: BinaryIO, value_format: str) -> list[int] | list[float]:
    length = read_int(f)
    dimensions = read_int(f)
    shape = [read_int(f) for _ in range(dimensions)]

    if dimensions != 1 or shape != [length]:
        raise ValueError(
            f"Expected a one-dimensional array of length {length} in {f.name}, "
            f"got shape {shape}"
        )

    item_size = struct.calcsize(value_format)
    return list(struct.unpack(f"<{length}{value_format}", read_exact(f, length * item_size)))


def read_matrix_array(f: BinaryIO) -> list[list[list[float]]]:
    matrices = []
    count = read_int(f)
    for _ in range(count):
        length = read_int(f)
        dimensions = read_int(f)
        shape = [read_int(f) for _ in range(dimensions)]
        if dimensions == 1:
            rows, columns = 1, shape[0]
        elif dimensions == 2:
            rows, columns = shape
        else:
            raise ValueError(f"Expected a one- or two-dimensional matrix in {f.name}")
        if rows * columns != length:
            raise ValueError(f"Matrix length and shape disagree in {f.name}")

        values = struct.unpack(f"<{length}f", read_exact(f, length * 4))
        matrices.append(
            [list(values[row * columns:(row + 1) * columns]) for row in range(rows)]
        )
    return matrices


def read_ann_params(path: str) -> dict:
    with open(path, "rb") as f:
        params = {
            "layers": read_array(f, "i"),
            "scale0": read_array(f, "f"),
            "scale1": read_array(f, "f"),
            "weights": read_matrix_array(f),
            "biases": read_matrix_array(f),
            "training_cost": read_array(f, "f"),
            "validation_cost": read_array(f, "f"),
        }
        if f.read(1):
            raise ValueError(f"Unexpected trailing data in {path}")
    return params


def cpp_float(value: float) -> str:
    return float(value).hex() + "f"


def format_vector(values: list, formatter=str) -> str:
    return "{" + ", ".join(formatter(value) for value in values) + "}"


def format_matrices(matrices: list[list[list[float]]]) -> str:
    lines = ["{"]
    for matrix in matrices:
        lines.append("    {")
        for row in matrix:
            lines.append(f"      {format_vector(row, cpp_float)},")
        lines.append("    },")
    lines.append("  }")
    return "\n".join(lines)


def convert_ann_params(path: str, description: str) -> str:
    params = read_ann_params(path)
    name = os.path.splitext(os.path.basename(path))[0]
    fields = [
        format_vector(params["layers"]),
        format_vector(params["scale0"], cpp_float),
        format_vector(params["scale1"], cpp_float),
        format_matrices(params["weights"]),
        format_matrices(params["biases"]),
        format_vector(params["training_cost"], cpp_float),
        format_vector(params["validation_cost"], cpp_float),
    ]
    body = ",\n  ".join(fields)
    return f"/* {description} */\ninline const ANNModelParams {name} = {{\n  {body}\n}};\n\n"


def save_header() -> None:
    header = """#pragma once

#include <cstdint>
#include <vector>

struct ANNModelParams {
  std::vector<int32_t> layers;
  std::vector<float> scale0;
  std::vector<float> scale1;
  std::vector<std::vector<std::vector<float>>> weights;
  std::vector<std::vector<std::vector<float>>> biases;
  std::vector<float> training_cost;
  std::vector<float> validation_cost;
};

"""
    for filename, description in MODEL_FILES.items():
        header += convert_ann_params(os.path.join(CURRENT_DIR, filename), description)

    with open(OUTPUT_PATH, "w", encoding="utf-8") as f:
        f.write(header)
    print(f"Saved ANN model parameters to {OUTPUT_PATH}")


if __name__ == "__main__":
    save_header()
