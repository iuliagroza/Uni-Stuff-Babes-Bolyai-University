/*
 * N received from cmd
 *
 * global array N integer elements
 *
 * Thread i will alter N%i elements in an infinite loop.
 * Main will print once per second the global array content.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *g;

pthread_mutex_t *m;

typedef struct {
    int id;
    int count;
} thread_args;

void *rutine(void *a) {
    thread_args *v=(thread_args*)a;
    int id=v->id;
    int n=v->count;
    int pos = n%(id+1);
    printf("Thread %d started: %d.\n", id, pos);
    while(1) {
        printf("Thread %d waiting on %d.\n", id, pos);
        pthread_mutex_lock(&m[pos]);
        printf("Thread %d.\n", id);
        g[pos] = id;
        pthread_mutex_unlock(&m[pos]);
    }
    printf("Thread %d ended.\n", id);
    free(v);
    return NULL;
}

int main(int argc, char **argv) {
    int i;
    if(argc > 1) {
        int n = atoi(argv[1]);
        printf("Creating the global array of %d elements.\n", n);
        g=(int*)malloc(n*sizeof(int));
        m=(pthread_mutex_t*)malloc(n*sizeof(pthread_mutex_t));

        pthread_t *th = (pthread_t*)malloc(sizeof(pthread_t)*n);

        for(i=0; i<n; i++) {
            pthread_mutex_init(&m[i], NULL);
        }
        
        for(i=0; i<n; i++) {
            thread_args *ta = (thread_args*)malloc(sizeof(thread_args));
            ta->id=i;
            ta->count=n;
            if(pthread_create(&th[i], NULL, rutine, ta)<0) {
                perror("Unable to create a thread.");
                exit(2);
            }
        }

        while(1) {
            printf("Main thread waiting for lock.\n");
            for(i=0; i<n; i++) {
                pthread_mutex_lock(&m[i]);
            }
            printf("Main, g: \n");
            for(i=0; i<n; i++) {
                printf("%d \n", g[i]);
            }
            for(i=0; i<n; i++) {
                pthread_mutex_unlock(&m[i]);
            }
            printf("Main thread unlocked all.]\n");
            sleep(5);   
        }

        for(i=0; i<n; i++) {
            pthread_join(th[i], NULL);
        }

        for(i=0; i<n; i++) {
            pthread_mutex_destroy(&m[i]);
        }

        free(th);
        free(g);
    } else {
        perror("Usage: #ofThreads");
        exit(1);
    }        
    return 0;

}
