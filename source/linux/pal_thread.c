/*----------------------------------------------------------------------------*/
/**
 * @file pal_status.c
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Implements the Linux version of pal_thread.h.
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */
/*----------------------------------------------------------------------------*/
/*--------------------------------Includes------------------------------------*/
// PAL Includes:
#include "pal/pal_thread.h"

// C Includes:
#include <assert.h>

// Linux Includes:
#include <pthread.h>
#include <string.h>

/*---------------------------Compile-Time Checks------------------------------*/
static_assert(sizeof(pthread_t) <= PAL_THREAD_SIZE,
              "PAL_THREAD_SIZE is too small for pthread_t on this platform.");

/*-------------------------------Definitions----------------------------------*/

pal_status_t pal_thread_attr_init(pal_thread_attrs_t* const attrs)
{
    pal_status_t status;
    pal_status_init(&status);

    // Exit early if our thread is NULL:
    if (NULL == attrs)
    {
        status.status = PAL_ERROR;
        strncpy(status.message, "Passed in attributes are NULL.",
                sizeof(status.message) - 1);

        return status;
    }

    // Initialize our attrs struct to default values:
    for (size_t index = 0; index < PAL_THREAD_NAME_MAX_LEN; index++)
    {
        attrs->tname[index] = '\0';
    }

    attrs->function = NULL;
    attrs->args = NULL;
    attrs->joinable = true;
    attrs->stack_size = PAL_THREAD_MIN_STACK_SIZE;

    return status;
}

/**
 * @brief Converts the given PAL thread attributes to pthread attributes.
 *
 * @param pal_attrs The PAL attributes.
 * @param pthread_attrs The resulting pthread attributes to populate.
 * @return pal_status_code_t OK if successful, otherwise returns the generated
 * error.
 */
static pal_status_code_t get_pthread_attr(
    const pal_thread_attrs_t* const pal_attrs,
    pthread_attr_t* const pthread_attrs)
{
    pal_status_code_t status = PAL_ERROR;

    // First, initialize our pthread attributes:
    int result = pthread_attr_init(pthread_attrs);
    if (result == 0)
    {
        // Set our detach state:
        int detached = (pal_attrs->joinable ? PTHREAD_CREATE_JOINABLE
                                            : PTHREAD_CREATE_DETACHED);
        result = pthread_attr_setdetachstate(pthread_attrs, detached);

        // Set our stack size:
        if (result == 0)
        {
            size_t stack = pal_attrs->stack_size;
            result = pthread_attr_setstacksize(pthread_attrs, stack);
        }

        // Set our error to OK if every setting was set properly:
        if (result == 0)
        {
            status = PAL_OK;
        }
    }

    return status;
}

pal_status_t pal_thread_init(pal_thread_t* const thread)
{
    pal_status_t status;
    pal_status_init(&status);

    // Exit early if any of our inputs are NULL:
    if (NULL == thread)
    {
        status.status = PAL_ERROR;
        strncpy(status.message, "Passed in attributes are NULL.",
                sizeof(status.message) - 1);

        return status;
    }

    // First, initialize our attributes to their defaults:
    status = pal_thread_attr_init(&thread->attributes);

    if (status.status == PAL_OK)
    {
        // Then, clear out the buffer that will contain our actual thread
        // object:
        for (size_t index = 0U; index < PAL_THREAD_SIZE; index++)
        {
            thread->_tdata[index] = 0;
        }
    }

    // Return any generated errors:
    return status;
}

pal_status_t pal_thread_create(pal_thread_t* const thread)
{
    pal_status_t status;
    pal_status_init(&status);

    // Exit early if any of our inputs are NULL:
    if (NULL == thread)
    {
        status.status = PAL_ERROR;
        strncpy(status.message, "Passed in thread is NULL.",
                sizeof(status.message) - 1);

        return status;
    }

    // Convert our PAL thread attributes to pthread attributes:
    pthread_attr_t pthread_attrs;
    status.status = get_pthread_attr(&thread->attributes, &pthread_attrs);

    // If successful, spawn our thread using pthreads:
    if (status.status == PAL_OK)
    {
        pthread_t* pthread = (pthread_t*)thread->_tdata;

        // May need to be ironed out. Unclear if this is a safe cast:
        int result =
            pthread_create(pthread, &pthread_attrs, thread->attributes.function,
                           thread->attributes.args);

        if (result != 0)
        {
            status.status = PAL_ERROR;
            strncpy(status.message, "Failed to create thread.",
                    sizeof(status.message) - 1);
        }
    }

    return status;
}

pal_status_t pal_thread_join(pal_thread_t* const thread, void** result)
{
    pal_status_t status;
    pal_status_init(&status);

    // Early return if our thread is NULL:
    if ((NULL == thread) || (NULL == (pthread_t*)thread->_tdata))
    {
        status.status = PAL_ERROR;
        strncpy(status.message, "Passed in thread is NULL.",
                sizeof(status.message) - 1);

        return status;
    }

    // Get our pthread out of the PAL thread:
    pthread_t* pthread = (pthread_t*)thread->_tdata;
    pthread_join(*pthread, result);

    return status;
}