#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>



void showPCB(void)
{
	struct task_struct *task;
	//struct task_struct *parent;
	//struct task_struct *child;
	task=&init_task;
	printk(KERN_INFO "init pid:%d\n",task->pid);
	printk(KERN_INFO "init state:%ld (-1 => not runable; 0 => runable; 1 => stopped)\n",task->state);
	printk(KERN_INFO "flags:%d\n", task->flags);
	printk(KERN_INFO "runtime priority:%d\n", task->rt_priority);
	printk(KERN_INFO "process policy:%d\n", task->policy);
	printk(KERN_INFO "tgid:%d\n", task->tgid);
	printk(KERN_INFO "link_count:%d\n", task->link_count);
	printk(KERN_INFO "comm:%s\n",task->comm);

}
/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");
    showPCB();
	return 0;
}


/* This function is called when the module is removed. */
void simple_exit(void) 
{
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

