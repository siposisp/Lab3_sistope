FLAGS = -Wall

all: lab3

# Regla para srep
funciones: funciones.o funciones.o
	gcc $(FLAGS) -o funciones funciones.o funciones.o

funciones.o: funciones.c funciones.h
	gcc $(FLAGS) -c funciones.c

funciones.o: funciones.c funciones.h
	gcc $(FLAGS) -c funciones.c

# Regla para lab3
lab3: lab3.o
	gcc $(FLAGS) -o lab3 lab3.o

lab3.o: lab3.c
	gcc $(FLAGS) -c lab3.c

# Limpiar archivos generados
clear:
	rm -f lab3 *.o
