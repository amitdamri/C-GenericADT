#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"

typedef struct KeyValuePair_t *Pair;

//creates the pair with the given key , value and functions and returns a pointer to the new pair
Pair createKeyValuePair(Element, Element, copyFunction copyKey,
		freeFunction freeKey, equalFunction equalKey, printFunction printKey,
		copyFunction copyValue, freeFunction freeValue,
		printFunction printValue);

//deletes the given pair and frees all of its memory - the memory of the key and of the value
status destroyKeyValuePair(Pair);

//prints the value of the pair
void displayValue(Pair);

//print the key of the pair
void displayKey(Pair);

//returns a pointer to the value of the pair
Element getValue(Pair);

//returns a pointer to the key of the pair
Element getKey(Pair);

//checks if the key of both pairs is equal
bool isEqualKey(Pair, Pair);


/****************************************************
 *****************Help Functions*********************
 ****************************************************/

//copy the given pair and returns a pointer to the new pair
Element copyPair(Element);

//frees the memory of the given pair
status freePair(Element);

////prints the value of the pair
status printPair(Element);

//checks if the key of both pairs is equal
bool isEqualPair(Element, Element);

#endif /* KEYVALUEPAIR_H_ */
