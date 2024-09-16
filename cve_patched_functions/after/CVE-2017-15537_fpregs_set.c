int fpregs_set(struct task_struct *target, const struct user_regset *regset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __user *ubuf)
{
	struct fpu *fpu = &target->thread.fpu;
	struct user_i387_ia32_struct env;
	int ret;

	fpu__activate_fpstate_write(fpu);
	fpstate_sanitize_xstate(fpu);

	if (!boot_cpu_has(X86_FEATURE_FPU))
		return fpregs_soft_set(target, regset, pos, count, kbuf, ubuf);

	if (!boot_cpu_has(X86_FEATURE_FXSR))
		return user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					  &fpu->state.fsave, 0,
					  -1);

	if (pos > 0 || count < sizeof(env))
		convert_from_fxsr(&env, target);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &env, 0, -1);
	if (!ret)
		convert_to_fxsr(target, &env);

	/*
	 * update the header bit in the xsave header, indicating the
	 * presence of FP.
	 */
	if (boot_cpu_has(X86_FEATURE_XSAVE))
		fpu->state.xsave.header.xfeatures |= XFEATURE_MASK_FP;
	return ret;
}
