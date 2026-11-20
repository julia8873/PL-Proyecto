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
// Funciones auxiliares internas

static int TS_ExisteEnBloqueActual(char *nombre) {
    if (nombre == NULL) return 0;

    for (int i = (int)TOPE - 1; i >= 0; i--) {
        if (TS[i].entrada == MARCA) {
            break;
        }
        if (TS[i].entrada != PARAMETRO_FORMAL &&
            TS[i].nombre != NULL &&
            strcmp(TS[i].nombre, nombre) == 0) {
            return 1;
        }
    }
    return 0;
}

//------------------------------------------------
// Funciones para el manejo de la TS

void TS_InsertaEntrada(entradaTS ent) {
    if (TOPE >= MAX_TS) {
        fprintf(stderr, "[Línea %2d] *** Error semántico: desbordamiento de la Tabla de Símbolos (MAX_TS = %d).\n",
                yylineno, MAX_TS);
        exit(EXIT_FAILURE);
    }

    TS[TOPE] = ent;
    TOPE++;
}

int TS_Buscar(char *nombre) {
    if (nombre == NULL) return -1;

    for (int i = (int)TOPE - 1; i >= 0; i--) {
        if (TS[i].entrada != MARCA &&
            TS[i].entrada != PARAMETRO_FORMAL &&
            TS[i].nombre != NULL &&
            strcmp(TS[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void TS_EliminaEntrada(void) {
    if (TOPE > 0) {
        TOPE--;
        if (TS[TOPE].nombre != NULL) {
            free(TS[TOPE].nombre);
            TS[TOPE].nombre = NULL;
        }
    }
}

void TS_VaciarEntradas(void) {
    while (TOPE > 0) {
        tipoEntrada tipo = TS[TOPE - 1].entrada;
        TS_EliminaEntrada();
        if (tipo == MARCA) {
            break;
        }
    }
}

int TS_BuscarVariable(char *nombre) {
    if (nombre == NULL) return -1;

    for (int i = (int)TOPE - 1; i >= 0; i--) {
        if (TS[i].entrada == VARIABLE &&
            TS[i].nombre != NULL &&
            strcmp(TS[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

int TS_BuscarSubprograma(char *nombre) {
    if (nombre == NULL) return -1;

    for (int i = (int)TOPE - 1; i >= 0; i--) {
        if (TS[i].entrada == SUBPROGRAMA &&
            TS[i].nombre != NULL &&
            strcmp(TS[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void TS_InsertaVariable(char *nombre, dtipo tipo, unsigned int tipoEstr) {
    if (TS_ExisteEnBloqueActual(nombre)) {
        printf("[Línea %2d] *** Error semántico: identificador '%s' ya declarado en el mismo bloque.\n",
               yylineno, nombre);
        return;
    }

    entradaTS ent;
    ent.entrada = VARIABLE;
    ent.nombre = (nombre != NULL) ? strdup(nombre) : NULL;
    ent.tipoDato = tipo;
    ent.tipoEstr = tipoEstr;
    ent.nParam = 0;

    TS_InsertaEntrada(ent);
}

void TS_InsertaMarca(void) {
    entradaTS ent;
    ent.entrada = MARCA;
    ent.nombre = NULL;
    ent.tipoDato = NO_ASIGNADO;
    ent.tipoEstr = 0;
    ent.nParam = 0;

    TS_InsertaEntrada(ent);
}

void TS_InsertaSubprograma(char *nombre, dtipo tipoRetorno) {
    if (TS_ExisteEnBloqueActual(nombre)) {
        printf("[Línea %2d] *** Error semántico: subprograma '%s' ya declarado en el mismo bloque.\n",
               yylineno, nombre);
        return;
    }

    entradaTS ent;
    ent.entrada = SUBPROGRAMA;
    ent.nombre = (nombre != NULL) ? strdup(nombre) : NULL;
    ent.tipoDato = tipoRetorno;
    ent.tipoEstr = 0;
    ent.nParam = 0;

    actualSubprog = TOPE;
    TS_InsertaEntrada(ent);
}

void TS_InsertaParamFormal(char *nombre, dtipo tipo, unsigned int tipoEstr) {
    if (nombre != NULL) {
        for (int i = (int)TOPE - 1; i > (int)actualSubprog; i--) {
            if (TS[i].entrada != PARAMETRO_FORMAL) {
                break;
            }
            if (TS[i].nombre != NULL && strcmp(TS[i].nombre, nombre) == 0) {
                printf("[Línea %2d] *** Error semántico: parámetro formal '%s' duplicado.\n",
                       yylineno, nombre);
                return;
            }
        }
    }

    entradaTS ent;
    ent.entrada = PARAMETRO_FORMAL;
    ent.nombre = (nombre != NULL) ? strdup(nombre) : NULL;
    ent.tipoDato = tipo;
    ent.tipoEstr = tipoEstr;
    ent.nParam = 0;

    TS_InsertaEntrada(ent);
}

void TS_ActualizaNParam(unsigned int posSubprog, unsigned int numParam) {
    if (posSubprog < TOPE && TS[posSubprog].entrada == SUBPROGRAMA) {
        TS[posSubprog].nParam = numParam;
    }
}

//------------------------------------------------
// Funciones de apoyo / depuración de la TS

void TS_MostrarTipoEntrada(tipoEntrada tipo) {
    switch (tipo) {
        case MARCA:            printf("%-16s", "MARCA"); break;
        case SUBPROGRAMA:      printf("%-16s", "SUBPROGRAMA"); break;
        case VARIABLE:         printf("%-16s", "VARIABLE"); break;
        case PARAMETRO_FORMAL: printf("%-16s", "PARAMETRO_FORMAL"); break;
        default:               printf("%-16s", "OTRO"); break;
    }
}

void TS_MostrarTipoDato(dtipo tipo) {
    switch (tipo) {
        case NO_ASIGNADO: printf("%-12s", "NO_ASIGNADO"); break;
        case ENTERO:      printf("%-12s", "ENTERO"); break;
        case FLOTANTE:    printf("%-12s", "FLOTANTE"); break;
        case CARACTER:    printf("%-12s", "CARACTER"); break;
        case BOOLEANO:    printf("%-12s", "BOOLEANO"); break;
        case MATRIZ:      printf("%-12s", "MATRIZ"); break;
        case DESCONOCIDO: printf("%-12s", "DESCONOCIDO"); break;
        default:          printf("%-12s", "DESCONOCIDO"); break;
    }
}

void TS_MostrarEntrada(int pos) {
    if (pos < 0 || pos >= (int)TOPE) {
        return;
    }

    printf("[%3d] ", pos);
    TS_MostrarTipoEntrada(TS[pos].entrada);
    printf(" | %-15s | ", (TS[pos].nombre != NULL) ? TS[pos].nombre : "-");
    TS_MostrarTipoDato(TS[pos].tipoDato);
    printf(" | Estr: %u | nParam: %u\n", TS[pos].tipoEstr, TS[pos].nParam);
}

void TS_Imprimir(void) {
    printf("\n==================== TABLA DE SÍMBOLOS (TOPE=%u) ====================\n", TOPE);
    for (int i = 0; i < (int)TOPE; i++) {
        TS_MostrarEntrada(i);
    }
    printf("=====================================================================\n");
}
