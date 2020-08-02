#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Defs.h"

typedef struct hashTable_s *hashTable;

//creates the hash table with all the given functions, and with the size of the hash table
hashTable createHashTable(copyFunction copyKey, freeFunction freeKey,
		printFunction printKey, copyFunction copyValue, freeFunction freeValue,
		printFunction printValue, equalFunction equalKey,
		transformIntoNumberFunction transformKeyIntoNumber, int hashNumber);

//deletes the given hash table and frees all of its memory
status destroyHashTable(hashTable);

//adds the given key and value to the hash table - only if it doesn't exist
status addToHashTable(hashTable, Element key, Element value);

//searches for the given key in the table and if exists returns pointer to its value
Element lookupInHashTable(hashTable, Element key);

//searches for the given key and if exists deletes the key from the table
status removeFromHashTable(hashTable, Element key);

//prints all of the elements in the hash table
status displayHashElements(hashTable);

#endif /* HASH_TABLE_H */
