# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# N Minus 1 Philosophers CMake file
#
################################################################################

set(DPP_N_MINUS_1_PHILOSOPHERS_EXECUTABLE_NAME "dpp_n_minus_1_philosophers")

add_executable(${DPP_N_MINUS_1_PHILOSOPHERS_EXECUTABLE_NAME})

# Source files #################################################################
    
target_sources(${DPP_N_MINUS_1_PHILOSOPHERS_EXECUTABLE_NAME}
  PRIVATE
    ${DPP_COMMON_SOURCES}
    "${PROJECT_SOURCE_DIR}/src/solutions/n_minus_1_philosophers/n_minus_1_philosophers.cc"
)

# Compiling ####################################################################
target_include_directories(${DPP_N_MINUS_1_PHILOSOPHERS_EXECUTABLE_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/"
)

# Linking ######################################################################
target_link_directories(${DPP_N_MINUS_1_PHILOSOPHERS_EXECUTABLE_NAME}
  PRIVATE
    ${VCPKG_LIBRARY_DIR}
)

target_precompile_headers(${DPP_N_MINUS_1_PHILOSOPHERS_EXECUTABLE_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/dpp_precompile.h"
)