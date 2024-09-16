static int tcp_v4_md5_add_func(struct sock *sk, struct sock *addr_sk,
			       u8 *newkey, u8 newkeylen)
{
	return tcp_v4_md5_do_add(sk, inet_sk(addr_sk)->inet_daddr,
				 newkey, newkeylen);
}
