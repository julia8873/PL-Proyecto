// *****************************************************************************
// ***
// *** Fichero : main.c
// *** Funcion : Programa principal del analizador sintáctico (Bison + Flex)
// ***
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yylineno;
int yyparse(void);

void yyerror(const char *s) {
    fprintf(stderr, "[Línea %2d] *** %s\n", yylineno, s);
}

FILE *abrir_entrada(int argc, char *argv[]) {
    FILE *f = NULL;
    if (argc > 1) {
        f = fopen(argv[1], "r");
        if (f == NULL) {
            fprintf(stderr, "Error: no se puede abrir el fichero de entrada '%s'\n", argv[1]);
            exit(1);
        }
    } else {
        f = stdin;
    }
    return f;
}

int main(int argc, char *argv[]) {
    yyin = abrir_entrada(argc, argv);
    return yyparse();
}
