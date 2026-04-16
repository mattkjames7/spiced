# SPICED

C++ implementation of SPICED model code

## Building

This project uses CMake for building. For detailed build instructions, see [BUILD.md](BUILD.md).

Quick start:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build
```

## Project Structure

- `src/` - Main library source code
- `lib/libann/` - Neural network library dependency (automatically fetched via CMake)
- `include/` - Public header files
- `test/` - Unit tests using Google Test

## Dependencies

- **libann v0.1.0** - Neural network library (automatically fetched)
- **Google Test** - Unit testing framework (used for testing only)
