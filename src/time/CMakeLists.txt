###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-06-21 19:06:14
### Package: src/logger/CMakeLists.txt 
###
### Gore time module
###
### ~ gore
###

cmake_minimum_required (VERSION 4.0)

set (MODULE_NAME time)
set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library (${MODULE_NAME} SHARED)

file (GLOB_RECURSE PUBLIC_HEADERS LIST_DIRECTORIES FALSE "${MODULE_DIR}/include/*.hpp")
file (GLOB_RECURSE CONNECT_SOURCES LIST_DIRECTORIES FALSE "${MODULE_DIR}/include/*.cpp")
file (GLOB_RECURSE PRIVATE_HEADERS LIST_DIRECTORIES FALSE "${MODULE_DIR}/src/*.hpp")
file (GLOB_RECURSE PRIVATE_SOURCES LIST_DIRECTORIES FALSE "${MODULE_DIR}/src/*.cpp")

target_sources ( ${MODULE_NAME}
  PRIVATE 
    ${PRIVATE_HEADERS} 
    ${PRIVATE_SOURCES} 
    ${CONNECT_SOURCES}
)

target_include_directories ( ${MODULE_NAME}
  PUBLIC 
    $<BUILD_INTERFACE:${MODULE_DIR}/include>
    $<INSTALL_INTERFACE:${GORE_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${MODULE_DIR}/src
)

set_target_properties ( ${MODULE_NAME} 
  PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set (MODULE_TARGET ${MODULE_NAME} PARENT_SCOPE)

