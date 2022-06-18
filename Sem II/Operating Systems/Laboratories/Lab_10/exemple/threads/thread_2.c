//
// thread_2.c - Thread creation example
//
// pthread_create() - create a thread
// pthread_join()   - wait for termination of another thread
//

#include <stdio.h>
#include <pthread.h>

#define MAX_NUM 100                     // maximum number of threads

//
// The thread start routine
//
void* f(void* a)
{
  int k = (int)a;
  printf("Eu sunt thread-ul %d\n", k);

  return NULL;
}



int main(int argc, char* argv[])
{
  pthread_t t[MAX_NUM];
  
  int i;
  for (i = 0; i < MAX_NUM; i++)
  {
    pthread_create(&t[i], NULL, f, (void *)i);
  }

  for (i = 0; i < MAX_NUM; i++)
  {
    pthread_join(t[i], NULL);
  }

  return 0;
}