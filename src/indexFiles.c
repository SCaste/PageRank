/*********************************/
/* Sage Castiglione              */
/* CS241                         */
/* April 29 2018                 */
/* indexFiles.c will implement   */
/* indexFiles.h, which will      */
/* hash each token in a given    */
/* webpage, and place them into  */
/* a hashtable.                  */
/*********************************/

#include "graphUtils.h"
#include "hashtable.h"
#include "indexFiles.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELIMITER " .,/""\\+-<>;:\n\t\r—[]()?!1234567890–\"\"\"'"
#define LETTERCOUNT 28 

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
char* doCaseCorrection(char* str)
{
  int i = 0;
  while(str[i])
  {
    if (str[i] < 91 && str[i] > 64)
    {
      str[i] = str[i] + 32;
    }
    i++;
  }
  return str;
}
/**********************************
 * Function: makeElt 
 * Parameter: str
 *   the token of the given element
 *   to be made
 * Parameter: url
 *   the url of the element
 * Parameter: g
 *  the graph where the url resides
 * Return: the made element
 * makeElt will create an element
 *   that will have the url 
 *   assigned as provided, as with
 *   the token. The pagerank will
 *   be located from the graph that
 *   is provided to the function.
 ************************************/
struct HashElt* makeElt(char* str, char* url, struct graph* g)
{
  struct HashElt* returnHE =
      (struct HashElt*) malloc(1 * sizeof(struct HashElt));
  char* str2 = malloc(sizeof(str));
  strcpy(str2, str);
  returnHE->url = url;
  returnHE -> pageRank = getPagerank(url, g);
  returnHE->token = str2;
  returnHE->next = NULL;
  return returnHE; 
}
/****************************
 * Function: clearString
 * Parameter: str
 *   the string to be cleared
 * Return: void
 * clearString clears the
 *   provided string. See
 *   comment in hashtable
 *   for credits to this 
 *   function
 ****************************/
void clearString(char* str)
{
  strcpy(str, "");
}
/***************************************
 * Function: getFileLength
 * Parameter: file
 *   the file whos length is to be
 *   collected. It is assumed file 
 *   will not be null. 
 * Return: length of the file 
 * getFileLength will seek to the end of 
 *   a file and then return that position
 *   before rewinding to get the length
 *   of a file in characters used. 
 ****************************************/
int getFileLength(FILE* file)
{
  int length;
  fseek(file, 0, SEEK_END);
  length = ftell(file);
  rewind(file);
  return length;
}
  
/************************************
 * Function: readInFile
 * Parameter: fn
 *   fn is a node which contains the
 *   page (or filename) to be read in
 * Parameter: table
 *   table is the table to insert the
 *   tokens to
 * Parameter: g
 *   the graph the node is from
 * Return: void
 * readInFile will take a node which
 *   represents a file, and read its
 *   contents, inserting it into our
 *   table using the graph information 
 *   to accurately collect pagerank
 **************************************/
void readInFile(struct node* fn, struct HTable* table, struct graph* g)
{
  FILE* in = fopen(fn->url, "r");
  char* inputLine;
  char* token = (char*) calloc(LETTERCOUNT , sizeof(char));
  int fileSize;
  if(fn == NULL) return;
  if(g == NULL) return;
  if(in == NULL) 
  {
    printf("Cannot locate %s, check that it is in the working directory.\n", 
            fn->url);
    return;
  }
  fileSize = getFileLength(in); 
  inputLine = (char*) malloc(fileSize * sizeof(char));
  clearString(inputLine);
  clearString(token);
  while(fgets(inputLine, fileSize,  in))
  { 
    token = strtok(inputLine, DELIMITER);
    if(token == NULL) continue;
    insert(makeElt(doCaseCorrection(token), fn->url, g), table);
    token = strtok(NULL, DELIMITER);
    while(token != NULL)
    {
      insert(makeElt(doCaseCorrection(token), fn->url, g), table);
      clearString(token);
      token = strtok(NULL, DELIMITER);
    }
    clearString(inputLine);
  }
  free(inputLine);
  fclose(in); 
}
