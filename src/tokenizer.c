#include "tokenizer.h"
#include <string.h>

void printNodeData_Token(void *data)
{
	Token *t_data = (Token *) data;
	printf("Token Name: %s\tToken Type: %d\n", t_data->tok_name, t_data->toktype);	
}

Token *createToken(enum tokentype _tt, char *tn)
{
	Token *token = malloc(sizeof(Token));
	*token = (Token) {_tt, tn};
	return token;
}
