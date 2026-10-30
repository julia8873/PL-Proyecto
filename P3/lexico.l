%{
// *****************************************************************************
// ***
// *** Fichero : lexico.l
// *** Funcion : Especificación LEX del lenguaje (Práctica 3)
// ***
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintactico.tab.h"
%}

%option noyywrap
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
.                   { printf("\n[Línea %2d] *** Error léxico: %s\n", yylineno, yytext); }

%%
