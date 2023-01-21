#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "hashTable.h"

HashTable* init() {
  HashTable* ht = createTable();
  set(ht, 300, "ID");
  set(ht, 301, "NUM");
  set(ht, 400, "BEGIN");
  set(ht, 401, "END");
  set(ht, 404, "NOT_FOUND");

  return ht;
}

#endif