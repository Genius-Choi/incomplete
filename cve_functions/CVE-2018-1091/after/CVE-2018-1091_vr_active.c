static int vr_active(struct task_struct *target,
		     const struct user_regset *regset)
{
	flush_altivec_to_thread(target);
	return target->thread.used_vr ? regset->n : 0;
}
