/**************************************/
/* Sage Castiglione                   */
/* April 20, 2018                     */
/* CS241                              */
/* queue.c implements functions       */ 
/*   to be used as a utility to the   */
/*   graph datatype in queue.h        */
/**************************************/
#include "queue.h"
#include "graph.h"
#include <stdlib.h>
/**********************************
 * Function: createQueue
 * Parameter: nData
 *   nData is the node to be placed
 *   in the queue.
 * Create queue will create a new
 *   queue item and point to it
 **********************************/
struct QueueItem* createQueue(struct node *nData)
{
  struct QueueItem* returnItem = malloc(1 * sizeof(struct QueueItem));
  returnItem->qNext = NULL;
  returnItem->data = nData; 
  return returnItem;
}
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
struct QueueItem* pushLast(struct QueueItem* head, struct node* last)
{
  struct QueueItem* qLast = createQueue(last);
  struct QueueItem* traverse = head;
  if(head == NULL) return qLast;
  while(traverse->qNext)
  {
    traverse = traverse->qNext;
  }
  traverse->qNext = qLast; 
  return head;
}

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
struct node* popStack(struct QueueItem** headRef)
{ 
  struct QueueItem* oldHead;
  struct QueueItem* newHead;
  struct node* returnData;
  if(*headRef == NULL) return NULL; 
  oldHead = *headRef;
  newHead = oldHead->qNext;
  returnData  = (*headRef)->data;
  free(oldHead); 
  *headRef = newHead; 
  return returnData;
}
