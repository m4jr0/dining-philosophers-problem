# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# Central Arbitor CMake file
#
################################################################################

set(DPP_CENTRAL_ARBITOR_EXECUTABLE_NAME "dpp_central_arbitor")

add_executable(${DPP_CENTRAL_ARBITOR_EXECUTABLE_NAME})

# Source files #################################################################
    
target_sources(${DPP_CENTRAL_ARBITOR_EXECUTABLE_NAME}
  PRIVATE
    ${DPP_COMMON_SOURCES}
    "${PROJECT_SOURCE_DIR}/src/solutions/central_arbitor/central_arbitor.cc"
)

# Compiling ####################################################################
target_include_directories(${DPP_CENTRAL_ARBITOR_EXECUTABLE_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/"
)

# Linking ######################################################################
target_link_directories(${DPP_CENTRAL_ARBITOR_EXECUTABLE_NAME}
  PRIVATE
    ${VCPKG_LIBRARY_DIR}
)

target_precompile_headers(${DPP_CENTRAL_ARBITOR_EXECUTABLE_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/dpp_precompile.h"
)