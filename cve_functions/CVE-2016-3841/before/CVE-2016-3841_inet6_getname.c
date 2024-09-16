int inet6_getname(struct socket *sock, struct sockaddr *uaddr,
		 int *uaddr_len, int peer)
{
	struct sockaddr_in6 *sin = (struct sockaddr_in6 *)uaddr;
	struct sock *sk = sock->sk;
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);

	sin->sin6_family = AF_INET6;
	sin->sin6_flowinfo = 0;
	sin->sin6_scope_id = 0;
	if (peer) {
		if (!inet->inet_dport)
			return -ENOTCONN;
		if (((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_SYN_SENT)) &&
		    peer == 1)
			return -ENOTCONN;
		sin->sin6_port = inet->inet_dport;
		sin->sin6_addr = sk->sk_v6_daddr;
		if (np->sndflow)
			sin->sin6_flowinfo = np->flow_label;
	} else {
		if (ipv6_addr_any(&sk->sk_v6_rcv_saddr))
			sin->sin6_addr = np->saddr;
		else
			sin->sin6_addr = sk->sk_v6_rcv_saddr;

		sin->sin6_port = inet->inet_sport;
	}
	sin->sin6_scope_id = ipv6_iface_scope_id(&sin->sin6_addr,
						 sk->sk_bound_dev_if);
	*uaddr_len = sizeof(*sin);
	return 0;
}
