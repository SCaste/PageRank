#ifndef INDEXFILES_H
#define INDEXFILES_H
#include "graph.h"
/* Reads in a file and stores each element in the hashtable */
/* Ensure that a file name 'fn' is in the current working directory */
void readInFile(struct node* fn, struct HTable* table, struct graph* g);
/************************************
 * Function: doCaseCorrection
 * Parameter: str
 *   the string to be case corrected
 * Return: the pointer back to the 
 *   string
 * if the character in the string is 
 *   between the uppercase ascii 
 *   range, then 32 is added to make
 *   it its equivalent lower case 
 *   value
 ***********************************/
char* doCaseCorrection(char* str);

#endif
