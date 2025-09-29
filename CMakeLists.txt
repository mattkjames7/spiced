cmake_minimum_required(VERSION 3.10)

project(spiced)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# check if we can use gcc or clang or mingw
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_COMPILER "g++")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_COMPILER "clang++")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MinGW")
    set(CMAKE_CXX_COMPILER "g++")
else()
    message(FATAL_ERROR "This project requires GCC or Clang or MinGW")
endif()
message(STATUS "Using compiler: ${CMAKE_CXX_COMPILER}")

# set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fPIC")

# add source directory
add_subdirectory(src)

# add tests directory
set(ENABLE_TESTS OFF CACHE BOOL "Enable tests")
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# install target
set(PREFIX ${CMAKE_INSTALL_PREFIX})

install(TARGETS spiced DESTINATION ${PREFIX}/lib)
install(DIRECTORY include/ DESTINATION ${PREFIX}/include)
