/**
 * lab4_task1.c
 * 
 * To compile:
 *
 *	gcc lab4_task1.c -lpthread
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

#define NUM_THREADS 10

double total_time = 0; 

clock_t ends[NUM_THREADS]; 


/* the thread runs in this function */
void *runner(void *param); 

int main(int argc, char *argv[])
{
	int i, policy;
	pthread_t tid[NUM_THREADS]; 	/* the thread identifier */
	pthread_attr_t attr; 		/* set of attributes for the thread */

	pthread_attr_init(&attr);
	// for (i = 0; i < NUM_THREADS; i++) {
	//   pthread_create(&tid[i],&attr,runner, &i); 
	// }

	// Create array to store the thread ids
	int tids_user[NUM_THREADS];
	for (i = 0; i < NUM_THREADS; i++) {
	  tids_user[i] = i;
	  pthread_create(&tid[i],&attr,runner, &tids_user[i]);
	}

	/**
	 * Now join on each thread
	 *
	 */
	for (i = 0; i < NUM_THREADS; i++) {
	  pthread_join(tid[i], NULL);
	}
}

/**
 * The thread will begin control in this function.
 */
void *runner(void *param) 
{
	/* do some work ... */
  int tid; 
  int sum = 0, i; 

  tid = *(int*)param; 

  fprintf(stderr, "thread %d starts ...\n", tid); 

  for (i = 0; i < 1e8; i++) 
    sum += i;

  fprintf(stderr, "thread %d is exiting\n", tid); 

  pthread_exit(0);
}

