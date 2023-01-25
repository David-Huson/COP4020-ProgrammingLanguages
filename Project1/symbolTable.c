#include "symbolTable.h"
#include "baseTypes.h"

HashTable* initSymbolTable() {
  ht = createTable(12);
  return ht;
}

int lookup(char* key) { return get(ht, key); }
