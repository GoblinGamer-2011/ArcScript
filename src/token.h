#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    // literals
    TOKEN_INT,
    TOKEN_IDENTIFIER,

    // keywords
    TOKEN_VAR,
    TOKEN_CONST,
    TOKEN_IF,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_FUNC,
    TOKEN_RETURN,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    // operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQUAL,
    TOKEN_PLUS_EQUAL,

    // punctuation
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,

    TOKEN_EOF,
    TOKEN_ERROR

} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;
    int line;
    int column;
} Token;

#endif
