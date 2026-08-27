import numpy as np
import os

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
SRC_DIR = os.path.join(CURRENT_DIR, '..', 'src')

model_files = {
    "mav.bin": "Average ion mass",
    "mavcpt.bin": "Average cold ion mass (plasmatrough)",
    "mavcps.bin": "Average cold ion mass (plasmasphere)",
    "mavh.bin": "Average hot ion mass",
    "prob.bin": "Probability of being in the plasmasphere",
    "ps.bin": "Electron density (plasmasphere)",
    "pt.bin": "Electron density (plasmatrough)"
}



def read_array(f: open) -> np.ndarray:

    print(f"Reading array from {f.name}...")

    # length of the array
    l = int.from_bytes(f.read(4), byteorder='little')

    # number of dimensions
    n = int.from_bytes(f.read(4), byteorder='little')

    # shape of the array
    shape = tuple(int.from_bytes(f.read(4), byteorder='little') for _ in range(n))

    # read in array
    arr = np.fromfile(f, dtype=np.float32, count=l)

    return arr.reshape(shape)


def read_model_params(fname: str) -> dict:
    with open(fname, 'rb') as f:
        params = {}
        params["name"] = os.path.splitext(os.path.basename(fname))[0]
        params["dc"] = read_array(f)
        params["real"] = read_array(f)
        params["imag"] = read_array(f)
    return params


def convert_static_model_params(fname: str, model_description: str):
    """

    The floats need to be formatted in hexadecimal float literals
    """
    params = read_model_params(fname)

    dc = params["dc"]
    real = params["real"]
    imag = params["imag"]

    if real.ndim != 2 or imag.ndim != 2:
        raise ValueError("Expected 2D arrays for real and imag model terms")

    dc_degree = int(dc.size) - 1
    m_degree = int(real.shape[1]) - 1


    buffer = f"/* {model_description} */\n"
    buffer += f"inline const ModelParams {params['name']} = {{\n"
    buffer += f"  {dc_degree},\n"
    buffer += f"  {m_degree},\n"
    buffer += "  {" + ", ".join(float(x).hex() for x in dc[::-1].flatten()) + "},\n"
    buffer += "  {\n"
    for row in real:
        buffer += "    {" + ", ".join(float(x).hex() for x in row[::-1]) + "},\n"
    buffer += "  },\n"
    buffer += "  {\n"
    for row in imag:
        buffer += "    {" + ", ".join(float(x).hex() for x in row[::-1]) + "},\n"
    buffer += "  }\n"
    buffer += "};\n\n"

    return buffer



def save_static_model_header():

    buffer = """
#pragma once

#include <cstdint>
#include <vector>

struct ModelParams {
  int8_t dc_degree;                            /* DC polynomial degree */
  int8_t m_degree;                             /* Real/imaginary polynomial degree */
  std::vector<float> dc;
  std::vector<std::vector<float>> real;
  std::vector<std::vector<float>> imag;
};

"""
    for file, description in model_files.items():
        fname = os.path.join(CURRENT_DIR, file)
        buffer += convert_static_model_params(fname, description)

    header_path = os.path.join(SRC_DIR, "model_params.h")
    with open(header_path, 'w') as f:
        f.write(buffer)
    print(f"Saved model parameters to {header_path}")


def main():

    save_static_model_header()


if __name__ == "__main__":
    main()
