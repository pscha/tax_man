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
long *moneys;
long *ins;
long *outs;
int stop = 0;

#ifdef BIGLOCK
pthread_mutex_t biglock;
#endif

#ifdef MULTILOCK
pthread_mutex_t *multilock;
#endif


void *tax_collector(void *field){
	/* target is a random number between 0 and NUM_COLLECTORS */
	int target;
	int my_tid;
	int get_money = 0;
	my_tid =  (long) field;
	target = my_tid;
	int i = 0;
	
	while(stop){
		
	}
	
	while(!stop){
		while (my_tid == target){
			target = rand() % num_collectors;
		}
			
		/* not a perfect randomness, but it should be sufficient for our
			* needs.
			*/
#ifdef BIGLOCK
		pthread_mutex_lock(&biglock);
#endif
		if (moneys[target] < 100 ){
			get_money = 100;
			for(i=0; i<10; i++){ 	
				if(moneys[target] < 100){
#ifdef BIGLOCK
					pthread_mutex_unlock(&biglock);
#endif
					sched_yield();
#ifdef BIGLOCK
					pthread_mutex_lock(&biglock);
#endif
				}
				else{
#ifdef MULTILOCK
					if(target < my_tid){
						pthread_mutex_lock(&multilock[target]);
						pthread_mutex_lock(&multilock[my_tid]);
			//			printf("Thread %d locked and target %d locked\n",my_tid,target);
					}else{
						pthread_mutex_lock(&multilock[my_tid]);
						pthread_mutex_lock(&multilock[target]);
			//			printf("Thread %d locked and target %d locked\n",my_tid,target);
						
					}
#endif					
					moneys[my_tid] += get_money;
					moneys[target] -= get_money;
					ins[my_tid]++;
					outs[target]++;

#ifdef MULTILOCK
					pthread_mutex_unlock(&multilock[target]);
					pthread_mutex_unlock(&multilock[my_tid]);
			//		printf("Thread %d and %d unlocked\n",my_tid,target);

#endif					
				}
			}
		} else {
#ifdef MULTILOCK
			if(target < my_tid){
				pthread_mutex_lock(&multilock[target]);
				pthread_mutex_lock(&multilock[my_tid]);
			//	printf("Thread %d locked and target %d locked\n",my_tid,target);
			}else{
				pthread_mutex_lock(&multilock[my_tid]);
				pthread_mutex_lock(&multilock[target]);
			//	printf("Thread %d locked and target %d locked\n",my_tid,target);
			}
#endif
			get_money = moneys[target];
			get_money = get_money / 100;
			if (get_money % 2) {get_money++;}
			get_money = get_money * 50;
			moneys[my_tid] += get_money;
			moneys[target] -= get_money;
#ifdef MULTILOCK
			pthread_mutex_unlock(&multilock[target]);
			pthread_mutex_unlock(&multilock[my_tid]);
		//	printf("Thread %d and %d unlocked\n",my_tid,target);
#endif					
			ins[my_tid]++;
			outs[target]++;
		}
#ifdef BIGLOCK
		pthread_mutex_unlock(&biglock);
#endif
		target = my_tid;
	}	
	pthread_exit(0);
	return 0;
}

int main(int argc, char **argv)
{
    int start_money = START_AMOUNT_OF_MONEY;
	long amount_money;
	long total_in=0;
	long total_out=0;
	long i;
	int test;
    int a;    
    
    (void)a;
    
    if ( argc > 1 ) {
      num_collectors = atoi(argv[1]);
      if ( argc > 2 ) start_money = atoi(argv[2]);
    }

    printf("Tax Collectors: %d\nAmount of money: %d\n",num_collectors,start_money);
#ifdef MULTILOCK
	printf("MULTILOCK \t activated \n");
#endif
#ifdef BIGLOCK
	printf("BIGLOCK \t activated \n");
#endif 
   	srand(time(NULL));
	amount_money = start_money;
	/* malloc the arrays */
	threads = malloc(sizeof(pthread_t) * num_collectors);
	moneys = malloc(sizeof(long) * num_collectors);
	ins = malloc(sizeof(long) * num_collectors);
	outs = malloc(sizeof(long) * num_collectors);

#ifdef MULTILOCK
	multilock = malloc(sizeof(pthread_mutex_t) * num_collectors);
#endif


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
	
	stop = 1;
   	/* initialize the threads array */
	for(i = 0; i < num_collectors; i++){
		test = pthread_create(&threads[i], NULL, tax_collector, (void*) i);
		if(test){
			printf("ERROR: could not initialize arrays on index %li\n",i);
			exit(-1);
		}
#ifdef MULTILOCK
		pthread_mutex_init(&multilock[i],NULL);
#endif
	}
	stop = 0; 
	sleep(20);
	stop = 1;
	sleep(3);
	/* collect all threads */
	for(i=0; i < num_collectors; i++){
		pthread_join(threads[i], NULL);
	}
	
	/* sum up ressources */
	for(i=0; i < num_collectors; i++){
		amount_money += moneys[i];
		total_in += ins[i];
		total_out += outs[i];
		printf("Collector %li  has:\t money=%li,\t in=%li,\t out=%li\n",i,moneys[i],ins[i],outs[i]);
	}	
	printf("ended with: amount money = %li,\t total_ins=%li,\t total_outs=%li\n",amount_money,total_in,total_out);
    return 0;
}
