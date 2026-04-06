#-------------------------------------------------------------------------------
# Copyright (c) 2026 Abigail Goodwin. All right reserved.
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

#-------------------------------Functions---------------------------------------

# Define a helper function to quickly add new unit test suites:
function(pal_add_tests test_file_name)
    # Create our test executable:
    add_executable(${test_file_name} ${test_file_name}.c)

    # Link against PAL and Unity:
    target_link_libraries(${test_file_name}
        PRIVATE
            PAL
            unity
    )

    # Add a test for CTest:
    add_test(NAME ${test_file_name} COMMAND ${test_file_name})
endfunction()

#---------------------------------Tests-----------------------------------------
pal_add_tests(test_pal_status)
pal_add_tests(test_pal_thread)