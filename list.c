/**
 * @author Michael Bianconi
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

List listCreate(size_t length, size_t datasize)
{
	List list = malloc(sizeof(struct List));
	list->length = 0;
	list->buffer = length * datasize;
	list->datasize = datasize;
	list->data = malloc(list->buffer);
	list->data[0] = '\0';
	return list;
}


void listDestroy(List list)
{
	if (!list) return;
	free(list->data);
	free(list);
}


char* listGet(List list, unsigned long n, char* buffer)
{
	if (n > list->length) return NULL;

	if (buffer)
	{
		strncpy(buffer, list->data+(n * list->datasize), list->datasize);
	}
	//printf("%s\n", buffer);
	return buffer;
}


unsigned char listSet(List list, unsigned long n, char* data)
{
	if (!list || n >= list->length) return 0;

	strncpy(list->data+n*list->datasize, data, list->datasize);
	return 1;
}


void listAdd(List list, char* data)
{
	if (list->length * list->datasize >= list->buffer)
	{
		list->data = realloc(list->data, list->buffer + list->datasize);
		list->buffer += list->datasize;
	}

	strncpy(list->data+((list->length)*list->datasize), data, list->datasize);
	list->length++;

	return;
}


char* listRemove(List list, unsigned long n, char* buffer)
{
	// Check in bounds
	if (n > list->length-1) return NULL;

	// If applicable, copy the data into the buffer
	if (buffer)
	{
		strncpy(buffer, list->data+(n*list->datasize), list->datasize);
	}

	// Create a new buffer to store the data
	char* newdata = malloc((list->length) * list->datasize);

	// For each item in the list
	for (long i = 0; i < (long) list->length-1; i++)
	{
		// If we've reached the given index, jump over it
		unsigned long offset = i > (long)(n)-1 ? list->datasize : 0;
		unsigned long newStart = i*list->datasize;
		unsigned long oldStart = (i*list->datasize) + offset;

		strncpy(newdata+newStart, list->data+oldStart, list->datasize);
	}

	free(list->data);
	list->data = newdata;
	list->length--;
	list->buffer -= list->datasize;

	return buffer;
}


void listPrint(List list)
{

	printf("[");
	for (unsigned long i = 0; i < list->length; i++)
	{
		printf("\"%s\",", list->data+(i*list->datasize));
	}
	printf("]\n");
}