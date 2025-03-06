#include "gen_assembly.h"
#include <stdio.h>

void generate_assembly(AbstractSyntaxTree ast) {
    FILE *output = fopen("main.s", "w");
    fprintf(output, ".global _main\n.align 4\n_main:\n");

    uint32_t stack_space = ((ast.varArr.total_stack_space / (8 * 16)) + 1) * 16;

    fprintf(output, "\t sub sp, sp, #%d\n", stack_space);
    fprintf(output, "\tmov w0, #0\n");
    fprintf(output, "\tstr wzr, [sp, #%d]\n", stack_space - 4);
    for (int i = 0; i < ast.astNodeArr.length; i++) {
        if (ast.astNodeArr.array[i].type == VAR_ASSIGNMENT) {
            fprintf(output, "\tmov w8, #%d\n", ast.astNodeArr.array[i].data.VAR_ASSIGNMENT.data);
            fprintf(output, "\tstr w8, [sp, #%d]\n", (stack_space - 4) - ((ast.varArr.array[ast.astNodeArr.array[i].data.VAR_ASSIGNMENT.index].stack_offset + ast.varArr.array[ast.astNodeArr.array[i].data.VAR_ASSIGNMENT.index].type) / 8));
        }
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
