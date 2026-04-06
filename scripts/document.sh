#!/usr/bin/env bash
#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

#---------------------------------Config----------------------------------------
# Script config:
set -euo pipefail # Makes us fail faster on errors.

#--------------------------------Globals----------------------------------------
DOCS_DIR="docs/html"
#------------------------------Functions----------------------------------------
# Prints usage info:
usage()
{
    echo "Usage: ./document.sh"
    exit 1
}

main()
{
    # Generate our docs:
    doxygen Doxyfile

    # Serve them on a local HTTP server:
    echo "Booting up docs. Type CTRL-C to exit at any time..."
    pushd ${DOCS_DIR}
    python3 -m http.server 8080
    popd
}

main "$@"
