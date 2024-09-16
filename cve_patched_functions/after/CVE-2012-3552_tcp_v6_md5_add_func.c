static int tcp_v6_md5_add_func(struct sock *sk, struct sock *addr_sk,
			       u8 *newkey, __u8 newkeylen)
{
	return tcp_v6_md5_do_add(sk, &inet6_sk(addr_sk)->daddr,
				 newkey, newkeylen);
}
