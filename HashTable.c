#include "HashTable.h"
#include "KeyValuePair.h"
#include  "LinkedList.h"

//represents the hash table
struct hashTable_s {
	copyFunction copyKeyElement;
	freeFunction freeKeyElement;
	printFunction printKeyElement;
	equalFunction equalKeyElement;
	copyFunction copyValueElement;
	freeFunction freeValueElement;
	printFunction printValueElement;
	transformIntoNumberFunction transformKeyIntoNumber;
	int hashNumber;
	List *hashTableArray;
};

//creates the hash table with all the given functions, and with the size of the hash table
hashTable createHashTable(copyFunction copyKey, freeFunction freeKey,
		printFunction printKey, copyFunction copyValue, freeFunction freeValue,
		printFunction printValue, equalFunction equalKey,
		transformIntoNumberFunction transformKeyIntoNumber, int hashNumber) {

	if (copyKey == NULL || freeKey == NULL || equalKey == NULL
			|| printKey == NULL || copyValue == NULL || freeValue == NULL
			|| printValue == NULL || transformKeyIntoNumber == NULL)
		return NULL;
	hashTable hash = (hashTable) malloc(sizeof(struct hashTable_s));
	hash->copyKeyElement = copyKey;
	hash->copyValueElement = copyValue;
	hash->equalKeyElement = equalKey;
	hash->freeKeyElement = freeKey;
	hash->freeValueElement = freeValue;
	hash->printKeyElement = printKey;
	hash->printValueElement = printValue;
	hash->transformKeyIntoNumber = transformKeyIntoNumber;
	hash->hashTableArray = (List*) malloc(sizeof(List) * hashNumber);
	for (int i = 0; i < hashNumber; i++) {
		hash->hashTableArray[i] = NULL;
	}
	hash->hashNumber = hashNumber;
	return hash;
}

//deletes the given hash table and frees all of its memory
status destroyHashTable(hashTable hash) {
	if (hash == NULL)
		return failure;
	for (int i = hash->hashNumber - 1; i >= 0; i--) {
		if (destroyList(hash->hashTableArray[i]) == failure)
			return failure;
	}
	free(hash->hashTableArray);
	hash->hashTableArray = NULL;
	free(hash);
	hash = NULL;
	return success;
}

/*creates a new pair with the given key and value and if it doesn't exist in the table -
adds it in the right index according to the transformIntoNumberFunction function and to the end
of the list in this index*/
status addToHashTable(hashTable hash, Element key, Element value) {
	if (hash == NULL || key == NULL)
		return failure;
	Pair newPair = createKeyValuePair(key, value, hash->copyKeyElement,
			hash->freeKeyElement, hash->equalKeyElement, hash->printKeyElement,
			hash->copyValueElement, hash->freeValueElement,
			hash->printValueElement);
	if (newPair == NULL)
		return failure;
	int Index = hash->transformKeyIntoNumber(key) % hash->hashNumber;
	if (hash->hashTableArray[Index] == NULL) {
		hash->hashTableArray[Index] = createLinkedList(copyPair, freePair,
				printPair, isEqualPair);
		if (appendNode(hash->hashTableArray[Index], newPair) == failure) {
			destroyKeyValuePair(newPair);
			return failure;
		}
	} else {
		Element element = searchInList(hash->hashTableArray[Index], newPair);
		if (element == NULL) {
			if (appendNode(hash->hashTableArray[Index], newPair) == failure) {
				destroyKeyValuePair(newPair);
				return failure;
			}
		} else {
			destroyKeyValuePair(newPair);
			return failure;
		}
	}
	destroyKeyValuePair(newPair);
	return success;
}

//searches for the given key in the table and if exists returns pointer to its value
Element lookupInHashTable(hashTable hash, Element key) {
	if (hash == NULL || key == NULL)
		return NULL;
	Pair newPair = createKeyValuePair(key, NULL, hash->copyKeyElement,
			hash->freeKeyElement, hash->equalKeyElement, hash->printKeyElement,
			hash->copyValueElement, hash->freeValueElement,
			hash->printValueElement);
	if (newPair == NULL)
		return NULL;
	int Index = hash->transformKeyIntoNumber(key) % hash->hashNumber;
	Element element = searchInList(hash->hashTableArray[Index], newPair);
	if (element == NULL) {
		destroyKeyValuePair(newPair);
		return NULL;
	}
	destroyKeyValuePair(newPair);
	return getValue((Pair) element);
}

//searches for the given key and if exists deletes all of the pair - its key and value.
status removeFromHashTable(hashTable hash, Element key) {
	if (hash == NULL || key == NULL)
		return failure;
	Pair newPair = createKeyValuePair(key, NULL, hash->copyKeyElement,
			hash->freeKeyElement, hash->equalKeyElement, hash->printKeyElement,
			hash->copyValueElement, hash->freeValueElement,
			hash->printValueElement);
	if (newPair == NULL)
		return failure;
	int Index = hash->transformKeyIntoNumber(key) % hash->hashNumber;
	if (deleteNode(hash->hashTableArray[Index], newPair) == failure) {
		destroyKeyValuePair(newPair);
		return failure;
	}
	destroyKeyValuePair(newPair);
	return success;
}

//prints all of the pairs in the hash table
status displayHashElements(hashTable hash) {
	if (hash == NULL)
		return failure;
	for (int i = 0; i < hash->hashNumber; i++) {
		displayList(hash->hashTableArray[i]);
	}
	return success;
}
