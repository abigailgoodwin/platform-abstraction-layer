/**
 * Copyright (c) 2026 Abigail Goodwin. All right reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file pal_status.h
 * @brief Defines common error and status types.
 */

 /*----------------------------------------------------------------------------*/

#ifndef PAL_STATUS_H
#define PAL_STATUS_H

static const uint8_t MAX_STATUS_MSG_LEN = 40U;

/**
 * @brief Defines the status codes available in the system.
 *
 */
enum PAL_StatusCode_t
{
  PAL_OK,
  PAL_ERROR,
  PAL_TIMEOUT,
  PAL_STATUS_COUNT
};

/**
 * @brief Defines the common error type used across the system.
 *
 */
typedef struct PALStatus_t
{
  PAL_StatusCode_t status;
  char message[]
} PALStatus_t;

#endif /* PAL_STATUS_H */