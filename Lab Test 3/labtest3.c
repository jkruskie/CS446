#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tidDeposit[7];
pthread_t tidWithdraw[3];
int depositCounter;
int withdrawCounter;
pthread_mutex_t lock;
int balance = 0;

void* withdraw(int amnt)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    withdrawCounter += 1;
    printf("\n Withdraw %d started\n", withdrawCounter);


    if((balance - amnt) > 0) {
        balance = balance - amnt;
        printf("\n Amount: %d", balance);
    }

    printf("\n Withdraw %d finished\n", withdrawCounter);
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* deposit(int amnt)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    depositCounter += 1;
    printf("\n Deposit %d started\n", depositCounter);

    if((balance) < 400) {
        balance = balance + amnt;
        printf("\n Amount: %d", balance);
    }

    printf("\n Deposit %d finished\n", depositCounter);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(int argc,char* argv[])
{
    int i = 0;
    int j = 0;
    int err;
    printf("\n Starting Balance: %d", balance);
    printf("\n Deposit Amount: %d", atoi(argv[1]));
    printf("\n Withdraw Amount: %d", atoi(argv[2]));

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    while(i < 7)
    {
        err = pthread_create(&(tidDeposit[i]), NULL, &deposit, atoi(argv[1]));
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }


    while(j < 3)
    {
        err = pthread_create(&(tidWithdraw[i]), NULL, &withdraw, atoi(argv[2]));
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        j++;
    }

    for(int i = 0; i < 7; i++) {
        pthread_join(tidDeposit[i], NULL);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(tidWithdraw[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("BALANCE IS: $%d", balance);

    return 0;
}