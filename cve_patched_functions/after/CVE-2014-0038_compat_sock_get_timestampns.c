int compat_sock_get_timestampns(struct sock *sk, struct timespec __user *userstamp)
{
	struct compat_timespec __user *ctv;
	int err;
	struct timespec ts;

	if (COMPAT_USE_64BIT_TIME)
		return sock_get_timestampns (sk, userstamp);

	ctv = (struct compat_timespec __user *) userstamp;
	err = -ENOENT;
	if (!sock_flag(sk, SOCK_TIMESTAMP))
		sock_enable_timestamp(sk, SOCK_TIMESTAMP);
	ts = ktime_to_timespec(sk->sk_stamp);
	if (ts.tv_sec == -1)
		return err;
	if (ts.tv_sec == 0) {
		sk->sk_stamp = ktime_get_real();
		ts = ktime_to_timespec(sk->sk_stamp);
	}
	err = 0;
	if (put_user(ts.tv_sec, &ctv->tv_sec) ||
			put_user(ts.tv_nsec, &ctv->tv_nsec))
		err = -EFAULT;
	return err;
}
