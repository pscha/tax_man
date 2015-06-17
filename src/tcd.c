#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>

/** NUM_COLLECTORS specifies,how much tax collectors are in the game. */
#define NUM_COLLECTORS  5
#define START_AMOUNT_OF_MONEY   300


int main(int argc, char **argv)
{
    int num_collectors = NUM_COLLECTORS;
    int start_money = START_AMOUNT_OF_MONEY;

    int a;    
    
    (void)a;
    
    if ( argc > 1 ) {
      num_collectors = atoi(argv[1]);
      if ( argc > 2 ) start_money = atoi(argv[2]);
    }

    printf("Tax Collectors: %d\nAmount of money: %d\n",num_collectors,start_money);

#ifdef NOLOCK
    printf("No Lock\n");
#else

#ifdef BIGLOCK
    printf("Biglock\n");
#else
    printf("1 lock per c\n");

#endif

#endif
    
#ifndef NOLOCK
#ifndef BIGLOCK
    printf("1 lock per c\n");
#else
    printf("Biglock\n");
#endif

#else
    printf("No Lock\n");
#endif
    
/*
#ifndef NOLOCK
#pragma "NOLOCK not def"
#endif
  */  
    //TODO!!
    
    
    return 0;
}
