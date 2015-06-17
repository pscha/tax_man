#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000
#define NUM_THREADS 10

pthread_t tids[NUM_THREADS];
int  cherries[NUM_THREADS];

int all_cherries;

pthread_mutex_t mutex;
sem_t sem;


void *ThreadAdd(void * a)
{
    int index = (int)a;
    int i;

    for(i = 0; i < NITER; i++) {
      cherries[index]++;
      sem_wait(&sem);
      all_cherries++;
      sem_post(&sem);
    }
}

int main(int argc, char * argv[])
{
    long sum_cherries = 0;
    int i;

    sem_init( &sem, 0, 1 );

    for ( i = 0; i < NUM_THREADS; i++ ) {
      if (pthread_create(&(tids[i]), NULL, ThreadAdd, (void*)i)) {
        printf("\n ERROR creating thread 1");
        exit(1);
      }
    }

    for ( i = 0; i < NUM_THREADS; i++ ) {
      if (pthread_join(tids[i], NULL)) {
        printf("\n ERROR joining thread");
        exit(1);
      } else {
        sum_cherries += cherries[i];
        printf("%d ",cherries[i]);
      }
    }

    printf("MUST: %d ALL: %d\n",NITER*NUM_THREADS,all_cherries);

    pthread_exit(NULL);
}


