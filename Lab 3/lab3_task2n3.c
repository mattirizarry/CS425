/**
 * lab4_task2n3.c
 *
 * To compile:
 *
 *	gcc lab4_task2n3.c -lpthread
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

#define NUM_THREADS 10


/* the thread runs in this function */
void *runner(void *param); 

double times[NUM_THREADS];

int main(int argc, char *argv[])
{
	int i, policy;
	pthread_t tid[NUM_THREADS]; 	/* the thread identifier */
	pthread_attr_t attr; 		/* set of attributes for the thread */
	clock_t start, end; 
	double elapse_time; 
	int tids_user[NUM_THREADS];

	/* get the default attributes */
	pthread_attr_init(&attr);


	start = clock(); 


	/* create the threads */
	for (i = 0; i < NUM_THREADS; i++) {
	  tids_user[i] = i; 
	  pthread_create(&tid[i],&attr,runner, &tids_user[i]); 
	}

	/**
	 * Now join on each thread
	 */
	for (i = 0; i < NUM_THREADS; i++) 
	  pthread_join(tid[i], NULL);

	end = clock(); 
	
	elapse_time = ((double) (end - start))/ CLOCKS_PER_SEC;

	printf("main thread elapse_time %f\n", elapse_time/10);

	double total_thread_time = 0.0;

    for (i = 0; i < NUM_THREADS; i++) {
        total_thread_time += times[i];
    } 

	printf("Total elapsed time of all runner threads: %f\n", total_thread_time);

}

/**
 * The thread will begin control in this function.
 */
void *runner(void *param) 
{
	/* do some work ... */
  int tid; 
  int sum = 0, i; 
  clock_t start, end; 
  double elapse_time; 

  tid = *(int*)param; 

  fprintf(stderr, "thread %d starts ...\n", tid); 

  start = clock(); 
   
  for (i = 0; i < 1e8; i++) 
    sum += i;

  end = clock(); 

  elapse_time = ((double) (end - start))/10000000;

  times[tid] = elapse_time / 10;

  fprintf(stderr, "thread %d is exiting, elapse time = %f\n", tid, elapse_time); 

  pthread_exit(0);
}

