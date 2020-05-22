#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char data[16];
	int pid;

	printf("Enter PID = ");
	scanf("%d", &pid);

	long int num_bytes = syscall(437, &pid, data, 16);
	printf("System call returns %ld\n", num_bytes);
	printf("Process's name: %s\n", data); 

       	return 0;
}
