static int tcp_v6_send_synack(struct sock *sk, struct request_sock *req,
			      struct request_values *rvp)
{
	struct inet6_request_sock *treq = inet6_rsk(req);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff * skb;
	struct ipv6_txoptions *opt = NULL;
	struct in6_addr * final_p, final;
	struct flowi6 fl6;
	struct dst_entry *dst;
	int err;

	memset(&fl6, 0, sizeof(fl6));
	fl6.flowi6_proto = IPPROTO_TCP;
	ipv6_addr_copy(&fl6.daddr, &treq->rmt_addr);
	ipv6_addr_copy(&fl6.saddr, &treq->loc_addr);
	fl6.flowlabel = 0;
	fl6.flowi6_oif = treq->iif;
	fl6.flowi6_mark = sk->sk_mark;
	fl6.fl6_dport = inet_rsk(req)->rmt_port;
	fl6.fl6_sport = inet_rsk(req)->loc_port;
	security_req_classify_flow(req, flowi6_to_flowi(&fl6));

	opt = np->opt;
	final_p = fl6_update_dst(&fl6, opt, &final);

	dst = ip6_dst_lookup_flow(sk, &fl6, final_p, false);
	if (IS_ERR(dst)) {
		err = PTR_ERR(dst);
		dst = NULL;
		goto done;
	}
	skb = tcp_make_synack(sk, dst, req, rvp);
	err = -ENOMEM;
	if (skb) {
		__tcp_v6_send_check(skb, &treq->loc_addr, &treq->rmt_addr);

		ipv6_addr_copy(&fl6.daddr, &treq->rmt_addr);
		err = ip6_xmit(sk, skb, &fl6, opt);
		err = net_xmit_eval(err);
	}

done:
	if (opt && opt != np->opt)
		sock_kfree_s(sk, opt, opt->tot_len);
	dst_release(dst);
	return err;
}
