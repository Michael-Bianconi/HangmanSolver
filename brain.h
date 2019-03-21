#ifndef BRAIN_H
#define BRAIN_H

#include "list.h"

List buildFromFile(List, FILE*, unsigned long);
void eliminate(char*, char*, List);
unsigned char isPossible(char*, char*, char*);
char mostCommonLetter(char*, List);

#endif