inline unsigned long copy_fpr_from_user(struct task_struct *task,
					void __user *from)
{
	return __copy_from_user(task->thread.fp_state.fpr, from,
			      ELF_NFPREG * sizeof(double));
}
