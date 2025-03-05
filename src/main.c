#include "ast.h"
#include "data_types.h"
#include "tokenizer.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *file_data = read_file(argv[1]);
    if (!file_data) {
        printf("What the fuck? I thought I could trust you.\n");
        return 0;
    }

    TokenArray tok_arr = tokenize(file_data, argv[1]);
    // for (int i = 0; i < tok_arr.length; i++) {
    //     printf(
    //         "Token Name: %s, Token Type: %d\n", tok_arr.array[i].token_name, tok_arr.array[i].type);
    // }
    // printf("%d\n", tok_arr.length);
    // printf("%d\n", tok_arr.capacity);

    Statements statements = GenerateStatements(tok_arr);
    for (int i = 0; i < statements.length; i++) {
        TokenArray arr = statements.array[i];
        printf("Statement %d\n", i + 1);
        for (int j = 0; j < arr.length; j++) {
            printf("Token Name: %s\tToken Type: %d\n", arr.array[j].token_name, arr.array[j].type);
        }
    }

    if (file_data != NULL) {
        free(file_data);
        file_data = NULL;
    }

    return 0;
}
