int xt_compat_target_to_user(const struct xt_entry_target *t,
			     void __user **dstptr, unsigned int *size)
{
	const struct xt_target *target = t->u.kernel.target;
	struct compat_xt_entry_target __user *ct = *dstptr;
	int off = xt_compat_target_offset(target);
	u_int16_t tsize = t->u.user.target_size - off;

	if (copy_to_user(ct, t, sizeof(*ct)) ||
	    put_user(tsize, &ct->u.user.target_size) ||
	    copy_to_user(ct->u.user.name, t->u.kernel.target->name,
			 strlen(t->u.kernel.target->name) + 1))
		return -EFAULT;

	if (target->compat_to_user) {
		if (target->compat_to_user((void __user *)ct->data, t->data))
			return -EFAULT;
	} else {
		if (copy_to_user(ct->data, t->data, tsize - sizeof(*ct)))
			return -EFAULT;
	}

	*size -= off;
	*dstptr += tsize;
	return 0;
}
