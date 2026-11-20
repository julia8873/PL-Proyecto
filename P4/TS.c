#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS.h"

// Definición de las variables globales de la TS
unsigned int TOPE = 0;
unsigned int subProg = 0;
unsigned int tipoTmp = 0;
dtipo tipoSubprog = NO_ASIGNADO;
unsigned int actualSubprog = 0;
unsigned int nParam = 0;

entradaTS TS[MAX_TS];

//------------------------------------------------
// Funciones para el manejo de la TS

void TS_InsertaEntrada(entradaTS ent) {
    // A IMPLEMENTAR
}

int TS_Buscar(char *nombre) {
    // A IMPLEMENTAR
    return -1;
}

void TS_EliminaEntrada(void) {
    // A IMPLEMENTAR
}

void TS_VaciarEntradas(void) {
    // A IMPLEMENTAR
}

int TS_BuscarVariable(char *nombre) {
    // A IMPLEMENTAR
    return -1;
}

int TS_BuscarSubprograma(char *nombre) {
    // A IMPLEMENTAR
    return -1;
}

void TS_InsertaVariable(char *nombre, dtipo tipo, unsigned int tipoEstr) {
    // A IMPLEMENTAR
}

void TS_InsertaMarca(void) {
    // A IMPLEMENTAR
}

void TS_InsertaSubprograma(char *nombre, dtipo tipoRetorno) {
    // A IMPLEMENTAR
}

void TS_InsertaParamFormal(char *nombre, dtipo tipo, unsigned int tipoEstr) {
    // A IMPLEMENTAR
}

void TS_ActualizaNParam(unsigned int posSubprog, unsigned int numParam) {
    // A IMPLEMENTAR
}

//------------------------------------------------
// Funciones de apoyo / depuración de la TS

void TS_MostrarEntrada(int pos) {
    // A IMPLEMENTAR
}

void TS_MostrarTipoEntrada(tipoEntrada tipo) {
    // A IMPLEMENTAR
}

void TS_MostrarTipoDato(dtipo tipo) {
    // A IMPLEMENTAR
}

void TS_Imprimir(void) {
    // A IMPLEMENTAR
}
