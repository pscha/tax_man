#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>

/** NUM_COLLECTORS specifies,how much tax collectors are in the game. */
#define NUM_COLLECTORS  5
#define START_AMOUNT_OF_MONEY   300
int num_collectors = NUM_COLLECTORS;
pthread_t *threads;
int *moneys;
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
			target = rand() % num_collectors;
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
			get_money = get_money / 100;
			if (get_money % 2) {get_money++;}
			get_money = get_money * 50;
			moneys[my_tid] += get_money;
			moneys[target] -= get_money;
		}
		target = my_tid;
	}	
	printf("tid= %i moneys=%i\n",my_tid,moneys[my_tid]);
	fflush(stdout);
	pthread_exit(0);
	return 0;
}

int main(int argc, char **argv)
{
    int start_money = START_AMOUNT_OF_MONEY;
	int amount_money;
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
	amount_money = start_money;
	/* malloc the arrays */
	threads = malloc(sizeof(pthread_t) * num_collectors);
	moneys = malloc(sizeof(int) * num_collectors);

	/* initialize the moneys array */
	i = 0;
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
		test = pthread_create(&threads[i], NULL, tax_collector, (void*) i);
		if(test){
			printf("ERROR: could not initialize arrays on index %li\n",i);
			exit(-1);
		}
	}
	
	sleep(20);
	stop = 1;
	/* collect all threads */
	for(i=0; i < num_collectors; i++){
		pthread_join(threads[i], NULL);
	}

	/* sum up ressources */
	for(i=0; i < num_collectors; i++){
		amount_money += moneys[i];
	}	
	printf("ended with: amount money = %i\n",amount_money);
    return 0;
}
