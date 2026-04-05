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

// Linux Includes:
#include <string.h>

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

pal_status_t pal_thread_init(pal_thread_t* const thread,
                             const pal_thread_attrs_t* const attrs)
{
    pal_status_t status;
    pal_status_init(&status);

    // TODO
    (void)thread;
    (void)attrs;

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