#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------
# Get our sources:
set(SOURCES
    pal_error.c
)

target_link_libraries(pal INTERFACE pal_linux)