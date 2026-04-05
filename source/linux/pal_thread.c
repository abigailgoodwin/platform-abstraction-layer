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
    attrs->stack_size = 0x1000;

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

pal_status_t pal_thread_init(pal_thread_t* const thread,
                             const pal_thread_attrs_t* const attrs)
{
    pal_status_t status;
    pal_status_init(&status);

    // Exit early if any of our inputs are NULL:
    if ((NULL == thread) || (NULL == attrs))
    {
        status.status = PAL_ERROR;
        strncpy(status.message, "Passed in attributes are NULL.",
                sizeof(status.message) - 1);

        return status;
    }

    // First, convert out PAL attributes to pthread attributes:
    pthread_attr_t attributes;
    status.status = get_pthread_attr(attrs, &attributes);

    // If successful, populate our PAL thread body with a pthread_t object:

    return status;
}

pal_status_t pal_thread_create(pal_thread_t* const thread)
{
    pal_status_t status;
    pal_status_init(&status);

    // TODO
    (void)thread;

    return status;
}

pal_status_t pal_thread_join(pal_thread_t* const thread)
{
    pal_status_t status;
    pal_status_init(&status);

    // TODO
    (void)thread;

    return status;
}