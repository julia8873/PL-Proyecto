#ifndef TS_H
#define TS_H

// Enumerado para el tipo de elemento de la TS
typedef enum {  
    NO_ASIGNADO=0,                    // Tipo aún sin asignación.
    ENTERO,                           // Tipo básico entero.
    FLOTANTE,                         // Tipo básico flotante.
    CARACTER,                         // Tipo básico carácter.
    BOOLEANO,                         // Tipo básico booleano.
    MATRIZ,                           // Tipo estructurado como tipo básico (el asignado al grupo).
    DESCONOCIDO                       // Cuando el tipo que se asigne sea incorrecto o desconocido.
} dtipo ;


// Enumerado para el tipo de entrada en la TS
typedef enum {
    MARCA = 0,         // Marca de inicio de bloque.
    SUBPROGRAMA,       // Entrada de subprograma (función o procedimiento, según lenguaje asignado).
    VARIABLE,          // Entrada de una variable.
    PARAMETRO_FORMAL   // Entrada de un parámetro formal de un subprograma
} tipoEntrada ;

// Estructura para un elemento de la TS
typedef struct {
    tipoEntrada entrada ;    // Tipo de entrada en la TS (marca, variable, ...).
    char *nombre ;           // Nombre en caso de variable o subprograma.
    dtipo tipoDato ;         // Tipo en caso de variable o subprograma.
    unsigned int tipoEstr ;  // Indicativo si la entrada es de tipo estructurado o no.
    unsigned int nParam ;    // Número de parámetros, si es subprograma.
} entradaTS ;

//---------------------------------------------------
// Dimensión máxima del array representativo de la TS

#define MAX_TS 500                   // Máximo número de entradas en nuestra TS.

//--------------------------------------------------------
// Variables internas que se usarán en la gestión de la TS

extern unsigned int TOPE ;           // Representa el índice del tope de la pila de la TS.
extern unsigned int subProg ;        // Iindicativo de inicio del bloque de un subprograma.
extern unsigned int tipoTmp ;        // Valor temporal usado para el tipo de una variable en declaración.
extern dtipo tipoSubprog ;           // Tipo que devolverá un subprograma.
extern unsigned int actualSubprog ;  // Entrada de la TS de un subprograma (para comprobar sus datos).
extern unsigned int nParam ;         // Valor del número de parámetros formales de un sobprograma.

extern int yylineno ;                // Este valor representará el número de línea que se está leyendo.

//------------------------------------------------
// Pila de la TS representada como un array 1D

extern entradaTS TS[MAX_TS] ;

//------------------------------------------------
// Declaración de la estructura de los atributos para los símbolos terminales y 
// no terminales de la gramática.

typedef struct {
    int atrib ;      // Atributo del símbolo (en su caso).
    char *cadena ;   // Nombre del lexema.
    dtipo tipo ;     // Tipo de elemento.
} atributos ;

//------------------------------------------------
// Asignación del tipo atributos a los símbolos gramaticales.

#define YYSTYPE atributos

//------------------------------------------------
// Prototipos de funciones para el manejo de la TS

void TS_InsertaEntrada(entradaTS ent);
int TS_Buscar(char *nombre);
void TS_EliminaEntrada(void);
void TS_VaciarEntradas(void);
int TS_BuscarVariable(char *nombre);
int TS_BuscarSubprograma(char *nombre);
void TS_InsertaVariable(char *nombre, dtipo tipo, unsigned int tipoEstr);
void TS_InsertaMarca(void);
void TS_InsertaSubprograma(char *nombre, dtipo tipoRetorno);
void TS_InsertaParamFormal(char *nombre, dtipo tipo, unsigned int tipoEstr);
void TS_ActualizaNParam(unsigned int posSubprog, unsigned int numParam);

// Funciones de apoyo / depuración de la TS

void TS_MostrarEntrada(int pos);
void TS_MostrarTipoEntrada(tipoEntrada tipo);
void TS_MostrarTipoDato(dtipo tipo);
void TS_Imprimir(void);

#endif