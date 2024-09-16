static ssize_t oom_adjust_write(struct file *file, const char __user *buf,
				size_t count, loff_t *ppos)
{
	struct task_struct *task;
	char buffer[PROC_NUMBUF];
	long oom_adjust;
	unsigned long flags;
	int err;

	memset(buffer, 0, sizeof(buffer));
	if (count > sizeof(buffer) - 1)
		count = sizeof(buffer) - 1;
	if (copy_from_user(buffer, buf, count))
		return -EFAULT;

	err = strict_strtol(strstrip(buffer), 0, &oom_adjust);
	if (err)
		return -EINVAL;
	if ((oom_adjust < OOM_ADJUST_MIN || oom_adjust > OOM_ADJUST_MAX) &&
	     oom_adjust != OOM_DISABLE)
		return -EINVAL;

	task = get_proc_task(file->f_path.dentry->d_inode);
	if (!task)
		return -ESRCH;
	if (!lock_task_sighand(task, &flags)) {
		put_task_struct(task);
		return -ESRCH;
	}

	if (oom_adjust < task->signal->oom_adj && !capable(CAP_SYS_RESOURCE)) {
		unlock_task_sighand(task, &flags);
		put_task_struct(task);
		return -EACCES;
	}

	task->signal->oom_adj = oom_adjust;

	unlock_task_sighand(task, &flags);
	put_task_struct(task);

	return count;
}
