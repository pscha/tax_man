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

void *tax_collector(){
	/* target is a random number between 0 and NUM_COLLECTORS */
	int target;
	
	while(!stop){
		if(target == -1){
			target = rand() % NUM_COLLECTORS; 
			/* not a perfect randomness, but it should be sufficient for our
			 * needs.
			 */
		}
		
	}	

	return 0;
}

int main(int argc, char **argv)
{
    int num_collectors = NUM_COLLECTORS;
    int start_money = START_AMOUNT_OF_MONEY;
	int amount_money;
	int i;
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
	amount_money = start_money;
	while(amount_money > 0){
		if(amount_money < 100){
			moneys[i] += amount_money;
			amount_money -= amount_money;
		}
		else{
			moneys[i] += 100;
			amount_money -= 100;
		}
		i = (i+1) % num_collectors;
	}

   	/* initialize the threads array */
	for(i = 0; i < num_collectors; i++){
		test = pthread_create(&threads[i], NULL, tax_collector, NULL);
		if(test){
			printf("ERROR: could not initialize arrays on index %i\n",i);
			exit(-1);
		}
	}
	
	sleep(2);
	printf("after sleep\n");
	stop = 1;
	/* collect all threads */
	for(i=0; i < num_collectors; i++){
		pthread_join(threads[i], NULL);
	}

	/* sum up ressources */
	for(i=0; i < num_collectors; i++){
		amount_money += moneys[i];
	}	
	
	printf("Ended with: money = %i\n",amount_money);

    return 0;
}
