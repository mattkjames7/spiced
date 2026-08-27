# List of source files
set(SPICED_SOURCES
    annmodel.cc
    avmodel.cc
    mavtrans.cc
    polynomial.cc
    rescale.cc
    reversearray.cc
    libspiced.cc
)

# Create the main library
add_library(spiced SHARED ${SPICED_SOURCES})
add_library(spiced::spiced ALIAS spiced)

if(WIN32)
    set_target_properties(spiced PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Set include directories
target_include_directories(spiced PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/_deps/libann-src/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(spiced PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# spiced.h exposes libann types, so consumers need libann's usage requirements
# (including the OpenMP headers and compiler flags).
target_link_libraries(spiced PUBLIC ann)

# Compiler warnings. Optimization is selected by the Release configuration.
if(MSVC)
    target_compile_options(spiced PRIVATE /W4)
else()
    target_compile_options(spiced PRIVATE -Wextra)
endif()

# Add OpenMP support
find_package(OpenMP REQUIRED)
target_link_libraries(spiced PRIVATE OpenMP::OpenMP_CXX)

# Unix exposes the C math functions through libm; MSVC provides them directly
# through its runtime library.
if(UNIX)
    target_link_libraries(spiced PRIVATE m)
endif()

# Set library properties
set_target_properties(spiced PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    EXPORT_NAME spiced
)

if(APPLE)
    set_target_properties(spiced PROPERTIES INSTALL_RPATH "@loader_path")
elseif(UNIX)
    set_target_properties(spiced PROPERTIES INSTALL_RPATH "$ORIGIN")
endif()

# Installation
install(TARGETS spiced
    EXPORT spicedTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES "${CMAKE_SOURCE_DIR}/include/spiced.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
