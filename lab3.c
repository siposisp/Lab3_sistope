#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "funciones.h"

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
    debug = NULL;               // Se setea por defecto NULL para el caso en donde no se quiere hacer "debug"

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
            
            pthread_create(&tids[i], NULL, funcion, posicion);   //
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