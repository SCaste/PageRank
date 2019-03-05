/******************************/
/* Sage Castiglione           */
/* CS241                      */
/* April 12, 2018             */
/* linkedlist.c will implement*/
/* the linkedlist as defined  */
/* in linkedlist.h            */
/******************************/
#include "linkedlist.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
/******************************************
 * Function: pushStack
 * Parameter: head
 *   head is the current head of the list 
 *   before the push operation
 * Parameter: data
 *   data is the data contained within the 
 *   new item to be pushed on the stack
 * Return: the new head of the stack 
 * pushStack will create a new head from
 *   the data given to it, and then return 
 *   it as the new head of the list while 
 *   setting its next to be the previous 
 *   head
 ******************************************/
struct node* pushStack(struct node* head, int data)
{
  struct node* newHead = createNode(data);
  newHead->next = head; 
  return newHead;
}
/********************************************
 * Function: popStack
 * Parameter: headRef
 *   headRef is a pointer to the head of
 *   the list or stack to be popped
 * Return: the data of the popped value
 * popStack will take a list, point the
 *   head to the next value of the previous
 *   head and return the data of the old 
 *   head after freeing it.
 ********************************************/
int popStack(struct node** headRef)
{
 
  struct node* oldHead = *headRef;
  struct node* newHead = oldHead->next;
  int data = (*headRef)->data;
  free(oldHead); 
  *headRef = newHead; 
  return data;
}
/*******************************************
 * Function: listLength
 * Parameter: head
 *   Head is the pointer to the head of the
 *   list whose length is to be counted
 * Return: the length of the list
 * listLength will continue to traverse each 
 *   node in the list until NULL is reached
 *   which signals the end of the list
 *   then return the number of times the
 *   traverse pointer was passed to the
 *   next pointer
 ******************************************/
int listLength(struct node* head) 
{
  struct node* traverse = head;
  int length = 0; 
  if(head == NULL) return 0;
  else 
  {
    while(traverse)
    {
      length++;
      traverse = traverse->next;
    }
  }
  return length;
}
/**************************************
 * Function: freeList
 * Parameter: head
 *   the head of the list to be free'd
 * Return: Void
 * Algorithm: Recursive
 * freeList will take a head to a list
 *   and then recursively free the list 
 *   until the new head is NULL, to 
 *   which the function will 
 *   recursively call back and free all 
 *   "heads", thus freeing the entirity
 *   of the list.
 **************************************/
void freeList(struct node* head) 
{
  if(head!= NULL){
    freeList(head->next); 
    free(head);
  }
  else  free(head); 

  return;
}
/**********************************
 * Function: flipPtrs
 * Parameter: leftPtr
 *   leftPtr is the left ptr of 
 *   the two to be flipped
 * Parameter: rightPtr
 *   rightPtr is the right ptr of
 *   the two to be flipped
 * flipPtr will make the right ptr
 *   point to the left one
 **********************************/
void flipPtrs(struct node* leftPtr, struct node* rightPtr)
{
  rightPtr->next = leftPtr;
}
/******************************************
 * Function: reverseList
 * Parameter: headRef 
 *   headRef is a pointer to the head of a
 *   list to be reversed
 * Return: void
 * reverseList will find the last element 
 *   of the given list to point to for
 *   the new head. It will then traverse
 *   the list looking at the previous and
 *   next node, turning the right of the
 *   node to point to the left
 ******************************************/
void reverseList(struct node** headRef)
{
  struct node* traverse = *(headRef);
  struct node* traverse2 = *(headRef);
  struct node* nextPtr;
  struct node* currentPtr;
  struct node* lastNode;
  
  while(traverse2->next)
  {
    traverse2 = traverse2->next;
  }
  lastNode = traverse2;
  currentPtr = &(*traverse);
  nextPtr = &(*(traverse->next));
  if(traverse->next->next != NULL) reverseList(&(traverse->next));
  flipPtrs(currentPtr, nextPtr);
  currentPtr->next = NULL;
  *headRef = lastNode;
  return;  
}
/* 
 * Function: pushLast
 * Adds a node to the last part of the list
 */
struct node* pushLast(struct node* head, int data)
{
  struct node* traverse = head;
  while(head->next)
  {
    head = head->next;
  }
  head->next = createNode(data);
}
      

