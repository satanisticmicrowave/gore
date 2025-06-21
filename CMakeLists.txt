###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-06-20 06:38:21
### Package: CMakeLists.txt 
###
### Gore is Opensource Reactive Engine
###
### ~ gore
###

cmake_minimum_required (VERSION 4.0)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message (STATUS "CMAKE_BUILD_TYPE not set, defaulting to Release")
    set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS 
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
    )
endif ()

if (CMAKE_GENERATOR MATCHES "Ninja" AND WIN32)
    set (CMAKE_MAKE_PROGRAM "ninja" CACHE INTERNAL "Ninja program")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_EXTENSIONS OFF)

set (CONAN_TOOLCHAIN_PATHS
    "${CMAKE_BINARY_DIR}/conan_toolchain.cmake"
    "${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake"
    "${CMAKE_BINARY_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake"
)

set (CONAN_FOUND FALSE)
foreach (path IN LISTS CONAN_TOOLCHAIN_PATHS)
    if (EXISTS "${path}")
        include ("${path}")
        set (CONAN_FOUND TRUE)
        message (STATUS "Using Conan toolchain: ${path}")
        break ()
    endif ()
endforeach ()

if (NOT CONAN_FOUND)
    message (WARNING "Conan toolchain not found. Run 'conan install' first.")
message ("${CMAKE_BINARY_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake")
endif ()

set (PROJECT_NAME gore)
set (PROJECT_VERSION "1.0.0")
set (PROJECT_DESCRIPTION "Gore is Opensource Reactive Engine")

project (${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION} LANGUAGES CXX)
message ("${PROJECT_NAME} v.${PROJECT_VERSION}")

file (GLOB_RECURSE GORE_MODULES RELATIVE ${PROJECT_SOURCE_DIR} "src/*/CMakeLists.txt")
set (GORE_MODULE_TARGETS)

foreach (GORE_MODULE IN LISTS GORE_MODULES)

    get_filename_component (MODULE_DIR ${GORE_MODULE} DIRECTORY)

    add_subdirectory (${MODULE_DIR})
    message (STATUS "Found GORE module: ${MODULE_DIR}")

    get_filename_component (MODULE_NAME ${MODULE_DIR} NAME)
    list (APPEND GORE_MODULE_TARGETS ${MODULE_NAME})
endforeach ()

message (STATUS "All GORE modules to install: ${GORE_MODULE_TARGETS}")

include (GNUInstallDirs)

set (GORE_INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/gore")
set (GORE_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/gore")

if (WIN32)
    set (GORE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/gore")
    set (GORE_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}/gore")
else ()
    set (GORE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/gore")
    set (GORE_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}/gore")
endif ()

add_library (Gore INTERFACE)
add_library (Gore::Gore ALIAS Gore)

foreach (module IN LISTS GORE_MODULE_TARGETS)
    if (TARGET ${module})
        target_link_libraries (Gore INTERFACE ${module})
        message (STATUS "  Adding module ${module} to Gore::Gore")
    else ()
        message (WARNING "Module ${module} not found, skipping")
    endif ()
endforeach ()

target_include_directories (Gore INTERFACE
    $<INSTALL_INTERFACE:${GORE_INSTALL_INCLUDE_DIR}>
)

if (GORE_MODULE_TARGETS)
    install (TARGETS ${GORE_MODULE_TARGETS}
        EXPORT GoreTargets
        ARCHIVE DESTINATION ${GORE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${GORE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${GORE_INSTALL_BINDIR}
    )
endif ()

install (TARGETS Gore
    EXPORT GoreTargets
)

set (MODULE_DIRS)
foreach (GORE_MODULE IN LISTS GORE_MODULES)
    get_filename_component (MODULE_DIR ${GORE_MODULE} DIRECTORY)
    list (APPEND MODULE_DIRS ${MODULE_DIR})
endforeach ()

foreach (module_dir IN LISTS MODULE_DIRS)
    get_filename_component (module_name "${module_dir}" NAME)
    set (main_include_dir "${module_dir}/include/gore/${module_name}")

  if (IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${main_include_dir}")
        message (STATUS "Installing headers for ${module_name}: ${main_include_dir}")
        install (
          DIRECTORY "${main_include_dir}/"
          DESTINATION "${GORE_INSTALL_INCLUDE_DIR}/${module_name}"
          FILES_MATCHING 
            PATTERN "*.hpp"
            PATTERN "*.h"
        )
    else ()
        message (WARNING "Main include directory not found for module ${module_name}: ${main_include_dir}")
    endif ()

    endforeach ()

include (CMakePackageConfigHelpers)

file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cmake)

write_basic_package_version_file (
    ${CMAKE_CURRENT_BINARY_DIR}/GoreConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/GoreConfig.cmake.in

    ${CMAKE_CURRENT_BINARY_DIR}/GoreConfig.cmake

    INSTALL_DESTINATION ${GORE_INSTALL_CMAKE_DIR}

)

install (EXPORT GoreTargets
    FILE GoreTargets.cmake
    NAMESPACE Gore::
    DESTINATION ${GORE_INSTALL_CMAKE_DIR}
)

install (FILES
    ${CMAKE_CURRENT_BINARY_DIR}/GoreConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/GoreConfigVersion.cmake
    DESTINATION ${GORE_INSTALL_CMAKE_DIR}
)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)
foreach (target IN LISTS GORE_MODULE_TARGETS)
    if (TARGET ${target})
        set_target_properties (${target} PROPERTIES FOLDER "Modules")
    endif ()
endforeach ()

if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set (WINDEPLOYQT_SUFFIX "release")
    else ()
        set (WINDEPLOYQT_SUFFIX "debug")
    endif ()

    if (CMAKE_GENERATOR MATCHES "Visual Studio")
        set (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif ()
endif ()
