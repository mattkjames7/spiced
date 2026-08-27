cmake_minimum_required(VERSION 3.20)

project(spiced_package_consumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(spiced CONFIG REQUIRED)

add_executable(spiced_package_example main.cc)
target_link_libraries(spiced_package_example PRIVATE spiced::spiced)