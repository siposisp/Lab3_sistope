FLAGS = -Wall -pthread

all: lab3

# Regla para generar el ejecutable lab3
lab3: lab3.o funciones.o
	gcc $(FLAGS) -o lab3 lab3.o funciones.o

funciones.o: funciones.c funciones.h
	gcc $(FLAGS) -c funciones.c

lab3.o: lab3.c funciones.h
	gcc $(FLAGS) -c lab3.c

# Limpiar archivos generados
clean:
	rm -f lab3 *.o
