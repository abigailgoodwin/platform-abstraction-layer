/*----------------------------------------------------------------------------*/
/**
 * @file pal_log.h
 * @author Abigail Goodwin (abby.goodwin@outlook.com)
 * @brief Defines the PAL's logging API.
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */
/*----------------------------------------------------------------------------*/
#ifndef PAL_LOG_H
#define PAL_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif
/*--------------------------------Includes------------------------------------*/
// PAL Includes:
#include "pal/pal_status.h"
/*-------------------------------Definitions----------------------------------*/

/**
 * @brief Defines the length of the log header.
 */
#define PAL_LOG_HEADER_LEN 32

/**
 * @brief Defines the maximum length, in characters, of a PAL log message.
 *
 */
#define PAL_MAX_LOG_MESSAGE_LEN 64

/**
 * @brief Defines the maximum length of any log type string.
 *
 */
#define PAL_LOG_TYPE_LEN 8

/**
 * @brief Defines the types of logs in the system.
 *
 */
typedef enum pal_log_type_t
{
    PAL_LOG_INFO,
    PAL_LOG_ERROR,
    PAL_LOG_FAILURE,
    PAL_LOG_DEBUG,
    PAL_LOG_TYPE_COUNT
} pal_log_type_t;

/**
 * @brief Defines the valid log destinations.
 *
 */
typedef enum pal_log_destination_t
{
    PAL_LOG_CONSOLE,
    PAL_LOG_FILE,
    PAL_LOG_DESTINATION_COUNT
} pal_log_destination_t;

/**
 * @brief The data structure used to hold log info.
 *
 */
typedef struct pal_log_t
{
    pal_log_type_t type;                   /** The type of the log. */
    pal_log_destination_t destination;     /** Where to log to. */
    char message[PAL_MAX_LOG_MESSAGE_LEN]; /** The message to log. */
} pal_log_t;

/**
 * @brief Initializes the log struct to a default state.
 * @details The default log level is LOG_INFO and its destination LOG_CONSOLE.
 *
 * @param log Pointer to the log object to intialize.
 */
void pal_log_init(pal_log_t* const log);

/**
 * @brief Executes logging of the given log struct.
 *
 * @param log The log to log.
 * @return pal_status_t PAL_OK if successful, otherwise returns the generated
 * error.
 */
pal_status_t pal_log(const pal_log_t* const log);

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // PAL_LOG_H
