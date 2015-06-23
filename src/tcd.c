#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>

/** NUM_COLLECTORS specifies,how much tax collectors are in the game. */
#define NUM_COLLECTORS  5
#define START_AMOUNT_OF_MONEY   300

pthread_d threads[NUM_COLLECTORS];
int moneys[NUM_COLLECTORS];

int ein;
int aus;

void *tax_collector(void *thread_id){
	(int) thread_id;
	
	int
}

int main(int argc, char **argv)
{
    int num_collectors = NUM_COLLECTORS;
    int amount_money = start_money = START_AMOUNT_OF_MONEY;
	int i;
	int test;
    int a;    
    
    (void)a;
    
    if ( argc > 1 ) {
      num_collectors = atoi(argv[1]);
      if ( argc > 2 ) start_money = atoi(argv[2]);
    }

    printf("Tax Collectors: %d\nAmount of money: %d\n",num_collectors,start_money);
   
	/* initialize the moneys array */
	i = 0;
	while(amount_money > 0){
		if(amount_money < 100)
			moneys[i] += amount_money;
		}
		else{
			moneys[i] += 100;
		}
		i = (i+1) % NUM_COLLECTORS;
	}

   	/* initialize the threads array */
	for(i = 0; i < NUM_COLLECTORS; i++){
		test = pthread_create(&threads[i], NULL, tax_collector, (void*) i);
		if(test){
			printf("ERROR: could not initialize arrays on index %i\n",i);
			exit(-1);
		}
	}
	
		


    return 0;
}
