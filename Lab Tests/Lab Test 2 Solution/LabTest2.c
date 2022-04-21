* Solution to Labtest2
* Compile in Linux: gcc -pthread -o labtest2 labtest2.c
* This program creates a total of 2 threads each returning the 
* largest number in half of the array.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMThreads 2
#define SIZE 10
int list[SIZE] = {77,12,19,43,18,24,21,62,15,18};
void *largestnum(void *param);

/*Parameter Data structure to pass in the from and to index.*/
typedef struct
{
	int from_index;
	int to_index;
	int returnval;
} parameters;
int large1, large2;

int main(int argc, const char *argv[])
{
	int i;
    
	pthread_t workers[NUMThreads];
	
	/* establish the first largestnum thread */
	parameters *data = (parameters *) malloc (sizeof(parameters));
	data->from_index = 0;
	data->to_index = (SIZE/2) - 1;
	data->returnval = 0;
	pthread_create(&workers[0], 0, largestnum, data);
	
	/* establish the second largestnum thread */
	parameters *data1 = (parameters *) malloc (sizeof(parameters));
	data1->from_index = (SIZE/2);
	data1->to_index = SIZE - 1;
	data1->returnval = 0;
	pthread_create(&workers[1], 0, largestnum, data1);
	/* now wait for the 2 largestnum threads to finish */
	for (i = 0; i < NUMThreads - 1; i++)
		pthread_join(workers[i], NULL);
	/* output the largest number */
	if(data->returnval > data1->returnval){
		printf("Largest number in the list is:%d \n", data->returnval);
	}
	else {
		printf("Largest number in the list is:%d \n", data1->returnval);
	}
    return 0;
}

/**
 * Largestnum thread.
 *
 */

void *largestnum(void *params)
{
	int i;
	parameters* p = (parameters *)params;
	int begin = p->from_index;
	int end = p->to_index;
	int large = p->returnval;
	printf("Begining: %d, and end: %d \n", begin, end);
	
	for (i = begin; i <= end; i++) {
		if (list[i] > large) 
		{
			large = list[i];
		}
	} 
	p->returnval = large;
	pthread_exit(0);
}


