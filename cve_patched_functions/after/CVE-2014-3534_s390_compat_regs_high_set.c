static int s390_compat_regs_high_set(struct task_struct *target,
				     const struct user_regset *regset,
				     unsigned int pos, unsigned int count,
				     const void *kbuf, const void __user *ubuf)
{
	compat_ulong_t *gprs_high;
	int rc = 0;

	gprs_high = (compat_ulong_t *)
		&task_pt_regs(target)->gprs[pos / sizeof(compat_ulong_t)];
	if (kbuf) {
		const compat_ulong_t *k = kbuf;
		while (count > 0) {
			*gprs_high = *k++;
			*gprs_high += 2;
			count -= sizeof(*k);
		}
	} else {
		const compat_ulong_t  __user *u = ubuf;
		while (count > 0 && !rc) {
			unsigned long word;
			rc = __get_user(word, u++);
			if (rc)
				break;
			*gprs_high = word;
			*gprs_high += 2;
			count -= sizeof(*u);
		}
	}

	return rc;
}
