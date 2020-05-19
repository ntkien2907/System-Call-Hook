#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE2(pnametoid, char __user *, data, int, len)
{
	/* task_struct la mot cau truc du lieu, chua cac thong tin cua process */
	struct task_struct *task;

	char buf[16];
	if(copy_from_user(buf, data, len))
		return -1;
	
	/* duyet qua tat ca cac process cua he dieu hanh */
	for_each_process(task) 
	{
		/* task->comm la mot mang char luu ten cua process 
		   so sanh ten process nhap vo (name) voi task->comm */
		printk("%s", task->comm);
		if(strcmp(task->comm, buf) == 0) 
		{
			/* task_pid_nr(task) tra ve "global" PIDs cua process hien 
			tai va con so nay la duy nhat trong toan bo he dieu hanh */
			return (long)task_pid_nr(task); 
		}	
	}
	return -1;
}
