###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-09-13 17:39:23
### Package: modules/logger/CMakeLists.txt 
###
### Gore logger module
###
### ~ gore
###

cmake_minimum_required(VERSION 3.10)

## ------------------------------------------------------------------------
## ## MODULE LOGGER
## ------------------------------------------------------------------------

set (_project_version 1.0.0)
project(logger_module LANGUAGES CXX VERSION ${_project_version})

## ------------------------------------------------------------------------
## ## File paths
## ------------------------------------------------------------------------
set(_mod_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(_include_dir ${_mod_dir}/include)
set(_src_dir     ${_mod_dir}/src)

## ------------------------------------------------------------------------
## ## Collect source files (implementation and private headers)
## ------------------------------------------------------------------------
file(GLOB_RECURSE _logger_src
    RELATIVE ${_mod_dir}
    ${_src_dir}/*.cpp
)
file(GLOB_RECURSE _logger_priv_headers
    RELATIVE ${_mod_dir}
    ${_include_dir}/p_*.hpp
)

## Private sources and headers are part of the target but not installed
add_library(logger SHARED
    ${_logger_src}
    ${_logger_priv_headers}
)

## Add export definition
target_compile_definitions(logger PRIVATE GORE_EXPORTS)

## ------------------------------------------------------------------------
## ## Collect public headers (exclude p_*.hpp)
## ------------------------------------------------------------------------
file(GLOB_RECURSE _logger_all_headers
    RELATIVE ${_include_dir}
    ${_include_dir}/*.hpp
)

## Remove private headers from the list
list(FILTER _logger_all_headers EXCLUDE REGEX ".*/p_.*\\.hpp$")
list(FILTER _logger_all_headers EXCLUDE REGEX "^p_.*\\.hpp$")

## ------------------------------------------------------------------------
## ## Interface include dirs for public headers
## ------------------------------------------------------------------------
target_include_directories(logger
    PUBLIC
        $<BUILD_INTERFACE:${_include_dir}>
        $<INSTALL_INTERFACE:include/gore/logger>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)

## ------------------------------------------------------------------------
## ## Register public headers for root installation

## ------------------------------------------------------------------------

set(_logger_public_headers ${_logger_all_headers} PARENT_SCOPE)


## ------------------------------------------------------------------------

## ## Dependencies
## ------------------------------------------------------------------------
## link libgore_common automatically via root umbrella
target_link_libraries(logger
    PUBLIC libgore_common
)
