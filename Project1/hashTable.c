#include "hashTable.h"

int
hash(const int key)
{
  return key % MAX_CAPACITY;
}

HashTable*
createTable()
{
  // allocate memory for the table
  HashTable* table = malloc(sizeof(HashTable));

  // allocate memory for the entities in the table (the data)
  table->entities = malloc(sizeof(Entity*) * MAX_CAPACITY);

  for (int i = 0; i < MAX_CAPACITY; ++i)
    table->entities[i] = NULL;

  return table;
}

Entity*
pair(const int key, const char* value)
{
  Entity* entity = malloc(sizeof(Entity) * 1);
  entity->value = malloc(strlen(value) + 1);
  entity->key = key;
  strcpy(entity->value, value);

  // next starts out null but may be set later on
  entity->next = NULL;

  return entity;
}

void
set(HashTable* table, const int key, const char* value)
{
  unsigned int slot = hash(key);

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
    if (entity->key == key) {
      // match found, replace value
      free(entity->value);
      entity->value = malloc(strlen(value) + 1);
      strcpy(entity->value, value);
      return;
    }

    // walk to next
    prev = entity;
    entity = prev->next;
  }

  // end of chain reached without a match, add new
  prev->next = pair(key, value);
}

char*
get(HashTable* table, const int key)
{
  unsigned int slot = hash(key);

  // try to find a valid slot
  Entity* entity = table->entities[slot];

  // no slot means no entry
  if (entity == NULL) {
    return NULL;
  }

  while (entity != NULL) {
    // return value if found
    if (entity->key == key) {
      return entity->value;
    }

    entity = entity->next;
  }
  return NULL;
}

void
del(HashTable* table, const int key)
{
  unsigned int bucket = hash(key);

  // try to find a valid bucket
  Entity* entity = table->entities[bucket];

  // no bucket means no entry
  if (entity == NULL) {
    return;
  }

  Entity* prev;
  int idx = 0;

  // walk through each entry until either the end is reached or a matching key
  // is found
  while (entity != NULL) {
    // check key
    if (entity->key == key) {
      // first item and no next entry
      if (entity->next == NULL && idx == 0) {
	table->entities[bucket] = NULL;
      }

      // first item with a next entry
      if (entity->next != NULL && idx == 0) {
	table->entities[bucket] = entity->next;
      }

      // last item
      if (entity->next == NULL && idx != 0) {
	prev->next = NULL;
      }

      // middle item
      if (entity->next != NULL && idx != 0) {
	prev->next = entity->next;
      }

      // free the deleted entry
      free(entity->value);
      free(entity);

      return;
    }

    // walk to next
    prev = entity;
    entity = prev->next;

    ++idx;
  }
}

void
destroy(HashTable* table)
{
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
	if (entity->value) {
	  free(entity->value);
	  entity->value = NULL;
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

void
print(HashTable* table)
{
  for (int i = 0; i < MAX_CAPACITY; ++i) {
    Entity* entity = table->entities[i];

    if (entity == NULL) {
      continue;
    }

    printf("slot[%4d]: ", i);

    while (1) {
      printf("%d=%s ", entity->key, entity->value);

      if (entity->next == NULL) {
	break;
      }

      entity = entity->next;
    }

    printf("\n");
  }
}