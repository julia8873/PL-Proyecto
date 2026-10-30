%{
// *****************************************************************************
// ***
// *** Fichero : lexico.l
// *** Funcion : Especificación LEX del lenguaje
// ***
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla.h"

/* Estructura de los atributos semánticos de los tokens */
typedef struct {
    int entero;
    double real;
    char caracter;
    char *cadena;
} TipoAtributo;

TipoAtributo yylval;
%}

%option noyywrap

/* Contador de líneas */
%option yylineno 

LETRA       [a-zA-Z]
DIGITO      [0-9]
LETRA_NUM   [a-zA-Z0-9_]

%%

[ \t\n]+                   ;
"//".*                     ; /* Comentario de una línea */
"/*"([^*]|\*+[^*/])*\*+"/" ; /* Comentario multilínea */

    /* TIPOS DE DATOS */
"entero"            { yylval.entero = 0; return TIPO_DATO; }
"real"              { yylval.entero = 1; return TIPO_DATO; }
"caracter"          { yylval.entero = 2; return TIPO_DATO; }
"booleano"          { yylval.entero = 3; return TIPO_DATO; }

    /* CONSTANTES BOOLEANAS */
"falso"             { yylval.entero = 0; return CTE_BOOLEANA; }
"verdadero"         { yylval.entero = 1; return CTE_BOOLEANA; }

    /* PALABRAS RESERVADAS */
"principal"         { return PRINCIPAL; }
"inicio_variables"  { return INICIO_VAR; }
"fin_variables"     { return FIN_VAR; }
"si"                { return SI; }
"sino"              { return SINO; }
"mientras"          { return MIENTRAS; }
"hacer"             { return HACER; }
"hasta"             { return HASTA; }
"leer"              { return LEER; }
"escribir"          { return ESCRIBIR; }
"devolver"          { return DEVOLVER; }

    /* IDENTIFICADORES */
{LETRA}{LETRA_NUM}* { yylval.cadena = strdup(yytext); return IDENT; }

    /* CONSTANTES COMPLEJAS Y CADENAS */
{DIGITO}+           { yylval.entero = atoi(yytext); return CTE_ENTERA; }
{DIGITO}+\.{DIGITO}+ { yylval.real = atof(yytext); return CTE_REAL_CARACTER; }
'[^']'              { yylval.caracter = yytext[1]; return CTE_REAL_CARACTER; }
\"[^\"]*\"          { yylval.cadena = strdup(yytext); return CTE_CADENA; }

    /* OPERADORES MULTIPLICATIVOS Y MATRICIALES (** antes que *) */
"**"                { yylval.entero = 2; return OP_MULTDIV; }
"*"                 { yylval.entero = 0; return OP_MULTDIV; }
"/"                 { yylval.entero = 1; return OP_MULTDIV; }

    /* OPERADORES ADITIVOS */
"+"                 { yylval.entero = 0; return OP_SUMRES; }
"-"                 { yylval.entero = 1; return OP_SUMRES; }

    /* OPERADORES RELACIONALES (<= y >= antes que < y >) */
"<="                { yylval.entero = 2; return OP_REL; }
">="                { yylval.entero = 3; return OP_REL; }
"<"                 { yylval.entero = 0; return OP_REL; }
">"                 { yylval.entero = 1; return OP_REL; }

    /* OPERADORES DE IGUALDAD */
"=="                { yylval.entero = 0; return OP_IGUAL; }
"!="                { yylval.entero = 1; return OP_IGUAL; }

    /* OPERADORES UNARIOS */
"++"                { yylval.entero = 0; return OP_UNARIO; }
"--"                { yylval.entero = 1; return OP_UNARIO; }
"!"                 { yylval.entero = 2; return OP_UNARIO; }

    /* OPERADORES LÓGICOS Y ASIGNACIÓN */
"&&"                { return OP_AND; }
"||"                { return OP_OR; }
"^"                 { return OP_XOR; }
"="                 { return OP_ASSIGN; }

    /* DELIMITADORES Y PUNTUACIÓN */
"("                 { return PAR_IZQ; }
")"                 { return PAR_DER; }
"{"                 { return LLAVE_IZQ; }
"}"                 { return LLAVE_DER; }
"["                 { return CORCH_IZQ; }
"]"                 { return CORCH_DER; }
","                 { return COMA; }
";"                 { return PUNTO_COMA; }

    /* ERROR LÉXICO */
. { printf("\n[Línea %2d] *** Error léxico: %s\n", yylineno, yytext); }

%%
const char *nombres_tokens[] = {
    "TIPO_DATO", /* Comienza en 257 */
    "CTE_BOOLEANA",
    "IDENT",
    "CTE_ENTERA",  
    "CTE_REAL_CARACTER",
    "CTE_CADENA",       
    "PRINCIPAL",     
    "INICIO_VAR",   
    "FIN_VAR",     
    "SI",           
    "SINO",         
    "MIENTRAS",      
    "HACER",   
    "HASTA",      
    "LEER",       
    "ESCRIBIR",    
    "DEVOLVER",   
    "OP_SUMRES", 
    "OP_MULTDIV",   
    "OP_REL",       
    "OP_IGUAL",     
    "OP_UNARIO",
    "OP_AND", 
    "OP_OR",       
    "OP_XOR",    
    "OP_ASSIGN",   
    "PAR_IZQ",    
    "PAR_DER",     
    "LLAVE_IZQ",    
    "LLAVE_DER",   
    "CORCH_IZQ",      
    "CORCH_DER",     
    "COMA",            
    "PUNTO_COMA"    
};
const char *obtener_nombre_token(int codigo) {
    if (codigo >= 257 && codigo <= 290) {
        return nombres_tokens[codigo - 257];
    }
    return "DESCONOCIDO";
}

int main(int argc, char **argv)
{
    
    int val;

    printf("Analizador de Léxico - Lenguaje C\n\n");
    ++argv, --argc; /* saltamos el nombre del ejecutable */
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    val = yylex();
    while (val != 0)
    {
        printf("[ %16s ] :: %-18s", yytext, obtener_nombre_token(val));
        
        /* Solo si tiene atributo */
        if (val == IDENT)
            printf(" :: %s", yylval.cadena);
        else if (val == CTE_ENTERA ||val == TIPO_DATO || val == OP_SUMRES || val == OP_MULTDIV || val == OP_REL || val == OP_IGUAL || val == OP_UNARIO)
            printf(" :: atrib = %d", yylval.entero);
            
        printf("\n");
        val = yylex();

    }
    exit(0);
}