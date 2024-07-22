/**
 * @file  : Queue.c
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Queue.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/Queue/Queque.h"


/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * @brief Init the queue to receive data from srec file
 *
 * @param: This function has no parameter
 *
 * @return srec queue
 */
srec_queue init_srec_queue(void)
{
    srec_queue ret_queue = {0}; /*This variable stores the return value of function*/

    /*Set end index to 0*/
    ret_queue.end = 0;
    /*Set first index in queue to 0*/
    ret_queue.first = 0;

    return ret_queue;
}

/**
 * @brief Deinit the queue.
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return: This function return nothing
 */
void deInit_srec_queue(srec_queue *queue)
{
    /*Set end index in queue to empty mark*/
    queue->end = QUEUE_EMPTY_MARK;
    /*Set first index in queue to empty mark*/
    queue->first = QUEUE_EMPTY_MARK;

    return;
}

/**
 * @brief Check if the queue is empty
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return 1 if queue is empty, 0 if not.
 */
uint8_t Queue_IsEmpty(srec_queue *queue)
{
    uint8_t ret_val = 0;    /*This variable stores the function return value*/

    /*Check if both first and end index is empty mark*/
    if (QUEUE_EMPTY_MARK == queue->first && QUEUE_EMPTY_MARK == queue->end)
    {
        ret_val = 1;
    }
    else
    {
        ret_val = 0;
    }

    return ret_val;
}

/**
 * @brief Add new element to queue
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return: This function return nothing
 */
void Queue_Enqueue(srec_queue *queue)
{
    /*Check if the queue is full*/
    if ((queue->end + 1) % MAX_QUEQUE_SIZE == queue->first)
    {
        /*Do nothing*/
    }
    /*If queue is empty*/
    if (Queue_IsEmpty(queue))
    {
        queue->end = 0;
        queue->first = 0;
    }
    /*Increase end*/
    else
    {
        queue->end = (queue->end + 1) % MAX_QUEQUE_SIZE;
    }

    return;
}

/**
 * @brief Dequeue the queue
 *
 * @param queue: A struct pointer has information of a srec queue
 *
 * @return: This function return nothing
 */
void Queue_Dequeue(srec_queue *queue)
{
    /*Check if queue is empty*/
    if (Queue_IsEmpty(queue))
    {
        /*Do nothing*/
    }
    /*If the queue currently has only 1 element*/
    else if (queue->end == queue->first)
    {
        queue->end = QUEUE_EMPTY_MARK;
        queue->first = QUEUE_EMPTY_MARK;
    }
    /*Increase the first index in queue*/
    else
    {
        queue->first = (queue->first + 1) % MAX_QUEQUE_SIZE;
    }

    return;
}

/*EOF*/
