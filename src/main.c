#include "custom_defined_types.c"
// #include "syntax_analysis.c"
#include "tokenizer.c"
#include "utils.c"
#include <assert.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *file_data = read_file(argv[1]);

    TokenArray tok_arr = tokenize(file_data, argv[1]);
    for (int i = 0; i < tok_arr.length; i++) {
        printf(
            "Token Name: %s, Token Type: %d\n", tok_arr.array[i].token_name, tok_arr.array[i].type);
    }
    // printf("%d\n", tok_arr.length);
    // printf("%d\n", tok_arr.capacity);

    if (file_data != NULL) {
        free(file_data);
        file_data = NULL;
    }

    return 0;
}
