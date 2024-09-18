static int fpregs_set(struct task_struct *target,
		       const struct user_regset *regset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __user *ubuf)
{
	int ret;

	ret = init_fpu(target);
	if (ret)
		return ret;

	set_stopped_child_used_math(target);

	if ((boot_cpu_data.flags & CPU_HAS_FPU))
		return user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					  &target->thread.xstate->hardfpu, 0, -1);

	return user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thread.xstate->softfpu, 0, -1);
}
