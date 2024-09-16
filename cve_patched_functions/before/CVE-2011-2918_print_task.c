static inline void print_task(struct task_struct *tsk)
{
	printk("Task pid %d\n", task_pid_nr(tsk));
}
