# SPICED

C++ implementation of SPICED model code

## Building

This repository now uses CMake exclusively. For detailed build and install instructions, see [BUILD.md](BUILD.md).

Quick start:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
cmake --install build
```

## Project Structure

- `src/` - Main library source code and embedded model assets
- `include/` - Public headers
- `test/` - Unit tests using Google Test
- `cmake/` - CMake package configuration templates

## Dependencies

- **libann v0.1.0** - Neural network library (automatically fetched)
- **Google Test** - Unit testing framework (fetched automatically when tests are enabled)

## Installation and Packaging

The install step exports a CMake package for `find_package(spiced CONFIG)` consumers.

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/path/to/prefix
cmake --build build
cmake --install build
```
