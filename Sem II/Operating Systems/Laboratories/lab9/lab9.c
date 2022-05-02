#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 2

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int g=0;

void *consumer(void *arg) {
    int id = *(int *)arg;
    printf("The consumer %d thread was started.\n", id);
    free(arg);

    while(1) {
        sleep(2);
        pthread_mutex_lock(&m);
        printf("Consumer %d read g: %d\n", id, g);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *producer(void *arg) {
    int id = *(int *)arg;
    printf("The producer %d was started\n", id);
    free(arg);
    while(1) {
        sleep(1);
        pthread_mutex_lock(&m);
        g=rand()%10+2;
        printf("Producer %d set g: %d\n", id, g);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
	pthread_t c[N];
    pthread_t prod[N];

    //pthread_mutext_init(&m, NULL);

    for(int i=0; i<N; i++) {
        //printf("Create the consumer %d.\n", i);
        int *p = (int *)malloc(sizeof(int));
        *p=i;
	    if(pthread_create(&c[i], NULL, consumer, p) < 0) {
		    perror("Unable to create a thread.");
		    exit(1);
	    }
	    //printf("The consumer %d was created.\n", i);
    }

    for(int i=0; i<N; i++) {
        //printf("Create the consumer %d.\n", i);
        int *p = (int *)malloc(sizeof(int));
        *p=i;
        if(pthread_create(&prod[i], NULL, producer, p) < 0) {
            perror("Unable to create a thread.");
            exit(1);
        }
        //printf("The consumer %d was created.\n", i);
    }


    for(int i=0; i<N; i++) {
        pthread_join(c[i], NULL);
    }

    for(int i=0; i<N; i++) {
        pthread_join(prod[i], NULL);
    }

    pthread_mutex_destroy(&m);

    return 0;
}
