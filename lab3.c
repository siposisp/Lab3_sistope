#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>


// Función para llenar un arreglo con los números del archivo.
int* readFileToArray(const char* filename, int size) {
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

int largo_arreglo(char* filename){
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    int tamano = 0;
    int temp;

        // Cuenta los numeros leyendo linea por linea.
    while (fscanf(file, "%d", &temp) == 1) {
        tamano++;
    }

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


//Bloque Principal
int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA****************\n\n");

    // Variables para almacenar las opciones de línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = NULL;
    char* debug = NULL;

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
    int cantidad_numeros = largo_arreglo(archivoentrada);
    
    
    int* A = readFileToArray(archivoentrada, cantidad_numeros); // Arreglo con los numeros de entrada

    // Guardar arreglo final.
    if(archivosalida != NULL){
        // Llamado a la funcion vaciar_archivo
        vaciar_archivo(archivosalida); //Se limpia el archivo de salida, si es que existe
        guardar_en_archivo(archivosalida, A, cantidad_numeros);
    }

    
    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}