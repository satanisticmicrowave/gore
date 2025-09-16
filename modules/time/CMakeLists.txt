###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-09-12 01:55:12
### Package: modules/time/CMakeLists.txt 
###
### Gore time module
###
### ~ gore
###

cmake_minimum_required(VERSION 3.10)

## ------------------------------------------------------------------------
## ## MODULE TIME
## ------------------------------------------------------------------------

set (_project_version 1.0.0)
project(time_module LANGUAGES CXX VERSION ${_project_version})

## ------------------------------------------------------------------------
## ## File paths
## ------------------------------------------------------------------------
set(_mod_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(_include_dir ${_mod_dir}/include)
set(_src_dir     ${_mod_dir}/src)

## ------------------------------------------------------------------------
## ## Collect source files (implementation and private headers)
## ------------------------------------------------------------------------
file(GLOB_RECURSE _time_src
    RELATIVE ${_mod_dir}
    ${_src_dir}/*.cpp
)
file(GLOB_RECURSE _time_priv_headers
    RELATIVE ${_mod_dir}
    ${_include_dir}/p_*.hpp
)

## Private sources and headers are part of the target but not installed
add_library(time SHARED
    ${_time_src}
    ${_time_priv_headers}
)

## Add export definition
target_compile_definitions(time PRIVATE GORE_EXPORTS)

## ------------------------------------------------------------------------
## ## Collect public headers (exclude p_*.hpp)
## ------------------------------------------------------------------------
file(GLOB_RECURSE _time_all_headers
    RELATIVE ${_include_dir}
    ${_include_dir}/*.hpp
)

## Remove private headers from the list

list(FILTER _time_all_headers EXCLUDE REGEX ".*/p_.*\\.hpp$")
list(FILTER _time_all_headers EXCLUDE REGEX "^p_.*\\.hpp$")


## ------------------------------------------------------------------------
## ## Interface include dirs for public headers
## ------------------------------------------------------------------------
target_include_directories(time
    PUBLIC
        $<BUILD_INTERFACE:${_include_dir}>
        $<INSTALL_INTERFACE:include/gore/time>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)

## ------------------------------------------------------------------------
## ## Register public headers for root installation

## ------------------------------------------------------------------------

set(_time_public_headers ${_time_all_headers} PARENT_SCOPE)

## ------------------------------------------------------------------------
## ## Dependencies
## ------------------------------------------------------------------------
## link libgore_common automatically via root umbrella
target_link_libraries(time
    PUBLIC libgore_common core
)
