#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_B = PTHREAD_MUTEX_INITIALIZER;

void *f_A(void *arg) {
    printf("Thread A started.\n");
    
    while(1) {
        pthread_mutex_lock(&m_A);
        printf("A\n");
        pthread_mutex_unlock(&m_B);
    }

    return NULL;
}

void *f_B(void *arg) {
    printf("Thread B started.\n");
    
    while(1) {
        pthread_mutex_lock(&m_B);
        printf("B\n");
        pthread_mutex_unlock(&m_A);
    }

    return NULL;
}

int main() {
    pthread_t A;
    pthread_t B;

    pthread_mutex_lock(&m_A);

    if(pthread_create(&A, NULL, f_A, NULL) < 0) {
        perror("Unable to create thread A.");
        exit(1);
    }

    if(pthread_create(&B, NULL, f_B, NULL) < 0) {
        perror("Unable to create thread B.");
        exit(2);
    }

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_mutex_destroy(&m_A);
    pthread_mutex_destroy(&m_B);

    return 0;
}
