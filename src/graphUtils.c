/**************************************/
/* Sage Castiglione                   */
/* April 12, 2018                     */
/* CS241                              */
/* graphUtils.c implements functions  */ 
/*   to be used as a utility to the   */
/*   graph datatype                   */
/**************************************/
#include "queue.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 50 
#define D .85
#define PRTRIALS 100

void printPageRank(struct graph* g, char* out);
/*
 * PageRankNode is a structure which will store our nodes with
 * the associated page rank in the form of two arrays which will
 * index in order according to the given list of our nodes
 */
struct PageRankNode 
{
  struct node* prNode;
  float pagerank;
  struct PageRankNode* pageListNext;
};
/*************************************************
 * Function: createPRN
 * Parameter: void
 * Return: a pointer to the newly created page
 *   rank node
 * createPRN will create a PageRankNode which will
 *   have each page rank initialized to zero, and
 *   each node initialized to NULL.
 *************************************************/
struct PageRankNode* createPRN(struct node* curNode)
{
  struct PageRankNode* prn = (struct PageRankNode*) malloc(1 * 
                            sizeof(struct PageRankNode));
  prn->prNode = curNode;
  prn->pagerank = curNode->pagerank;
  prn->pageListNext = NULL;
  return prn;
}
/***************************************
 * Function: freeAllPRN
 * Parameter: prn
 *   the head of the list of page rank
 *   nodes.
 * Return: void
 * freeAllPRN will traverse each in the
 *   list of PRNs freeing once the
 *   final node is reached
 ***************************************/
void freeAllPRN(struct PageRankNode* prn)
{
  if(prn != NULL) freeAllPRN(prn->pageListNext);
  free(prn);
}
/******************************************
 * Function: numEdges
 * Parameter: eNode
 *   eNode is the node whos edges are to
 *   be summed
 * Return: the number of edges to the node
 * numEdges will traverse the edges 
 *   that connect to the node until NULL
 *   is reached, indiciating that the list
 *   has no more edges
 ******************************************/
int numEdges(struct node* eNode)
{
  struct edge* traverse = eNode->edges;
  int edgeCount = 0;
  while(traverse)
  {
    edgeCount++;
    traverse = traverse->next;
  }
  return edgeCount;
}
/***************************************
 * Function: compareFloats
 * Parameter: float1
 *   float1 is the float to be compared
 * Parameter: float2
 *   float2 is the second to be compared
 * Return: If the two are within error
 *   bounds
 * compareFloats will compare two floats
 *   to a .0000001 accuracy to represent
 *   the accurate range of floats. And
 *   be appropriately compared
 ***************************************/
int compareFloats(float float1, float float2)
{
  int difference = float1 - float2;
  if(difference < -0.0000001 || difference > 0.0000001) return 0;
  return 1;
}
/******************************
 * Function: getPagerank
 * Parameter: url 
 *   the name of the node 
 * Parameter: g
 *   the graph the node is in
 * Return: the pagerank of the
 *   the node
 * getPageRank will search for
 *   the node asked for, and if
 *   it is found, will return
 *   the pagerank of the node
 *******************************/
float getPagerank(char* url, struct graph* g)
{
  struct node* start;
  if(url == NULL || g == NULL) return 0;
  start = g->firstNode;
  while(start) 
  {
    if(!strcmp(start->url, url)) return start->pagerank;
    start = start->next;
  }
  return 0;
}
   
/***************************************
 * Function: calculatePageHelper
 * Parameter: g
 *   the graph whos pageRank is held
 * Parameter: head
 *   the head of the list of the data
 *   structure which holds old page
 *   rank values
 * Return: whether calculations are
 *   done or not (old page rank = new PR)
 * calculatePageHelper will support 
 *   the calculatePageRank by assigning
 *   each page rank to the data structure
 *   provided. By running through each 
 *   connection node and adding .15 along
 *   with the page rank of each additional
 *   node that it is connected to by 
 *   in accordance with the standard PR
 *   calculation provided to us 
 *****************************************/
