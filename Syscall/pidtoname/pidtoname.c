#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

asmlinkage long sys_pidtoname(int pid, char __user *buf, int len)
{	
	struct task_struct *task;
	int len_process_name = 0;	
	char* kernel_buf = kmalloc(16, GFP_KERNEL);

	for_each_process(task) 
	{
		if((int)task_pid_nr(task) == pid) 
		{
			strcpy(kernel_buf, task->comm);
			len_process_name = strlen(task->comm);
			kernel_buf[len_process_name] = 0;

			copy_to_user(buf, kernel_buf, len_process_name); 

			if(len > len_process_name)
				return 0;		

			return len_process_name;			
		}
	}
    	return -1;
}
