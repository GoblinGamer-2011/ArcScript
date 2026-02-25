#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main() {

    const char *source =
        "var x = 4;\n"
        "x += 1;\n"
        "// comment\n"
        "const y = 10;\n";

    Lexer lexer;
    lexer_init(&lexer, source);

    Token tok;
    printf("Enum Value | Token Value | line y col x");
    do {
        tok = lexer_next_token(&lexer);

        printf(
            "Token %-3d | %-10s | line %d col %d\n",
            tok.type,
            tok.lexeme,
            tok.line,
            tok.column
        );

    } while (tok.type != TOKEN_EOF);

    return 0;
}
