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
TESTS=()
BUILD_DIR="build/tests/"
VERBOSE=false

#------------------------------Functions----------------------------------------

# Prints usage info:
usage()
{
    echo "Usage: ./test.sh [-t <test1> <test2> <...>] [-v]"
    echo "  -t            The unit tests to run. Defaults to 'all'."
    echo "  -v            Toggle on verbose output."
    exit 1
}

# Read in CLI args:
parse_args()
{
    while getopts ":t" opt; do
        case ${opt} in
            t)
                shift $((OPTIND - 1))
                while [[ $# -gt 0 && "${1}" != -* ]]; do
                    FILES+=("${1}")
                    shift
                done
                ;;
            v) VERBOSE=true ;;
            :) echo "Error: -${OPTARG} requires an argument."; usage ;;
            \?) echo "Error: Unknown flag -${OPTARG}"; usage ;;
        esac
    done
}

run_tests()
{
    # First, check if our unit tests were built:
    if [[ ! -d "${BUILD_DIR}" ]]; then
        echo "Error: unit tests have not been built. Run build.sh first."
        exit 1
    fi

    # Configure the ctest args:
    local ctest_args=("--test-dir" "${BUILD_DIR}")
    if [[ "${VERBOSE}" == true ]]; then
        ctest_args+=("--output-on-failure" "-V")
    fi

    # If no unit test names were provided with -t, then just run all of them:
    if [[ ${#TESTS[@]} -gt 0 ]]; then
        local test_regex
        test_regex=$(IFS="|"; echo "${TESTS[*]}")
        ctest_args+=("-R" "${test_regex}")
        echo "Running tests matching: ${test_regex}"
    else
        echo "Running all tests..."
    fi

    ctest "${ctest_args[@]}"
}

#----------------------------------Main-----------------------------------------

main()
{
    parse_args "$@"
    run_tests
}

main "$@"

