/**
 * @file  : Queue.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Queue.c.
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Header guard
 ******************************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * Macro
 ******************************************************************************/

/**
 * @brief Reference of maximum element of queue.
 */
#define MAX_QUEQUE_SIZE (4u)

/**
 * @brief Reference of the empty mark for queue
 */
#define QUEUE_EMPTY_MARK (MAX_QUEQUE_SIZE)

/*******************************************************************************
 * Enum
 ******************************************************************************/

/**
 * @brief Reference of the queue element state.
 */
typedef enum queue_state
{
    QUEUE_ELEMENT_EMPTY = 0u,   /*Element is empty, ready to store data*/
    QUEUE_ELEMENT_READY = 1u,   /*Element is ready, ready to read data*/
} queue_element_state_t;

/*******************************************************************************
 * Struct
 ******************************************************************************/

/**
 * @brief Reference of the queue information
 */
typedef struct srec_queue
{
    volatile uint8_t record[MAX_QUEQUE_SIZE][80];   /*Store lines from srec file*/
    volatile uint8_t first;                         /*Index of first element in queue*/
    volatile uint8_t end;                           /*Index of last element in queue*/
    volatile uint8_t queue_state[MAX_QUEQUE_SIZE];  /*Status of each element in queue*/
} srec_queue;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Init the queue to receive data from srec file
 *
 * @param: This function has no parameter
 *
 * @return: The srec queue
 */
srec_queue init_srec_queue(void);

/**
 * @brief Deinit the queue.
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return: This function return nothing
 */
void deInit_srec_queue(srec_queue *queue);

/**
 * @brief Check if the queue is empty
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return 1 if queue is empty, 0 if not.
 */
uint8_t Queue_IsEmpty(srec_queue *queue);

/**
 * @brief Add new element to queue
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return: This function return nothing
 */
void Queue_Enqueue(srec_queue *queue);

/**
 * @brief Dequeue the queue
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return: This function return nothing
 */
void Queue_Dequeue(srec_queue *queue);

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif
/*EOF*/
