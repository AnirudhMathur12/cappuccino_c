#include "ast.h"
#include "data_types.h"

Statements GenerateStatements(TokenArray tok_arr) {
    Statements statements = Statements_init(128);

    statements.array[statements.length] = TokenArray_init(8);
    TokenArray *curr = &statements.array[statements.length];
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            statements.array[++statements.length] = TokenArray_init(8);
            if (statements.length == statements.capacity - 1) {
                statements.capacity = (int)(statements.capacity * 2.5);
                statements.array = realloc(statements.array, statements.capacity);
            }
            curr = &statements.array[statements.length];
            continue;
        }
        curr->array[curr->length++] = tok_arr.array[i];
        if (curr->length == curr->capacity - 1) {
            curr->capacity = (int)(curr->capacity * 2.5);
            curr->array = realloc(curr->array, curr->capacity);
        }
    }

    return statements;
}

ASTNodeArray GenerateAbstractSyntaxTree(Statements statements) {

    ASTNodeArray ast;
    ast = ASTNodeArray_init(128);

    return ast;
}
