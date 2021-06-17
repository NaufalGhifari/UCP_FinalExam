/* linkedList.h */

#ifndef LINKEDLISTHEADER
#define LINKEDLISTHEADER

typedef struct listNode
{
    void* value;
    struct listNode* next;

} list_node_t;

typedef struct linkedList
{
    void* head;
    void* tail;
    int count;

} list_t;

typedef void(*printFunction_t)(void* thingToPrint, FILE* file);//

list_t* createList();
void addToList (list_t* list, void* thingToAdd);
void appendToList (list_t* list, void* thingToAdd);
void removeNode(list_t* list);
void freeList (list_t* list);
void printList (list_t* list, FILE* myFile, printFunction_t printThing); //



#endif