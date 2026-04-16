import numpy as np


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