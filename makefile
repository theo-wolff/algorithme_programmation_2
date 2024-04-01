main.o : main.c code.h
	gcc -c main.c
code.o : code.c code.h dico.h
	gcc -c code.c
dico.o : dico.c dico.h
	gcc -c dico.c
main : main.o code.o dico.o
	gcc main.o code.o dico.o -o main -lm

