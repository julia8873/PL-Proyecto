# *****************************************************************************
# ***
# *** Fichero : Makefile
# *** Funcion : Compilar el analizador semántico (Bison + Flex + TS + GestSem + main.c)
# ***
# *****************************************************************************

CC = gcc
CFLAGS = -Wall -g

analizador: semantico.tab.o TS.o GestSem.o main.o
	$(CC) $(CFLAGS) -o analizador semantico.tab.o TS.o GestSem.o main.o

semantico.tab.o: semantico.tab.c lex.yy.c GestSem.h TS.h
	$(CC) $(CFLAGS) -c semantico.tab.c

TS.o: TS.c TS.h
	$(CC) $(CFLAGS) -c TS.c

GestSem.o: GestSem.c GestSem.h TS.h
	$(CC) $(CFLAGS) -c GestSem.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

semantico.tab.c semantico.tab.h: semantico.y
	bison -d -v semantico.y

lex.yy.c: lexico.l semantico.tab.h
	flex lexico.l

comp: analizador

clean:
	rm -f analizador *.o lex.yy.c semantico.tab.c semantico.tab.h semantico.output
