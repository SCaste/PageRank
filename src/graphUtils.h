/*************************************/
/* Sage Castiglione                  */
/* CS241                             */
/* graphUtils.h contains specific    */ 
/* definitions for                   */
/* the graphUtils.c file to be       */
/* utilized by other files for       */
/* calculating pageRank and          */
/* conducting searches               */
#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H
#include "graph.h"
#include "queue.h"
float getPagerank(char* url, struct graph* g);
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
void calculatePageRank(struct graph* g);

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
void printPageRank(struct graph* g, char* out);

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
struct graph* readGraph(char* graphFile);
#endif
