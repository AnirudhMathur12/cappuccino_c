#ifndef UTILS
#define UTILS

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define ISALPHA(chr) ((65 <= chr && chr <= 90) || (97 <= chr && chr <= 122))
#define ISNUM(chr) (48 <= chr && chr <= 57)
#define ISWHITESPACE(chr) (chr == 9 || chr == 32 || chr == 10)
#define ISBRACKET(chr)                                                                             \
    (chr == 40 || chr == 41 || chr == 123 || chr == 125 || chr == 91 || chr == 93)

int strcpy_but_better(char *dst, char *src);
char *read_file(const char *path);

#endif
