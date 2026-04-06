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
 * @brief Verifies that PAL thread functions are properly protected against NULL
 * values.
 *
 */
void test_pal_thread_null_protections(void)
{
    // Call our initialize functions and verify that they reject the inputs:
    pal_status_t status = pal_thread_attr_init(NULL);
    TEST_ASSERT_NOT_EQUAL(status.status, PAL_OK);

    status = pal_thread_init(NULL);
    TEST_ASSERT_NOT_EQUAL(status.status, PAL_OK);

    status = pal_thread_create(NULL);
    TEST_ASSERT_NOT_EQUAL(status.status, PAL_OK);

    status = pal_thread_join(NULL, NULL);
    TEST_ASSERT_NOT_EQUAL(status.status, PAL_OK);
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
    TEST_ASSERT_EQUAL(attrs.stack_size, PAL_THREAD_MIN_STACK_SIZE);
}

/**
 * @brief Verifies that PAL threads are properly initialized.
 *
 */
void test_pal_thread_init(void)
{
    // Create a PAL thread and populate it with garbage:
    pal_thread_t thread;
    memset(&thread, 3, sizeof(pal_thread_t));

    // Call initialize:
    pal_status_t status = pal_thread_init(&thread);

    // Verify that our thread's buffer was cleared:
    TEST_ASSERT_EQUAL(status.status, PAL_OK);
    TEST_ASSERT_EACH_EQUAL_INT8(0, thread._tdata, PAL_THREAD_SIZE);
}

/**
 * @brief Test routine for verifying that we can spawn threads.
 *
 * @param args N/A
 * @return void* N/A
 */
void* test_thread_routine(void* args) { thread_executed = true; }

/**
 * @brief Verifies that PAL threads can be properly spawned and joined.
 *
 */
void test_pal_thread_create_join(void)
{
    // Create a PAL thread and initialize it:
    pal_thread_t thread;
    pal_status_t status = pal_thread_init(&thread);
    TEST_ASSERT_EQUAL(status.status, PAL_OK);

    // Set the thread attributes:
    thread.attributes.function = test_thread_routine;

    // Create our thread and then join it:
    status = pal_thread_create(&thread);
    TEST_ASSERT_EQUAL(status.status, PAL_OK);

    status = pal_thread_join(&thread, NULL);
    TEST_ASSERT_EQUAL(status.status, PAL_OK);

    // Check our flag to make sure the thread routine actually ran:
    TEST_ASSERT_TRUE(thread_executed);
}

/**
 * @brief Runs all of the unit tests in this suite.
 *
 * @return int 0 if succesful, otherwise returns the generated error code.
 */
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_pal_thread_null_protections);
    RUN_TEST(test_pal_thread_attr_init);
    RUN_TEST(test_pal_thread_init);
    RUN_TEST(test_pal_thread_create_join);
    return UNITY_END();
}