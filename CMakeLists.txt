# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# Main CMake file
#
################################################################################

cmake_minimum_required(VERSION 3.21)

# CMake setup ##################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE on)

# Generic builds.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Multi-config builds.
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
endforeach()

# Global variables #############################################################
# Executables.
set(EXECUTABLE_NAME "dpp")

# Other.
set(MESSAGE_PREFIX "[DPP] ")

# Build type.
if (NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "${MESSAGE_PREFIX}Build type: ${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(DPP_DEBUG)
endif()

# OS specifics #################################################################
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

# Project ######################################################################
message(STATUS
  "${MESSAGE_PREFIX}Building ${CMAKE_PROJECT_NAME} "
  "to ${CMAKE_CURRENT_BINARY_DIR}...")

project("Dining Philosophers Problem"
  VERSION 0.1.0
  DESCRIPTION "Some canonical solutions to the famous Dining Philosophers Problem"
  LANGUAGES CXX
)

# Disable any non-conformant code with Microsoft Visual C++.
if(MSVC)
    add_compile_options(/permissive-)
endif()

set(DPP_COMMON_SOURCES "")

# Common code used accross all solutions.
add_subdirectory("${PROJECT_SOURCE_DIR}/src/common")

# Solution executables.
add_subdirectory("${PROJECT_SOURCE_DIR}/src/solutions/central_arbitor")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/solutions/chandra_misra")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/solutions/global_order")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/solutions/n_minus_1_philosophers")

message(STATUS "${MESSAGE_PREFIX}Done.")
