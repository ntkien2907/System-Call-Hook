#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char data[16];
	int pid;
	long int num_bytes;

	printf("Enter PID = ");
	scanf("%d", &pid);

	num_bytes = syscall(318, pid, data, 16);

	if(num_bytes > 0)
		printf("Process's name: %s\n", data);
	else
		printf("Process does not exist\n");
	
       	return 0;
}
