#include "funciones.h"

pthread_mutex_t lock;        // Mutex para proteger el acceso al arreglo A
int* A = NULL;               // Arreglo global que contiene los números
int cantidad_numeros = 0;    // Número de elementos en el arreglo
char* debug = NULL;          // Variable de control para el debug

// Entradas: Recibe un char* correspondiente al nombre del archivo y un entero (int) "size" que indica el tamaño del arreglo.
// Salida: Retorna un puntero a un arreglo de enteros con los datos leidos del archivo.
// Descripción: Llena un arreglo con los numeros obtenidos de un archivo de texto.
int* readFileToArray(char* filename, int size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    int* array = malloc(size * sizeof(int));
    if (!array) {
        perror("Error al asignar memoria");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);
    return array;
}

// Entradas: Recibe un char* correspondiente al nombre del archivo de output.
// Salida: No retorna nada.
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea.
void vaciar_archivo(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "w");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    // Cerrar el archivo
    fclose(archivo);
}

// Entradas: Recibe un char* correspondiente al nombre del archivo.
// Salida: Retorna un entero que indica la cantidad de numeros en el archivo.
// Descripción: Cuenta cuántos números hay en el archivo.
int largo_arreglo(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    int tamano = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        tamano++;
    }
    fclose(file); // Cierra correctamente el archivo
    return tamano;
}

// Entradas: Recibe un char* correspondiente al nombre del archivo, un puntero a un arreglo de enteros y su largo.
// Salida: No retorna nada.
// Descripción: Guarda los elementos de un arreglo en un archivo, añadiendolos como nuevas lineas.
void guardar_en_archivo(char *nombreArchivo, int* arreglo, int largo){
    FILE *archivo = fopen(nombreArchivo, "a");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }
    
    // Escribir una nueva línea en el archivo
    for (int i=0; i<largo;i++){
        fprintf(archivo, "%d\n", arreglo[i]);
    }
    
    // Cerrar el archivo
    fclose(archivo);
}

// Entradas: Recibe un puntero genérico "arg" (void) que corresponde a la posicion del elemento del arreglo que sera procesado.
// Salida: Retorna NULL.
// Descripción: Procesa una posicion del arreglo global "A" para actualizar su valor con base en su posición anterior.
void* funcion(void* arg) {
    // Si todos los elementos del arreglo son iguales, salir
    if(iguales(A, cantidad_numeros)){
        return NULL;
    }
    // Extraer la posición y liberar memoria
    int posicion = *(int*)arg;
    free(arg);

    // Calcular la posición anterior considerando la circularidad
    int posicion_anterior;
    if (posicion == 0) {
        posicion_anterior = cantidad_numeros - 1;
    } else {
        posicion_anterior = posicion - 1;
    }

    // Actualizar el valor en el arreglo global
    pthread_mutex_lock(&lock); // Bloquear el acceso al recurso compartido para evitar condición de carrera
    int myval = A[posicion];   //valor inicial A[i]
    if (myval < A[posicion_anterior]) {
        A[posicion] = A[posicion_anterior]; // Asignar el mayor valor
    }

    // Imprimir por pantalla para hacer "debug"
    if (debug != NULL) {
        printf("Contenido del arreglo: [ ");
        for (int i = 0; i < cantidad_numeros; i++) {
            printf("%d ", A[i]);
        }
        printf("]\n");
    }

    pthread_mutex_unlock(&lock); // Desbloquear el recurso compartido

    return NULL;
}

// Entradas: Recibe un arreglo de enteros y su tamaño (int).
// Salida: Retorna 1 si todos los elementos del arreglo son iguales, en caso de no ser iguales retornara 0.
// Descripción: Verifica si todos los elementos dentro de un arreglo son iguales.
int iguales(int arreglo[], int tamano) {
    // Si el tamaño es 0 o 1, consideramos que todos son iguales
    if (tamano <= 1) {
        return 1;
    }

    // Comparamos todos los elementos con el primero
    for (int i = 1; i < tamano; i++) {
        if (arreglo[i] != arreglo[0]) {
            return 0;
        }
    }
    return 1;
}
