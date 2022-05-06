#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int fr[10];

pthread_mutex_t m[10];

void *thread(void *arg) {
    char* number = (char*)arg;
    printf("Thread started\n");
    for (int i = 0; i < strlen(number); i++) {
        int digit = number[i] - '0';
        pthread_mutex_lock(&m[digit]);
        fr[digit]++;
            pthread_mutex_unlock(&m[digit]);
    }

    return NULL;
}

int main(int argc, char** args) {
    pthread_t* tr = (pthread_t*)(malloc(argc * sizeof(pthread_t)));

    for(int i = 0; i < 10; i++) {
        pthread_mutex_init(&m[i], NULL);
    }

    for (int i = 1; i < argc; i++) {
        printf("%s\n", args[i]);
        if (pthread_create(&tr[i - 1], NULL, thread, args[i]) < 0) {
            perror("Unable to create a thread\n");
            exit(1);
        }
    }

    for(int i = 0; i < argc - 1; i++) {
        pthread_join(tr[i], NULL);
    }

    for(int i = 0; i < 10; i++) {
        pthread_mutex_destroy(&m[i]);
    }

    for(int i = 0; i < 10; i++) {
        printf("%d ", fr[i]);
    }
    printf("\n");

    return 0;
}
