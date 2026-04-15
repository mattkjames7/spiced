# Makefile for spiced unit tests using Google Test

# Include flags
IFLAGS=-I../include -I../lib/libann/include -I../external/googletest/googletest/include

# Compiler detection and configuration
OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LDFLAGS=-Wl,-rpath='$$ORIGIN/../lib' -L ../lib -lspiced -L../lib/libann/lib -lann -L../external/googletest/build/lib -lgtest -lgtest_main -pthread
	CFLAGS=-lm -std=c++17 -Wextra -O3 -fopenmp
	CCo=g++ -fPIC -c $(CFLAGS) $(IFLAGS)
	CC=g++ -fPIC $(CFLAGS) $(IFLAGS)
else
	LDFLAGS=-L../lib -lspiced -L/usr/local/opt/libomp/lib -lomp -L../external/googletest/build/lib -lgtest -lgtest_main -pthread
	CFLAGS=-lm -std=c++17 -Wextra -O3 "-I/usr/local/opt/libomp/include"
	CCo=g++ -Xpreprocessor -fopenmp -c $(CFLAGS) $(IFLAGS)
	CC=g++ -Xpreprocessor -fopenmp $(CFLAGS) $(IFLAGS)
endif

# Test source files (excluding old test files and matdot)
TEST_SOURCES = test_probmodels.cc \
               test_psmodels.cc \
               test_ptmodels.cc \
               test_mavhmodels.cc \
               test_mavpsmodels.cc \
               test_mavptmodels.cc \
               test_mavtrans.cc \
               test_netfunc.cc \
               test_utils.cc \
               test_c_api.cc \
               test_runner.cc

TEST_OBJECTS = $(TEST_SOURCES:.cc=.o)

# Main test executable
TEST_EXEC = run_tests

.PHONY: all test clean

all: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $(TEST_EXEC) $(LDFLAGS)

%.o: %.cc
	$(CCo) $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	-rm -v *.o
	-rm -v $(TEST_EXEC)
	-rm -v test

help:
	@echo "Spiced Unit Tests - Build Targets:"
	@echo "  make          - Build test executable"
	@echo "  make test     - Build and run all tests"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make help     - Show this message"
	@echo ""
	@echo "Requirements: Google Test (gtest) library must be installed"
