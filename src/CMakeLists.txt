# First, we need to handle the binary data files
# These are model parameter files that need to be embedded as object files

# Function to convert binary files to object files
function(add_binary_object target_name binary_file)
    get_filename_component(obj_name ${binary_file} NAME_WE)
    set(obj_file ${CMAKE_CURRENT_BINARY_DIR}/${obj_name}.o)
    
    if(APPLE)
        # macOS uses a different approach - we'd need to implement macbins.sh equivalent
        # For now, let's assume we have the script
        add_custom_command(
            OUTPUT ${obj_file}
            COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/macbins.sh "gcc -c" ${CMAKE_CURRENT_BINARY_DIR} ${binary_file}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${binary_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Converting ${binary_file} to object file for macOS"
        )
    else()
        # Linux/Unix approach
        add_custom_command(
            OUTPUT ${obj_file}
            COMMAND ld -r -b binary -o ${obj_file} ${binary_file}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${binary_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Converting ${binary_file} to object file"
        )
    endif()
    
    add_custom_target(${target_name} DEPENDS ${obj_file})
    set_target_properties(${target_name} PROPERTIES BINARY_OBJECT_FILE ${obj_file})
endfunction()

# Create object files for all binary data
set(BINARY_FILES
    mavh.bin
    mavcps.bin
    mavcpt.bin
    ps.bin
    pt.bin
    prob.bin
    mavhann.bin
    mavcpsann.bin
    mavcptann.bin
    psann.bin
    ptann.bin
    probann.bin
    mavlambda.bin
)

set(BINARY_OBJECTS "")
foreach(bin_file ${BINARY_FILES})
    get_filename_component(target_name ${bin_file} NAME_WE)
    add_binary_object(${target_name}_obj ${bin_file})
    get_target_property(obj_file ${target_name}_obj BINARY_OBJECT_FILE)
    list(APPEND BINARY_OBJECTS ${obj_file})
endforeach()

# Find libann dependency - check for existing built libraries first
set(ANN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/include)

if(APPLE)
    set(ANN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/lib/libann.dylib)
elseif(WIN32)
    set(ANN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/lib/libann.dll)
else()
    set(ANN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann/lib/libann.so)
endif()

# Check if library exists, if not try to build it
if(NOT EXISTS ${ANN_LIBRARY})
    message(STATUS "libann library not found at ${ANN_LIBRARY}, attempting to build it")
    add_custom_target(build_libann
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libann
        COMMENT "Building libann dependency"
    )
    # After building, the library should exist
    set(LIBANN_NEEDS_BUILD TRUE)
else()
    message(STATUS "Found existing libann library: ${ANN_LIBRARY}")
    set(LIBANN_NEEDS_BUILD FALSE)
endif()

# Add source files (corrected list based on makefile)
set(SOURCES
    annmodel.cc
    annmavhmodel.cc
    annmavpsmodel.cc
    annmavptmodel.cc
    annprobmodel.cc
    annpsmodel.cc
    annptmodel.cc
    avmodel.cc
    avmavhmodel.cc
    avmavpsmodel.cc
    avmavptmodel.cc
    avprobmodel.cc
    avpsmodel.cc
    avptmodel.cc
    libspiced.cc
    mavtrans.cc
    polynomial.cc
    rescale.cc
    reversearray.cc
)

# Create the shared library
add_library(spiced SHARED ${SOURCES})

# Add include directories
target_include_directories(spiced PRIVATE 
    ${ANN_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Link the binary objects and dependencies
target_link_libraries(spiced PRIVATE ${ANN_LIBRARY})

# Add the binary objects to the library
foreach(obj_file ${BINARY_OBJECTS})
    target_sources(spiced PRIVATE ${obj_file})
endforeach()

# Set compiler flags
target_compile_options(spiced PRIVATE -fopenmp)
target_link_options(spiced PRIVATE -fopenmp)

# Platform-specific settings
if(APPLE)
    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(spiced PRIVATE OpenMP::OpenMP_CXX)
    endif()
    set_target_properties(spiced PROPERTIES SUFFIX ".dylib")
elseif(UNIX)
    target_link_libraries(spiced PRIVATE m)  # math library
endif()

# Ensure binary objects are built before the library
foreach(bin_file ${BINARY_FILES})
    get_filename_component(target_name ${bin_file} NAME_WE)
    add_dependencies(spiced ${target_name}_obj)
endforeach()

# If we had to build libann, make sure it's built first
if(LIBANN_NEEDS_BUILD AND TARGET build_libann)
    add_dependencies(spiced build_libann)
endif()