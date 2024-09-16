void update_rlimit_cpu(struct task_struct *task, unsigned long rlim_new)
{
	u64 nsecs = rlim_new * NSEC_PER_SEC;

	spin_lock_irq(&task->sighand->siglock);
	set_process_cpu_timer(task, CPUCLOCK_PROF, &nsecs, NULL);
	spin_unlock_irq(&task->sighand->siglock);
}
