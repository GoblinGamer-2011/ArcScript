#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    const char *src;
    int pos;
    int line;
    int column;
    char current;
} Lexer;

void lexer_init(Lexer *lexer, const char *source);
Token lexer_next_token(Lexer *lexer);

#endif
