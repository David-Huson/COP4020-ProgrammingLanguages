#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 49999

typedef struct Entity{
    int key;
	char* value;
    struct Entity* next;
}Entity;

typedef struct HashTable{ 
	Entity** entities;
}HashTable; 

int hash(const int key);
HashTable* createTable();
Entity* pair(const int key, const char *value);
void set(HashTable* table, const int key, const char* value);
char* get(HashTable* table, const int key);
void del(HashTable* table, const int key);
void print(HashTable* table);

#endif