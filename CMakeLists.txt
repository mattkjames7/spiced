cmake_minimum_required(VERSION 3.20)
project(spiced 
        VERSION 0.1.0
        DESCRIPTION "C++ SPICED model code"
        LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default install path
if(NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX /usr/local)
endif()

# Find or fetch libann v0.1.0
include(FetchContent)

FetchContent_Declare(
    libann
    GIT_REPOSITORY https://github.com/mattkjames7/libann
    GIT_TAG v0.1.0
)

FetchContent_MakeAvailable(libann)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)
