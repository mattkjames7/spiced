# Test directory CMakeLists.txt

# Find libann dependency for tests - same logic as main library
if(APPLE)
    set(ANN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/lib/libann.dylib)
elseif(WIN32)
    set(ANN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/lib/libann.dll)
else()
    set(ANN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/lib/libann.so)
endif()

# Add test source files
set(TEST_SOURCES
    matdot.cc
    mavhmodels.cc
    mavpsmodels.cc
    mavptmodels.cc
    netfunc.cc
    probmodels.cc
    psmodels.cc
    ptmodels.cc
    test.cc
    testmavtrans.cc
)

# Create test executable
add_executable(spiced_test ${TEST_SOURCES})

# Link against the main spiced library and libann
target_link_libraries(spiced_test PRIVATE spiced ${ANN_LIBRARY})

# Add include directories
target_include_directories(spiced_test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/include
)

# Set compiler flags to match the main library
target_compile_options(spiced_test PRIVATE -fopenmp)
target_link_options(spiced_test PRIVATE -fopenmp)

# Platform-specific settings
if(APPLE)
    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(spiced_test PRIVATE OpenMP::OpenMP_CXX)
    endif()
elseif(UNIX)
    target_link_libraries(spiced_test PRIVATE m)  # math library
endif()

# Add the test to CTest
add_test(NAME spiced_unit_tests COMMAND spiced_test)