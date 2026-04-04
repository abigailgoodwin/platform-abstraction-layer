#!/usr/bin/env bash
#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

#---------------------------------Config----------------------------------------
# Script config:
set -euo pipefail # Makes us fail faster on errors.

#--------------------------------Globals----------------------------------------

# Script variables:
CLEAN_BUILD=false
PLATFORM=""

#------------------------------Functions----------------------------------------

# Prints usage info:
usage()
{
    echo "Usage: ./build.sh [-K] [-P <platform>]"
    echo "  -K            Perform a clean build (removes build directory first)"
    echo "  -P <platform> Target platform to build for (e.g. linux)"
    exit 1
}

# Read in CLI args:
parse_args()
{
    while getopts ":KP:" opt; do
        case ${opt} in
            K) CLEAN_BUILD=true ;;
            P) PLATFORM="${OPTARG}" ;;
            :) echo "Error: -${OPTARG} requires an argument."; usage ;;
            \?) echo "Error: Unknown flag -${OPTARG}"; usage ;;
        esac
    done

    if [[ -z "${PLATFORM}" ]]; then
        echo "Error: -P <platform> is required."
        usage
    fi
}

# Clean up build dirs/artifacts:
clean_build()
{
    echo "Cleaning build directory..."
    rm -rf build/
}

build()
{
    echo "Platform:    ${PLATFORM}"
    echo "Clean Build: ${CLEAN_BUILD}"

    if [[ "${CLEAN_BUILD}" == true ]]; then
        clean_build
    fi

    cmake -S . -B build
    cmake --build build
}

#----------------------------------Main-----------------------------------------

main()
{
    parse_args "$@"
    build
}

main "$@"

