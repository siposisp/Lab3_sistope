#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int contador = 0;
pthread_mutex_t lock; // Los mutex se ocupan como variable global

void * funcion(void * msg){
    int cont = 0;
    cont++;
    char * msg1= (char*)msg;

    pthread_mutex_lock(&lock);
    contador++;
    printf("%s, Global: %d, Local: %d\n",msg1,contador,cont);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main () {

    // Se inicia el mutex
    pthread_mutex_init(&lock, NULL);

    // Para N hebras
    char mensaje[20] = "Mensaje";
    pthread_t tids[5];
    for(int i=0;i<5;i++){
        pthread_create(&tids[i], NULL, funcion, (void*)mensaje);
    }
    for(int i=0;i<5;i++){
        pthread_join(tids[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    printf("Termino el proceso.\n");
    return 0;
}





