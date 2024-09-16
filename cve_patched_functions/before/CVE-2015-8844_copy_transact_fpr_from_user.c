inline unsigned long copy_transact_fpr_from_user(struct task_struct *task,
						 void __user *from)
{
	return __copy_from_user(task->thread.transact_fp.fpr, from,
				ELF_NFPREG * sizeof(double));
}
