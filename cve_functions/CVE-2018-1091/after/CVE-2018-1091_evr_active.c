static int evr_active(struct task_struct *target,
		      const struct user_regset *regset)
{
	flush_spe_to_thread(target);
	return target->thread.used_spe ? regset->n : 0;
}
