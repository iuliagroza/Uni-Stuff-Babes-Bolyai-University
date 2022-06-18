//
// thread_4.c - Thread creation example
//
// pthread_create() - create a thread
// pthread_join()   - wait for termination of another thread
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUM 100                     // maximum number of threads

//
// The thread start routine
//
void* f(void* a)
{
  int k = *(int *)a;
  free(a);                              // dealocate

  printf("Eu sunt thread-ul %d\n", k);

  return NULL;
}



int main(int argc, char* argv[])
{
  pthread_t t[MAX_NUM];
  
  int i;
  int* p;
  for (i = 0; i < MAX_NUM; i++)
  {
    p = (int *)malloc(sizeof(int));      // dynamic allocation
    *p = i;

    pthread_create(&t[i], NULL, f, p);
  }

  for (i = 0; i < MAX_NUM; i++)
  {
    pthread_join(t[i], NULL);
  }

  return 0;
}