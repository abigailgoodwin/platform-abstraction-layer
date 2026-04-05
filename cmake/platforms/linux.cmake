#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------
# Contains platform-specific sizing and alignment information.
include(CheckTypeSize)
set(CMAKE_EXTRA_INCLUDE_FILES "pthread.h")
check_type_size("pthread_t" PAL_THREAD_SIZE LANGUAGE C)
check_type_size("pthread_attr_t" PAL_THREAD_SIZE LANGUAGE C)