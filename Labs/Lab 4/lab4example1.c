/**
*  Example to help you work on lab 4
*  You can verify your answer by counting
*  the number of unique processes which are output
*  by the call to getpid() - which is 3 unique processes.
*  Note: The statement 'printf("%d\n",getpid());' prints
*  the pid of the current process.
*  Process tree: In the current program, the root P1 has a child P2,
*  and P2 has a child  P3.
*/

#include <stdio.h>
#include  <sys/types.h> /* This header file has the definition for pid_t type*/
#include <unistd.h>


int main()
{
pid_t pid;
printf("%d\n",getpid()); /*This Will print the root*/
pid = fork();
printf("%d\n",getpid());
if(pid == 0) {
fork();
printf("%d\n",getpid());
}
else {
/*Do Nothing*/
}
return 0;
}
