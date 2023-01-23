#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "hashTable.h"

HashTable* ht;

HashTable* init();
int lookup(char* key);

#endif