int calculatePageHelper(struct graph* g, struct PageRankNode* head)
{
  struct PageRankNode* prTraverse;
  struct node* nodeTraverse;
  struct edge* connectedEdge;
  int stopCalculating= 1;
  int edgeCount = 0;
  prTraverse = head;
  if(prTraverse == NULL) return 0;
  /* Initialize each pageRank accordingly to .15 for our calculations */
  while(prTraverse != NULL)
  {
    prTraverse->prNode->pagerank = 1 - D;
    prTraverse = prTraverse -> pageListNext;
  } 
  prTraverse = head;
  /* 
   * Traverse each node in our pageRankList, adding the page rank of the current
   * node to each node that it is connected to
   */
  while(prTraverse != NULL)
  {
    nodeTraverse = prTraverse->prNode;
    edgeCount = numEdges(nodeTraverse);
    connectedEdge = nodeTraverse->edges;
    while(connectedEdge != NULL)
    {
      connectedEdge->connectsTo->pagerank +=
          D * (prTraverse->pagerank / edgeCount);
      connectedEdge = connectedEdge->next;
    }
    prTraverse = prTraverse->pageListNext;
  }
  /* Compare the new pageranks of the old pageranks, and then update
   * all of the values for our calculations */
  prTraverse = head; 
  nodeTraverse = g->firstNode;

  while(prTraverse != NULL && nodeTraverse != NULL)
  {
    if(compareFloats(prTraverse->pagerank, nodeTraverse->pagerank))
    {
      stopCalculating = 0;
    }
    prTraverse->pagerank = nodeTraverse->pagerank;
    prTraverse = prTraverse->pageListNext;
    nodeTraverse = nodeTraverse->next;
  }
  return stopCalculating;
}


/*****************************************
 * Function: calculatePageRank 
 * Parameter: g
 *   g is the graph whos nodes are to be
 *   calculated for pagerank
 * Parameter: pr
 *   the page rank node utilized to
 *   calculate the pagerank
 * Return: whether the previous pageranks
 *   are equal to the current ones.
 * calculatePageRank will initialze the values
 *   of the pagerank node, and then use 
 *   number of edges to calculate one 
 *   round of it before putting the 
 *   values back into the graph
 ****************************************/
void calculatePageRank(struct graph* g)
{
  int i = 0;
  struct node* traverse = g->firstNode;
  struct PageRankNode* prTraverse;
  struct PageRankNode* prHead;
  if(traverse == NULL) return;
  else 
  {
    /* Creating a new page rank structure for each node in our graph */
    prHead = createPRN(traverse);
    traverse = traverse->next;
    prTraverse = prHead;
    while(traverse)
    {
      prTraverse->pageListNext = createPRN(traverse);
      traverse = traverse->next;
      prTraverse = prTraverse->pageListNext;
    }
  }
  for(; i < PRTRIALS; i++)
  {
    if(calculatePageHelper(g, prHead)) break;
  }
  freeAllPRN(prHead);
  return;
}
  
/********************************
 * Function: resetVisited
 * Parameter: g
 *   g is the graph who's visited
 *   nodes are to be reset
 * Return: void
 * resetVisited will traverse 
 *   each node in a graph ensuring
 *   that the visited values for 
 *   each node is 0
 *********************************/
void resetVisited(struct graph* g)
{
  struct node* traverse = g->firstNode;
  if(traverse == NULL) return;
  else
  {
    while(traverse)
    {
      traverse->visited = 0; 
      traverse = traverse->next;
    }
  }
}
/***************************************
 * Function: depthSearchNodes
 * Parameter: node
 *   the first node in the graph
 * Parameter: url
 *   the url to be searched for in the 
 *   graph starting with node
 * depthSearchNodes will start with the
 *   first node in the graph, and proceed 
 *   to search through each node 
 *   by recursively searching in an in
 *   order fashion, moving past
 *   nodes marked as visited. Once the 
 *   node has been checked for url 
 *   equality, then it will pass as
 *   visited, and search through the
 *   next edge connection. 
 * Algorithm: depth first search
 ****************************************/
