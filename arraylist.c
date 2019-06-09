/**
 * @author Michael Bianconi
 * @since 04-02-2019
 *
 * Source code for ArrayList.h.
 */
#include "arraylist.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <stdarg.h> // valist
#include <string.h> // strcpy

void ArrayList_add(ArrayList list, char* item)
{
	// Copy the item into a buffer
	char* data = malloc(strlen(item) + 1);
	strcpy(data, item);

	// ArrayList memory allocation reached, double allocation
	if (list->size == list->buffer) ArrayList_expand(list, list->buffer);

	// Add the item to the list
	list->items[list->size] = data;
	list->size++;
}


ArrayList ArrayList_create(size_t size)
{
	// Size cannot be 0
	if (size == 0)
	{
		return NULL;
	}

	// Construct list and allocate memory
	ArrayList list = malloc(sizeof(struct ArrayList_s));
	list->size = 0;
	list->buffer = size;
	list->items = malloc(list->buffer * sizeof(char*));

	return list;
}


void ArrayList_expand(ArrayList list, size_t amount)
{
	list->buffer += amount;
	list->items = realloc(list->items, list->buffer * sizeof(char*));
}


void ArrayList_free(ArrayList list)
{
	// Free all items held by the list
	for (size_t i = 0; i < list->size; i++)
	{
		free(list->items[i]);
	}

	// Free the parent array
	free(list->items);

	// Free the list itself
	free(list);
}


char* ArrayList_get(ArrayList list, size_t n)
{
	// Index out of bounds
	if (n >= list->size)
	{
		return NULL;
	}

	return list->items[n];
}


void ArrayList_remove(ArrayList list, size_t n)
{
	// index out of bounds
	if (n >= list->size)
	{
		return;
	}

	// free the removed item
	free(list->items[n]);

	// shift everything down to fill the gap
	for (size_t i = n + 1; i < list->size; i++)
	{
		list->items[i-1] = list->items[i];
	}

	list->size--;
}


void ArrayList_trim(ArrayList list)
{
	// trim the buffer down to size + 1
	list->buffer = list->size + 1;
	list->items = realloc(list->items, list->buffer * sizeof(char*));
}
