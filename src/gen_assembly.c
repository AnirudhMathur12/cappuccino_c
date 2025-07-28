#include "gen_assembly.h"
#include "data_types.h"
#include <stdio.h>

uint32_t stack_space;

uint32_t cond_branch_num = 0;

void emit(FILE *out, ASTNode *node, VariableArray *var_arr, int priority) {
    switch (node->type) {
    case ASSIGNMENT:
        emit(out, node->data.ASSIGNMENT.node, var_arr, 0);
        fprintf(out, "\tstr w8, [sp, #%d]\n",
                stack_space - 8 -
                    var_arr->array[node->data.ASSIGNMENT.index].stack_offset /
                        8);
        break;
    case ADDITION:
        if (node->data.ADDITION.node1->type != INTEGER) {
            emit(out, node->data.ADDITION.node1, var_arr, 0);
            emit(out, node->data.ADDITION.node2, var_arr, 1);
        } else {
            emit(out, node->data.ADDITION.node2, var_arr, 0);
            emit(out, node->data.ADDITION.node1, var_arr, 1);
        }
        fprintf(out, "\tadd w8, w8, w9\n");
        break;
    case SUBTRACTION:
        if (node->data.SUBTRACTION.node1->type != INTEGER) {
            emit(out, node->data.SUBTRACTION.node1, var_arr, 0);
            emit(out, node->data.SUBTRACTION.node2, var_arr, 1);
            fprintf(out, "\tsub w8, w8, w9\n");
        } else {
            emit(out, node->data.SUBTRACTION.node2, var_arr, 0);
            emit(out, node->data.SUBTRACTION.node1, var_arr, 1);
            fprintf(out, "\tsub w8, w9, w8\n");
        }
        break;
    case INTEGER:
        fprintf(out, "\tmov w%d, #%d\n", 8 + priority, node->data.INTEGER.data);
        break;
    case VARIABLE:
        fprintf(out, "\tldr w%d, [sp, #%d]\n", 8 + priority,
                stack_space - 8 -
                    var_arr->array[node->data.ASSIGNMENT.index].stack_offset /
                        8);
        break;
    case CONDITIONAL:
        emit(out, node->data.CONDITIONAL.node1, var_arr, 0);
        emit(out, node->data.CONDITIONAL.node2, var_arr, 1);

        fprintf(out, "\tsubs w8, w8, w9\n");
        switch (node->data.CONDITIONAL.type) {
        case GREATER:
            fprintf(out, "\tb.le CB_%d\n", cond_branch_num++);
            break;
        }

        fprintf(out, "\tb CB_%d\n", cond_branch_num++);
        fprintf(out, "\tCB_%d:\n", cond_branch_num - 2);
        fprintf(out, "\tCB_%d:\n", cond_branch_num - 1);
    }
}

void generate_assembly(AbstractSyntaxTree ast) {

    FILE *output = fopen("main.s", "w");
    fprintf(output, ".global _main\n.align 4\n_main:\n");

    stack_space = ((ast.varArr.total_stack_space / (8 * 16)) + 1) * 16;

    fprintf(output, "\t sub sp, sp, #%d\n", stack_space);
    fprintf(output, "\tmov w0, #0\n");
    fprintf(output, "\tstr wzr, [sp, #%d]\n", stack_space - 4);

    for (int i = 0; i < ast.astNodeArr.length; i++) {
        emit(output, ast.astNodeArr.array[i], &ast.varArr, 0);
    }

    fprintf(output, "\tadd sp, sp, #%d\n", stack_space);

    // sucessful exit
    fprintf(output, "\n\tmov x0, #0\n");
    fprintf(output, "\tmov x16, #1\n");
    fprintf(output, "\tsvc 0");

    fclose(output);

    system("clang -c main.s -o main.o");
    system("clang main.o -Wl");
}
