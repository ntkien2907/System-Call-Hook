#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char data[16];
	printf("Enter process's name: ");
	scanf("%s", data);
	while((getchar()) != '\n');

	long int pid = syscall(436, data);
	printf("PID = %ld\n", pid); 
       	return 0;
}
