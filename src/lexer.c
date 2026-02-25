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

static TokenType keyword_type(const char *id) {
    if (!strcmp(id,"var")) return TOKEN_VAR;
    if (!strcmp(id,"const")) return TOKEN_CONST;
    if (!strcmp(id,"if")) return TOKEN_IF;
    if (!strcmp(id,"elif")) return TOKEN_ELIF;
    if (!strcmp(id,"else")) return TOKEN_ELSE;
    if (!strcmp(id,"while")) return TOKEN_WHILE;
    if (!strcmp(id,"for")) return TOKEN_FOR;
    if (!strcmp(id,"func")) return TOKEN_FUNC;
    if (!strcmp(id,"return")) return TOKEN_RETURN;
    if (!strcmp(id,"True")) return TOKEN_TRUE;
    if (!strcmp(id,"False")) return TOKEN_FALSE;
    if (!strcmp(id,"and")) return TOKEN_AND;
    if (!strcmp(id,"or")) return TOKEN_OR;
    if (!strcmp(id,"not")) return TOKEN_NOT;

    return TOKEN_IDENTIFIER;
}
