#ifndef AST
#define AST
#include "data_types.h"

Statements GenerateStatements(TokenArray tok_arr);
AbstractSyntaxTree GenerateAbstractSyntaxTree(Statements statements);
int assignIndex(char *name, VariableArray *var_arr);
Datatype assignDataType(char *dt);

#endif
