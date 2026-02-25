#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

/* --------------------------------------------------
   Utility
-------------------------------------------------- */

static char *arc_strndup(const char *src, size_t n) {
    char *dest = malloc(n + 1);
    if (!dest) return NULL;

    memcpy(dest, src, n);
    dest[n] = '\0';
    return dest;
}

/* --------------------------------------------------
   Lexer core
-------------------------------------------------- */

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
    if (!l->src[l->pos + 1])
        return '\0';
    return l->src[l->pos + 1];
}

/* --------------------------------------------------
   Skipping
-------------------------------------------------- */

static void skip_whitespace(Lexer *l) {
    while (l->current && isspace(l->current))
        advance(l);
}

static void skip_comment(Lexer *l) {
    // // comment
    while (l->current && l->current != '\n')
        advance(l);
}

/* --------------------------------------------------
   Token creation
-------------------------------------------------- */

static Token make_token(Lexer *l, TokenType type, const char *text) {
    Token t;
    t.type = type;
    t.lexeme = strdup(text);
    t.line = l->line;
    t.column = l->column;
    return t;
}

/* --------------------------------------------------
   Keywords
-------------------------------------------------- */

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

/* --------------------------------------------------
   Token scanners
-------------------------------------------------- */

static Token identifier(Lexer *l) {
    int start = l->pos;

    while (isalnum(l->current) || l->current == '_')
        advance(l);

    int length = l->pos - start;
    char *text = arc_strndup(l->src + start, length);

    TokenType type = keyword_type(text);
    Token tok = make_token(l, type, text);

    free(text);
    return tok;
}

static Token number(Lexer *l) {
    int start = l->pos;

    while (isdigit(l->current))
        advance(l);

    int length = l->pos - start;
    char *text = arc_strndup(l->src + start, length);

    Token tok = make_token(l, TOKEN_INT, text);

    free(text);
    return tok;
}

/* --------------------------------------------------
   MAIN LEXER FUNCTION
-------------------------------------------------- */

Token lexer_next_token(Lexer *l) {

    while (1) {

        /* ---- stop at end ---- */
        if (!l->current)
            return make_token(l, TOKEN_EOF, "EOF");

        /* ---- skip whitespace ---- */
        if (isspace(l->current)) {
            skip_whitespace(l);
            continue;
        }

        /* ---- skip comments ---- */
        if (l->current == '/' && peek(l) == '/') {
            skip_comment(l);
            continue;
        }

        /* ---- identifiers ---- */
        if (isalpha(l->current) || l->current == '_')
            return identifier(l);

        /* ---- numbers ---- */
        if (isdigit(l->current))
            return number(l);

        /* ---- operators ---- */
        switch (l->current) {

            case '+':
                if (peek(l) == '=') {
                    advance(l);
                    advance(l);
                    return make_token(l, TOKEN_PLUS_EQUAL, "+=");
                }
                advance(l);
                return make_token(l, TOKEN_PLUS, "+");

            case '=':
                advance(l);
                return make_token(l, TOKEN_EQUAL, "=");

            case '{':
                advance(l);
                return make_token(l, TOKEN_LBRACE, "{");

            case '}':
                advance(l);
                return make_token(l, TOKEN_RBRACE, "}");

            case '(':
                advance(l);
                return make_token(l, TOKEN_LPAREN, "(");

            case ')':
                advance(l);
                return make_token(l, TOKEN_RPAREN, ")");

            case ';':
                advance(l);
                return make_token(l, TOKEN_SEMICOLON, ";");

            case '/':
                advance(l);
                return make_token(l, TOKEN_SLASH, "/");

            case '*':
                advance(l);
                return make_token(l, TOKEN_STAR, "*");

            case '-':
                advance(l);
                return make_token(l, TOKEN_MINUS, "-");
        }

        /* ---- unknown ---- */
        advance(l);
        return make_token(l, TOKEN_ERROR, "unknown");
    }
}
