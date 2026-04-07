/*----------------------------------------------------------------------------*/
/**
 * @file pal_log.c
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Implements the Linux version of pal_log.h.
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */
/*----------------------------------------------------------------------------*/
/*--------------------------------Includes------------------------------------*/
// PAL Includes:
#include "pal/pal_log.h"

#include "pal/pal_status.h"
#include "pal/pal_types.h"

// C Includes:
#include <stdio.h>
#include <string.h>

/*-------------------------------Definitions----------------------------------*/

void pal_log_init(pal_log_t* const log)
{
    // Early return if our inputs are NULL:
    if (NULL == log)
    {
        return;
    }

    // Set our default log type to INFO and its destination to CONSOLE:
    log->type = PAL_LOG_INFO;
    log->destination = PAL_LOG_CONSOLE;

    // Clear out our message string and fill it with null terminators:
    for (size_t index = 0U; index < PAL_MAX_LOG_MESSAGE_LEN; index++)
    {
        log->message[index] = 0;
    }
}

/**
 * @brief Populates the log header with the required info and formatting.
 *
 * @param header The header to format.
 * @param log The log information.
 */
static void populate_header(char* const header, const pal_log_t* const log)
{
    if ((NULL == header) || (NULL == log))
    {
        return;
    }

    // Clear out our header string, just in case:
    memset(header, 0, PAL_LOG_HEADER_LEN);

    // Convert our log enum to a string:
    char log_level_str[PAL_LOG_TYPE_LEN];
    memset(log_level_str, 0, PAL_LOG_TYPE_LEN);
    switch (log->type)
    {
        case PAL_LOG_INFO:
            strncpy(log_level_str, "INFO", PAL_LOG_TYPE_LEN);
            break;
        case PAL_LOG_ERROR:
            strncpy(log_level_str, "ERROR", PAL_LOG_TYPE_LEN);
            break;
        case PAL_LOG_FAILURE:
            strncpy(log_level_str, "FAILURE", PAL_LOG_TYPE_LEN);
            break;
        case PAL_LOG_DEBUG:
            strncpy(log_level_str, "DEBUG", PAL_LOG_TYPE_LEN);
            break;
        default:
            // Unknown value.
            break;
    }

    // Copy our log string into the header:
    // TODO (abigailgoodwin): Need return type on this function and proper
    // error handling of sys calls.
    strncat(header, "[", 2U);
    strncat(header, log_level_str, PAL_LOG_TYPE_LEN);
    strncat(header, "] ", 3U);
}

/**
 * @brief Internal helper function to log to console.
 *
 * @param log The log.
 * @return pal_status_code_t OK if successful, otherwise returns the
 * generated error.
 */
static pal_status_code_t log_to_console(const pal_log_t* const log)
{
    pal_status_code_t status = PAL_ERROR;

    // Early return if our inputs are NULL:
    if (NULL == log)
    {
        return status;
    }

    // Format our log header:
    char header[PAL_LOG_HEADER_LEN];
    populate_header(header, log);

    // Concatenate our header and our log message, plus a null terminator
    static const uint8_t TOTAL_LENGTH =
        PAL_LOG_HEADER_LEN + PAL_MAX_LOG_MESSAGE_LEN + 1U;

    char log_str[TOTAL_LENGTH];
    memset(log_str, 0, sizeof(log_str));
    strncpy(log_str, header, PAL_LOG_HEADER_LEN);
    strncat(log_str, log->message, PAL_MAX_LOG_MESSAGE_LEN);

    // Finally, write to console:
    int bytes_written = puts(log_str);

    if (bytes_written > 0)
    {
        // TODO (agoodwin): Need to check for partial writes here.
        status = PAL_OK;
    }

    return status;
}

pal_status_t pal_log(const pal_log_t* const log)
{
    pal_status_t status;
    pal_status_init(&status);

    // Early return if our inputs are NULL:
    if (NULL == log)
    {
        status.status = PAL_ERROR;
        strncpy(status.message, "Invalid log input.", PAL_MAX_STATUS_MSG_LEN);
        return status;
    }

    // Determine where we're logging to:
    switch (log->type)
    {
        case PAL_LOG_CONSOLE:
            status.status = log_to_console(log);
            break;
        case PAL_LOG_FILE:
            status.status = PAL_ERROR;
            strncpy(status.message, "File logging is not yet provided.",
                    sizeof(status.message));
            break;
        default:
            status.status = PAL_ERROR;
            strncpy(status.message, "Unknown log destination.",
                    sizeof(status.message));
            break;
    }

    return status;
}