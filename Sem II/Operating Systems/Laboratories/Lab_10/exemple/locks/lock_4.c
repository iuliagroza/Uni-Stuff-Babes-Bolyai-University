//
// lock_2.c - Using read-write lock object
//
// pthread_rwlock_init()    - initialize a read-write lock object
// pthread_rwlock_destroy() - destroy the read-write lock object
//
// pthread_rwlock_rdlock()
// pthread_rwlock_wrlock()
// pthread_rwlock_unlock()
//

#include <stdio.h>
#include <pthread.h>

#define MAX_READ  100   // maximun number of readers
#define MAX_WRITE 10    // maximun number of readers

int seats = 100;        // initial number of seats
float price = 75.0f;    // initial price

pthread_rwlock_t rwl;   // a read-write lock

//
// Readers start routine
//
void* check(void* a)
{
  int k = (int)a;

  pthread_rwlock_rdlock(&rwl);      // lock for read

  printf("Reader %2d: Locuri %d, pret %f\n",
    k, seats, price * (2 - seats/100.0f));

  pthread_rwlock_unlock(&rwl);      // unlock

  return NULL;
}

//
// Writers start routine
//
void* buy(void* a)
{
  int k = (int)a;

  pthread_rwlock_wrlock(&rwl);      // lock for write

  printf("Writer %2d: Locul meu este %d, pret %f\n",
    k, seats, price * (2 - seats/100.0f));
  seats--;

  pthread_rwlock_unlock(&rwl);      // unlock

  return NULL;
}



int main(int argc, char* argv[])
{
  pthread_t tr[MAX_READ];
  pthread_t tw[MAX_WRITE];

  pthread_rwlock_init(&rwl, NULL);  // init a read-write lock
  
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

  pthread_rwlock_destroy(&rwl);     // destroy the read-write lock

  return 0;
}
