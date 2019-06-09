/**
 * @author Michael Bianconi
 * @since 04-02-2019
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>

// STRUCT DEFINITION ==========================================================

/**
 * ArrayList_s is a dynamically-resizing array of strings.
 */
struct ArrayList_s
{
	/** The current max elements that can be in memory. */
	size_t buffer;

	/** The current number of elements in the ArrayList. */
	size_t size;

	/** The data held by this ArrayList. */
	char** items;
};

typedef struct ArrayList_s* ArrayList;

// FUNCTION DECLARATION =======================================================


/**
 * Adds a new Element to the given ArrayList. If the new
 * element would otherwise exceed the buffer, then
 * ArrayList_expand() is called.
 *
 * @param list ArrayList to add to.
 * @param item Item to copy into the List.
 */
void ArrayList_add(ArrayList list, char* item);


/**
 * Construct a new ArrayList with the default given size.
 * 
 * @param size Allocate enough space to hold this many items.
 *             ArrayList will never resize under this amount.
 *             May not be 0.
 * @return Returns the constructed ArrayList.
 */
ArrayList ArrayList_create(size_t size);


/**
 * Increases the size of the ArrayList's buffer. Called automatically
 * when adding an item that exceeds the allocated memory.
 *
 * @param list List to expand.
 * @param amount Amount to expand by.
 */
void ArrayList_expand(ArrayList list, size_t amount);


/**
 * Frees all memory allocated by this ArrayList.
 *
 * @param list ArrayList to free.
 */
void ArrayList_free(ArrayList list);


/**
 * Retrieves a pointer to the n'th item from the ArrayList.
 *
 * @param list ArrayList to retrieve from.
 * @param n Index to retrieve at.
 * @return Returns the n'th item, or null if out of bounds.
 * @see ArrayList_getCopy()
 */
char* ArrayList_get(ArrayList list, size_t n);


/**
 * Removes an element from the ArrayList. Shifts all others down
 * to fill the gap. Does not resize the array.
 *
 * @param list ArrayList to alter.
 * @param n Remove the n'th item in the list.
 */
void ArrayList_remove(ArrayList list, size_t n);


/**
 * Trims unneeded memory space from the ArrayList's buffer.
 * Use if the size of the list decreased dramatically.
 * Reduces buffer to current list size + 1.
 *
 * @param list ArrayList to trim.
 */
void ArrayList_trim(ArrayList list);


#endif