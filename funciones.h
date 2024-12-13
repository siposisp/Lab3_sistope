#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

extern pthread_mutex_t lock; // Los mutex se ocupan como variable global
extern int* A;               // Arreglo global compartido
extern int cantidad_numeros; // Tamaño del arreglo
extern char* debug;

// Entradas: Recibe un char* correspondiente al nombre del archivo y un entero (int) "size" que indica el tamaño del arreglo.
// Salida: Retorna un puntero a un arreglo de enteros con los datos leidos del archivo.
// Descripción: Llena un arreglo con los números obtenidos de un archivo de texto.
int* readFileToArray(char* filename, int size);

// Entradas: Recibe un char* correspondiente al nombre del archivo de output.
// Salida: No retorna nada.
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea.
void vaciar_archivo(char *nombreArchivo);

// Entradas: Recibe un char* correspondiente al nombre del archivo.
// Salida: Retorna un entero que indica la cantidad de numeros en el archivo.
// Descripción: Cuenta cuántos números hay en el archivo.
int largo_arreglo(char* filename);

// Entradas: Recibe un char* correspondiente al nombre del archivo, un puntero a un arreglo de enteros y su largo.
// Salida: No retorna nada.
// Descripción: Guarda los elementos de un arreglo en un archivo, añadiendolos como nuevas lineas.
void guardar_en_archivo(char *nombreArchivo, int* arreglo, int largo);

// Entradas: Recibe un puntero genérico "arg" (void) que corresponde a la posicion del elemento del arreglo que sera procesado.
// Salida: Retorna NULL.
// Descripción: Procesa una posicion del arreglo global "A" para actualizar su valor con base en su posición anterior.
void* funcion(void* arg);

// Entradas: Recibe un arreglo de enteros y su tamaño (int).
// Salida: Retorna 1 si todos los elementos del arreglo son iguales, en caso de no ser iguales retornara 0.
// Descripción: Verifica si todos los elementos dentro de un arreglo son iguales.
int iguales(int arreglo[], int tamano);
