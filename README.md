# hangman

## Summary
This hangman application solves a game of hangman, where the word is
provided by the user. It reads in a dictionary of words and systematically
eliminates those that are not possible with the current known elements.

### Usage

    $ gcc *.c -o hangman
    $ ./hangman <word> <dictionary>

## Algorithm
It reads in only words of the correct length, which is the only known
variable at the start of the game. Then, it determines the most common
letter. The most common letter is that which appears at least once in
the highest number of words. Letters are not counted multiple times if
the occur more than once in the same letter.

After each guess, the brain eliminates impossible words. If the guess
was correct, it eliminates all words without the correct letters in the
correct positions. If the guess was missed, it eliminates all words that
contain that guess.

It repeats this until either it wins, loses, or determines that the target
word does not exist in its dictionary. It wins if all letters were correctly
guessed, and loses if it reaches six incorrect guesses.

## Issues

### Data Structures
In order to leverage memory vs computing power, possible words are stored
in an ArrayList-like data structure with an underlying array holding the
data. This array is dynamically resized as need be. It allows for quick
retrieval of items, but slower insertions and removals.

### Unsolvable Words
Due to the way the algorithm is set up, there may be words, that exist in
the given dictionary, that will never be guessed. For example, in the
words.txt file provided with this application, the word "wolf" will never
be guessed. The algorithm will narrow the list down to all of the four
letter words with "olf" in them, but will never chose "wolf" before it
runs out of guesses attempting the other words.