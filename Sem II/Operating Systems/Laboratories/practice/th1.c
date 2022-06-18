#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t ma = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mb = PTHREAD_MUTEX_INITIALIZER;

void *fa(void *arg) {
    printf("Thread A started.\n");
    while(1) {
        pthread_mutex_lock(&ma);
        printf("A\n");
        pthread_mutex_unlock(&mb);
    }
    return NULL;
}

void *fb(void *arg) {
    printf("Thread B started.\n");
    while(1) {
        pthread_mutex_lock(&mb);
        printf("B\n");
        pthread_mutex_unlock(&ma);
    }
    return NULL;
}

int main() {
    pthread_t A, B;
    
    pthread_mutex_lock(&ma);

    if(pthread_create(&A, NULL, fa, NULL) < 0) {
        perror("Unable to create thread A.");
        exit(1);
    }
    
    if(pthread_create(&B, NULL, fb, NULL) < 0) {
        perror("Unable to create thread B.");
        exit(2);
    }

    pthread_join(A, NULL);
    pthread_join(B, NULL);

    pthread_mutex_destroy(&ma);
    pthread_mutex_destroy(&mb);
    return 0;
}
