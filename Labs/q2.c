#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define NUM_THREADS 3

void * sort_thread(void * params);
void * merge_thread(void * params);

int list[SIZE] = {2,1,8,16,4,12,18,22,17,3};
int sorted[SIZE];

typedef struct parameters {
    int start;
    int end;
}
parameters;

int main() {
    printf("Unsorted: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }

    pthread_t threads[NUM_THREADS];

    parameters * params1 = malloc(sizeof(parameters *));
    params1->start = 0;
    params1->end = (SIZE) / 2;
    pthread_create( & threads[0], 0, sort_thread, params1);

    parameters * params2 = malloc(sizeof(parameters *));
    params2->start = params1->end;
    params2->end = SIZE;
    pthread_create( & threads[1], 0, sort_thread, params2);

    pthread_join(threads[0], 0);
    pthread_join(threads[1], 0);

    params1->end = params2->start;
    pthread_create( & threads[2], 0, merge_thread, params1);
    pthread_join(threads[2], 0);

    printf("\nMerge: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sorted[i]);
    }

    return 0;
}

void * sort_thread(void * params) {
    parameters * param = (parameters * ) params;
    int start = param->start;
    int end = param->end;
    int smallest;
    int temp;

    for(int i = start; i < end; i++)
    {
        for(int j = i + 1; j < end; j++)
        {
            if(list[j] < list[i])
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    pthread_exit(0);
}

void * merge_thread(void * params) {
    int temp;
    printf("\nSort: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    parameters * param = (parameters * ) params;
    int start = param->start;
    int end = SIZE;
    for ( int i = 0; i < end; i ++ )           
    {
        int j = i - 1;
        while ( j >= 0 && sorted[j] > list[i] ) 
        {
            sorted[j+1] = sorted[j];             
            j --;
        }
        sorted[j+1] = list[i];                  
    }

    pthread_exit(0);
}
