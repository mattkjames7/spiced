cmake_minimum_required(VERSION 3.20)

# Find or fetch Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# List of test files (excluding old_tests)
set(TEST_SOURCES
    test_probmodels.cc
    test_psmodels.cc
    test_ptmodels.cc
    test_mavhmodels.cc
    test_mavpsmodels.cc
    test_mavptmodels.cc
    test_mavtrans.cc
    test_netfunc.cc
    test_utils.cc
    test_c_api.cc
    test_runner.cc
)

# Create test executable
add_executable(run_tests ${TEST_SOURCES})

# Include directories
target_include_directories(run_tests PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

# Find OpenMP for test compilation
find_package(OpenMP REQUIRED)

# Link against spiced library, libann, and gtest
target_link_libraries(run_tests PRIVATE
    spiced_embedded_data
    spiced
    ann
    gtest
    gtest_main
    OpenMP::OpenMP_CXX
)

# Add the tests to CTest
add_test(NAME SpicedTests COMMAND run_tests)

# Optional: Set RPATH for finding shared libraries at runtime
if(APPLE)
    set_target_properties(run_tests PROPERTIES
        BUILD_RPATH "@loader_path/../lib"
        INSTALL_RPATH "@loader_path/../lib"
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(run_tests PROPERTIES
        BUILD_RPATH "$ORIGIN/../lib"
        INSTALL_RPATH "$ORIGIN/../lib"
    )
endif()

# Installation (optional)
install(TARGETS run_tests DESTINATION bin)
