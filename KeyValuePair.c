#include "KeyValuePair.h"

//represents the key value pair
struct KeyValuePair_t {
	copyFunction copyKeyElement;
	freeFunction freeKeyElement;
	equalFunction isEqualKeyElement;
	printFunction printKeyElement;
	copyFunction copyValueElement;
	freeFunction freeValueElement;
	printFunction printValueElement;
	Element key;
	Element value;
};

//creates the pair with the given key , value and functions and returns a pointer to the new pair
Pair createKeyValuePair(Element key, Element value, copyFunction copyFuncKey,
		freeFunction freeFuncKey, equalFunction equalFuncKey,
		printFunction printFuncKey, copyFunction copyFuncValue,
		freeFunction freeFuncValue, printFunction printFuncValue) {
	if (key == NULL || copyFuncKey == NULL || freeFuncKey == NULL
			|| equalFuncKey == NULL || printFuncKey == NULL
			|| copyFuncValue == NULL || freeFuncValue == NULL
			|| printFuncValue == NULL)
		return NULL;
	Pair pair = (Pair) malloc(sizeof(struct KeyValuePair_t));
	if (pair == NULL)
		return NULL;
	pair->copyKeyElement = copyFuncKey;
	pair->freeKeyElement = freeFuncKey;
	pair->isEqualKeyElement = equalFuncKey;
	pair->printKeyElement = printFuncKey;
	pair->copyValueElement = copyFuncValue;
	pair->freeValueElement = freeFuncValue;
	pair->printValueElement = printFuncValue;
	pair->key = pair->copyKeyElement(key);
	pair->value = pair->copyValueElement(value);
	return pair;
}

//deletes the given pair and frees all of its memory - the memory of the key and of the value
status destroyKeyValuePair(Pair pair) {
	if (pair == NULL)
		return failure;
	if (pair->value !=NULL)
			if(pair->freeValueElement(pair->value) == failure)
				return failure;
	if (pair->freeKeyElement(pair->key) == failure)
		return failure;
	free(pair);
	pair = NULL;
	return success;
}

//prints the value of the pair
void displayValue(Pair pair) {
	if (pair == NULL)
		return;
	pair->printValueElement(pair->value);
}

//print the key of the pair
void displayKey(Pair pair) {
	if (pair == NULL)
		return;
	pair->printKeyElement(pair->key);
}

//returns a pointer to the value of the pair
Element getValue(Pair pair) {
	if (pair == NULL)
		return NULL;
	return pair->value;
}

//returns a pointer to the key of the pair
Element getKey(Pair pair) {
	if (pair == NULL)
		return NULL;
	return pair->key;
}

//checks if the key of both pairs is equal
bool isEqualKey(Pair firstPair, Pair secondPair) {
	if (firstPair == NULL || secondPair == NULL)
			return false;
	if ((secondPair->isEqualKeyElement(firstPair->key, secondPair->key)) == true)
		return true;
	return false;
}

//copy the given pair and returns a pointer to the new pair
Element copyPair(Element pair) {
	if (pair == NULL)
		return NULL;
	Pair pairToReturn = createKeyValuePair(((Pair) pair)->key,
			((Pair) pair)->value, ((Pair) pair)->copyKeyElement,
			((Pair) pair)->freeKeyElement, ((Pair) pair)->isEqualKeyElement,
			((Pair) pair)->printKeyElement, ((Pair) pair)->copyValueElement,
			((Pair) pair)->freeValueElement, ((Pair) pair)->printValueElement);
	return pairToReturn;
}

//frees the memory of the given pair
status freePair(Element pair) {
	if (pair == NULL)
		return failure;
	if (destroyKeyValuePair((Pair) pair) == success)
		return success;
	return failure;
}

//prints the value of the pair
status printPair(Element pair) {
	if (pair == NULL)
		return failure;
	displayValue((Pair)pair);
	return success;
}

//checks if the key of both pairs is equal
bool isEqualPair(Element pair1, Element pair2) {
	if (pair1 == NULL || pair2 == NULL)
		return false;
	if (isEqualKey((Pair)pair1, (Pair)pair2) == false)
		return false;
	return true;
}

