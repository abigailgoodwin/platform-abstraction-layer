#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22)
#-------------------------------------------------------------------------------
# Project Details
#-------------------------------------------------------------------------------
project(PAL
    VERSION 0.1.0
    DESCRIPTION "Platform Abstraction Layer"
    LANGUAGES C
)

#-------------------------------------------------------------------------------
# Language Standards
#-------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

#-------------------------------------------------------------------------------
# Supported Build Types
#-------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "[PAL] No build type specified — defaulting to Debug.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

#-------------------------------------------------------------------------------
# Platform Selection
#-------------------------------------------------------------------------------
set(PAL_SUPPORTED_PLATFORMS linux)
 
set(PAL_PLATFORM "linux" CACHE STRING
    "Target platform backend. One of: ${PAL_SUPPORTED_PLATFORMS}")
 
set_property(CACHE PAL_PLATFORM PROPERTY STRINGS ${PAL_SUPPORTED_PLATFORMS})
 
if(NOT PAL_PLATFORM IN_LIST PAL_SUPPORTED_PLATFORMS)
    message(FATAL_ERROR
        "[PAL] Unknown platform '${PAL_PLATFORM}'. "
        "Must be one of: ${PAL_SUPPORTED_PLATFORMS}"
    )
endif()
 
message(STATUS "[PAL] Building for platform: ${PAL_PLATFORM}")

#-------------------------------------------------------------------------------
# Build Options
#-------------------------------------------------------------------------------
option(PAL_BUILD_TESTS "Builds the unit tests." ON)

#-------------------------------------------------------------------------------
# Compile Definitions
#-------------------------------------------------------------------------------
add_library(pal_compile_options INTERFACE)
 
target_compile_options(pal_compile_options INTERFACE
    $<$<C_COMPILER_ID:GNU,Clang>:
        -Wall
        -Wextra
        -Wshadow
        -Wdouble-promotion
        -Wformat=2
        -fno-common
    >
)

#-------------------------------------------------------------------------------
# Project Includes
#-------------------------------------------------------------------------------
add_subdirectory(source)

 if(PAL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
