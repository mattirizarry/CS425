/*
 * lab4_task1.2.c
 */

#include<pthread.h>
#include<stdio.h>

int n;    
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[])
{
  pthread_t tid_producer, tid_consumer;    /* thread identifier */
  pthread_attr_t attr_producer, attr_consumer;  /* set of thread attributes */

  /* get default attribute */
  pthread_attr_init(&attr_producer);
  pthread_attr_init(&attr_consumer);

  /*create threads */
  pthread_create(&tid_consumer, &attr_consumer, consumer, NULL);
  pthread_create(&tid_producer, &attr_producer, producer, NULL);

  /* wait for producer and consumer threads to exit */
  pthread_join(tid_producer, NULL);
  pthread_join(tid_consumer, NULL);

}


/* produce value n */
void *producer(void *param)
{
  int i;
  for (i=0; i<1e8; i++)
     n++; // increment n

  pthread_exit(0);
}

/* ''consume'' and print value n */
void *consumer(void *param)
{
  int i;
  for (i=0; i<1e8; i++) 
    if ( i% 10000000 == 0)
      printf("%d ", n);
    
  pthread_exit(0);
}

