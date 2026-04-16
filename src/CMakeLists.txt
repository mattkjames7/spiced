cmake_minimum_required(VERSION 3.20)

# List of source files
set(SPICED_SOURCES
    annmodel.cc
    annmavhmodel.cc
    annmavpsmodel.cc
    annmavptmodel.cc
    annprobmodel.cc
    annpsmodel.cc
    annptmodel.cc
    avmodel.cc
    avpsmodel.cc
    avptmodel.cc
    avprobmodel.cc
    avmavhmodel.cc
    avmavpsmodel.cc
    avmavptmodel.cc
    mavtrans.cc
    polynomial.cc
    rescale.cc
    reversearray.cc
    libspiced.cc
)

# List of binary files to embed
set(BINARY_FILES
    mavh
    mavcps
    mavcpt
    mavhann
    mavcpsann
    mavcptann
    mavlambda
    ps
    pt
    prob
    psann
    ptann
    probann
)

# Create directory for generated object files
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/binary_objects")

# Function to embed binary files
function(add_binary_dependencies)
    if(APPLE)
        # macOS: use xxd to convert binary to C++ source
        foreach(bin_name ${BINARY_FILES})
            set(bin_file "${CMAKE_CURRENT_SOURCE_DIR}/${bin_name}.bin")
            set(cc_file "${CMAKE_CURRENT_BINARY_DIR}/${bin_name}_binary.cc")
            
            add_custom_command(
                OUTPUT "${cc_file}"
                COMMAND xxd -i ${bin_name}.bin > ${cc_file}
                COMMAND sed -i .bak 's/${bin_name}_bin/_binary_${bin_name}_bin_start/g' ${cc_file}
                COMMAND sed -i .bak 's/_binary_${bin_name}_bin_start_len/_binary_${bin_name}_bin_size/g' ${cc_file}
                COMMAND rm -f ${cc_file}.bak
                DEPENDS ${bin_file}
                COMMENT "Embedding binary file ${bin_name}.bin (macOS)"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            )
            
            list(APPEND SPICED_BINARY_SOURCES "${cc_file}")
        endforeach()
    else()
        # Linux/other: use ld to create object files
        foreach(bin_name ${BINARY_FILES})
            set(bin_file "${CMAKE_CURRENT_SOURCE_DIR}/${bin_name}.bin")
            set(obj_file "${CMAKE_CURRENT_BINARY_DIR}/binary_objects/${bin_name}.o")
            
            add_custom_command(
                OUTPUT "${obj_file}"
                COMMAND ld -r -b binary -o ${obj_file} ${bin_name}.bin
                DEPENDS ${bin_file}
                COMMENT "Embedding binary file ${bin_name}.bin (Linux)"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            )
            
            list(APPEND SPICED_BINARY_OBJECTS "${obj_file}")
        endforeach()
    endif()
    
    set(SPICED_BINARY_SOURCES ${SPICED_BINARY_SOURCES} PARENT_SCOPE)
    set(SPICED_BINARY_OBJECTS ${SPICED_BINARY_OBJECTS} PARENT_SCOPE)
endfunction()

add_binary_dependencies()

# Create a reusable target for embedded model data so executables can
# reference the raw _binary_* symbols directly.
if(APPLE)
    add_library(spiced_embedded_data STATIC ${SPICED_BINARY_SOURCES})
else()
    add_library(spiced_embedded_data STATIC ${SPICED_BINARY_OBJECTS})
endif()

set_target_properties(spiced_embedded_data PROPERTIES
    LINKER_LANGUAGE CXX
)

# Create the main library
add_library(spiced SHARED ${SPICED_SOURCES})

# Set include directories
target_include_directories(spiced PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_BINARY_DIR}/_deps/libann-src/include"
)

target_include_directories(spiced PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

# Link libann
target_link_libraries(spiced PUBLIC ann)
target_link_libraries(spiced PRIVATE spiced_embedded_data)

# Compiler flags
target_compile_options(spiced PRIVATE 
    -fPIC 
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
)

# Installation
install(TARGETS spiced
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(FILES "../include/spiced.h" DESTINATION include)
