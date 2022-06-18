/*
 * N threads A - rand(2-5) add random element from a global array
 *
 * 2 threads B - once per 2 sec. will print the array
 */
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define N 100

int ga[N];

pthread_mutex_t m[N];

void *fa(void *a) {
    int id=*(int*)a;
    free(a);
    printf("Thread a[%d] started.\n", id);
    
    while(1) {
        // select a random element
        // add a random value (2, 5) to it
        int i=rand()%N;
        int r=rand()%4+2;
        printf("Thread a[%d] altering ga[%d]+=%d.\n", id, i, r);
        pthread_mutex_lock(&m[i]);
        ga[i] += r;
        sleep(1);
        pthread_mutex_unlock(&m[i]);
    }
    return NULL;
}

void *fb(void *a) {
    printf("Thread B started.\n");
    
    while(1) {
        //print ga once per 2 seconds

        for(int i=0; i<N; i++) {
            pthread_mutex_lock(&m[i]);
        }

        for(int i=0; i<N; i++) {
            //pthread_mutex_lock(&m[i]);
            printf("%d ", ga[i]);
            //pthread_mutex_unlock(&m[i]);
        }
        printf("\n");

        for(int i=0; i<N; i++) {
            pthread_mutex_unlock(&m[i]);
        }

        sleep(2);
    }
}

int main(int argc, char **argv) {
    if(argc > 1) {
        int n=atoi(argv[1]);
        printf("N: %d\n", n);


        pthread_t b1, b2;
        pthread_t *th = (pthread_t*)malloc(n*sizeof(pthread_t));

        for(int i=0; i<N; i++) {
            pthread_mutex_init(&m[i], NULL);
        }
        
        for(int i=0; i<n; i++) {
            int *p = (int*)malloc(sizeof(int));
            *p=i;
            if(pthread_create(&th[i], NULL, fa, p) < 0) {
                perror("Unable to create a thread of type a");
                exit(1);
            }
        }

        if(pthread_create(&b1, NULL, fb, NULL) < 0) {
            perror("Unable to create a thread of type b");
            exit(2);
        }

        if(pthread_create(&b2, NULL, fb, NULL) < 0) {
            perror("Unable to create a thread of type b");
            exit(3);
        }

        for(int i=0; i<n; i++) {
            pthread_join(th[i], NULL);
        }

        for(int i=0; i<N; i++) {
            pthread_mutex_destroy(&m[i]);
        }

        free(th);
    } else {
        printf("Usage #thread of type a\n");
        exit(4);
    }
    return 0;
}
