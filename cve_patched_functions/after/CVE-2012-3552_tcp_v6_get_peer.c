static struct inet_peer *tcp_v6_get_peer(struct sock *sk, bool *release_it)
{
	struct rt6_info *rt = (struct rt6_info *) __sk_dst_get(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct inet_peer *peer;

	if (!rt ||
	    !ipv6_addr_equal(&np->daddr, &rt->rt6i_dst.addr)) {
		peer = inet_getpeer_v6(&np->daddr, 1);
		*release_it = true;
	} else {
		if (!rt->rt6i_peer)
			rt6_bind_peer(rt, 1);
		peer = rt->rt6i_peer;
		*release_it = false;
	}

	return peer;
}
