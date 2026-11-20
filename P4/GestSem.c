/* ********************************************************************************
***
*** Fichero : GestSem.c
*** Funcion : Implementación de funciones para la gestión del A. Semántico
***
******************************************************************************* */

#include "GestSem.h"

/* ******************************************************************************
*** ANÁLISIS SEMÁNTICO - Apéndice F.2
****************************************************************************** */

// Punto 1: ya hecho en lexico.l con strdup(yytext) en IDENT

// Punto 2
void GS_DeclararVariable(char *nombre, unsigned int tipoEstr) {
    TS_InsertaVariable(nombre, (dtipo)tipoTmp, tipoEstr);
}

// Punto 3
void GS_InicioBloque(void) {
    TS_InsertaMarca();

    if (subProg) {
        for (unsigned int i = 1; i <= nParam; i++) {
            unsigned int idx = actualSubprog + i;
            if (idx < TOPE && TS[idx].entrada == PARAMETRO_FORMAL) {
                TS_InsertaVariable(TS[idx].nombre, TS[idx].tipoDato, TS[idx].tipoEstr);
            }
        }
        subProg = 0;
    }
}

// Punto 4
dtipo GS_ConvertirTipo(int atribTipo) {
    switch (atribTipo) {
        case 0:  return ENTERO;
        case 1:  return FLOTANTE;
        case 2:  return CARACTER;
        case 3:  return BOOLEANO;
        default: return DESCONOCIDO;
    }
}

// Punto 4
void GS_EstablecerTipoTmp(dtipo tipo) {
    tipoTmp = (unsigned int)tipo;
}

// Punto 5
void GS_FinBloque(void) {
    TS_Imprimir();
    TS_VaciarEntradas();
}

// Punto 6
void GS_InicioSubprograma(char *nombre, dtipo tipoRetorno) {
    TS_InsertaSubprograma(nombre, tipoRetorno);
    nParam = 0;
    subProg = 1;
    tipoSubprog = tipoRetorno;
}

// Punto 7
void GS_DeclararParametro(char *nombre, dtipo tipo, unsigned int tipoEstr) {
    TS_InsertaParamFormal(nombre, tipo, tipoEstr);
    nParam++;
}

// Punto 7
void GS_FinCabeceraSubprograma(void) {
    TS_ActualizaNParam(actualSubprog, nParam);
}

/* ******************************************************************************
*** ANÁLISIS SEMÁNTICO - Apéndice F.4
****************************************************************************** */

// Punto 1
dtipo GS_ObtenerTipoVariable(char *nombre) {
    int pos = TS_BuscarVariable(nombre);
    if (pos == -1) {
        printf("[Línea %2d] *** Error semántico: variable '%s' no declarada.\n",
               yylineno, (nombre != NULL) ? nombre : "?");
        return DESCONOCIDO;
    }
    return TS[pos].tipoDato;
}

// Punto 1
int GS_ObtenerSubprograma(char *nombre) {
    int pos = TS_BuscarSubprograma(nombre);
    if (pos == -1) {
        printf("[Línea %2d] *** Error semántico: subprograma '%s' no declarado o fuera de ámbito.\n",
               yylineno, (nombre != NULL) ? nombre : "?");
    }
    return pos;
}

// Punto 1
dtipo GS_ComprobarIndiceArray(dtipo tipoIdx) {
    if (tipoIdx != ENTERO && tipoIdx != DESCONOCIDO) {
        printf("[Línea %2d] *** Error semántico: el índice de un array debe ser de tipo ENTERO.\n",
               yylineno);
        return DESCONOCIDO;
    }
    return tipoIdx;
}

// Punto 2
void GS_ComprobarCondicion(dtipo tipoCond) {
    if (tipoCond != BOOLEANO && tipoCond != DESCONOCIDO) {
        printf("[Línea %2d] *** Error semántico: la condición de la sentencia de control debe ser BOOLEANO.\n",
               yylineno);
    }
}

// Punto 3
void GS_ComprobarAsignacion(dtipo tipoIzq, dtipo tipoDer) {
    if (tipoIzq != DESCONOCIDO && tipoDer != DESCONOCIDO && tipoIzq != tipoDer) {
        printf("[Línea %2d] *** Error semántico: tipos incompatibles en la asignación.\n",
               yylineno);
    }
}

// Punto 3
void GS_ComprobarDevolver(dtipo tipoExpr) {
    if (tipoExpr != DESCONOCIDO && tipoSubprog != NO_ASIGNADO && tipoExpr != tipoSubprog) {
        printf("[Línea %2d] *** Error semántico: el tipo de la expresión en 'devolver' no coincide con el de la función.\n",
               yylineno);
    }
}

