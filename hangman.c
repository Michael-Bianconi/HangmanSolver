/**
 * @author Michael Bianconi
 *
 * This program implements an AI that plays Hangman.
 */

#include <stdio.h>
#include <string.h> // strlen, strcmp
#include <unistd.h>
#include "brain.h"
#include "arraylist.h"

#define TRUE 1
#define FALSE 0
typedef unsigned char BOOLEAN;

#define MAX_MISSES 6
#define NUM_CHARACTERS 26
#define LIST_LENGTH 1000

/**
 * Slots the letter into the phrase whereever it exists in
 * the answer. Note, the letter may already be discovered.
 * This function will still return TRUE.
 *
 * @param phrase Null terminated string the same size as the answer.
 * @param answer Null terminated string that contains the answer.
 * @param letter Letter to discover.
 * @return Returns TRUE if a letter was discovered, FALSE otherwise.
 */
static BOOLEAN discover(char* phrase, char* answer, char letter)
{
    unsigned long index = 0;
    BOOLEAN discovered = FALSE;

    while (answer[index])
    {
        if (answer[index] == letter)
        {
            phrase[index] = letter;
            discovered = TRUE;
        }

        index++;
    }

    return discovered;
}


/**
 * Adds the letter to the string of letters.
 *
 * @param buffer Buffer holding the characters.
 * @param letter Letter to add.
 */
static char* addLetter(char* buffer, char letter)
{
    unsigned long index = 0;

    while (buffer[index]) index++;
    buffer[index] = letter;
    buffer[index+1] = '\0';

    return buffer;
}

/**
 * Checks if the letter exists in the string.
 *
 * @param string String to check.
 * @param letter Letter to check.
 * @return Returns TRUE if the letter exists in the string, FALSE otherwise.
 */
static BOOLEAN existsIn(char* string, char letter)
{
    unsigned long index = 0;
    while (string[index]) if (string[index++] == letter) return TRUE;
    return FALSE;
}

/**
 * Checks if the game has been won (the phrase matches the answer).
 *
 * @param phrase Phrase to check.
 * @param answer Answer to check.
 * @return Returns TRUE if the game has been won, FALSE otherwise.
 */
static BOOLEAN gameWon(char* phrase, char* answer)
{
    return strcmp(phrase, answer) == 0;
}

/**
 * Checks if the game has been lost (the number of misses is
 * greater than or equal to MAX_MISSES).
 *
 * @param misses The letters missed.
 * @return Returns TRUE if the game has been lost, FALSE otherwise.
 */
static BOOLEAN gameLost(char* missed)
{
    return strlen(missed) >= MAX_MISSES;
}

/**
 * Copies the answer into the phrase, with all letters as _.
 * Spaces are copied directly.
 *
 * @param phrase Phrase being copied into.
 * @param answer Answer being copied from.
 * @return Returns phrase.
 */
static char* initPhrase(char* phrase, char* answer)
{
    unsigned long index = 0;

    while (answer[index])
    {
        if (answer[index] == ' ') phrase[index] = ' ';
        else                      phrase[index] = '_';

        index++;
    }

    phrase[index] = '\0';
    return phrase;
}

/**
 * Attempts the given letter. If the correct, it is discovered
 * in the phrase. If it is incorrect, it is added to the list
 * of missed letters. It is always added to the list of
 * attempted letters.
 *
 * @param phrase Phrase being attempted.
 * @param answer Answer to te phrase.
 * @param attempts All attempted letters.
 * @param missed All missed letters.
 * @param letter Letter to attempt.
 * @return Returns TRUE if the letter was correct.
 */
static BOOLEAN guessLetter(
    char* phrase, char* answer, char* attempts, char* missed, char letter)
{

    if (existsIn(attempts, letter)) return FALSE; // Letter already guessed
    addLetter(attempts, letter);
    if (discover(phrase, answer, letter)) return TRUE; // Letter discovered!
    addLetter(missed, letter); // Letter missed
    return FALSE;
}

/**
 * Prints out the hangman.
 *
 * @param phrase The possibly undiscovered phrase being guessed.
 * @param missed The characters incorrectly guessed.
 */
static void printHangman(char* phrase, char* missed)
{
    size_t fails = strlen(missed);

    printf("\nMissed: [%s]\n", missed);

                            printf("|-------|  \n");
                            printf("|/      |  \n");
    if (fails > 0)        { printf("|       O  \n"); }
    else                  { printf("|          \n"); }
    if (fails >= 4)       { printf("|      /|\\\n"); }
    else if (fails == 3)  { printf("|      /|  \n"); }
    else if (fails == 2)  { printf("|       |  \n"); }
    else                  { printf("|          \n"); }
    if (fails == 6)       { printf("|      / \\\n"); }
    else if (fails == 5)  { printf("|      /   \n"); }
    else                  { printf("|          \n"); }
                            printf("|          \n");
                            printf("---------  \n");

    printf("Phrase: %s\n\n", phrase);
}

int main(int argc, char** argv)
{
    // Invalid arguments
    if (argc <= 2 || argc >= 4)
    {
        fprintf(stderr, "Usage: ./hangman <word> <dictionary>\n");
        return 1;
    }

    char* answer = argv[1];        // provided word to guess
    char phrase[strlen(answer)+1]; // the known letters in the word
    char missed[NUM_CHARACTERS];   // incorrectly guessed letters
    char attempted[NUM_CHARACTERS];// all guessed letters
    initPhrase(phrase, answer);    // initialize the given phrase

    missed[0] = '\0';
    attempted[0] = '\0';

    // Open the dictionary and build the list from it
    FILE* in = fopen(argv[2], "r");
    if (!in)
    {
        fprintf(stderr, "Bad dictionary: %s\n", argv[2]);
        return 1;
    }
    ArrayList list = buildFromFile(in, strlen(answer));
    while (1)
    {
        printHangman(phrase, missed);

        printf("%lu possible words\n", list->size);

        // The answer was found
        if (gameWon(phrase, answer))
        {
            printf("Brain won!\n");
            break;
        }

        // The guesses limit was reached
        if (gameLost(missed))
        {
            printf("Brain lost!\n");
            break;
        }

        char letter = mostCommonLetter(attempted, list);
        if (!letter)
        {
            printf("The word doesn't exist in the dictionary!\n");
            break;
        }

        printf("Guessing: %c\n", letter);

        // Check if the letter was correct
        guessLetter(phrase, answer, attempted, missed, letter);

        // Amend the list of possible words, based on the guess
        eliminate(phrase, missed, list);
    }

    // Close resources
    ArrayList_free(list);
    fclose(in);

}