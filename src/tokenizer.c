#include "tokenizer.h"
#include <string.h>

#define MAXTOKENSIZE 1024
#define KEYWORDSSIZE 9
#define DATATYPESIZE 4
#define BRACKETSIZE 4

char *keywords[KEYWORDSSIZE] = {"return", "fn", "continue", "break", "if", "else", "while", "for", "unsigned"};

char *datatypes[DATATYPESIZE] = {"int", "float", "string", "char"};

char *brackets[BRACKETSIZE] = {"{", "}", "(", ")"};

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

LinkedList *tokenize(char *data)
{
	if(sizeof(data) == 0)
		return NULL;
	LinkedList *token_ll = createLinkedList(NULL);
	char *buffer = malloc(MAXTOKENSIZE);
	int offset = 0;

	for(int i = 0; i < strlen(data); i++)
	{
		if(!isalphanum(data[i]))
		{
			buffer[i - offset] = '\0';
			Token *token = bufferdump(buffer);
			insertLinkedList(token_ll, (void *) token, -1);
			if(data[i] == ' ' || data[i] == '\t' || data[i] == '\n')
			{
				offset = i + 1;
				continue;
			}
			offset = i;
		}
		buffer[i - offset] = data[i];
	}

	return token_ll;
}

Token *bufferdump(char *buffer)
{
	char *tok_name = malloc(strlen(buffer));
	strcpy(tok_name, buffer);
	Token *token = createToken(identifytokentype(tok_name), tok_name);

	memset(buffer, 0, strlen(buffer));	
	
	return token;
}

int identifytokentype(char *data)
{
	int is_num = 1;
    
    for(int i = 0; i < BRACKETSIZE; i++)
    {
        if(!strcmp(data, brackets[i]))
        {
            return TOK_BRACKET;
        }
    }

	for(int i = 0; i < strlen(data); i++)
	{
		if(!(48 <= data[i] && data[i] <= 57))
		{
			is_num = 0;
			break;
		}
	}
	if(is_num) return TOK_CONSTANT;
	for(int i = 0; i < KEYWORDSSIZE; i++)
	{
		if(!strcmp(data, keywords[i]))
		{
			return TOK_KEYWORD;
		}
	}

	for(int i = 0; i < DATATYPESIZE; i++)
	{
		if(!strcmp(data, datatypes[i]))
		{
			return TOK_DATATYPE;
		}
	}

	
	
	return TOK_IDENTIFIER;
}

