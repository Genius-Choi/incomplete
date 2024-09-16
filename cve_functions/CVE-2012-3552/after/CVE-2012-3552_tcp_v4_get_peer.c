struct inet_peer *tcp_v4_get_peer(struct sock *sk, bool *release_it)
{
	struct rtable *rt = (struct rtable *) __sk_dst_get(sk);
	struct inet_sock *inet = inet_sk(sk);
	struct inet_peer *peer;

	if (!rt || rt->rt_dst != inet->inet_daddr) {
		peer = inet_getpeer_v4(inet->inet_daddr, 1);
		*release_it = true;
	} else {
		if (!rt->peer)
			rt_bind_peer(rt, 1);
		peer = rt->peer;
		*release_it = false;
	}

	return peer;
}
