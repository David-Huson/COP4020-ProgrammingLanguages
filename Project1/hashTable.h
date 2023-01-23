#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 49999
#define ID           "id"
#define NUM          "num"
#define BEGIN        "begin"
#define END          "end"
#define NOT_FOUND    "not_found"
#define DONE         "done"

typedef struct Entity {
  char* key;
  int value;
  struct Entity* next;
} Entity;

typedef struct HashTable {
  Entity** entities;
} HashTable;

int hash(const char* key);
HashTable* createTable();
Entity* pair(const char* key, const int value);
void set(HashTable* table, const char* key, const int value);
int get(HashTable* table, const char* key);
void del(HashTable* table, const char* key);
void dump(HashTable* table);
void destroy(HashTable* table);

#endif