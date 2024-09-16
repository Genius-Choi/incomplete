static void *tcp_v6_tw_get_peer(struct sock *sk)
{
	struct inet6_timewait_sock *tw6 = inet6_twsk(sk);
	struct inet_timewait_sock *tw = inet_twsk(sk);

	if (tw->tw_family == AF_INET)
		return tcp_v4_tw_get_peer(sk);

	return inet_getpeer_v6(&tw6->tw_v6_daddr, 1);
}
