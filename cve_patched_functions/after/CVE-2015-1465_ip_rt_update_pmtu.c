static void ip_rt_update_pmtu(struct dst_entry *dst, struct sock *sk,
			      struct sk_buff *skb, u32 mtu)
{
	struct rtable *rt = (struct rtable *) dst;
	struct flowi4 fl4;

	ip_rt_build_flow_key(&fl4, sk, skb);
	__ip_rt_update_pmtu(rt, &fl4, mtu);
}
