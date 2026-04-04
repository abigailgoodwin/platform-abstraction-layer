#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Target Details
#-------------------------------------------------------------------------------
add_library(PAL STATIC)

target_include_directories(PAL
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PAL
    PRIVATE pal_compile_options
)

#-------------------------------------------------------------------------------
# Subdirectories
#-------------------------------------------------------------------------------
add_subdirectory(${PAL_PLATFORM})