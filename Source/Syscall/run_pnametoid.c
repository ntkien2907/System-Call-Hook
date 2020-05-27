#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char data[16];
	long int pid;

	printf("Enter process's name: ");
	scanf("%s", data);
	while((getchar()) != '\n');

	pid = syscall(317, data);
	printf("PID = %ld\n", pid); 
       	return 0;
}
