static int fpregs_active(struct task_struct *target,
			 const struct user_regset *regset)
{
	return tsk_used_math(target) ? regset->n : 0;
}
