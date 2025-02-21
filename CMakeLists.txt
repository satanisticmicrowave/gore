### Copyright 2025-02-15 06:39:22 satanisticmicrowave. All rights reserved.
###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-02-15 06:39:22
### File: CMakeLists.txt
###
### Project [GORE] - self-sufficient game engine on c++
### Made with love :3

cmake_minimum_required (VERSION 3.9)

## Initialize project 
set (PROJECT_NAME "gore")
set (PROJECT_VERSION 1.0.0)
set (PROJECT_DESCRIPTION "GORE - self-sufficient game engine")
set (PROJECT_CXX_STANDARD 26)

project (${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION "${PROJECT_DESCRIPTION}")
message ("\n${PROJECT_DESCRIPTION} v${PROJECT_VERSION}\n")

## Define paths
set (PROJECT_ROOT ${PROJECT_SOURCE_DIR})
set (PROJECT_INCLUDE_DIR "${PROJECT_ROOT}/include")
set (PROJECT_LIBRARY_DIR "${PROJECT_ROOT}/gore")
set (PROJECT_LIBRARY_SOURCE_DIR "${PROJECT_ROOT}/lib")

## Define sources
file (GLOB_RECURSE PROJECT_SOURCES "${PROJECT_INCLUDE_DIR}/*.cpp")
file (GLOB_RECURSE PROJECT_LIBRARY "${PROJECT_LIBRARY_DIR}/*.cpp")
file (GLOB_RECURSE PROJECT_HEADERS "${PROJECT_INCLUDE_DIR}/*.hpp")

## Connect private headers to public headers
include_directories(${PROJECT_INCLUDE_DIR})

## Switch compiler to clang
set (CMAKE_C_COMPILER "/usr/bin/clang")
set (CMAKE_C_FLAGS "-Wall")
set (CMAKE_C_FLAGS_DEBUG "-g")
set (CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
set (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++${PROJECT_CXX_STANDARD}")
set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set (CMAKE_AR "/usr/bin/llvm-ar")
set (CMAKE_LINKER "/usr/bin/llvm-ld")
set (CMAKE_NM "/usr/bin/llvm-nm")
set (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
set (CMAKE_RANLIB "/usr/bin/llvm-ranlib")

## Connect libraries
find_package (OpenAL REQUIRED)
find_package (VulkanHeaders REQUIRED)
find_package (fmt REQUIRED)

## Create a library
add_library (${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${PROJECT_LIBRARY} ${PROJECT_HEADERS})

set_target_properties (${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

## Link libraries
target_link_libraries (${PROJECT_NAME} PRIVATE
OpenAL::OpenAL 
vulkan-headers::vulkan-headers 
fmt::fmt
)

## Move library to library path
include(GNUInstallDirs)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
  DIRECTORY ${PROJECT_LIBRARY_DIR}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING PATTERN "*.h"
)

## Create & configure PC file
configure_file ("${PROJECT_ROOT}/${PROJECT_NAME}.pc.in" "${PROJECT_NAME}.pc" @ONLY)

install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig")


