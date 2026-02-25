#include <stdio.h>
#include "lexer.h"

int main() {

    const char *src =
        "var x = 4;\n"
        "x += 1;\n";

    Lexer lexer;
    lexer_init(&lexer, src);

    Token tok;

    do {
        tok = lexer_next_token(&lexer);
        printf("Token: %d (%s)\n", tok.type, tok.lexeme);
    } while (tok.type != TOKEN_EOF);

    return 0;
}
