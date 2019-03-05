/**************************************/
/* Sage Castiglione                   */
/* April 30, 2018                     */
/* CS241                              */
/* query.c will combine the structures*/
/* created in graphUtils, hashTable,  */
/* indexFiles, to create a working    */
/* hashtable with lookup for tokens   */
/* based upon pagerank                */
/**************************************/
#include "graph.h"
#include "graphUtils.h"
#include "hashtable.h"
#include "indexFiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define URL_LENGTH 50
/*************************************
 * Function: initializeGraph
 * Parameter: g
 *   the graph to be initialized
 * Parameter: graphFile
 *   the file which holds the graph
 * Return: the new graph's pointer
 * initializeGraph will initialize a
 *   graph from a given file and 
 *   calculate the pagerank
 ************************************/
struct graph* initializeGraph(struct graph* g, char* graphFile)
{ 
  if(graphFile == NULL) return NULL;
  g = readGraph(graphFile);
  calculatePageRank(g); 
  return g;
}
/*************************************
 * Function: initializeTable
 * Parameter: table
 *   the table to be initialized
 * Return: void
 * initializeTable will initialize the
 *   table to the default size.
 ****************************************/
void initializeTable(struct HTable* table)
{ 
  table->size = 2000;
  table->n = 0;
}

int main(int argc, char* argv[])
{
  struct graph* g = NULL;
  struct HashElt* lookUpList = NULL;
  struct HTable tab;
  struct HTable* table = &tab;
  int i = 0;
  int identicalFlag = 0;
  struct node* traverse;
  g = initializeGraph(g, argv[1]); 
  initializeTable(table);
  if(g == NULL) 
  {
    printf("Graph cannot be made from given file\n");
    return 1;
  }
  traverse = g->firstNode;
/* While we have nodes, read them into the table for their tokens to be hased
   appropriately */
  while(traverse)
  {
    readInFile(traverse, table, g);
    traverse = traverse->next;
  }
  /* If we are to look up a word */
  if(argc >= 3)
  {
    lookUpList = lookup(doCaseCorrection(argv[2]), table);
  }
  /* Flag to print exact duplicate tokens or not */
  if(argc == 4)
  {
    if(!(strcmp(argv[3], "1")))  identicalFlag = 1;
  }
  /* Printing the first five, or the only amount of urls which match the
     input token */
  while(i < 5 && lookUpList != NULL)
  {
    if(identicalFlag == 0)
    {
      if(!strcmp(lookUpList->token, argv[2])) printf("%s\n", lookUpList->url);
    }
    if(identicalFlag) printf("%s\n", lookUpList->url);
    lookUpList = lookUpList->next;
    i++;
  } 
  return 0;
}  


   
