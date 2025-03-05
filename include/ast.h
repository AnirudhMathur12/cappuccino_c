#ifndef AST
#define AST
#include "data_types.h"

Statements GenerateStatements(TokenArray tok_arr);

ASTNodeArray GenerateAbstractSyntaxTree(Statements statements);

#endif
