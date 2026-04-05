/*----------------------------------------------------------------------------*/
/**
 * @file pal_status.h
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Defines the PAL's status and error API.
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/*----------------------------------------------------------------------------*/
#ifndef PAL_STATUS_H
#define PAL_STATUS_H
/*--------------------------------Includes------------------------------------*/
#include "stdint.h"
/*-------------------------------Definitions----------------------------------*/

/**
 * @brief Defines the maximum length of the status strings.
 *
 */
#define PAL_MAX_STATUS_MSG_LEN 64

    /**
     * @brief Defines the status codes available in the system.
     *
     */
    typedef enum PAL_StatusCode_t
    {
        PAL_OK,
        PAL_ERROR,
        PAL_TIMEOUT,
        PAL_STATUS_COUNT
    } PAL_StatusCode_t;

    /**
     * @brief Defines the common error type used across the system.
     *
     */
    typedef struct PALStatus_t
    {
        PAL_StatusCode_t status;
        char message[PAL_MAX_STATUS_MSG_LEN];
    } PALStatus_t;

    /**
     * @brief Initializes the status struct to a default state.
     * @details Sets the status to OK and sets the message string to null
     * terminators.
     *
     * @param status The status object to initialize.
     */
    void pal_status_init(PALStatus_t* const status);

#endif /* PAL_STATUS_H */
#ifdef __cplusplus
}
#endif