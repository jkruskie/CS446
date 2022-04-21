#include <stdio.h>
#include <sys/types.h>
#include <unitstd.h>
#include <stdlib.h>

int main() {
    printf("[parent] pid %d\n", getpid());
    for(int i=0; i<10; i++) {
        pid_t pid = fork();
        if(pid == 0) { // child
            printf("[child] pid %d\n", getpid());
            exit(0);
        }
    }
}