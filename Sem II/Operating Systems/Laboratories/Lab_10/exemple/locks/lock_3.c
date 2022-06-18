//
// lock_2.c - Using a semaphore
//
// sem_init()
// sem_destroy()
//
// sem_wait()
// sem_post()
//

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READ  100   // maximun number of readers
#define MAX_WRITE 10    // maximun number of readers

int seats = 100;        // initial number of seats
float price = 75.0f;    // initial price

sem_t sem;              // a semaphore

//
// Readers start routine
//
void* check(void* a)
{
  int k = (int)a;

  sem_wait(&sem);                   // lock

  printf("Reader %2d: Locuri %d, pret %f\n",
    k, seats, price * (2 - seats/100.0f));

  sem_post(&sem);                   // unlock

  return NULL;
}

//
// Writers start routine
//
void* buy(void* a)
{
  int k = (int)a;

  sem_wait(&sem);                   // lock

  printf("Writer %2d: Locul meu este %d, pret %f\n",
    k, seats, price * (2 - seats/100.0f));
  seats--;

  sem_post(&sem);                   // unlock

  return NULL;
}



int main(int argc, char* argv[])
{
  pthread_t tr[MAX_READ];
  pthread_t tw[MAX_WRITE];

  sem_init(&sem, 0, 1);             // init the semaphore
  
  int i;
  for (i = 0; i < MAX_READ; i++)
  {
    pthread_create(&tr[i], NULL,
      check, (void*)i);             // create readers
  }

  for (i = 0; i < MAX_WRITE; i++)
  {
    pthread_create(&tw[i], NULL,
      buy, (void*)i);               // create writers
  }

  for (i = 0; i < MAX_READ; i++)
  {
    pthread_join(tr[i], NULL);      // wait for readers to finish
  }

  for (i = 0; i < MAX_WRITE; i++)
  {
    pthread_join(tw[i], NULL);      // wait for writers to finish
  }

  sem_destroy(&sem);                // destroy the semaphore

  return 0;
}
