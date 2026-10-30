# *****************************************************************************
# ***
# *** Fichero : Makefile
# *** Funcion : Archivo makefile para generar el analizador de léxico.
# ***
# *****************************************************************************

lex.yy.c: lexico.l
	flex -l lexico.l

comp: lex.yy.c
	gcc -o lexico lex.yy.c

clean:
	rm -f lex.yy.c lexico
