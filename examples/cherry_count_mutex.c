#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 100000
#define NUM_THREADS 10

pthread_t tids[NUM_THREADS];
int  cherries[NUM_THREADS];

int all_cherries;

pthread_mutex_t mutex;

void *ThreadAdd(void * a)
{
    int index = (int)a;
    int i,j,y;

   y = 0;
    for(i = 0; i < NITER; i++) {
      cherries[index]++;
      while (pthread_mutex_trylock(&mutex) != 0) {
				y++;
				sched_yield();
      }
      //pthread_mutex_lock (&mutex);
      //for ( j = 0; j < 1000; j++) 
      all_cherries++;
      printf("Thread-ID: %d yield: %d\n", index, y);
      pthread_mutex_unlock (&mutex);
    }
}

int main(int argc, char * argv[])
{
    long sum_cherries = 0;
    int i;
/*
    for ( i = 0; i < NUM_THREADS; i++) {
      int j;
      for(j = 0; j < NITER; j++) {
        cherries[i]++;
        all_cherries++;
      }
    }

    printf("MUST: %d ALL: %d\n",NITER*NUM_THREADS,all_cherries);

   exit(0);
  */
    pthread_mutex_init (&mutex, NULL);

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


