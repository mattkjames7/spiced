cmake_minimum_required(VERSION 3.20)

project(spiced
        VERSION 0.1.0
        DESCRIPTION "C++ SPICED model code"
        LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(FetchContent)
include(GNUInstallDirs)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(
    libann
    GIT_REPOSITORY https://github.com/mattkjames7/libann
    GIT_TAG v0.1.0
)

FetchContent_MakeAvailable(libann)

if(APPLE)
    set(_spiced_install_rpath "@loader_path")
elseif(UNIX)
    set(_spiced_install_rpath "$ORIGIN")
endif()

if(DEFINED _spiced_install_rpath)
    set_target_properties(ann PROPERTIES
        INSTALL_RPATH "${_spiced_install_rpath}"
    )
endif()

install(TARGETS ann
    EXPORT spicedTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

set(SPICED_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/spiced")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/spicedConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/spicedConfig.cmake"
    INSTALL_DESTINATION "${SPICED_CMAKE_INSTALL_DIR}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/spicedConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT spicedTargets
    FILE spicedTargets.cmake
    NAMESPACE spiced::
    DESTINATION "${SPICED_CMAKE_INSTALL_DIR}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/spicedConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/spicedConfigVersion.cmake"
    DESTINATION "${SPICED_CMAKE_INSTALL_DIR}"
)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/licenses/spiced"
)