// Punto 4
dtipo GS_ComprobarOpUnario(int op, dtipo tipo) {
    if (tipo == DESCONOCIDO) return DESCONOCIDO;

    if (op == 2) { // !
        if (tipo != BOOLEANO) {
            printf("[Línea %2d] *** Error semántico: el operador '!' requiere un operando BOOLEANO.\n",
                   yylineno);
            return DESCONOCIDO;
        }
        return BOOLEANO;
    } else { // ++ o --
        if (tipo != ENTERO && tipo != FLOTANTE) {
            printf("[Línea %2d] *** Error semántico: el operador unario requiere un operando numérico.\n",
                   yylineno);
            return DESCONOCIDO;
        }
        return tipo;
    }
}

// Punto 4
dtipo GS_ComprobarSignoUnario(dtipo tipo) {
    if (tipo == DESCONOCIDO) return DESCONOCIDO;

    if (tipo != ENTERO && tipo != FLOTANTE) {
        printf("[Línea %2d] *** Error semántico: el operador de signo unario requiere un operando numérico.\n",
               yylineno);
        return DESCONOCIDO;
    }
    return tipo;
}

// Punto 4
dtipo GS_ComprobarOpLogico(dtipo tipo1, dtipo tipo2) {
    if (tipo1 == DESCONOCIDO || tipo2 == DESCONOCIDO) return DESCONOCIDO;

    if (tipo1 != BOOLEANO || tipo2 != BOOLEANO) {
        printf("[Línea %2d] *** Error semántico: los operadores lógicos requieren operandos de tipo BOOLEANO.\n",
               yylineno);
        return DESCONOCIDO;
    }
    return BOOLEANO;
}

// Punto 4
dtipo GS_ComprobarOpIgualdad(dtipo tipo1, dtipo tipo2) {
    if (tipo1 == DESCONOCIDO || tipo2 == DESCONOCIDO) return DESCONOCIDO;

    if (tipo1 != tipo2) {
        printf("[Línea %2d] *** Error semántico: los operadores de igualdad requieren operandos del mismo tipo.\n",
               yylineno);
        return DESCONOCIDO;
    }
    return BOOLEANO;
}

// Punto 4
dtipo GS_ComprobarOpRelacional(dtipo tipo1, dtipo tipo2) {
    if (tipo1 == DESCONOCIDO || tipo2 == DESCONOCIDO) return DESCONOCIDO;

    if (tipo1 != tipo2 || (tipo1 != ENTERO && tipo1 != FLOTANTE)) {
        printf("[Línea %2d] *** Error semántico: los operadores relacionales requieren operandos numéricos del mismo tipo.\n",
               yylineno);
        return DESCONOCIDO;
    }
    return BOOLEANO;
}

// Punto 4
dtipo GS_ComprobarOpAritmetico(int op, dtipo tipo1, dtipo tipo2) {
    if (tipo1 == DESCONOCIDO || tipo2 == DESCONOCIDO) return DESCONOCIDO;

    if (op == 2) { // ** (producto matricial)
        if (tipo1 != tipo2 || (tipo1 != ENTERO && tipo1 != FLOTANTE && tipo1 != MATRIZ)) {
            printf("[Línea %2d] *** Error semántico: tipos incompatibles en el operador '**'.\n",
                   yylineno);
            return DESCONOCIDO;
        }
        return tipo1;
    }

    if (tipo1 != tipo2 || (tipo1 != ENTERO && tipo1 != FLOTANTE)) {
        printf("[Línea %2d] *** Error semántico: los operadores aritméticos requieren operandos numéricos del mismo tipo.\n",
               yylineno);
        return DESCONOCIDO;
    }
    return tipo1;
}

// Punto 4
void GS_ComprobarParametroLlamada(int posSubprog, unsigned int numArg, dtipo tipoArg) {
    if (posSubprog < 0) return;

    if (numArg <= TS[posSubprog].nParam) {
        unsigned int idxParam = (unsigned int)posSubprog + numArg;
        if (idxParam < TOPE && TS[idxParam].entrada == PARAMETRO_FORMAL) {
            if (tipoArg != DESCONOCIDO && tipoArg != TS[idxParam].tipoDato) {
                printf("[Línea %2d] *** Error semántico: tipo incorrecto en el argumento %u de la llamada a '%s'.\n",
                       yylineno, numArg, TS[posSubprog].nombre);
            }
        }
    }
}

// Punto 4
dtipo GS_ComprobarNumParamLlamada(int posSubprog, unsigned int numArgs) {
    if (posSubprog < 0) return DESCONOCIDO;

    if (numArgs != TS[posSubprog].nParam) {
        printf("[Línea %2d] *** Error semántico: número de argumentos incorrecto en la llamada a '%s' (esperados %u, recibidos %u).\n",
               yylineno, TS[posSubprog].nombre, TS[posSubprog].nParam, numArgs);
    }
    return TS[posSubprog].tipoDato;
}
