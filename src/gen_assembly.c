#include "gen_assembly.h"
#include "data_types.h"
#include <stdio.h>

void emit(ASTNode *node);

void generate_assembly(AbstractSyntaxTree ast) {

    FILE *output = fopen("main.s", "w");
    fprintf(output, ".global _main\n.align 4\n_main:\n");

    uint32_t stack_space = ((ast.varArr.total_stack_space / (8 * 16)) + 1) * 16;

    fprintf(output, "\t sub sp, sp, #%d\n", stack_space);
    fprintf(output, "\tmov w0, #0\n");
    fprintf(output, "\tstr wzr, [sp, #%d]\n", stack_space - 4);

    fprintf(output, "\tadd sp, sp, #%d\n", stack_space);
    for (int i = 0; i < ast.astNodeArr.length; i++) {
        ASTNode *node = ast.astNodeArr.array[i];
        switch (node->type) { case ASSIGNMENT: }
    }

    // sucessful exit
    fprintf(output, "\n\tmov x0, #0\n");
    fprintf(output, "\tmov x16, #1\n");
    fprintf(output, "\tsvc 0");

    fclose(output);

    system("clang -c main.s -o main.o");
    system("clang main.o -Wl");
}
