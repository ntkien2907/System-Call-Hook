#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

void main() {
	int fd = open("file_test.txt", O_WRONLY | O_CREAT | O_APPEND);
	if(fd >= 0) {
		printf("Open File: Success");
		if(write(fd,"Hook System Call", 16) == 16)
			printf("Write File: Success\n");
		else
			printf("Write File: Failure\n");
	}
	else
		printf("Open File: Failure\n");
}
