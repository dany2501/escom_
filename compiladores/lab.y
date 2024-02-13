%token INT CHAR VOID FLOAT ID NUM
%token '+' '-' '*' '/' '<' '>' '==' '!=' '<=' '>=' '=' '(' ')' ',' ';' WHILE

%%

funcion: TIPO ID '(' parametros ')' '{' bloque '}'
       ;

parametros: listaparam
          | VOID
          ;

listaparam: TIPO ID listaparam_opt
          ;

listaparam_opt: ',' TIPO ID listaparam_opt
              | /* vacío */
              ;

bloque: listainst
      ;

listainst: listainst INSTRUCCION
         | /* vacío */
         ;

instruccion: DECLARACION
           | ASIGNACION
           | INVOCACION
           | WHILE
           ;

declaracion: TIPO ID ';'
           ;

tipo: INT
    | CHAR
    | VOID
    | FLOAT
    ;

asignacion: ID '=' exparitmetica ';'
          ;

invocacion: ID '(' argumentos ')' ';'
          ;

argumentos: exparitmetica argumentos_opt
          ;

argumentos_opt: ',' exparitmetica argumentos_opt
              | /* vacío */
              ;

while: WHILE '(' explogica ')' '{' bloque '}'
     ;

exparitmetica: ID
            | NUM
            | '(' exparitmetica ')'
            | exparitmetica '+' exparitmetica
            | exparitmetica '-' exparitmetica
            | exparitmetica '*' exparitmetica
            | exparitmetica '/' exparitmetica
            ;

explogica: exparitmetica OPERADORLOGICO exparitmetica
         ;

OPERADORLOGICO: '<'
              | '>'
              | '=='
              | '!='
              | '<='
              | '>='
              ;

%%

int main() {
    yyparse();
    return 0;
}
