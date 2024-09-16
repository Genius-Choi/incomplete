static int sctp_writeable(struct sock *sk)
{
	int amt = 0;

	amt = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
	if (amt < 0)
		amt = 0;
	return amt;
}
