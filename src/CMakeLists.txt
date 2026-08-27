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

# Set include directories
target_include_directories(spiced PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/_deps/libann-src/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(spiced PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link libann
target_link_libraries(spiced PRIVATE
    $<BUILD_INTERFACE:ann>
)

# Compiler flags
target_compile_options(spiced PRIVATE 
    -Wextra
    -O3
)

# Add OpenMP support
find_package(OpenMP REQUIRED)
target_link_libraries(spiced PRIVATE OpenMP::OpenMP_CXX)

# Link math library
target_link_libraries(spiced PRIVATE m)

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
