#include <stdio.h>
#include "lex.yy.c"  // Incluye el código generado por Flex.

int lookahead;

void match(int token) {
    if (lookahead == token) {
        lookahead = yylex();  // Obtener el siguiente token.
    } else {
        fprintf(stderr, "Error de sintaxis.\n");
        exit(1);
    }
}

void Lista();
void ListaX();

void S() {
    lookahead = yylex();
    Lista();
    match('$');
    printf("Análisis sintáctico exitoso.\n");
}

void Lista() {
    if (lookahead == 'x') {
        match('x');
        ListaX();
    } else {
        fprintf(stderr, "Error de sintaxis.\n");
        exit(1);
    }
}

void ListaX() {
    if (lookahead == 'x') {
        match('x');
        ListaX();
    } else if (lookahead == '$') {
        // ListaX -> ε
    } else {
        fprintf(stderr, "Error de sintaxis.\n");
        exit(1);
    }
}

int main() {
    S();  // Iniciar el análisis sintáctico.
    return 0;
}
