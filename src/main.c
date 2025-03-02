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
    for (int i = 0; i < tok_arr.length; i++) {
        printf(
            "Token Name: %s, Token Type: %d\n", tok_arr.array[i].token_name, tok_arr.array[i].type);
    }
    printf("%d\n", tok_arr.length);
    printf("%d\n", tok_arr.capacity);

    // ASTNodeArray ast = process_tok_to_ast(tok_arr);
    // for (int i = 0; i < ast.length; i++) {
    //     if (ast.array[i].type == VAR_DECLARATION) {
    //         printf("Variable Declaration:\n");
    //         printf("\tVariable Type: %s\n", ast.array[i].data.VAR_DECLARATION.identifier_name);
    //         printf("\tVariable Name: %s\n", ast.array[i].data.VAR_DECLARATION.identifier_type);
    //     }
    // }

    if (file_data != NULL) {
        free(file_data);
        file_data = NULL;
    }

    return 0;
}
