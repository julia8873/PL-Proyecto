/* ********************************************************************************
***
*** Fichero : GestSem.h
*** Funcion : Declaración de datos y funciones para la gestión del A. Semántico
***           y de Generación de Código Intermedio.
***
********************************************************************************* */

#ifndef __SEMANTICOGEST__
#define __SEMANTICOGEST__

#include <stdio.h>
#include <string.h>
#include "TS.h"

/* ******************************************************************************
*** Funciones para el Análisis Semántico - Apéndice F.2
****************************************************************************** */

// Punto 1: ya hecho en lexico.l con strdup(yytext) en IDENT

// Punto 2
void GS_DeclararVariable(char *nombre, unsigned int tipoEstr);

// Punto 3
void GS_InicioBloque(void);

// Punto 4
dtipo GS_ConvertirTipo(int atribTipo);
void GS_EstablecerTipoTmp(dtipo tipo);

// Punto 5
void GS_FinBloque(void);

// Punto 6
void GS_InicioSubprograma(char *nombre, dtipo tipoRetorno);

// Punto 7
void GS_DeclararParametro(char *nombre, dtipo tipo, unsigned int tipoEstr);
void GS_FinCabeceraSubprograma(void);

/* ******************************************************************************
*** Funciones para el Análisis Semántico - Apéndice F.4
****************************************************************************** */

// Punto 1
dtipo GS_ObtenerTipoVariable(char *nombre);
int GS_ObtenerSubprograma(char *nombre);
dtipo GS_ComprobarIndiceArray(dtipo tipoIdx);

// Punto 2
void GS_ComprobarCondicion(dtipo tipoCond);

// Punto 3
void GS_ComprobarAsignacion(dtipo tipoIzq, dtipo tipoDer);
void GS_ComprobarDevolver(dtipo tipoExpr);

// Punto 4
dtipo GS_ComprobarOpUnario(int op, dtipo tipo);
dtipo GS_ComprobarSignoUnario(dtipo tipo);
dtipo GS_ComprobarOpLogico(dtipo tipo1, dtipo tipo2);
dtipo GS_ComprobarOpIgualdad(dtipo tipo1, dtipo tipo2);
dtipo GS_ComprobarOpRelacional(dtipo tipo1, dtipo tipo2);
dtipo GS_ComprobarOpAritmetico(int op, dtipo tipo1, dtipo tipo2);
void GS_ComprobarParametroLlamada(int posSubprog, unsigned int numArg, dtipo tipoArg);
dtipo GS_ComprobarNumParamLlamada(int posSubprog, unsigned int numArgs);



#endif
