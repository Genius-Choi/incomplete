static int ebt_standard_compat_to_user(void __user *dst, const void *src)
{
	compat_int_t cv = *(int *)src;

	if (cv >= 0)
		cv -= xt_compat_calc_jump(NFPROTO_BRIDGE, cv);
	return copy_to_user(dst, &cv, sizeof(cv)) ? -EFAULT : 0;
}
