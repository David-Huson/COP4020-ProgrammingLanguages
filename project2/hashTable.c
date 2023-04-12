/******************************************************************************
 * @file hashTable.c
 * @author David Huson
 * @brief A hashtable using separate chaining. Supports Inserting, searching,
 * and dumping the contents of either the entire table or all the keys with a
 * specific value.
 * @date 2023-01-22
 ******************************************************************************/
#include "hashTable.h"

/**
 * @brief String Rolling hash function.
 * Sums the values of the string 4 bytes at a time. Every 4th byte is
 * interpreted as a single long integer.
 * @param key the key to hash
 * @return int the hashed index of the key
 */

int hash(const char* key) {
  int index = 0;
  int c;

  // some sekC assignment trickery
  while ((c = *key++))
    index = ((MAX_CAPACITY << 5) + MAX_CAPACITY) + c;

  return index % MAX_CAPACITY;
}

HashTable* createTable() {
  // allocate memory for the table
  HashTable* table = malloc(sizeof(HashTable));

  // allocate memory for the entities in the table (the data)
  table->entities = malloc(sizeof(Entity*) * MAX_CAPACITY);
  table->numEntities = 0;

  for (int i = 0; i < MAX_CAPACITY; ++i)
    table->entities[i] = NULL;

  return table;
}

// Creates a single key value pair
Entity* pair(const char* key, const int value) {
  Entity* entity = malloc(sizeof(Entity) * 1);
  entity->key = malloc(strlen(key) + 1);
  strcpy(entity->key, key);
  entity->value = value;

  // next starts out null but may be set later on
  entity->next = NULL;

  return entity;
}

// insert a key and value into the table
void set(HashTable* table, const char* key, const int value) {
  int slot = hash(key);

  // try to look up an entity set
  Entity* entity = table->entities[slot];

  // no entity means slot empty, insert immediately
  if (entity == NULL) {
    table->entities[slot] = pair(key, value);
    return;
  }

  Entity* prev;

  // walk through each entity until either the end is
  // reached or a matching key is found
  while (entity != NULL) {
    // check key
    if (strcmp(entity->key, key) == 0) {
      // match found, replace value
      entity->value = value;
      return;
    }

    // walk to next
    prev = entity;
    entity = prev->next;
  }

  // end of chain reached without a match, add new
  prev->next = pair(key, value);
}

// search for a specific value by its key
int get(HashTable* table, const char* key) {
  int slot = hash(key);

  // try to find a valid slot
  Entity* entity = table->entities[slot];
  // printf("The entity at slot %d is %d\n", slot, entity->value);

  while (entity != NULL) {
    // return value if found
    if (strcmp(entity->key, key) == 0) {
      return entity->value;
    }

    entity = entity->next;
  }
  return NOT_FOUND;
}

// destroy the entire hashtable and free all memory allocated
void destroy(HashTable* table) {
  if (!table)
    return;
  size_t i = 0;
  if (table->entities) {
    // Free all entries
    Entity* current;
    while (i < MAX_CAPACITY) {
      Entity* entity = table->entities[i];
      while (1) {
        if (entity == NULL) {
          break;
        }
        if (entity->key) {
          free(entity->key);
          entity->value = 0;
        }
        current = entity;
        entity = entity->next;
        free(current);
      }
      i++;
    }
    // Free the entry list pointer
    free(table->entities);
    table->entities = NULL;
  }

  // Free the hashtable pointer
  free(table);
  table = NULL;
  return;
}

// print all the contents of the hash table
void dump(HashTable* table) {
  printf("slot[    ] key = value\n");
  for (int i = 0; i < MAX_CAPACITY; ++i) {
    Entity* entity = table->entities[i];

    if (entity == NULL) {
      continue;
    }

    while (1) {
      printf("slot[%4d]: ", i);
      printf("%s=%d\n", entity->key, entity->value);

      if (entity->next == NULL) {
        break;
      }

      entity = entity->next;
    }
  }
}

// print all the keys of a given type
void dumpType(HashTable* table, int type) {
  printf("printing all identifiers...\n");
  if (type == ID)
    printf("Identifiers: [ ");

  for (int i = 0; i < MAX_CAPACITY; ++i) {
    Entity* entity = table->entities[i];

    if (entity == NULL) {
      continue;
    }

    while (1) {
      if (entity->value == type) {
        printf("%s, ", entity->key);

        if (entity->next == NULL) {
          break;
        }
        entity = entity->next;
      }
      if (entity->next == NULL) {
        break;
      }
    }
  }
  printf("]\n");
}