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

/* ========================================================================== */
/* DECLARACIÓN DE TOKENS                                                     */
/* ========================================================================== */

/* Palabras reservadas */
%token PRINCIPAL
%token INICIO_VAR FIN_VAR
%token SI SINO
%token MIENTRAS HACER HASTA
%token LEER ESCRIBIR DEVOLVER

/* Tipos de datos y constantes */
%token <entero> TIPO_DATO
%token <entero> CTE_BOOLEANA
%token <entero> CTE_ENTERA
%token <real> CTE_REAL
%token <caracter> CTE_CARACTER
%token <cadena> CTE_CADENA
%token <cadena> IDENT

/* Asignación y signos de puntuación */
%token OP_ASSIGN
%token PAR_IZQ PAR_DER
%token LLAVE_IZQ LLAVE_DER
%token CORCH_IZQ CORCH_DER
%token COMA PUNTO_COMA

/* Operadores con precedencia y asociatividad */
%left OP_OR
%left OP_XOR
%left OP_AND
%left OP_IGUAL
%left OP_REL
%left OP_SUMRES
%left OP_MULTDIV
%right OP_UNARIO

/* Precedencia para resolver el conflicto si-sino (dangling else) */
%precedence ENTONCES
%precedence SINO

/* Símbolo inicial */
%start Programa

%%

/* ==================================================================== */
/* 1. ESTRUCTURA GENERAL DEL PROGRAMA                                   */
/* ==================================================================== */

Programa
    : Cabecera_programa bloque
    ;

Cabecera_programa
    : TIPO_DATO PRINCIPAL PAR_IZQ PAR_DER
    ;

bloque
    : LLAVE_IZQ Declar_de_variables_locales Declar_de_subprogs Sentencias LLAVE_DER
    ;

Declar_de_subprogs
    : Declar_de_subprogs Declar_subprog
    | /* lambda */
    ;

Declar_subprog
    : Cabecera_subprog bloque
    ;

/* ==================================================================== */
/* 2. DECLARACIÓN DE VARIABLES LOCALES                                  */
/* ==================================================================== */

Declar_de_variables_locales
    : INICIO_VAR Variables_locales FIN_VAR
    | /* lambda */
    ;

Variables_locales
    : Variables_locales Cuerpo_declar_variables
    | Cuerpo_declar_variables
    ;

Cuerpo_declar_variables
    : Tipo_dato Lista_identificadores PUNTO_COMA
    | error
    ;

Tipo_dato
    : TIPO_DATO
    ;

Lista_identificadores
    : Lista_identificadores COMA Variable_declar
    | Variable_declar
    ;

Variable_declar
    : IDENT
    | IDENT CORCH_IZQ CTE_ENTERA CORCH_DER
    | IDENT CORCH_IZQ CTE_ENTERA CORCH_DER CORCH_IZQ CTE_ENTERA CORCH_DER
    ;

/* ==================================================================== */
/* 3. SUBPROGRAMAS (FUNCIONES)                                          */
/* ==================================================================== */

Cabecera_subprog
    : Tipo_dato IDENT PAR_IZQ Lista_parametros PAR_DER
    | Tipo_dato IDENT PAR_IZQ PAR_DER
    ;

Lista_parametros
    : Lista_parametros COMA Parametro
    | Parametro
    ;

Parametro
    : Tipo_dato Variable_declar
    | error
    ;

/* ==================================================================== */
/* 4. SENTENCIAS DEL LENGUAJE                                           */
/* ==================================================================== */

Sentencias
    : Sentencias Sentencia
    | Sentencia
    ;

Sentencia
    : bloque
    | sentencia_asignacion
    | sentencia_incdec
    | sentencia_si
    | sentencia_mientras
    | sentencia_entrada
    | sentencia_salida
    | sentencia_devolver
    | sentencia_hacer_hasta
    | llamada_funcion PUNTO_COMA
    | error
    ;

sentencia_asignacion
    : Variable_usar OP_ASSIGN expresion PUNTO_COMA
    ;

sentencia_incdec
    : OP_UNARIO Variable_usar PUNTO_COMA
    ;

sentencia_si
    : SI PAR_IZQ expresion PAR_DER Sentencia %prec ENTONCES
    | SI PAR_IZQ expresion PAR_DER Sentencia SINO Sentencia
    ;

sentencia_mientras
    : MIENTRAS PAR_IZQ expresion PAR_DER Sentencia
    ;

sentencia_entrada
    : LEER lista_variables PUNTO_COMA
    ;

sentencia_salida
    : ESCRIBIR lista_expresiones_o_cadena PUNTO_COMA
    ;

sentencia_devolver
    : DEVOLVER expresion PUNTO_COMA
    ;

sentencia_hacer_hasta
    : HACER bloque HASTA PAR_IZQ expresion PAR_DER PUNTO_COMA
    ;

lista_variables
    : lista_variables COMA Variable_usar
    | Variable_usar
    ;

lista_expresiones_o_cadena
    : lista_expresiones_o_cadena COMA elem_salida
    | elem_salida
    ;

elem_salida
    : expresion
    | CTE_CADENA
    ;

/* ==================================================================== */
/* 5. EXPRESIONES, OPERADORES Y VARIABLES                               */
/* ==================================================================== */

expresion
    : PAR_IZQ expresion PAR_DER
    | OP_UNARIO expresion
    | OP_SUMRES expresion %prec OP_UNARIO
    | expresion OP_OR expresion
    | expresion OP_XOR expresion
    | expresion OP_AND expresion
    | expresion OP_IGUAL expresion
    | expresion OP_REL expresion
    | expresion OP_SUMRES expresion
    | expresion OP_MULTDIV expresion
    | Variable_usar
    | constante
    | llamada_funcion
    | error
    ;

Variable_usar
    : IDENT
    | IDENT CORCH_IZQ expresion CORCH_DER
    | IDENT CORCH_IZQ expresion CORCH_DER CORCH_IZQ expresion CORCH_DER
    ;

llamada_funcion
    : IDENT PAR_IZQ lista_expresiones PAR_DER
    | IDENT PAR_IZQ PAR_DER
    ;

lista_expresiones
    : lista_expresiones COMA expresion
    | expresion
    ;

/* ==================================================================== */
/* 6. CONSTANTES Y ARRAYS                                               */
/* ==================================================================== */

constante
    : CTE_ENTERA
    | CTE_REAL
    | CTE_BOOLEANA
    | CTE_CARACTER
    | constante_array
    ;

constante_array
    : LLAVE_IZQ fila_array LLAVE_DER
    | LLAVE_IZQ lista_filas LLAVE_DER
    ;

fila_array
    : lista_expresiones
    ;

lista_filas
    : fila_array PUNTO_COMA fila_array
    | lista_filas PUNTO_COMA fila_array
    ;

%%

