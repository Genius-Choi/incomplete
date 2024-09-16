static int vfp_set(struct task_struct *target,
			  const struct user_regset *regset,
			  unsigned int pos, unsigned int count,
			  const void *kbuf, const void __user *ubuf)
{
	int ret;
	struct thread_info *thread = task_thread_info(target);
	struct vfp_hard_struct new_vfp;
	const size_t user_fpregs_offset = offsetof(struct user_vfp, fpregs);
	const size_t user_fpscr_offset = offsetof(struct user_vfp, fpscr);

	vfp_sync_hwstate(thread);
	new_vfp = thread->vfpstate.hard;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &new_vfp.fpregs,
				  user_fpregs_offset,
				  user_fpregs_offset + sizeof(new_vfp.fpregs));
	if (ret)
		return ret;

	ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
				user_fpregs_offset + sizeof(new_vfp.fpregs),
				user_fpscr_offset);
	if (ret)
		return ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &new_vfp.fpscr,
				 user_fpscr_offset,
				 user_fpscr_offset + sizeof(new_vfp.fpscr));
	if (ret)
		return ret;

	vfp_flush_hwstate(thread);
	thread->vfpstate.hard = new_vfp;

	return 0;
}
