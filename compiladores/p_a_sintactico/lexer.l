%{
    #include <stdio.h>
%}

%%
x       { return 'x'; }
\$      { return '$'; }
[ \t\n] { }  /* Ignorar espacios en blanco y saltos de línea. */
.       { fprintf(stderr, "Error: Caracter no válido '%c'\n", yytext[0]); }
%%

int yywrap() {
    return 1;
}
