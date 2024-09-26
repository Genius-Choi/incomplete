static int dccp_v6_send_response(struct sock *sk, struct request_sock *req,
				 struct request_values *rv_unused)
{
	struct inet6_request_sock *ireq6 = inet6_rsk(req);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *skb;
	struct ipv6_txoptions *opt = NULL;
	struct in6_addr *final_p, final;
	struct flowi6 fl6;
	int err = -1;
	struct dst_entry *dst;

	memset(&fl6, 0, sizeof(fl6));
	fl6.flowi6_proto = IPPROTO_DCCP;
	ipv6_addr_copy(&fl6.daddr, &ireq6->rmt_addr);
	ipv6_addr_copy(&fl6.saddr, &ireq6->loc_addr);
	fl6.flowlabel = 0;
	fl6.flowi6_oif = ireq6->iif;
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

	skb = dccp_make_response(sk, dst, req);
	if (skb != NULL) {
		struct dccp_hdr *dh = dccp_hdr(skb);

		dh->dccph_checksum = dccp_v6_csum_finish(skb,
							 &ireq6->loc_addr,
							 &ireq6->rmt_addr);
		ipv6_addr_copy(&fl6.daddr, &ireq6->rmt_addr);
		err = ip6_xmit(sk, skb, &fl6, opt);
		err = net_xmit_eval(err);
	}

done:
	if (opt != NULL && opt != np->opt)
		sock_kfree_s(sk, opt, opt->tot_len);
	dst_release(dst);
	return err;
}
