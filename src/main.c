#include "custom_defined_types.c"
#include "tokenizer.c"
#include "utils.c"
#include <assert.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *file_data = read_file(argv[1]);

    TokenArray *tok_arr = tokenize(file_data);
    for (int i = 0; i < tok_arr->lenght; i++) {
        printf("Token Name: %s, Token Type: %d\n", tok_arr->array[i].token_name,
               tok_arr->array[i].type);
    }
    printf("%d\n", tok_arr->lenght);
    printf("%d\n", tok_arr->capacity);

    // analyze_statements(tok_arr);

    if (file_data != NULL) {
        free(file_data);
        file_data = NULL;
    }

    TokenArray_free(tok_arr);
    tok_arr = NULL;
    return 0;
}
