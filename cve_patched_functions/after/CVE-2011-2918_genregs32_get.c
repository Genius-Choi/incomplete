static int genregs32_get(struct task_struct *target,
			 const struct user_regset *regset,
			 unsigned int pos, unsigned int count,
			 void *kbuf, void __user *ubuf)
{
	if (kbuf) {
		compat_ulong_t *k = kbuf;
		while (count >= sizeof(*k)) {
			getreg32(target, pos, k++);
			count -= sizeof(*k);
			pos += sizeof(*k);
		}
	} else {
		compat_ulong_t __user *u = ubuf;
		while (count >= sizeof(*u)) {
			compat_ulong_t word;
			getreg32(target, pos, &word);
			if (__put_user(word, u++))
				return -EFAULT;
			count -= sizeof(*u);
			pos += sizeof(*u);
		}
	}

	return 0;
}
