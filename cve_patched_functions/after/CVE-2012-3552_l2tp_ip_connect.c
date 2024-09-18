static int l2tp_ip_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct sockaddr_l2tpip *lsa = (struct sockaddr_l2tpip *) uaddr;
	struct inet_sock *inet = inet_sk(sk);
	struct flowi4 fl4;
	struct rtable *rt;
	__be32 saddr;
	int oif, rc;

	rc = -EINVAL;
	if (addr_len < sizeof(*lsa))
		goto out;

	rc = -EAFNOSUPPORT;
	if (lsa->l2tp_family != AF_INET)
		goto out;

	sk_dst_reset(sk);

	oif = sk->sk_bound_dev_if;
	saddr = inet->inet_saddr;

	rc = -EINVAL;
	if (ipv4_is_multicast(lsa->l2tp_addr.s_addr))
		goto out;

	rt = ip_route_connect(&fl4, lsa->l2tp_addr.s_addr, saddr,
			      RT_CONN_FLAGS(sk), oif,
			      IPPROTO_L2TP,
			      0, 0, sk, true);
	if (IS_ERR(rt)) {
		rc = PTR_ERR(rt);
		if (rc == -ENETUNREACH)
			IP_INC_STATS_BH(&init_net, IPSTATS_MIB_OUTNOROUTES);
		goto out;
	}

	rc = -ENETUNREACH;
	if (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) {
		ip_rt_put(rt);
		goto out;
	}

	l2tp_ip_sk(sk)->peer_conn_id = lsa->l2tp_conn_id;

	if (!inet->inet_saddr)
		inet->inet_saddr = rt->rt_src;
	if (!inet->inet_rcv_saddr)
		inet->inet_rcv_saddr = rt->rt_src;
	inet->inet_daddr = rt->rt_dst;
	sk->sk_state = TCP_ESTABLISHED;
	inet->inet_id = jiffies;

	sk_dst_set(sk, &rt->dst);

	write_lock_bh(&l2tp_ip_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &l2tp_ip_bind_table);
	write_unlock_bh(&l2tp_ip_lock);

	rc = 0;
out:
	return rc;
}
