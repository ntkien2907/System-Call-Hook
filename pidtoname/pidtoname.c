#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>

SYSCALL_DEFINE3(pidtoname, int, id, char __user *, data, int, len)
{	
	int len_process_name;

	/* task_struct la cau truc du lieu chua cac thong tin cua process */
	struct task_struct *task;

	/* struct pid la mot khai niem trong linux kernel ve viec nhan dang mot 
	   process. No cho biet cac cong viec, cac nhom va sessions cua mot process */
	//struct pid *pid_struct;
	printk("%d", id);

	/* tim kiem mot pid_struct khi biet truoc PID cua mot process */
	task = get_pid_task(find_get_pid(id), PIDTYPE_PID);

	printk("%s", task->comm);
	
    	copy_to_user(data, task->comm, len);

	/* chieu dai cua ten process */
	//len_process_name = strlen(data);
	
	/* gan ki tu ket thuc chuoi vao */
	//data[len_process_name] = '\0';

    	//if(len > len_process_name)
        //	return 0;

    	//if(len <= len_process_name)
        //	return len_process_name;
	
    	return -1;
}
