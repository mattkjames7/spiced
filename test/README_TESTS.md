# Spiced Unit Tests

This directory contains unit tests for the spiced module using Google Test (gtest).

## Overview

The test suite uses Google Test with automated assertions. Each test file focuses on specific components of the spiced library.

## Test Files

### Active Test Files (gtest-based)
- **test_probmodels.cc** - Tests for probability models (AvProbModel, ANNProbModel)
- **test_psmodels.cc** - Tests for PS models (AvPSModel, ANNPSModel)
- **test_ptmodels.cc** - Tests for PT models (AvPTModel, ANNPTModel)
- **test_mavhmodels.cc** - Tests for Mav H models (AvMavHModel, ANNMavHModel)
- **test_mavpsmodels.cc** - Tests for Mav PS models (AvMavPSModel, ANNMavPSModel)
- **test_mavptmodels.cc** - Tests for Mav PT models (AvMavPTModel, ANNMavPTModel)
- **test_mavtrans.cc** - Tests for MavTrans transformations (forward and reverse)
- **test_netfunc.cc** - Tests for NetworkFunc ANN predictions
- **test_runner.cc** - Main test runner entry point

## Building and Running Tests

### Prerequisites
- C++17 compatible compiler
- CMake 3.20 or later
- Git access so CMake can fetch dependencies

### Build and Run Tests
```bash
cmake -S .. -B ../build -DCMAKE_BUILD_TYPE=Release
cmake --build ../build
ctest --test-dir ../build --output-on-failure
```

## Test Structure

Each test file follows the gtest pattern:
- Uses test fixtures (classes inheriting from `::testing::Test`) to set up common test data
- Includes `SetUp()` methods to initialize test data before each test
- Uses `EXPECT_NEAR()` for floating-point comparisons with appropriate tolerances
- Uses `EXPECT_TRUE()` for NaN validation
- Provides detailed error messages showing input values when tests fail

## Test Coverage

The tests verify:
1. **Model accuracy** - Output values match expected results within tolerance
2. **NaN handling** - Invalid inputs produce expected NaN results
3. **Transform correctness** - Forward and reverse transformations are consistent
4. **ANN predictions** - Neural network model components match expected values

## Detecting Regressions

The gtest framework will:
- Automatically run all tests and report failures
- Show exactly which values don't match expected results
- Provide input values that caused failures for debugging
- Return non-zero exit code if any tests fail (useful for CI/CD)

Example output on failure:
```
test_probmodels.cc:45: Failure
Expected equality of these values:
  out[i]
    Which is: 0.94
  expav[i]
    Which is: 0.93885595
Mismatch at index 2: M=12, R=3
```

## Future Enhancements

Potential improvements:
- Add parametrized tests for testing multiple input combinations
- Add edge case tests (extreme values, boundary conditions)
- Add performance benchmarks
- Add tests for error handling and invalid inputs
- Increase coverage for untested code paths
