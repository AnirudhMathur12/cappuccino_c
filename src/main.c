#include "ast.h"
#include "data_types.h"
#include "gen_assembly.h"
#include "tokenizer.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>

void print_ast(ASTNode *node, int indent);

void print_ast(ASTNode *node, int indent) {
    switch (node->type) {
        case INTEGER:
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Type: INTEGER\n");
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Data: %d\n", node->data.INTEGER.data);
            break;
        case VARIABLE:
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Type: VARIABLE\n");
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Variable Index: %d\n", node->data.VARIABLE.index);
            break;
        case ADDITION:
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Type: ADDITION\n");
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Node 1:\n");
            print_ast(node->data.ADDITION.node1, indent + 1);
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Node 2:\n");
            print_ast(node->data.ADDITION.node2, indent + 1);
            break;
        case ASSIGNMENT:
            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Type: ASSIGNMENT\n");

            for (int i = 0; i < indent; i++)
                printf("\t");
            printf("Variable Index: %d\n", node->data.ASSIGNMENT.index);
            printf("Node:\n");
            print_ast(node->data.ASSIGNMENT.node, indent + 1);
            break;
    }
}

int main(int argc, char **argv) {
    char *file_data = read_file(argv[1]);
    if (!file_data) {
        printf("What the fuck? I thought I could trust you.\n");
        return 0;
    }

    TokenArray tok_arr = tokenize(file_data, argv[1]);
    // for (int i = 0; i < tok_arr.length; i++) {
    //     printf(
    //         "Token Name: %s, Token Type: %d\n", tok_arr.array[i].token_name,
    //         tok_arr.array[i].type);
    // }
    // printf("%d\n", tok_arr.length);
    // printf("%d\n", tok_arr.capacity);

    Statements statements = GenerateStatements(tok_arr);
    // for (int i = 0; i < statements.length; i++) {
    //     TokenArray arr = statements.array[i];
    //     printf("Statement %d\n", i + 1);
    //     for (int j = 0; j < arr.length; j++) {
    //         printf("Token Name: %s\tToken Type: %d\n", arr.array[j].token_name,
    //         arr.array[j].type);
    //     }
    // }

    AbstractSyntaxTree ast = GenerateAbstractSyntaxTree(statements);
    // for (int i = 0; i < ast.varArr.length; i++) {
    //     printf("Variable Index: %d\n", i);
    //     printf("\tVariable Name: %s\n", ast.varArr.array[i].variable_name);
    //     printf("\tVariable Type: %d\n", ast.varArr.array[i].type);
    // }
    // for (int i = 0; i < ast.astNodeArr.length; i++) {
    //     print_ast(ast.astNodeArr.array[i], 0);
    // }
    // for (int i = 0; i < ast.varArr.length; i++) {
    //     printf("Type: %d, Name: %s, Offset: %d\n",
    //         ast.varArr.array[i].type,
    //         ast.varArr.array[i].variable_name,
    //         ast.varArr.array[i].stack_offset);
    // }
    //
    // for (int i = 0; i < ast.astNodeArr.length; i++) {
    //     printf("Index: %d, Data: %d\n",
    //         ast.astNodeArr.array[i]->data.VAR_ASSIGNMENT.index,
    //         ast.astNodeArr.array[i]->data.VAR_ASSIGNMENT.data);
    // }

    // generate_assembly(ast);

    if (file_data != NULL) {
        free(file_data);
        file_data = NULL;
    }

    return 0;
}
