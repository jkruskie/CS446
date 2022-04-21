* Solution to lab test 1	
 */

#include <stdio.h>
#include  <sys/types.h> /* This header file has the definition for pid_t type*/

int main()
{
	int i;	
	pid_t pid, pid1;	
	printf("%d\n",getpid()); /*This Will print the root*/
	pid = fork();
	printf("%d\n",getpid());
	
	if(pid == 0) {
		fork();
		printf("%d\n",getpid());		
		fork();
		printf("%d\n",getpid());
		fork();
		printf("%d\n",getpid());
	}
	else {
		pid1=fork();
		printf("%d\n",getpid());
		if(pid1==0){
			fork();
			printf("%d\n",getpid());	
		}	
	}
	
	return 0;
}

