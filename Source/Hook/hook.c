#include <asm/unistd.h>
#include <asm/cacheflush.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/pgtable_types.h>
#include <linux/highmem.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/fdtable.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nguyen Trung Kien: 18127123 - Nguyen Quang Phap: 18127174 - Nguyen Ha Thanh: 18127214");

void **system_call_table_addr;
char buff[100];

/* My custom syscall that takes process name */
asmlinkage int (*open_syscall) (const char *, int, mode_t);
asmlinkage int (*write_syscall) (int, void *, size_t);

/* Hook */
asmlinkage int new_open_syscall(const char * filename, int flags, mode_t mode) {
	copy_from_user(buff,filename,100);
	printk(KERN_INFO "Process Name: %s Filename is open: %s\n", current->comm, buff);
	return open_syscall(filename, flags, mode);
}

asmlinkage int new_write_syscall(int fd, void *buf, size_t len) {
	/* Ham lay duong dan ten file tu gia tri fd */
	char *tmp;
	char *pathname;
	struct file *file;
	struct path *path;

	spin_lock(&current->files->file_lock);
	file = fcheck_files(current->files, fd);
	if (!file) {
		spin_unlock(&current->files->file_lock);
		return -ENOENT;
	}

	path = &file->f_path;
	path_get(path);
	spin_unlock(&current->files->file_lock);

	tmp = (char *)__get_free_page(GFP_KERNEL);

	if (!tmp) {
		path_put(path);
		return -ENOMEM;
	}

	pathname = d_path(path, tmp, PAGE_SIZE);
	path_put(path);

	if (IS_ERR(pathname)) {
		free_page((unsigned long)tmp);
		return PTR_ERR(pathname);
	}

	free_page((unsigned long)tmp);
	if(strcmp(current->comm, "user_test") == 0)
		printk(KERN_INFO "Process Name: %s Filename is write: %s fd: %d nByte: %d\n", current->comm, pathname, fd,(int)len);
	
	return write_syscall(fd,buf,len);
}

/* Pha lop bao ve sys_call_table */
int make_rw(unsigned long address){
	unsigned int level;
	pte_t *pte = lookup_address(address, &level);
	if(pte->pte &~_PAGE_RW){
		pte->pte |=_PAGE_RW;
	}
	return 0;
}

/* Khoi phuc lai lop bao ve sys_call_table */
int make_ro(unsigned long address){
	unsigned int level;
	pte_t *pte = lookup_address(address, &level);
	pte->pte = pte->pte &~_PAGE_RW;
	return 0;
}

static int __init entry_point(void){
	printk(KERN_INFO "Captain Hook loaded successfully..\n");

	/* Dia chi cua sys_call_table */
	system_call_table_addr = (void *)0xffffffff81801460;
	
	/* Khoi tao cac bien can theo doi */
	open_syscall = (void *)system_call_table_addr[__NR_open];
	write_syscall = (void *)system_call_table_addr[__NR_write];

	/* Pha lop bao ve cho sys_call_table */
	make_rw((unsigned long)system_call_table_addr);
	
	/* Change syscall to our syscall function */
	system_call_table_addr[__NR_open] = new_open_syscall;
	system_call_table_addr[__NR_write] = new_write_syscall;
	return 0;
}

static void __exit exit_point(void){
	printk(KERN_INFO "Unloaded Captain Hook successfully\n");

	/* Restore original system call */
	system_call_table_addr[__NR_open] = open_syscall;
	system_call_table_addr[__NR_write] = write_syscall;

	/* Phuc hoi lop bao ve cho sys_call_table */
	make_ro((unsigned long)system_call_table_addr);
}

module_init(entry_point);
module_exit(exit_point);
