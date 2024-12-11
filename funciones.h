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


// Función para llenar un arreglo con los números del archivo.
int* readFileToArray(char* filename, int size);

// Entradas: Recibe un char* correspondiente al nombre del archivo de output.
// Salida: No retorna nada.
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea.
void vaciar_archivo(char *nombreArchivo);

// Cuenta cuántos números hay en el archivo
int largo_arreglo(char* filename);


void guardar_en_archivo(char *nombreArchivo, int* arreglo, int largo);



// Función que ejecuta cada hebra
void* funcion(void* arg);



// Funcion que verifica si todos los elementos dentro de un arreglo son iguales
int iguales(int arreglo[], int tamano);
