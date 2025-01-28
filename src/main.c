#include "tokenizer.c"
#include "utils.c"
#include <assert.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *file_data = read_file(argv[1]);

    Token *tok_arr = tokenize(file_data);
    int iter = 0;
    while (tok_arr[iter].type != TOK_ARR_TERMINATE) {
        printf("Token Name: %s, Token Type: %d\n", tok_arr[iter].token_name,
               tok_arr[iter].type);
        iter++;
    }
    printf("%d\n", iter);

    if (file_data != NULL) {
        free(file_data);
    }

    free(tok_arr);
    return 0;
}
