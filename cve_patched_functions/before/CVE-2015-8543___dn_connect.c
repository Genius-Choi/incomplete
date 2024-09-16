static int __dn_connect(struct sock *sk, struct sockaddr_dn *addr, int addrlen, long *timeo, int flags)
{
	struct socket *sock = sk->sk_socket;
	struct dn_scp *scp = DN_SK(sk);
	int err = -EISCONN;
	struct flowidn fld;
	struct dst_entry *dst;

	if (sock->state == SS_CONNECTED)
		goto out;

	if (sock->state == SS_CONNECTING) {
		err = 0;
		if (scp->state == DN_RUN) {
			sock->state = SS_CONNECTED;
			goto out;
		}
		err = -ECONNREFUSED;
		if (scp->state != DN_CI && scp->state != DN_CC) {
			sock->state = SS_UNCONNECTED;
			goto out;
		}
		return dn_wait_run(sk, timeo);
	}

	err = -EINVAL;
	if (scp->state != DN_O)
		goto out;

	if (addr == NULL || addrlen != sizeof(struct sockaddr_dn))
		goto out;
	if (addr->sdn_family != AF_DECnet)
		goto out;
	if (addr->sdn_flags & SDF_WILD)
		goto out;

	if (sock_flag(sk, SOCK_ZAPPED)) {
		err = dn_auto_bind(sk->sk_socket);
		if (err)
			goto out;
	}

	memcpy(&scp->peer, addr, sizeof(struct sockaddr_dn));

	err = -EHOSTUNREACH;
	memset(&fld, 0, sizeof(fld));
	fld.flowidn_oif = sk->sk_bound_dev_if;
	fld.daddr = dn_saddr2dn(&scp->peer);
	fld.saddr = dn_saddr2dn(&scp->addr);
	dn_sk_ports_copy(&fld, scp);
	fld.flowidn_proto = DNPROTO_NSP;
	if (dn_route_output_sock(&sk->sk_dst_cache, &fld, sk, flags) < 0)
		goto out;
	dst = __sk_dst_get(sk);
	sk->sk_route_caps = dst->dev->features;
	sock->state = SS_CONNECTING;
	scp->state = DN_CI;
	scp->segsize_loc = dst_metric_advmss(dst);

	dn_nsp_send_conninit(sk, NSP_CI);
	err = -EINPROGRESS;
	if (*timeo) {
		err = dn_wait_run(sk, timeo);
	}
out:
	return err;
}
