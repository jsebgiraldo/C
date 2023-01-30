/*
 * queue.h
 *
 *  Created on: Jan 29, 2023
 *      Author: Juan Sebastian Giraldo Duque
 * 		github: https://github.com/jsebgiraldo
 */

#ifndef INC_APIS_QUEUE_H_
#define INC_APIS_QUEUE_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * INCLUDE TYPEDEFS
 ****************************************************************************************
*/

struct queue_handle {
    size_t item_size;
    size_t queue_len;
    size_t head;
    size_t tail;
    void * q;
};

typedef void * QueueHandle_t;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
*/

/**
 * @brief Creates a new queue and returns a handle by which the queue can be referenced.
 * 
 * @param uxQueueLength The maximum number of items the queue can hold at any one time.
 * @param uxItemSize The size, in bytes, required to hold each item in the queue.
 * Items are queued by copy, not by reference, so this is the number of bytes that will be copied for each queued item. 
 * Each item in the queue must be the same size.
 * 
 * @return If the queue is created successfully then a handle to the created queue is returned. 
 * If the memory required to create the queue could not be allocated then NULL is returned. 
 */
QueueHandle_t xQueueCreate(size_t uxQueueLength, size_t uxItemSize);

/**
 * @brief Delete a queue - freeing all the memory allocated 
 * for storing of items placed on the queue.
 * 
 * @param xQueue A handle to the queue to be deleted.
 */

void vQueueDelete( QueueHandle_t xQueue )

/**
 * @brief Post an item on a queue. The item is queued by copy, not by reference.
 * 
 * @param xQueue 	The handle to the queue on which the item is to be posted.
 * @param pvItemToQueue A pointer to the item that is to be placed on the queue. 
 * The size of the items the queue will hold was defined when the queue was created, 
 * so this many bytes will be copied from pvItemToQueue into the queue storage area.
 * 
 * @return pdTRUE if the item was successfully posted, otherwise pdFALSE. 
 */

bool xQueueSend(QueueHandle_t xQueue,  void * pvItemToQueue);

/**
 * @brief Receive an item from a queue. The item is received by copy so a buffer of adequate size must be provided. 
 * The number of bytes copied into the buffer was defined when the queue was created.
 * 
 * @param xQueue The handle to the queue from which the item is to be received.
 * @param pvBuffer Pointer to the buffer into which the received item will be copied.
 * 
 * @return pdTRUE if an item was successfully received from the queue, otherwise pdFALSE. 
 */

bool xQueueReceive(QueueHandle_t xQueue, void *pvBuffer);

/**
 * @brief Return the number of free spaces in a queue.
 * 
 * @param xQueue A handle to the queue being queried.
 * 
 * @return size_t 
 * The number of free spaces available in the queue.
 */
size_t uxQueueSpacesAvailable(QueueHandle_t xQueue);

#endif /* INC_APIS_QUEUE_H_ */