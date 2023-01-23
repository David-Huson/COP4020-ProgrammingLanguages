#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "hashTable.h"

HashTable* ht;

HashTable* initSymbolTable();
int lookup(char* key);

#endif