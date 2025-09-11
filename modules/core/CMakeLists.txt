###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-08-24 10:25:30
### Package: modules/core/CMakeLists.txt 
###
### Gore core module
###
### ~ gore
###

cmake_minimum_required(VERSION 3.10)

## ------------------------------------------------------------------------
## ## MODULE CORE
## ------------------------------------------------------------------------
set (_project_version 1.0.0)
project(core_module LANGUAGES CXX VERSION ${_project_version})

## ------------------------------------------------------------------------
## ## File paths
## ------------------------------------------------------------------------
set(_mod_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(_include_dir ${_mod_dir}/include)
set(_src_dir     ${_mod_dir}/src)

## ------------------------------------------------------------------------
## ## Collect source files (implementation and private headers)
## ------------------------------------------------------------------------
file(GLOB_RECURSE _core_src
    RELATIVE ${_mod_dir}
    ${_src_dir}/*.cpp
)
file(GLOB_RECURSE _core_priv_headers
    RELATIVE ${_mod_dir}
    ${_include_dir}/p_*.hpp
)
## Private sources and headers are part of the target but not installed
add_library(core STATIC
    ${_core_src}
    ${_core_priv_headers}
)

## ------------------------------------------------------------------------
## ## Collect public headers (exclude p_*.hpp)
## ------------------------------------------------------------------------
file(GLOB_RECURSE _core_all_headers
    RELATIVE ${_mod_dir}
    ${_include_dir}/*.hpp
)

## Remove private headers from the list
list(FILTER _core_all_headers EXCLUDE REGEX ".*/p_.*\\.hpp$")
list(FILTER _core_all_headers EXCLUDE REGEX "^p_.*\\.hpp$")

## ------------------------------------------------------------------------
## ## Interface include dirs for public headers
## ------------------------------------------------------------------------
target_include_directories(core
    PUBLIC
        $<BUILD_INTERFACE:${_include_dir}>
        $<INSTALL_INTERFACE:include/gore/core>
)

## ------------------------------------------------------------------------
## ## Register public headers for root installation
## ------------------------------------------------------------------------
set(_core_public_headers ${_core_all_headers} PARENT_SCOPE)

## ------------------------------------------------------------------------
## ## Dependencies
## ------------------------------------------------------------------------
## link libgore_common automatically via root umbrella
target_link_libraries(core
    PUBLIC libgore_common
)
