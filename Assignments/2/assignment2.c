#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_t t_prod[10], t_cons[10], t_test;
sem_t s_full, s_empty;

# define size 5
int count = 0;
int list[size];

void *producer(void *x ){
  printf("\nEnter the number to be produced:");
  int produced;
  scanf("%d", &produced);

  sem_wait(&s_empty);
  pthread_mutex_lock(&mutex);
  printf("Produced is %d\n", produced);

  list[count++] = produced;
  pthread_mutex_unlock(&mutex);
  sem_post(&s_full);
//   pthread_exit(NULL);
}

void *consumer(void *x)
{
  int consumed;
  sem_wait(&s_full);
  pthread_mutex_lock(&mutex);
  consumed = list[--count];
  printf("Item consumed is %d\n", consumed);

  pthread_mutex_unlock(&mutex);
  sem_post(&s_empty);
  pthread_exit(NULL);
}

void main (){
  sem_init(&s_full, 0, 0);
  sem_init(&s_empty, 0, 5);
  int produced, consumed;
  printf("\nHow many would you like to produce?");

  scanf("%d", &produced);
  for(int x = 0; x < produced; x++)
  {
    pthread_create(&t_prod[x], NULL, producer, NULL);
    sleep(3);
  }
  for(int x = 0; x < produced; x++)
  {
    pthread_join(t_prod[x], NULL);
  }
  printf("\nHow many woudld you like to consume?");

  scanf("%d", &consumed);
  for(int x = 0; x < consumed; x++)
  {  
    if(x > produced){
        printf("\nCannot Consume Items more than Produced So exiting Now...\n");
        break;
    }
    pthread_create(&t_cons[x], NULL, consumer, NULL);
    sleep(1);
  }

  for(int x = 0; x < consumed; x++)
  {
    pthread_join(t_cons[x], NULL);
  }
}