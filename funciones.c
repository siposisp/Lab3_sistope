#include "funciones.h"

pthread_mutex_t lock;        // Mutex para proteger el acceso al arreglo A
int* A = NULL;               // Arreglo global que contiene los números
int cantidad_numeros = 0;    // Número de elementos en el arreglo
char* debug = NULL;          // Variable de control para el debug

// Función para llenar un arreglo con los números del archivo.
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

// Cuenta cuántos números hay en el archivo
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



// Función que ejecuta cada hebra
void* funcion(void* arg) {
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
        printf("Contenido del arreglo:[");
        for (int i = 0; i < cantidad_numeros; i++) {
            printf("%d ", A[i]);
        }
        printf("]\n");
    }

    pthread_mutex_unlock(&lock); // Desbloquear el recurso compartido

    return NULL;
}



// Funcion que verifica si todos los elementos dentro de un arreglo son iguales
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
