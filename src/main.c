#include "custom_defined_types.c"
#include "syntax_analysis.c"
#include "tokenizer.c"
#include "utils.c"
#include <assert.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *file_data = read_file(argv[1]);

    TokenArray tok_arr = tokenize(file_data, argv[1]);
    // for (int i = 0; i < tok_arr.length; i++) {
    //     printf("Token Name: %s, Token Type: %d\n", tok_arr.array[i].token_name,
    //     tok_arr.array[i].type);
    // }
    // printf("%d\n", tok_arr.length);
    // printf("%d\n", tok_arr.capacity);

    Statements statements = analyze_statements(tok_arr);
    // for (int i = 0; i < global_scope.size; i++) {
    //     TokenArray arr = global_scope.statements[i];
    //     printf("Statement %d:\n", i + 1);
    //     for (int j = 0; j < arr.length; j++) {
    //         printf("Token Name: %s\tToken Type: %d\n", arr.array[j].token_name,
    //         arr.array[j].type);
    //     }
    //     printf("\n");
    // }

    // AST ast = generate_AST(global_scope);
    for (int i = 0; i < 16; i++) {

        uint32_t stack_space = ((int)(i / 4) + 1) * 16;
        printf("%d: %d\n", i, stack_space);
    }
    // for (int i = 0; i < ast.length; i++) {
    //     switch (ast.array[i].type) {
    //     case VAR_DECL:
    //         printf("Variable Declaration:\n");
    //         printf("\tData type: %s\n", ast.array[i].data.VAR_DECL.data_type.token_name);
    //         printf("\tIdentifier Name: %s\n", ast.array[i].data.VAR_DECL.identifier.token_name);
    //         break;
    //     case VAR_ASSIGMENT:
    //         printf("Variable Assignment:\n");
    //         printf("\tIdentifier Name: %s\n",
    //                ast.array[i].data.VAR_ASSIGMENT.identifier.token_name);
    //         printf("\tValue: %s\n", ast.array[i].data.VAR_ASSIGMENT.value.token_name);
    //         break;
    //     }
    // }

    if (file_data != NULL) {
        free(file_data);
        file_data = NULL;
    }

    return 0;
}
