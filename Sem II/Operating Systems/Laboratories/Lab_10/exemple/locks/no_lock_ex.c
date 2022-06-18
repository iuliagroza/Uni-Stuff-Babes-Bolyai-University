//
// no_lock_ex.c
//
// Increment a variable in 100 threads without using locks
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THR 100                             // maximum number of threads

int val = 0;

//
// The thread start routine
//
void* f(void* a)
{
    int k = *(int*)a;
    free(a);

    //int b = val;
    //sleep(1);
    //val = b + 1;

    val = val + 1;
    printf("Thread %2d - val: %d\n", k, val);

    return NULL;
}



int main(int argc, char* argv[])
{
    pthread_t tid[MAX_THR];                     // an array of thread IDs

    int i;
    for (i = 0; i < MAX_THR; i++)
    {
        int* p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_create(&tid[i], NULL, f, p);    // create a thread
    }

    for (i = 0; i < MAX_THR; i++)
    {
        pthread_join(tid[i], NULL);             // wait for each thread to finish
    }

    return 0;
}
