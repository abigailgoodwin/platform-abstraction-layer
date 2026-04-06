/*----------------------------------------------------------------------------*/
/**
 * @file test_pal_thread.c
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Tests the PAL threading library for Linux.
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */
/*----------------------------------------------------------------------------*/

/*--------------------------------Includes------------------------------------*/
// Unity Includes:
#include "unity.h"

// PAL Includes:
#include "pal/pal_thread.h"

// C Includes:
#include <string.h>
/*---------------------------------Globals------------------------------------*/
/**
 * @brief Used to track whether or not the test thread actually executed.
 */
static volatile bool thread_executed = false;

/*-------------------------------Definitions----------------------------------*/

/**
 * @brief Sets up the test fixture.
 *
 */
void setUp(void)
{
    // Set our global flag to false:
    thread_executed = false;
}

/**
 * @brief Cleans up the test fixture.
 *
 */
void tearDown(void)
{
    // No-op.
}

/**
 * @brief Verifies that PAL thread attributes are properly intialized.
 *
 */
void test_pal_thread_attr_init(void)
{
    // Create a PAL thread attribute struct and fill it with garbage:
    pal_thread_attrs_t attrs;
    memset(&attrs, 3, sizeof(pal_thread_attrs_t));

    // Call init:
    pal_status_t status = pal_thread_attr_init(&attrs);

    // Verify that our fields are defaulted to known values:
    TEST_ASSERT_EQUAL(status.status, PAL_OK);
    TEST_ASSERT_NULL(attrs.function);
    TEST_ASSERT_NULL(attrs.args);
    TEST_ASSERT_TRUE(attrs.joinable);
    TEST_ASSERT_EQUAL(attrs.stack_size, 0x1000);
}

/**
 * @brief Runs all of the unit tests in this suite.
 *
 * @return int 0 if succesful, otherwise returns the generated error code.
 */
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_pal_thread_attr_init);
    return UNITY_END();
}