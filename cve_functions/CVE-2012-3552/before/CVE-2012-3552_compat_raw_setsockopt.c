static int compat_raw_setsockopt(struct sock *sk, int level, int optname,
				 char __user *optval, unsigned int optlen)
{
	if (level != SOL_RAW)
		return compat_ip_setsockopt(sk, level, optname, optval, optlen);
	return do_raw_setsockopt(sk, level, optname, optval, optlen);
}
