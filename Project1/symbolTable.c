/******************************************************************************
 * @file symbolTable.c
 * @author David Huson
 * @brief Provides a abstraction for initializing a hash table with a lookup
 *function
 * @date 2023-01-22
 ******************************************************************************/

#include "symbolTable.h"
#include "baseTypes.h"

HashTable* initSymbolTable() {
  ht = createTable(12);
  return ht;
}

int lookup(char* key) { return get(ht, key); }
