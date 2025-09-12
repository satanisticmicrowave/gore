###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-08-17 18:16:19
### Package: CMakeLists.txt
###
### Gore is Opensource Reactive Engine
### ~ gore
###

cmake_minimum_required(VERSION 3.15)

## Enable new CMP0091 policy
if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

set(CMAKE_SUPPRESS_REGENERATION TRUE)

## Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Project base info
set(_project_name "GORE")
set(_project_version "1.0.0")
set(_project_description "GORE is opensource reactive engine")

project(${_project_name}
    VERSION ${_project_version}
    DESCRIPTION ${_project_description}
    LANGUAGES CXX
)
message(STATUS "${_project_name} v.${_project_version}")

## Include Conan toolchain
if(NOT DEFINED GORE_CONAN_TOOLCHAIN_PATH)
  message(FATAL_ERROR "GORE_CONAN_TOOLCHAIN_PATH is not defined! Please build the project with python script make.py")
endif()
if(NOT EXISTS ${GORE_CONAN_TOOLCHAIN_PATH})
  message(FATAL_ERROR "GORE_CONAN_TOOLCHAIN_PATH points to non-existent file: ${GORE_CONAN_TOOLCHAIN_PATH}")
endif()

## Include conan2 toolchain
include(${GORE_CONAN_TOOLCHAIN_PATH})

## Include CMake package helpers
include(CMakePackageConfigHelpers)

## File paths
set(_project_common_dir ${PROJECT_SOURCE_DIR}/common)
set(_project_modules_dir ${PROJECT_SOURCE_DIR}/modules)

## ------------------------------------------------------------------------
## ## COMMON (hidden target)
## ------------------------------------------------------------------------
add_library(libgore_common INTERFACE)
target_include_directories(libgore_common
  INTERFACE

    $<BUILD_INTERFACE:${_project_common_dir}>  # Теперь указывает на common/
    $<INSTALL_INTERFACE:include>               # При установке будет include/
)

install(DIRECTORY ${_project_common_dir}/gore
        DESTINATION include

        FILES_MATCHING PATTERN "*.hpp"
)

## Export libgore_common into GORETargets so modules can link PUBLIC to it
install(TARGETS libgore_common
        EXPORT GORETargets
)

## ------------------------------------------------------------------------
## ## MODULES discovery and registration
## ------------------------------------------------------------------------
file(GLOB GORE_MODULE_DIRECTORIES
     LIST_DIRECTORIES true
     ${_project_modules_dir}/*
)

set(_gore_module_targets "")

foreach(module_dir IN LISTS GORE_MODULE_DIRECTORIES)
  if(IS_DIRECTORY ${module_dir})
    get_filename_component(module_name ${module_dir} NAME)

    message(STATUS "Found module: ${module_name}")
    list(APPEND _gore_module_targets ${module_name})
    add_subdirectory(${module_dir})

  endif()
endforeach()

## ------------------------------------------------------------------------
## ## Create aliases and export list
## ------------------------------------------------------------------------
set(GORE_TARGETS "")

## Create alias for each module and add to export list
foreach(module IN LISTS _gore_module_targets)

  add_library(GORE::${module} ALIAS ${module})
  list(APPEND GORE_TARGETS ${module})
endforeach()

## Create umbrella target that links all modules (common is pulled by modules)
add_library(Gore INTERFACE)
target_link_libraries(Gore INTERFACE ${GORE_TARGETS})
add_library(GORE::Gore ALIAS Gore)
list(APPEND GORE_TARGETS Gore)

## ------------------------------------------------------------------------
## ## Install public headers and libraries for each module
## ------------------------------------------------------------------------
foreach(module IN LISTS _gore_module_targets)
  message(STATUS "Installing ${module}")


  ## Compute variable name for public headers list
  string(CONCAT hdr_var "_" ${module} "_public_headers")

  if(NOT DEFINED ${hdr_var})
    message(WARNING "Variable ${hdr_var} is not defined in this scope.")
    message(FATAL_ERROR "Unable to get ${module} public headers!")
  endif()

  set(module_headers ${${hdr_var}})
  set(module_dir ${_project_modules_dir}/${module})

  ## Install each public header preserving relative path

  foreach(rel_hdr IN LISTS module_headers)

    set(src ${module_dir}/include/${rel_hdr})
    get_filename_component(rel_path ${rel_hdr} PATH)
    install(FILES ${src}
            DESTINATION include/gore/${module}/${rel_path}
    )
  endforeach()


  ## Set output name prefix and install the library into export set
  string(CONCAT export_name "gore_${module}")
  set_target_properties(${module} PROPERTIES OUTPUT_NAME ${export_name})
  set_target_properties(${module} PROPERTIES PUBLIC_HEADER "${${module}_public_headers}") 

  install(TARGETS ${module}
          EXPORT GORETargets
          ARCHIVE DESTINATION lib/gore
          LIBRARY DESTINATION lib/gore
          RUNTIME DESTINATION bin/gore
  )

  set_target_properties(${module} PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib"
    SKIP_BUILD_RPATH TRUE
  )
  
  ## Define paths to libraries
  if(WIN32)
    # Windows
    set_target_properties(${module} PROPERTIES
      IMPORTED_IMPLIB "${CMAKE_INSTALL_PREFIX}/lib/gore/$<TARGET_LINKER_FILE_NAME:${module}>"
      IMPORTED_LOCATION "${CMAKE_INSTALL_PREFIX}/bin/$<TARGET_FILE_NAME:${module}>"
    )
  else()
    # Unix
    set_target_properties(${module} PROPERTIES
      IMPORTED_LOCATION "${CMAKE_INSTALL_PREFIX}/lib/gore/$<TARGET_FILE_NAME:${module}>"
    )

  endif()

endforeach()


## Install the umbrella target into the same export set
install(TARGETS Gore
        EXPORT GORETargets
)

## ------------------------------------------------------------------------
## ## Install export for modules and umbrella (common is internal)
## ------------------------------------------------------------------------

install(
  EXPORT GORETargets
  NAMESPACE GORE::
  DESTINATION lib/cmake/GORE
)

## ------------------------------------------------------------------------
## ## Generate and install Config files for find_package
## ------------------------------------------------------------------------

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GOREConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/GOREConfig.cmake"
  INSTALL_DESTINATION lib/cmake/GORE

)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/GOREConfigVersion.cmake"
  VERSION ${_project_version}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/GOREConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GOREConfigVersion.cmake"
  DESTINATION lib/cmake/GORE
)
