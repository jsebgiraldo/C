/*
 * queue.c
 *
 *  Created on: Jan 29, 2023
 *      Author: Juan Sebastian Giraldo Duque
 * 		github: https://github.com/jsebgiraldo/C/tree/main/data_structures/queue
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "queue.h"

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
*/

static bool send_q( struct queue_handle *h ,  size_t * pvItemToQueue, size_t uxItemSize)
{
    size_t head = (h->head + 1) % (h->queue_len+1);
    if(head == h->tail) return false; // queue is full

    memcpy(&h->q[h->head*uxItemSize], pvItemToQueue, uxItemSize);
    h->head = head;
    return true;
}

static bool recv_q( struct queue_handle *h, size_t *pvBuffer,  size_t uxItemSize)
{
    if(h->head == h->tail) return false; // No data available

    memcpy(pvBuffer, &h->q[h->tail*uxItemSize], uxItemSize);
    h->tail = (h->tail + 1) % (h->queue_len + 1);
    return true;
}

QueueHandle_t xQueueCreate(size_t uxQueueLength, size_t uxItemSize) 
{
    assert(uxQueueLength && uxItemSize);

    struct queue_handle * h = calloc(1, sizeof(struct queue_handle));

    h->item_size = uxItemSize;
    h->queue_len = uxQueueLength;

    h->q = malloc(uxQueueLength * uxItemSize);

    return (QueueHandle_t)h;
}

void vQueueDelete( QueueHandle_t xQueue )
{
    struct queue_handle * h = xQueue;
    free(h->q);
    free(h);
}

bool xQueueSend(QueueHandle_t xQueue,  void * pvItemToQueue)
{
    struct queue_handle * h = xQueue;
    return send_q(h, (size_t*)pvItemToQueue, h->item_size) ? true : false;
}

bool xQueueReceive(QueueHandle_t xQueue, void *pvBuffer)
{
    struct queue_handle * h = xQueue;
    return recv_q(h, (size_t*)pvBuffer, h->item_size) ? true : false;
}

size_t uxQueueSpacesAvailable(QueueHandle_t xQueue)
{
    struct queue_handle * h = xQueue;
    return (h->queue_len + h->head - h->tail) % h->queue_len;
}

//********	FUNCTIONS END **********
