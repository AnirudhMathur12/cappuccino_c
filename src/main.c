#include "tokenizer.h"
#include "utils.h"
#include <stdio.h>

void printNodeData_Int(void *data)
{
	printf("%d\n", *(int *) data);
}

int main(int argc, char **argv)
{
    printf("lmfao %s\n", argv[1]);
    char *file_data = read_file(argv[1]);

    if (file_data != NULL)
    {
        free(file_data);
    }
    return 0;
}
