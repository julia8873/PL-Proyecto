# *****************************************************************************
# ***
# *** Fichero : Makefile
# *** Funcion : Compilar el analizador sintáctico (Bison + Flex + main.c)
# ***
# *****************************************************************************

analizador: sintactico.tab.c lex.yy.c main.c
	gcc -o analizador sintactico.tab.c lex.yy.c main.c

sintactico.tab.c sintactico.tab.h: sintactico.y
	bison -d -v sintactico.y

lex.yy.c: lexico.l sintactico.tab.h
	flex lexico.l

comp: analizador

clean:
	rm -f analizador lex.yy.c sintactico.tab.c sintactico.tab.h sintactico.output
