static int sctp_setsockopt_recvrcvinfo(struct sock *sk,
				       char __user *optval,
				       unsigned int optlen)
{
	int val;

	if (optlen < sizeof(int))
		return -EINVAL;
	if (get_user(val, (int __user *) optval))
		return -EFAULT;

	sctp_sk(sk)->recvrcvinfo = (val == 0) ? 0 : 1;

	return 0;
}
