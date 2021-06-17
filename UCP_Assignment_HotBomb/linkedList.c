/* linkedList.c */

#include <stdio.h>
#include <stdlib.h>

#include "bombHeader.h"
#include "linkedList.h"

/* create a linked list */
list_t* createList()
{
    return calloc(1, sizeof (list_t));
}

/* adds to the head of the list */
void addToList (list_t* list, void* thingToAdd)
{
    list_node_t* newNode = calloc (1, sizeof(list_node_t));

    newNode->value = thingToAdd;

    newNode->next = list->head;

    list->head = newNode;

    list->count = list->count + 1;
}

/* adds to the end of the list (also adds to the head if empty) */
void appendToList (list_t* list, void* thingToAdd)
{
    list_node_t* newNode = calloc(1, sizeof (list_node_t));
    list_node_t* current = list->head;

    newNode->value = thingToAdd;

    newNode->next = NULL;

    if (current == NULL) /* adds to the head of the list if it is empty */
    {
        list->head = newNode;
    }
    
    else /* otherwise adds to the end */
    {
        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    list->count = list->count + 1;
}

/* removes a node from the list */
void removeNode(list_t* list)
{
    list_node_t* current = list->head;

    list->head = current->next;

    list->count = list->count - 1;

    free (current->value);
    free (current);
}

/* print the list to a file */
void printList (list_t* list, FILE* myFile, printFunction_t printThing) //
{
    list_node_t* current;
    current = list->head;

    while (current != NULL)
    {
        printThing (current->value, myFile);
        current = current->next;
    }
}

/* free existing list */
void freeList (list_t* list)
{
    list_node_t* current;
    current = list->head;

    while (current != NULL)
    {
        list_node_t* nextTemp = current->next;
        free (current->value);
        free (current);
        current = nextTemp;
    }
}