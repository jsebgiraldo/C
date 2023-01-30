# Queue Management

Queues are the primary form of intertask communications. They can be used to send messages between tasks, and between interrupts and tasks. In most cases they are used as thread safe FIFO (First In First Out) buffers with new data being sent to the back of the queue, although data can also be sent to the front.

![queue](https://www.freertos.org/fr-content-src/uploads/2018/07/queue_animation.gif)

## Modules

* ***xQueueCreate***
* ***vQueueDelete***
* ***xQueueSend***
* ***xQueueReceive***
* ***uxQueueSpacesAvailable***

## Usage

This example shows how to create one and be able to send and receive data through a structure.

```C
struct AMessage
 {
    char ucMessageID;
    char ucData[ 20 ];
 } xMessage;

unsigned long ulVar = 10UL;

int main()
{

    QueueHandle_t xQueue1, xQueue2;
    struct AMessage *pxMessage;
    struct AMessage *xRxedStructure;
    
    /* Create a queue capable of containing 10 unsigned long values. */
    xQueue1 = xQueueCreate( 10, sizeof( unsigned long ) );

    /* Create a queue capable of containing 10 pointers to AMessage structures.
    These should be passed by pointer as they contain a lot of data. */
    xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) );

    /* ... */


    if( xQueue1 != 0 )
    {
        /* Send an unsigned long.*/
        if( xQueueSend( xQueue1,( void * ) &ulVar ) != true )
        {
            /* Failed to post the message.*/
        }
    }


    if( xQueue2 != NULL )
    {
      /* Receive a message from the created queue to hold pointers. The value is read into a
      pointer variable, and as the value received is the address of the xMessage
      variable, after this call pxRxedPointer will point to xMessage. */
      if( xQueueReceive( xQueue2, &( xRxedStructure ) ) == true )
      {
         /* *pxRxedPointer now points to xMessage. */
         printf("%s number %c",xRxedStructure->ucData,xRxedStructure->ucMessageID);
         /* print out -> Queue number 2*/
      }
    }
    
    return 0;
}
```

## Files

* queue.c - queue implementations
* queue.h - import for usage