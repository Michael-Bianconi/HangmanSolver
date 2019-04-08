#ifndef BRAIN_H
#define BRAIN_H

#include "arraylist.h"

ArrayList buildFromFile(FILE*, unsigned long answerLength);
void eliminate(char*, char*, ArrayList);
unsigned char isPossible(char*, char*, char*);
char mostCommonLetter(char*, ArrayList);

#endif