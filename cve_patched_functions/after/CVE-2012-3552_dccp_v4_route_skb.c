static struct dst_entry* dccp_v4_route_skb(struct net *net, struct sock *sk,
					   struct sk_buff *skb)
{
	struct rtable *rt;
	struct flowi4 fl4 = {
		.flowi4_oif = skb_rtable(skb)->rt_iif,
		.daddr = ip_hdr(skb)->saddr,
		.saddr = ip_hdr(skb)->daddr,
		.flowi4_tos = RT_CONN_FLAGS(sk),
		.flowi4_proto = sk->sk_protocol,
		.fl4_sport = dccp_hdr(skb)->dccph_dport,
		.fl4_dport = dccp_hdr(skb)->dccph_sport,
	};

	security_skb_classify_flow(skb, flowi4_to_flowi(&fl4));
	rt = ip_route_output_flow(net, &fl4, sk);
	if (IS_ERR(rt)) {
		IP_INC_STATS_BH(net, IPSTATS_MIB_OUTNOROUTES);
		return NULL;
	}

	return &rt->dst;
}
