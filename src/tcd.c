#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>

/** NUM_COLLECTORS specifies,how much tax collectors are in the game. */
#define NUM_COLLECTORS  5
#define START_AMOUNT_OF_MONEY   300

pthread_t threads[NUM_COLLECTORS];
int moneys[NUM_COLLECTORS];
int stop = 0;

void *tax_collector(void *field){
	/* target is a random number between 0 and NUM_COLLECTORS */
	int target;
	int my_tid;
	int get_money;
	my_tid =  (long) field;
	target = my_tid;
	
	while(!stop){
			while (my_tid == target){
				target = rand() % NUM_COLLECTORS;
			}
			 
			/* not a perfect randomness, but it should be sufficient for our
			 * needs.
			 */
			if (moneys[target] < 100 ){
				get_money = 100;
				while (moneys[target] < 100){
					sched_yield();	
				}
				moneys[my_tid] += get_money;
				moneys[target] -= get_money;
				
			} else {
				get_money = moneys[target];
				get_money = get_money % 100;
				if (get_money % 2) {get_money++;}
				get_money = get_money * 50;
				moneys[my_tid] += get_money;
				moneys[target] -= get_money;
			}
			target = my_tid;
	}	
	pthread_exit(0);
	return 0;
}

int main(int argc, char **argv)
{
    int num_collectors = NUM_COLLECTORS;
    int start_money = START_AMOUNT_OF_MONEY;
	int amount_money = start_money;
	long i;
	int test;
    int a;    
    
    (void)a;
    
    if ( argc > 1 ) {
      num_collectors = atoi(argv[1]);
      if ( argc > 2 ) start_money = atoi(argv[2]);
    }

    printf("Tax Collectors: %d\nAmount of money: %d\n",num_collectors,start_money);
   	srand(time(NULL));
	/* initialize the moneys array */
	i = 0;
	while(amount_money > 0){
		if(amount_money < 100){
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
			printf("ERROR: could not initialize arrays on index %li\n",i);
			exit(-1);
		}
	}
	
    return 0;
}
