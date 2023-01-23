#include "symbolTable.h"
#include "baseTypes.h"

HashTable* initSymbolTable() {
  ht = createTable();
  set(ht, ID, 300);
  set(ht, NUM, 301);
  set(ht, BEGIN, 400);
  set(ht, END, 401);
  set(ht, NOT_FOUND, -1);
  set(ht, DONE, 0);

  return ht;
}

int lookup(char* key) { return get(ht, key); }
