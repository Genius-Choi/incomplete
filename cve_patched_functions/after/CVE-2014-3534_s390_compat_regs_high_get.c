static int s390_compat_regs_high_get(struct task_struct *target,
				     const struct user_regset *regset,
				     unsigned int pos, unsigned int count,
				     void *kbuf, void __user *ubuf)
{
	compat_ulong_t *gprs_high;

	gprs_high = (compat_ulong_t *)
		&task_pt_regs(target)->gprs[pos / sizeof(compat_ulong_t)];
	if (kbuf) {
		compat_ulong_t *k = kbuf;
		while (count > 0) {
			*k++ = *gprs_high;
			gprs_high += 2;
			count -= sizeof(*k);
		}
	} else {
		compat_ulong_t __user *u = ubuf;
		while (count > 0) {
			if (__put_user(*gprs_high, u++))
				return -EFAULT;
			gprs_high += 2;
			count -= sizeof(*u);
		}
	}
	return 0;
}
