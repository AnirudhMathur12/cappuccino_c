#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Could not open %s\n", path);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
    {
        printf("Buffer allocation to read file: %s failed.", path);
        return NULL;
    }
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';

    fclose(fp);
    return buffer;
}

int isalphanum(char c)
{
	return ((48 <= c) && (c <= 57)) || ((65 <= c) && (c <= 90)) || ((97<= c) && (c <= 122));
}

Node *createNode(void *data, Node *next)
{
	Node *node = malloc(sizeof(Node));
	node->data = data;
	node->next = next;
	return node;
}


LinkedList *createLinkedList(void *data)
{
	LinkedList *ll = malloc(sizeof(LinkedList));
	if(!data)
	{
		ll->head = NULL;
		ll->size=0;
	}
	else 
	{
		ll->head = createNode(data, NULL);
		ll->size = 1;
	}
	 return ll;
}

void insertLinkedList(LinkedList *ll, void *data, int pos)
{
	if(ll->size == 0)
	{
		ll->head = createNode(data, NULL);
		ll->size = 1;
		return;
	}

	if(pos == -1)
	{
		Node *iter = ll->head;
		while(iter->next != NULL)
		{
			iter = iter->next;
		}
		iter->next = createNode(data, NULL);
	}	
	else if(pos == 0)
	{
		Node *old_head = ll->head;
		Node* new_head = createNode(data, old_head);
		ll->head = new_head;
	}

	ll->size++;

}

void printLinkedList(LinkedList *ll, void (*printNodeData)(void *Node))
{
	Node *iter = ll->head;
	while(iter)
	{
		printNodeData(iter->data);	
		iter = iter->next;
	}
}

int hash(char *data, int limit)
{
	char *str_copy = malloc(strlen(data));
	strcpy(str_copy, data);
	unsigned int long hash_value = 1024;
	char c;
	while(c = *str_copy++)
	{
		hash_value = ((hash_value << 5) + hash_value) + c;
	}

	return hash_value;
}

