# hangman

## Summary
This hangman application solves a game of hangman, where the word is
provided by the user. It reads in a dictionary of words and systematically
eliminates those that are not possible with the current known elements. The
provided dictionary, words.txt contains over 85,000 words. However, it does
not contain words with fewer than 4 letters, proper nouns, words with
capital letters, or words with symbols. Dictionaries with these words
included are permitted, but the brain will most likely never guess them.

### Usage

    $ gcc *.c -o hangman
    $ ./hangman <word> <dictionary>

## Algorithm
It reads in only words of the correct length, which is the only known
variable at the start of the game. Then, it determines the most common
letter. The most common letter is that which appears at least once in
the highest number of words. Letters are not counted multiple times if
they occur more than once in the same word.

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

#### ArrayList (07 April 2019)

Replaced previous List structure with dedicated, fully featured
[ArrayList](https://github.com/Michael-Bianconi/ArrayList) structure.
When tested with the answer "shirt" and dict.txt, the number of mallocs and
frees were reduced from 12,453 to 6,731. The total bytes allocated was
reduced from 268 megabytes to 783 <i>kilobytes</i>, reducing total
memory allocation by \~99.7%.

### Unsolvable Words
Due to the way the algorithm is set up, there may be words, that exist in
the given dictionary, that will never be guessed. For example, in the
words.txt file provided with this application, the word "wolf" will never
be guessed. The algorithm will narrow the list down to all of the four
letter words with "olf" in them, but will never chose "wolf" before it
runs out of guesses attempting the other words.
