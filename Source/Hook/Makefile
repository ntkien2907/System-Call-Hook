obj-m += hook.o
all:	test.c
	cc -o user_test test.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm user_test
