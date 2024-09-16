int xt_compat_match_to_user(const struct xt_entry_match *m,
			    void __user **dstptr, unsigned int *size)
{
	const struct xt_match *match = m->u.kernel.match;
	struct compat_xt_entry_match __user *cm = *dstptr;
	int off = xt_compat_match_offset(match);
	u_int16_t msize = m->u.user.match_size - off;

	if (copy_to_user(cm, m, sizeof(*cm)) ||
	    put_user(msize, &cm->u.user.match_size) ||
	    copy_to_user(cm->u.user.name, m->u.kernel.match->name,
			 strlen(m->u.kernel.match->name) + 1))
		return -EFAULT;

	if (match->compat_to_user) {
		if (match->compat_to_user((void __user *)cm->data, m->data))
			return -EFAULT;
	} else {
		if (copy_to_user(cm->data, m->data, msize - sizeof(*cm)))
			return -EFAULT;
	}

	*size -= off;
	*dstptr += msize;
	return 0;
}
