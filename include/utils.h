#ifndef UTILS_H_
#define UTILS_H_
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR 10000

char *read_file(const char *path);

typedef struct Node Node;

struct Node
{
	void *data;
	Node *next;
};

Node *createNode(void *data, Node *next);

typedef struct
{
	Node *head;
	size_t size;
} LinkedList;

LinkedList *createLinkedList(void *data);
void insertLinkedList(LinkedList *ll, void *data, int pos);
void printLinkedList(LinkedList *ll, void (*printNodeData)(void *Node));

#endif
