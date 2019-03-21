/**
 * @author Michael Bianconi
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

struct List
{
	size_t length;   // Number of items in the list.
	size_t buffer;   // Maximum number of items before resize.
	size_t datasize; // Number of characters reserved for each string.
	char* data;		 // Strings held.
};

typedef struct List* List;

/**
 * Allocates enough memory for length number of strings, delimited
 * by \0.
 *
 * @param length Number of strings to hold.
 * @param datasize Largest string possible.
 * @return Returns malloc'd pointer to the new list.
 */
List listCreate(size_t length, size_t datasize);

/**
 * @param list List to retrieve from.
 * @param n N'th index to retrieve.
 * @param buffer Buffer to store the data.
 * @return Returns the n'th item in the List, or NULL
 *         if out of bounds.
 */
char* listGet(List list, unsigned long n, char* buffer);

/**
 * Adds the data to the list. If the list needs more
 * space, reallocates it.
 *
 * @param list List to add to.
 * @param data Data to add.
 */
void listAdd(List list, char* data);

/**
 * Removes the item from the list and returns it.
 * Shift all other items down to fill the gap.
 *
 * @param list List to alter.
 * @param n Index of item to remove.
 * @param buffer Holds the returned data. Can be null.
 * @return Returns the item at the given index.
 */
char* listRemove(List list, unsigned long n, char* buffer);

/**
 * Sets the data at the given node. If the index is out of
 * bounds, do nothing.
 *
 * @param list List to alter.
 * @param n Index to alter.
 * @param data New data to fill.
 * @return Returns 1 if successfully set, 0 otherwise.
 */
unsigned char listSet(List list, unsigned long n, char* data);

/**
 * Frees all memory in the list.
 *
 * @param list List to free.
 */
void listDestroy(List list);

/**
 * Prints everything in the list.
 *
 * @param list List to print.
 */
void listPrint(List list);

#endif