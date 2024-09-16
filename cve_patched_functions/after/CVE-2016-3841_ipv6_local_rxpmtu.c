void ipv6_local_rxpmtu(struct sock *sk, struct flowi6 *fl6, u32 mtu)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6hdr *iph;
	struct sk_buff *skb;
	struct ip6_mtuinfo *mtu_info;

	if (!np->rxopt.bits.rxpmtu)
		return;

	skb = alloc_skb(sizeof(struct ipv6hdr), GFP_ATOMIC);
	if (!skb)
		return;

	skb_put(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);
	iph->daddr = fl6->daddr;

	mtu_info = IP6CBMTU(skb);

	mtu_info->ip6m_mtu = mtu;
	mtu_info->ip6m_addr.sin6_family = AF_INET6;
	mtu_info->ip6m_addr.sin6_port = 0;
	mtu_info->ip6m_addr.sin6_flowinfo = 0;
	mtu_info->ip6m_addr.sin6_scope_id = fl6->flowi6_oif;
	mtu_info->ip6m_addr.sin6_addr = ipv6_hdr(skb)->daddr;

	__skb_pull(skb, skb_tail_pointer(skb) - skb->data);
	skb_reset_transport_header(skb);

	skb = xchg(&np->rxpmtu, skb);
	kfree_skb(skb);
}
