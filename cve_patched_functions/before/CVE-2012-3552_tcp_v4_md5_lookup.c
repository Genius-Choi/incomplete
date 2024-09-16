struct tcp_md5sig_key *tcp_v4_md5_lookup(struct sock *sk,
					 struct sock *addr_sk)
{
	return tcp_v4_md5_do_lookup(sk, inet_sk(addr_sk)->inet_daddr);
}
