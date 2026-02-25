#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

void lexer_init(Lexer *l, const char *source) {
    l->src = source;
    l->pos = 0;
    l->line = 1;
    l->column = 1;
    l->current = source[0];
}

static void advance(Lexer *l) {
    if (l->current == '\n') {
        l->line++;
        l->column = 0;
    }

    l->pos++;
    l->column++;
    l->current = l->src[l->pos];
}

static char peek(Lexer *l) {
    return l->src[l->pos + 1];
}

static void skip_whitespace(Lexer *l) {
    while (isspace(l->current)) {
        advance(l);
    }
}

static void skip_comment(Lexer *l) {
    if (l->current == '/' && peek(l) == '/') {
        while (l->current && l->current != '\n')
            advance(l);
    }
}

static Token make_token(Lexer *l, TokenType type, const char *text) {
    Token t;
    t.type = type;
    t.lexeme = strdup(text);
    t.line = l->line;
    t.column = l->column;
    return t;
}
