# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# Common CMake file
#
################################################################################

# Source files #################################################################

set(DPP_COMMON_SOURCES ${DPP_COMMON_SOURCES}
  "${PROJECT_SOURCE_DIR}/src/common/compiler.h"
  "${PROJECT_SOURCE_DIR}/src/common/debug.cc"
  "${PROJECT_SOURCE_DIR}/src/common/dining_party.cc"
  "${PROJECT_SOURCE_DIR}/src/common/entry_point.cc"
  "${PROJECT_SOURCE_DIR}/src/common/logger.cc"
  "${PROJECT_SOURCE_DIR}/src/common/os.h"
  "${PROJECT_SOURCE_DIR}/src/common/primitive.h"
  "${PROJECT_SOURCE_DIR}/src/common/utils.cc"
  PARENT_SCOPE
)
