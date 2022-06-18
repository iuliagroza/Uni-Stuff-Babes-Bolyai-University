//
// cond_var.c - Using a condition variable
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_NUM 1000  // maximum number of integers
#define MAX_THR 10    // maximum number of threads
#define MAX_STEP 100

int fd;
int sum = 0;

int flag = 0;        // 0 = empty buffer, 1 = full buffer
int buffer[1000];

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

//
// Function to check if buffer is empty
//
int is_empty()
{
  if (flag == 0)
    return 1;

  return 0;
}

//
// Function to check if buffer is full
//
int is_full()
{
  if (flag == 1)
    return 1;

  return 0;
}

//
// Consumers start routine
//
void* consume(void* a)
{
  int cnum = *(int*)a;  // consumer number
  free(a);

  printf("[Consumer %d] Starting ...\n", cnum);

  pthread_mutex_lock(&mtx);
  while (is_empty())
  {
    printf("[Consumer %d] Buffer is empty. I'm waiting to become full ...\n", cnum);
    pthread_cond_wait(&cv, &mtx);
  }

  printf("[Consumer %d] Buffer is full. Start consumption ...\n", cnum);

  int start = cnum * MAX_STEP;    // index to start
  int finish = start + MAX_STEP;  // index to finish

  int i = start;
  while (i < finish)
  {
    sum += buffer[i];
    i++;
  }
  
  flag = 0;

  printf("[Consumer %d] Finished consumption. Buffer is now empty.\n", cnum);

  pthread_cond_signal(&cv);
  pthread_mutex_unlock(&mtx);

  return NULL;
}

//
// Producers start routine
//
void* produce(void* a)
{
  int pnum = *(int*)a;  // producer number
  free(a);

  printf("[Producer %d] Starting ...\n", pnum);

  pthread_mutex_lock(&mtx);
  while (is_full())
  {
    printf("[Producer %d] Buffer is full. I'm waiting to become empty ...\n", pnum);
    pthread_cond_wait(&cv, &mtx);
  }

  printf("[Producer %d] Buffer is empty. Start production ...\n", pnum);

  int start = pnum * MAX_STEP;    // index to start
  int finish = start + MAX_STEP;  // index to finish

  int i = start;
  while (i < finish)
  {
    read(fd, &buffer[i], 2);
    i++;
  }
    
  flag = 1;

  printf("[Producer %d] Finished production. Buffer is now full.\n", pnum);

  pthread_cond_signal(&cv);
  pthread_mutex_unlock(&mtx);

  return NULL;
}



int main(int argc, char* argv[])
{
  pthread_t tc[MAX_THR];  // an array of consumers
  pthread_t tp[MAX_THR];  // an array of producers

  fd = open("random-file", O_RDONLY);
  if (fd < 0)
  {
    perror("open: ");
    exit(EXIT_FAILURE);
  }
  
  int i;
  for (i = 0; i < MAX_THR; i++)
  {
    int *k = (int*)malloc(sizeof(int));
    *k = i;                                   // thread number
    pthread_create(&tp[i], NULL, produce, k); // create a producer thread
    pthread_create(&tc[i], NULL, consume, k); // create a consumer thread
  }

  for (i = 0; i < MAX_THR; i++)
  {
    pthread_join(tp[i], NULL);                // wait for each producer to finish
    pthread_join(tc[i], NULL);                // wait for each consumer to finish
  }

  printf("Sum: %d\n", sum);

  close(fd);

  return 0;
}
