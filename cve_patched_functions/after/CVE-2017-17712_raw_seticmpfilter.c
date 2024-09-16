static int raw_seticmpfilter(struct sock *sk, char __user *optval, int optlen)
{
	if (optlen > sizeof(struct icmp_filter))
		optlen = sizeof(struct icmp_filter);
	if (copy_from_user(&raw_sk(sk)->filter, optval, optlen))
		return -EFAULT;
	return 0;
}
