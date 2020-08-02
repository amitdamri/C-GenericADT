
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"

typedef struct LinkedList_t *List;

//creates new Linked List with the necessary functions and returns pointer to the new List
List createLinkedList(copyFunction, freeFunction, printFunction, equalFunction);

//destroys the given list and frees all of the memory
status destroyList(List);

//adds a new node to the end of the List
status appendNode(List, Element);

//deletes the given element from the list and frees its memory
status deleteNode(List, Element);

//prints all the nodes of the list
status displayList(List);

//searches if the given element exists in the list. if it does - returns pointer to the element
Element searchInList(List, Element);


#endif /* LINKEDLIST_H_ */
