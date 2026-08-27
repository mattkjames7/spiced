# Building SPICED with CMake

This project uses a CMake-only build. The old Make and batch-script workflow has been retired.

## Prerequisites

- CMake 3.20 or later
- C++17 compatible compiler (g++, clang, MSVC)
- OpenMP development libraries (usually included with compilers)
- Git (for FetchContent to work)

### Optional
- Google Test (fetched automatically when tests are enabled)
- libann v0.1.0 or later (fetched automatically via FetchContent)

## Quick Start

### Configure the build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

### Build

```bash
cmake --build build
```

### Run tests

```bash
ctest --test-dir build --output-on-failure
```

### Install

```bash
cmake --install build
```

## Build Options

### Custom installation prefix

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/path/to/install
```

### Debug build with symbols

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

### Release build with optimizations

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

## Project Structure

- `CMakeLists.txt` - Root CMake configuration
- `src/CMakeLists.txt` - Main library build configuration
- `test/CMakeLists.txt` - Test suite configuration
- `examples/package-consumer/` - Example external project using `find_package(spiced)`
- `cmake/spicedConfig.cmake.in` - Installed package configuration template
- `include/spiced.h` - Public header file

## Dependencies

The build automatically fetches:

1. **libann v0.1.0** - Neural network library (via FetchContent)
2. **Google Test** - Unit testing framework (via FetchContent, only when `BUILD_TESTING=ON`)

## Binary Data Files

Legacy model binaries and their conversion scripts are retained in `legacy/`.
The model parameters used at runtime have been converted to C++ headers, except
for `mavlambda.bin`, which is still embedded by the build:
- macOS: Uses `xxd` to convert binaries to C++ source files
- Linux: Uses `ld -r -b binary` to create linkable object files

This remaining binary is automatically handled by the CMake build system.

## Platform-Specific Notes

### Linux
- Uses standard g++ compiler
- OpenMP support via `-fopenmp` flag
- Binary embedding via `ld` utility

### macOS
- Uses system clang/g++
- OpenMP support requires Homebrew clang: `brew install libomp`
- Binary embedding via `xxd` utility

### Windows
- Uses MinGW or MSVC compiler
- Note: Binary embedding for Windows needs additional configuration

## Troubleshooting

### CMake not found
```bash
# Install CMake
sudo apt-get install cmake  # Ubuntu/Debian
brew install cmake          # macOS
```

### OpenMP not found (macOS)
```bash
# Install libomp via Homebrew
brew install libomp
```

### FetchContent fails
- Ensure you have an active internet connection
- Check that git is installed and available in PATH
- Verify GitHub is accessible from your network

### Disable tests during packaging builds

```bash
cmake -S . -B build -DBUILD_TESTING=OFF
```

## Package Consumption

After installation, consumers can use the exported CMake package:

```cmake
find_package(spiced CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE spiced::spiced)
```

The installed package currently exports both `spiced` and its fetched `ann` dependency in the same export set so consumers get a self-consistent target graph.

## Consumer Example

A standalone consumer example lives in `examples/package-consumer/` and can be validated against an installed prefix:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
rm -rf /tmp/spiced-install
cmake --install build --prefix /tmp/spiced-install

cmake -S examples/package-consumer -B examples/package-consumer/build \
	-DCMAKE_PREFIX_PATH=/tmp/spiced-install
cmake --build examples/package-consumer/build
./examples/package-consumer/build/spiced_package_example
```
