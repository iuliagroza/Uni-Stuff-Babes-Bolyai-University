#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int n = 0;

void* thread(void *arg) {
        int id = *(int *)(arg);
        printf("Thread %d started\n", id);

        while(1) {
                pthread_mutex_lock(&m);
                if (n < 0 || n > 1000)
                {
                        pthread_mutex_unlock(&m);
                        break;
                }
                int p = rand()%1001 - 500;
                n += p;
                printf("Thread generated %d\n", n);
                pthread_mutex_unlock(&m);
        }
        return NULL;
}

int main() {
        pthread_t t1;
        pthread_t t2;

        srand(getpid());

        int id1 = 1;
        if (pthread_create(&t1, NULL, thread, &id1) < 0) {
                perror("Unable to create a thread\n");
                exit(1);
        }

        int id2 = 2;
        if (pthread_create(&t2, NULL, thread, &id2) < 0) {
                perror("Unable to create a thread\n");
                exit(1);
        }

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_mutex_destroy(&m);

        return 0;
}
