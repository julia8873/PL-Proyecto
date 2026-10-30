%{
// *****************************************************************************
// ***
// *** Fichero : sintactico.y
// *** Funcion : Especificación sintáctica BISON del lenguaje BABAD 
// ***
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>

extern int yylex(void);
extern int yylineno;
extern void yyerror(const char *s);
%}

/* Genera mensajes de error sintáctico detallados */
%define parse.error verbose

/* Estructura para yylval */
%union {
    int entero;
    double real;
    char caracter;
    char *cadena;
}

/* --- TAREA 2 --- */


%left OP_OR    
%left OP_XOR     
%left OP_AND        
%left OP_IGUAL   
%left OP_REL     
%left OP_SUMRES         
%left OP_MULTDIV      
%right OP_UNARIO           

%precedence THEN
%precedence SINO

/* Símbolo inicial */
%start programa

%%

programa
    : /* Aquí irán las reglas de la BNF */
    ;

%%

