inline unsigned long copy_fpr_to_user(void __user *to,
				      struct task_struct *task)
{
	return __copy_to_user(to, task->thread.fp_state.fpr,
			      ELF_NFPREG * sizeof(double));
}
