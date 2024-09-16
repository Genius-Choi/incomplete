static int s390_compat_regs_set(struct task_struct *target,
				const struct user_regset *regset,
				unsigned int pos, unsigned int count,
				const void *kbuf, const void __user *ubuf)
{
	int rc = 0;

	if (target == current)
		save_access_regs(target->thread.acrs);

	if (kbuf) {
		const compat_ulong_t *k = kbuf;
		while (count > 0 && !rc) {
			rc = __poke_user_compat(target, pos, *k++);
			count -= sizeof(*k);
			pos += sizeof(*k);
		}
	} else {
		const compat_ulong_t  __user *u = ubuf;
		while (count > 0 && !rc) {
			compat_ulong_t word;
			rc = __get_user(word, u++);
			if (rc)
				break;
			rc = __poke_user_compat(target, pos, word);
			count -= sizeof(*u);
			pos += sizeof(*u);
		}
	}

	if (rc == 0 && target == current)
		restore_access_regs(target->thread.acrs);

	return rc;
}
