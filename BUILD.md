# Building SPICED with CMake

This project has been converted from Make to CMake for better build management and cross-platform support.

## Prerequisites

- CMake 3.20 or later
- C++17 compatible compiler (g++, clang, MSVC)
- OpenMP development libraries (usually included with compilers)
- Git (for FetchContent to work)

### Optional
- Google Test (will be fetched automatically)
- libann v0.1.0 or later (will be fetched automatically via FetchContent)

## Quick Start

### Configure the build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

### Build

```bash
cmake --build build
```

### Run tests

```bash
cmake --build build --target test
# or
cd build && ctest
```

### Install

```bash
cmake --install build
# or
sudo cmake --install build  # if using system default /usr/local prefix
```

## Build Options

### Custom installation prefix

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=/path/to/install
```

### Debug build with symbols

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

### Release build with optimizations

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

## Project Structure

- `CMakeLists.txt` - Root CMake configuration
- `src/CMakeLists.txt` - Main library build configuration
- `test/CMakeLists.txt` - Test suite configuration
- `include/spiced.h` - Public header file

## Dependencies

The build automatically fetches:

1. **libann v0.1.0** - Neural network library (via FetchContent)
2. **Google Test** - Unit testing framework (via FetchContent) - only used for tests

## Binary Data Files

SPICED embeds several binary data files (`.bin` files) containing pre-trained model parameters:
- macOS: Uses `xxd` to convert binaries to C++ source files
- Linux: Uses `ld -r -b binary` to create linkable object files

These binaries are automatically handled by the CMake build system.

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

## Previous Build System

The repository previously used Make-based build system. The migration to CMake provides:
- Better cross-platform support
- Automated dependency management (FetchContent)
- Integrated test discovery and reporting
- Improved IDE integration
