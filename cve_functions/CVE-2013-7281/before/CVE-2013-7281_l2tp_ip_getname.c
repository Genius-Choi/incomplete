static int l2tp_ip_getname(struct socket *sock, struct sockaddr *uaddr,
			   int *uaddr_len, int peer)
{
	struct sock *sk		= sock->sk;
	struct inet_sock *inet	= inet_sk(sk);
	struct l2tp_ip_sock *lsk = l2tp_ip_sk(sk);
	struct sockaddr_l2tpip *lsa = (struct sockaddr_l2tpip *)uaddr;

	memset(lsa, 0, sizeof(*lsa));
	lsa->l2tp_family = AF_INET;
	if (peer) {
		if (!inet->inet_dport)
			return -ENOTCONN;
		lsa->l2tp_conn_id = lsk->peer_conn_id;
		lsa->l2tp_addr.s_addr = inet->inet_daddr;
	} else {
		__be32 addr = inet->inet_rcv_saddr;
		if (!addr)
			addr = inet->inet_saddr;
		lsa->l2tp_conn_id = lsk->conn_id;
		lsa->l2tp_addr.s_addr = addr;
	}
	*uaddr_len = sizeof(*lsa);
	return 0;
}
