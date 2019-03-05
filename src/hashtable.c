/*****************************/
/* Sage Castiglione          */
/* April 19, 2018            */
/* hashtable.c will implement*/
/* a hashtable defined in    */
/* hashtable.h               */
/*****************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
/************************************
 * Function: hash
 * Parameter: elt
 *   elt is a HashElement which
 *   is defined in hashtable.h
 * Return: the hash value of a string
 * hash will take the character 
 *   values in ascii and sum them to
 *   get the hash value of a stirng.
 *   hash will return 0 if the token 
 *   is invalid for any reason
 *************************************/
int hash(struct HashElt* elt)
{
  char* ourToken;
  char c;
  int hashTotal = 0;
  int i = 0; 
  if(elt == NULL) return 0;
  ourToken= elt->token;
  c = ourToken[i];
  while(c != '\0')
  {
    if(c > 64 && c < 91) c = (c + 32);
    else if(c > 96 && c < 123) { }
    else return 0; 
    hashTotal += (int)c;
    i++;
    c = ourToken[i];
  }
  return hashTotal;
}
/*******************************
 * Function: duplicateToken
 * Parameter: el1
 *   the first hash element
 * Parameter: el2   
 *   the second hash element
 * Return: if the elements are
 *   equivelent. 
 * duplicateToken will compare
 *   the token and url to see if
 *   the elements are the same
 *   Return 1: token and url are
 *   the same. 
 *   Return 0: otherwise
 *******************************/
int duplicateToken(struct HashElt* el1, struct HashElt* el2)
{
  if(el1 == NULL || el2 == NULL) return 0;
  if(!strcmp(el1->token, el2->token))
  {
    if(!strcmp(el1->url, el2->url)) return 1;
  }
  return 0;
}
/********************************************
 * Function: insert
 * Parameter: elt 
 *   elt is the has element to be inserted
 * Parameter: table
 *   the hash table where elt will be 
 *   inserted
 * Return: void
 * insert will point to a specific location 
 *   in the table as determined by the 
 *   hashed value of the element MOD size of 
 *   the table.
 ********************************************/
void insert(struct HashElt* elt, struct HTable* table)
{ 
  int hashValue = hash(elt) % table->size;
  struct HashElt* elTraverse = table->table[hashValue];
  struct HashElt* oldNode = NULL;
  if(hashValue == 0) return;
  if(elt == NULL) return;
  /* Our list is empty, we insert to the head */ 
  if(elTraverse == NULL)
  { 
    table->table[hashValue] = elt; 
    (table->n)++;
    return;
  }
  /* Check the entire non NULL list for duplicates prior to inserting */
  while(elTraverse)
  {
    if(duplicateToken(elTraverse, elt)) return;
    elTraverse = elTraverse->next;
  }
  elTraverse = table->table[hashValue];
  /* if we need to insert to the second location in the list */
  if(elTraverse->pageRank < elt->pageRank)
  {
    oldNode = elTraverse;
    table->table[hashValue] = elt;
    elt->next = oldNode;
    (table->n)++;
    return;
  }

  /* Insert the element in the order of page rank following an implementation
   * of a sorted linked list */
  while(elTraverse->next)
  { 
    if(elTraverse->next->pageRank < elt->pageRank)
    {
      oldNode = elTraverse->next;
      elt->next = oldNode;
      elTraverse->next = elt;
      (table->n)++;
      return;
    }
    elTraverse = elTraverse->next;
  } 
  elTraverse->next = elt;
  (table->n)++; 
  return;
   
}
/**********************************
 * Function: createElm
 * Parameter: str
 *   str is the string of the 
 *   element to be created
 * Return: the new element
 * createElm will create a naieve 
 *   element to be hashed 
 **********************************/
struct HashElt* createElm(char* str)
{
  struct HashElt* returnHE =
      (struct HashElt*) malloc(1 * sizeof(struct HashElt));
  returnHE->url = NULL;
  returnHE -> pageRank = 0;
  returnHE->token = str;
  returnHE->next = NULL;
  return returnHE; 
}
/******************************************
 * Function: lookup
 * Parameter: key
 *   key is the string to be 
 *   looked up in the hash table
 * Parameter: table
 *   the table containing to be 
 *   used in lookup
 * Return: the list of HashElt 
 *   that is hashed to the value
 *   of the key
 * lookup will take the location of
 *   the key's hashed value and return
 *   the list that is located in the table 
 *   at the given hash value.
 *******************************************/
struct HashElt* lookup(char* key, struct HTable* table)
{
  struct HashElt* newElt;
  struct HashElt* returnElt;
  int hashedStr;
  if(key == NULL) return NULL;
  newElt = createElm(key);
  hashedStr = hash(newElt); 
  returnElt = table->table[hashedStr];
  
  free(newElt);
  return returnElt;
}
