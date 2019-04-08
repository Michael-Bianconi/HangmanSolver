/**
 * @author Michael Bianconi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strncpy
#include <ctype.h> // isalpha
#include "trimit.h"
#include "brain.h"
#include "arraylist.h"


/**
 * Retrieves the number of lines in the given file.
 * Dictionaries should have only one word per line.
 *
 * @param in File to line count. Must be opened to a valid
 *           file.
 * @return Returns the number of lines in the dictionary.
 */
static size_t getFileLength(FILE* in)
{
	size_t numLines = 0;

	while (EOF != fscanf(in, "%*[^\n]") && EOF != fscanf(in,"%*c"))
	    ++numLines;

	return numLines;
}


/**
 * Populates a queue with every word in the file containing
 * the same number of characters as the given answer.
 *
 * @param queue Holds possibilities. Must have large enough datasize.
 * @param in File to look in.
 * @param length Length to look for.
 * @return Returns buffer.
 */
ArrayList buildFromFile(FILE* in, unsigned long answerLength)
{

	size_t fileLength = getFileLength(in);
	ArrayList list = ArrayList_create(fileLength);

	unsigned long lineSize = 0;
	char* lineBuffer = NULL;

	// Go to the beginning of the file
	fseek(in, 0, SEEK_SET);

	// Add every line from the file where the line length == given length
    while (getline(&lineBuffer, &lineSize, in) != -1) {
    	if (strlen(trim(lineBuffer)) == answerLength)
    	{
    		ArrayList_add(list, trim(lineBuffer));
    	}
    }

    if (lineBuffer) free(lineBuffer);
    ArrayList_trim(list);

    return list;
}

/**
 * Create a new Queue from the old one, copying only those queues that
 * are still possibilities for the phrase. Frees the old queue.
 */
void eliminate(char* phrase, char* missed, ArrayList list)
{
	for (unsigned long i = 0; i < list->size; i++)
	{

		char* word = ArrayList_get(list, i);

		if (!isPossible(phrase, missed, word))
		{
			ArrayList_remove(list, i);
			i--;
		}
	}
	return;
}

/**
 * Checks if, of the discovered letters, those letters are the
 * same in the word.
 *
 * @param phrase Phrase to check.
 * @param word Guessed word to check.
 * @return Returns 1 if TRUE, 0 if FALSE.
 */
unsigned char isPossible(char* phrase, char* missed, char* word)
{
	unsigned long index = 0;

	while (phrase[index])
	{
		// Letter doesnt match the word
		if (isalpha(phrase[index]) && phrase[index] != word[index])
		{
			return 0;
		}

		// Letter already attempted
		unsigned long a = 0;
		while (missed[a])
		{
			if (word[index] == missed[a])
			{
				return 0;
			}
			a++;
		}

		index++;
	}
	return 1;
}

/**
 * Find the letter most common to the words in the
 * queue, ignoring those that have already been attempted.
 *
 * @param attempts All letters already used.
 * @param queue Possible words.
 * @return Returns the most common letter.
 */
char mostCommonLetter(char* attempts, ArrayList list)
{
	unsigned long letters[26] =
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (unsigned long i = 0; i < list->size; i++)
	{
		char* buffer = ArrayList_get(list, i);

		unsigned long lettersInWord[26] =
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		// Get all of the letters in the word
		unsigned long dataIdx = 0;
		while (buffer[dataIdx])
		{
			lettersInWord[buffer[dataIdx] - 'a']++;
			dataIdx++;
		}

		// If it appeared once, add to the letters
		for (int i = 0; i < 26; i++)
		{
			if (lettersInWord[i]) letters[i]++;
		}
	}

	// Remove all letters already attempted
	unsigned long index = 0;

	while (attempts[index])
	{
		letters[attempts[index] - 'a'] = 0;
		index++;
	}

	// Return the most common letter
	unsigned long mostCommon = 0;
	char letter = '\0';

	for (int i = 0; i < 26; i++)
	{
		if (letters[i] > mostCommon)
		{
			mostCommon = letters[i];
			letter = i + 'a';
		}
	}

	return letter;
}