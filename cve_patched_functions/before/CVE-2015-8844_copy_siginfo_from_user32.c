int copy_siginfo_from_user32(siginfo_t *to, struct compat_siginfo __user *from)
{
	if (copy_from_user(to, from, 3*sizeof(int)) ||
	    copy_from_user(to->_sifields._pad,
			   from->_sifields._pad, SI_PAD_SIZE32))
		return -EFAULT;

	return 0;
}