int depthSearchNodes(struct node* node, char* url)
{
  struct edge* nextEd;
  if(node == NULL) return 0; 
  nextEd = node->edges;
  if(!strcmp(node->url, url)) return 1;
  /* Our node is not the node of interest, but the next node it connects
     to might be, and thus we enter this loop */
  else if(nextEd != NULL && nextEd->connectsTo != NULL)
  {
 
    if(node->visited == 1) 
    {
     return 0;
    }
    else 
    {
      /* Place printf here to get nodes visited */
      node->visited = 1;
      if(depthSearchNodes(nextEd->connectsTo, url)) return 1; 
    }
  }
 
  if(nextEd == NULL)
  {
    return 0;
  }
  /* In the case that we reach the end of a node's next node 
,    we enter this loop which will
     cycle through the list of each nodes nodes, checking each one */
  while(nextEd->next != NULL)
  {  
    node->visited = 1;
    /* Place printf here to get nodes visited */
    nextEd = nextEd->next;
    if(depthSearchNodes(nextEd->connectsTo, url)) return 1;
  }   
  return 0;
}
    
/*********************************
 * Function: depthFirstSearch
 * Parameter: g
 *   g is the graph to be searched
 * Parameter: url
 *   url is the url that is being
 *   searched for in the graph    
 * Return: whether the url was 
 *   located
 * depthFirstSearch will conduct 
 *   a depthFirstSearch algorithm 
 *   to find a given url
 * Algorithm: depth first search
 **********************************/
int depthFirstSearch(struct graph* g, char* url)
{
  if(depthSearchNodes(g->firstNode, url))
  {
    resetVisited(g);
    return 1;
  }
  else 
  {
    resetVisited(g);
    return 0;
  }
}
/***********************************
 * breadthFirstSearch
 * Parameter: g 
 *   g is the graph to be searched
 * Parameter: url
 *   url is the url to be searched
 *   for in the graph
 * Return: whether the url was
 *   located
 * breadthFirstSearch will use a 
 *   implemented queue structure
 *   which will add a nodes children
 *   to the queue in order of 
 *   discovery, popping the nodes
 *   off of the queue and then
 *   checking to see if they 
 *   are the node with the url
 *   being searched for
 * Algorithm: breadth first search
 ***********************************/
int breadthFirstSearch(struct graph* g, char* url)
{
  struct QueueItem* qHead = NULL;
  struct edge* nextEd;
  struct node* nextNode = g->firstNode;
  if(!strcmp(nextNode->url, url)) return 1;
  else 
  {
    qHead = pushLast(qHead,(g->firstNode));
    g->firstNode->visited = 1;
    /* We'll pop each node off of the stack and see if its null, then
       compare it */
    while(nextNode != NULL)
    {
      nextEd = nextNode->edges;
      /* We've located our node */
      if(!strcmp(nextNode->url, url))
      {
        while(nextNode!= NULL)
        {
          nextNode = popStack(&qHead);
        }
        resetVisited(g);
	return 1;
      }
      /* Add all of the nodes that our current node connects to
         to the queue of nodes that we need to visit and check */
      while(nextEd !=NULL)
      {
        if(nextEd->connectsTo->visited == 0)
        { 
          qHead = pushLast(qHead, (nextEd->connectsTo));
          nextEd->connectsTo->visited = 1;
        }
        nextEd = nextEd->next;
      }
      nextNode = popStack(&qHead);
      /* Place printf here to see the order of traversal */
      /* Node doesnt exist in our graph */
      if(nextNode == NULL)
      {
        resetVisited(g);
        return 0; 
      }
    }

  }
  resetVisited(g);
  return 0;
}


