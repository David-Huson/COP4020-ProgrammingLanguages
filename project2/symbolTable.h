/******************************************************************************
 * @file symbolTable.h
 * @author David Huson
 * @brief The header with funciton declarations for the symbol table.
 * @date 2023-01-22
 ******************************************************************************/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "hashTable.h"

HashTable* ht;
HashTable* initSymbolTable();
int lookup(char* key);

#endif