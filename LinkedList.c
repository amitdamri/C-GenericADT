#include "LinkedList.h"

//represents the nodes of the list
typedef struct Node_t {
	Element element;
	struct Node_t *next;
}*Node;

//represents the linked list
struct LinkedList_t {
	struct Node_t *head;
	copyFunction copyElement;
	freeFunction freeElement;
	printFunction printElement;
	equalFunction equalElement;
};

//creates new Linked List with the necessary functions and returns pointer to the new List
List createLinkedList(copyFunction copyFunc, freeFunction freeFunc,
		printFunction printFunc, equalFunction equalFunc) {

	if (copyFunc == NULL || freeFunc == NULL || equalFunc == NULL
			|| printFunc == NULL)
		return NULL;
	List list = (List) malloc(sizeof(struct LinkedList_t));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	list->copyElement = copyFunc;
	list->equalElement = equalFunc;
	list->freeElement = freeFunc;
	list->printElement = printFunc;
	return list;
}

//destroys the given list and frees all of the memory
status destroyList(List list) {
	if (list == NULL)
		return success;
	Node temp = NULL;
	// no elements in the list
	if(list->head ==NULL){
		free(list);
		return success;
	}
	while (list->head->next != NULL) {
		temp = list->head->next;
		if (list->freeElement(list->head->element) == failure)
			return failure;
		free(list->head);
		list->head = temp;
	}
	if (list->freeElement(list->head->element) == failure)
		return failure;
	free(list->head);
	free(list);
	return success;
}

//adds a new node to the end of the List
status appendNode(List list, Element element) {
	if (list == NULL || element == NULL)
		return failure;
	Node newNodeToAdd = (Node) malloc(sizeof(struct Node_t));
	if(newNodeToAdd ==NULL)
		return failure;
	newNodeToAdd->element = list->copyElement(element);
	newNodeToAdd->next = NULL;
	if (list->head == NULL){
		list->head = newNodeToAdd;
		list->head->next =NULL;
	}
	else {
		Node temp = list->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNodeToAdd;
	}
	return success;
}

//deletes the given element from the list and frees its memory
status deleteNode(List list, Element element){
	if (list ==NULL || element ==NULL)
		return failure;
	if (list->head == NULL)
		return failure;
	Node temp = list->head;

	//if needs to delete the head node
	if (list->equalElement(list->head->element,element) == true){
		temp = temp->next;
		if(list->freeElement(list->head->element)==failure)
			return failure;
		free(list->head);
		list->head = temp;
		return success;
	}

	//deletes the requested node except the head node
	Node nodeToDelete = NULL;
	while (temp->next != NULL){
		if (list->equalElement(temp->next->element,element) == true){
			nodeToDelete = temp->next;
			temp->next = (temp->next)->next;
			if (list->freeElement(nodeToDelete->element)==failure)
				return failure;
			free(nodeToDelete);
			nodeToDelete=NULL;
			return success;
		}
		temp = temp->next;
	}
	return failure;
}

//prints all the nodes of the list
status displayList(List list){
	if (list ==NULL || list->head ==NULL)
		return failure;
	Node temp = list->head;
	while (temp != NULL){
		list->printElement(temp->element);
		temp = temp->next;
	}
	return success;
}

//searches in the list for the given element according to the comparison function
Element searchInList(List list, Element element){
	if (list ==NULL || element ==NULL || list->head ==NULL)
		return NULL;
	Node temp = list->head;
	Element elementToReturn =NULL;
	while (temp != NULL){
		if(list->equalElement(temp->element, element) == true){
			elementToReturn = temp->element;
			return elementToReturn;
		}
		temp = temp->next;
	}
	return NULL;
}
