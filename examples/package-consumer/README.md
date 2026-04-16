# SPICED Package Consumer Example

This directory contains a minimal standalone CMake project that consumes an installed SPICED package with `find_package(spiced CONFIG REQUIRED)`.

Example workflow:

```bash
cmake -S /path/to/spiced -B /path/to/spiced/build -DCMAKE_BUILD_TYPE=Release
cmake --build /path/to/spiced/build
cmake --install /path/to/spiced/build --prefix /tmp/spiced-install

cmake -S . -B build -DCMAKE_PREFIX_PATH=/tmp/spiced-install
cmake --build build
./build/spiced_package_example
```