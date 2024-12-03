#include "tokenizer.h"
#include "utils.h"
#include <stdio.h>

void printNodeData_Int(void *data)
{
	printf("%d\n", *(int *) data);
}

void leak_stuff(void)
{
	int i;
	for(int i = 0; i < 10; i++)
	{
		int *x = malloc(sizeof *x);
		*x = i;
		printf("%d\n", *x);
	}
}

int main(int argc, char **argv)
{
    printf("lmfao %s\n", argv[1]);
    char *file_data = read_file(argv[1]);

	LinkedList *token_ll = tokenize(file_data);
	printLinkedList(token_ll, printNodeData_Token);


    if (file_data != NULL)
    {
        free(file_data);
    }
    return 0;
}
