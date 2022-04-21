#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD 2


int a[]={3,4,6,2,9,5,7,0,8,1};
struct sortArg {
  int start;
  int size;
};

struct sortArg sortArgs[MAX_THREAD];

int cmpfunc(const void* a, const void* b) {
  return (*(int*)a-*(int*)b);
}

void* sort(void *arg) {
  struct sortArg *sArg =(struct sortArg*) arg;
  //get a pointer to the array we are to sort
  int *arr=a+sArg->start;
  //sort our section of the array
  qsort(arr,sArg->size,sizeof(int),cmpfunc);
}



int main() {
  pthread_t threads[MAX_THREAD];
  int i=0;
  //calculate how to split our array. our array needs to split evenly
  int size=sizeof(a)/sizeof(a[0]);
  int partSize = size/MAX_THREAD;

  //print our array
  printf("Initial: ");
  for (i=0;i<size;i++)
    printf("%d ",a[i]);
  printf("\n");
  for (i=0;i<MAX_THREAD;i++) {
    sortArgs[i].start=i*partSize;
    sortArgs[i].size=partSize;
    pthread_create(&threads[i],NULL,sort,&sortArgs[i]);
  }

  //Join threads
  for (i=0;i<MAX_THREAD;i++)
    pthread_join(threads[i],NULL);
  //print our array
  printf("After threads: ");
  for (i=0;i<size;i++)
    printf("%d ",a[i]);
  printf("\n");
  //at this point the array is semi sorted, bottom half and top half are sorted
  //we will now sort the mostly sorted array to get a final sorted array
  //resulting in a multi-threaded qsort
  qsort(a,size,sizeof(int),cmpfunc);
  //print our array
  printf("Final: ");
  for (i=0;i<size;i++)
    printf("%d ",a[i]);
  printf("\n");

}
