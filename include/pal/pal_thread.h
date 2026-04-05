/*----------------------------------------------------------------------------*/
/**
 * Copyright (c) 2026 Abigail Goodwin. All right reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file pal_thread.h
 * @brief Defines the interface for threading.
 */
/*----------------------------------------------------------------------------*/
#ifndef PAL_THREAD_H
#define PAL_THREAD_H

#ifdef __cplusplus
extern "C"
{
#endif
/*--------------------------------Includes------------------------------------*/
// PAL Includes:
#include "pal/pal_config.h"
#include "pal/pal_status.h"
#include "pal/pal_types.h"

/*-------------------------------Definitions----------------------------------*/

/**
 * @brief Defines the maximum length of a thread/task name.
 *
 */
#define PAL_THREAD_NAME_MAX_LEN 32

/**
 * @brief Typedef for the entry point/function pointer used in threads.
 *
 */
typedef void (*pal_thread_func_t)(void* arg);

/**
 * @brief Defines the thread options/attributes data structure.
 *
 */
typedef struct pal_thread_attrs_t
{
    char tname[PAL_THREAD_NAME_MAX_LEN]; /** The name of the thread. */
    pal_thread_func_t function;          /** Routine/function to run. */
    void* args;        /* The arguments to pass to the function.*/
    bool joinable;     /** Whether or not the thread is joinable. */
    size_t stack_size; /** The thread's stack size. */
} pal_thread_attrs_t;

/**
 * @brief Defines the thread data structure.
 *
 */
typedef struct pal_thread_t
{
    uint8_t _tdata[PAL_THREAD_SIZE]; /** Contains the underlying thread data
                                        structure. */
} pal_thread_t;

/**
 * @brief Initializes the thread attribute struct to a default state.
 *
 * @details The default is to create a joinable thread.
 *
 * @param attrs Pointer to the attribute to initialize.
 * @return pal_status_t OK if successful, otherwise returns the generated error.
 */
pal_status_t pal_thread_attr_init(pal_thread_attrs_t* const attrs);

/**
 * @brief Initializes the thread struct using the given attributes.
 *
 * @param thread The thread to initialize.
 * @param attrs The attributes to use.
 * @return pal_status_t OK if successful, otherwise returns the generated error.
 */
pal_status_t pal_thread_init(pal_thread_t* const thread,
                             const pal_thread_attrs_t* const attrs);

/**
 * @brief Spawns the given thread.
 *
 * @param thread The thread to create and run.
 * @return pal_status_t OK if successful, otherwise returns the generated error.
 */
pal_status_t pal_thread_create(pal_thread_t* const thread);

/**
 * @brief Waits on the given thread for it to exit its routine.
 *
 * @param thread The thread to join.
 * @return pal_status_t OK if successful, otherwise returns the generated error.
 */
pal_status_t pal_thread_join(pal_thread_t* const thread);

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // PAL_THREAD_H
