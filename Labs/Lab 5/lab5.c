#include <stdio.h>
#include <pthread.h>
#define MAX 20
#define MAX_THREAD 2
int list[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int add[2] = { 0 };
int part = 0;

void* sum_thread(void* arg)
{
   int thread_part = part++;
       for (int i = thread_part * (MAX / 2); i < (thread_part + 1) * (MAX / 2); i++)
       add[thread_part] += list[i];
       printf("\n summing thread.....\n");
}

int main()
{
   pthread_t threads[MAX_THREAD];
   for (int i = 0; i < MAX_THREAD; i++)
       pthread_create(&threads[i], NULL, sum_thread, (void*)NULL);

   for (int i = 0; i < MAX_THREAD; i++)
       pthread_join(threads[i], NULL);

   int total = 0;
   for (int i = 0; i < MAX_THREAD; i++)
       total+= add[i];
       printf("\nSum is %d", total );
   return 0;
}
