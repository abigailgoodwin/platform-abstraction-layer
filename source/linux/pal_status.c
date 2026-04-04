/*----------------------------------------------------------------------------*/
/**
 * @file pal_status.c
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Implements the Linux version of pal_status.h.
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */
/*----------------------------------------------------------------------------*/
/*--------------------------------Includes------------------------------------*/
// PAL Includes:
#include "pal/pal_status.h"
#include "pal/pal_types.h"

/*-------------------------------Definitions----------------------------------*/

/**
 * @brief Initializes the status struct to a default state.
 * @details Sets the status to OK and sets the message string to null
 * terminators.
 *
 * @param status The status object to initialize.
 */
void pal_status_init(PALStatus_t *const status)
{
    if (NULL == status)
    {
        return;
    }

    for (uint8_t index = 0U; index < PAL_MAX_STATUS_MSG_LEN; index++)
    {
        status->message[index] = 0;
    }
}