/*****************************************
 * Function: printPageRank
 * Parameter: g
 *   g is the graph whos nodes are to be
 *   printed
 * Parameter: out
 *   the name of the file to print out to
 * Return: void
 * printPageRank will traverse each node
 *   in the graph, printing its page rank
 *   to 2 decimal places.
 ****************************************/
void printPageRank(struct graph* g, char* out)
{
  FILE* output; 
  struct node *nodeTraverse = g->firstNode;
  output = fopen(out, "w");
  if(output == NULL) return;
  while(nodeTraverse)
  {
    fprintf(output, "%s,%.2f\n", nodeTraverse->url, nodeTraverse->pagerank);
    nodeTraverse = nodeTraverse->next;
  }
  fclose(output);
}
/*************************************
 * Function: insertNToGraph
 * Parameter: g
 *   the graph hae the node 
 *   inserted to
 * Parameter: node
 *   the url of the node to be added
 * Return: void
 * insertNtoGraph will check to see
 *   if a node exists in a graph, 
 *   if it does it will not add it.
 ************************************/
void insertNtoGraph(struct graph* g, char* node) 
{
  struct node *traverse = g->firstNode;
  char* newNode = (char*) malloc(MAXLENGTH * sizeof(char));
  if(traverse != NULL)
  {
    while(traverse)
    {
      if(!strcmp(traverse->url, node)) return;
      traverse = traverse->next;
    }
  }
  strcpy(newNode, node);
  insertNode(g, newNode);
}

/* Slick way to clear strings courtesy of user Bejamin on StackOverflow
 * See:
 * https://stackoverflow.com/questions/8107826/proper-way-to-empty-a-c-string */

/************************************
 * Function: clearStrigns
 * Parameter: str1
 *   the first string to be cleared
 * Parameter: str2
 *   the second string to be cleared
 * Return: void
 * clearStrigns will clear each string
 *   in order to assure an equal 
 *   starting base for each string
 *************************************/
void clearStrings(char* str1, char*str2)
{
  strcpy(str1, "");
  strcpy(str2, "");
}
/**************************************
 * Function: readGraph
 * Parameter: graphFile
 *   a file containing the structure
 *   of the graph to be created.
 * Return: a pointer to the graph 
 * readGraph will accept a file which
 *   contains the structure of a graph.
 *   readGraph will read each line of
 *   the file with the assumption each
 *   line contains a set of two URLs
 *   seperated by a comma with a max
 *   of 50 characters for one URL.
 *   The graph will then use a flag
 *   to assign which url is being 
 *   read to, check if the node exists
 *   and add each to the graph
 **************************************/
struct graph* readGraph(char* graphFile)
{
  FILE* in;
  char c;
  char url1[MAXLENGTH];
  char url2[MAXLENGTH];
  int i = 0, firstURL = 0;
  struct graph* webGraph = createGraph();
  if(graphFile == NULL)
  {
    printf("No input file given, please provide file with graph structure\n");
    return NULL;
  }
  in = fopen(graphFile, "r");
  if(in == NULL) return NULL;
  while( (c = getc(in)) != EOF)
  {
    if(i == MAXLENGTH)
    {
      printf("Node URL too long to be utilized\n");
      printf("Restrict URL size to be at most 50 characters\n");
      return NULL;
    } 
    if(c == ',')
    {
      url1[i] = '\0';
      firstURL = 1;
      i = 0;
      continue;
    }
    else if(c == '\n')
    {
      url2[i] = '\0';
      firstURL = 0;
      insertNtoGraph(webGraph, url1);
      insertNtoGraph(webGraph, url2);
      insertEdge(webGraph, url1, url2);
      i = 0;
      continue;
    }
    if(!firstURL) url1[i] = c;
    else url2[i] = c;
    i++;
  }
  fclose(in);
  return webGraph;
}
    

