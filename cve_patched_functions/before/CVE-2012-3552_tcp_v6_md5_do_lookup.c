static struct tcp_md5sig_key *tcp_v6_md5_do_lookup(struct sock *sk,
						   const struct in6_addr *addr)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int i;

	BUG_ON(tp == NULL);

	if (!tp->md5sig_info || !tp->md5sig_info->entries6)
		return NULL;

	for (i = 0; i < tp->md5sig_info->entries6; i++) {
		if (ipv6_addr_equal(&tp->md5sig_info->keys6[i].addr, addr))
			return &tp->md5sig_info->keys6[i].base;
	}
	return NULL;
}
