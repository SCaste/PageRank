/***********************************/
/* Sage Castiglione                */
/* CS241                           */
/* queue.h contains a definition   */
/* for the queue data struct       */
/***********************************/
#ifndef QUEUE_H
#define QUEUE_H
/*
 * QueueItem is an item to be used in our queue that represents
 * our "data" which is a node and the next item in the queue
 */
struct QueueItem 
{
  struct node* data;
  struct QueueItem* qNext;
};

/**********************************
 * Function: createQueue
 * Parameter: nData
 *   nData is the node to be placed
 *   in the queue.
 * Create queue will create a new
 *   queue item and point to it
 **********************************/
struct QueueItem* createQueue(struct node *nData);

/******************************************************************** 
 * Function: pushLast
 * Parameter: head
 *   head is the head of the queue
 * Parameter: last
 *   last is the node to be placed last in the queue to follow FIFO 
 *   order
 * QueueItem pushLast will traverse the queue until the last item is
 * reached and have the last items next point to our new item
 ********************************************************************/
struct QueueItem* pushLast(struct QueueItem* head, struct node* last);

/********************************************
 * Function: popStack
 * Parameter: headRef
 *   headRef is a pointer to the head of
 *   the list or stack to be popped
 * Return: the node of the popped item 
 * popStack will take a queu, point the
 *   head to the next value of the previous
 *   head and return the node of the old 
 *   head after freeing it.
 ********************************************/
struct node* popStack(struct QueueItem** headRef);

#endif
