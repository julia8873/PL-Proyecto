/* ********************************************************************************
***
*** Fichero : GestSem.c
*** Funcion : Implementación de funciones para la gestión del A. Semántico
***
******************************************************************************* */

#include "GestSem.h"

unsigned int nParam;         // Número de parámetros de un subprograma.
unsigned int TOPE = 0;       // Apuntador al tope de la Pila de la TS.
unsigned int subProg;        // Indicativo de inicio de bloque de un subprograma.
unsigned int tipoTmp;        // Tipo de variable de una lista de variables.
                             // En C, se indica el tipo y luego una lista.
dtipo tipoSubprog;           // Tipo que devuelve una función.
unsigned int actualSubprog;  // Entrada de la TS de un subprograma.

/* ******************************************************************************
*** ANÁLISIS SEMÁNTICO
****************************************************************************** */



/* ******************************************************************************
*** GENERACIÓN DE CÓDIGO INTERMEDIO
****************************************************************************** */



