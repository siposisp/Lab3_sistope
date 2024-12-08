#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

pthread_mutex_t lock; // Los mutex se ocupan como variable global
int* A;               // Arreglo global compartido
int cantidad_numeros; // Tamaño del arreglo
char* debug;


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

    // Actualizar el valor en el arreglo global
    pthread_mutex_lock(&lock); // Bloquear el acceso al recurso compartido para evitar condicion de carrera
    if (A[posicion] < A[posicion + 1]) {
        A[posicion] = A[posicion + 1]; // Asignar el mayor valor
    }

    if(posicion == cantidad_numeros-1){
        if(A[posicion] < A[0]){
            A[posicion] = A[0];
        }
    }

    // Imprimir por pantalla para hacer "debug"
    if (strcmp(debug, "debug") == 0) {
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


//Bloque Principal
int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA****************\n\n");

    // Se inicia el mutex
    pthread_mutex_init(&lock, NULL);

    // Variables para almacenar las opciones de línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = NULL;
    debug = NULL;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:o:D")) != -1) {
        switch (option) {
            case 'D':
                debug = "debug";    // Opcion para mostrar por stdout
                break;         
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'o':
                archivosalida = optarg; //Nombre del archivo de salida
                break;
            default:
                fprintf(stderr, "Uso: %s [-c columnas]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (archivoentrada == NULL) {
        // Si no se proporciona un archivo de entrada, pedir al usuario que ingrese el nombre
        char nombre_archivo[256];
        printf("Ingrese el nombre del archivo de entrada: ");
        
        if (fscanf(stdin, "%s", nombre_archivo) == 1) {  // Leer desde stdin
            archivoentrada = strdup(nombre_archivo); // Asignar el nombre del archivo a archivoentrada
        } else {
            fprintf(stderr, "Error al leer el nombre del archivo de entrada.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Contamos la cantidad de numeros en el arreglo
    cantidad_numeros = largo_arreglo(archivoentrada);
    
    // Transformamos los numeros del archivo en un arreglo
    A = readFileToArray(archivoentrada, cantidad_numeros); // Arreglo con los numeros de entrada

    int listo = 0; //Variable para controlar cuando todos los elementos del arreglo sean iguales
    while(!listo){
        // Creamos N hebras
        pthread_t tids[cantidad_numeros];
        for(int i=0;i<cantidad_numeros;i++){
            int* posicion = malloc(sizeof(int)); // Reservar memoria para el número
            *posicion = i;
            //printf("i: %d, contenido arreglo: %d\n", i, A[i]);

            pthread_create(&tids[i], NULL, funcion, posicion);
            //if(iguales(A, cantidad_numeros) && i == cantidad_numeros - 1){
            //    i = 0;
            //}
        }
        
        //Esperar a que terminen las hebras
        for(int i=0;i<cantidad_numeros;i++){
            pthread_join(tids[i], NULL);
        }
        listo = iguales(A, cantidad_numeros);

    }

    // Guardar arreglo final.
    if(archivosalida != NULL){
        // Llamado a la funcion vaciar_archivo
        vaciar_archivo(archivosalida); //Se limpia el archivo de salida, si es que existe
        guardar_en_archivo(archivosalida, A, cantidad_numeros);
    }
    
    free(A);
    pthread_mutex_destroy(&lock);

    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}