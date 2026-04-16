import numpy as np
import os


def read_array(f: open) -> np.ndarray:

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


def save_model_params(params: dict, fname: str):
    """
    Save model parameters to a C++ header file.

    The floats need to be formatted in hexadecimal float literals
    """

    buffer = """
#include <vector>
#include <cstdint>

typedef struct {
  int8_t dc_degree;                            /* DC polynomial degrees */
  int8_t m_degree;                             /* Real/imaginary polynomial degrees */
  std::vector<float32_t> dc;
  std::vector<std::vector<float32_t>> real;
  std::vector<std::vector<float32_t>> imag;
} ModelParams;


"""

    buffer += f"const ModelParams {params['name']} = {{\n"
    buffer += "  {" + ", ".join(float(x).hex() for x in params['dc'][::-1].flatten()) + "},\n"
    buffer += "  {\n"
    for row in params['real']:
        buffer += "    {" + ", ".join(float(x).hex() for x in row[::-1]) + "},\n"
    buffer += "  },\n"
    buffer += "  {\n"
    for row in params['imag']:
        buffer += "    {" + ", ".join(float(x).hex() for x in row) + "},\n"
    buffer += "  }\n"
    buffer += "};\n"

    with open(fname, 'w') as f:
        f.write(buffer)