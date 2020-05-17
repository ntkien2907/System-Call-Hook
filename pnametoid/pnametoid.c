#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include "pnametoid.h"

asmlinkage int sys_pnametoid (char* name) 
{
	/* task_struct la mot cau truc du lieu, chua cac thong tin cua process */
	struct task_struct *task;

	/* duyet qua tat ca cac process cua he dieu hanh */
	for_each_process(task) 
	{
		/* task->comm la mot mang char luu ten cua process 
		   so sanh ten process nhap vo (name) voi task->comm */
		if(strcmp(task->comm, name) == 0) 
		{
			/* task_pid_nr(task) tra ve "global" PIDs cua process hien 				   tai va con so nay la duy nhat trong toan bo he dieu hanh */
			return (int)task_pid_nr(task); 
		}	
	}
	return -1;
}
