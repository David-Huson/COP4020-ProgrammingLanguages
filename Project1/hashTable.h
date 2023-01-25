#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "baseTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 49999

typedef struct Entity {
  char* key;
  int value;
  struct Entity* next;
} Entity;

typedef struct HashTable {
  Entity** entities;
  int numEntities;
  int size;
} HashTable;

int hash(const char* key);
HashTable* createTable();
Entity* pair(const char* key, const int value);
void set(HashTable* table, const char* key, const int value);
int get(HashTable* table, const char* key);
// void del(HashTable* table, const char* key);
void dump(HashTable* table);
void dumpType(HashTable* table, int type);
void destroy(HashTable* table);

#endif