/*----------------------------------------------------------------------------*/
/**
 * @file test_pal_status.c
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Tests the PAL Status library.
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
#include "pal/pal_status.h"

// C Includes:
#include <string.h>
/*-------------------------------Definitions----------------------------------*/

/**
 * @brief Sets up the test fixture.
 *
 */
void setUp(void)
{
    // No-op.
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
 * @brief Verifies that the PAL's status init function properly initializes the
 * struct to a known default state.
 *
 */
void test_init_status(void)
{
    // Create a status struct and fill it with garbage:
    PALStatus_t status;
    status.status = PAL_ERROR;
    memset(status.message, 'a', PAL_MAX_STATUS_MSG_LEN);

    // Call initialize:
    pal_status_init(&status);

    // Verify that our status code is the default (OK) and our message
    // is clear:
    TEST_ASSERT_EQUAL(status.status, PAL_OK);
    TEST_ASSERT_EACH_EQUAL_INT8(0, status.message, PAL_MAX_STATUS_MSG_LEN);
}

/**
 * @brief Runs all of the unit tests in this suite.
 *
 * @return int 0 if succesful, otherwise returns the generated error code.
 */
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_status);
    return UNITY_END();
}