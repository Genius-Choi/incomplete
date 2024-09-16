osf_fix_iov_len(const struct iovec __user *iov, unsigned long count)
{
	unsigned long i;

	for (i = 0 ; i < count ; i++) {
		int __user *iov_len_high = (int __user *)&iov[i].iov_len + 1;

		if (put_user(0, iov_len_high))
			return -EFAULT;
	}
	return 0;
}
