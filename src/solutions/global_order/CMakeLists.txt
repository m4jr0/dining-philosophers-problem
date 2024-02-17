# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# Global Order CMake file
#
################################################################################

set(DPP_GLOBAL_ORDER_EXECUTABLE_NAME "dpp_global_order")

add_executable(${DPP_GLOBAL_ORDER_EXECUTABLE_NAME})

# Source files #################################################################
    
target_sources(${DPP_GLOBAL_ORDER_EXECUTABLE_NAME}
  PRIVATE
    ${DPP_COMMON_SOURCES}
    "${PROJECT_SOURCE_DIR}/src/solutions/global_order/global_order.cc"
)

# Compiling ####################################################################
target_include_directories(${DPP_GLOBAL_ORDER_EXECUTABLE_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/"
)

# Linking ######################################################################
target_link_directories(${DPP_GLOBAL_ORDER_EXECUTABLE_NAME}
  PRIVATE
    ${VCPKG_LIBRARY_DIR}
)

target_precompile_headers(${DPP_GLOBAL_ORDER_EXECUTABLE_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/dpp_precompile.h"
)