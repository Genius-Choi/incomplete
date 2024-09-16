void ipv6_icmp_error(struct sock *sk, struct sk_buff *skb, int err,
		     __be16 port, u32 info, u8 *payload)
{
	struct ipv6_pinfo *np  = inet6_sk(sk);
	struct icmp6hdr *icmph = icmp6_hdr(skb);
	struct sock_exterr_skb *serr;

	if (!np->recverr)
		return;

	skb = skb_clone(skb, GFP_ATOMIC);
	if (!skb)
		return;

	skb->protocol = htons(ETH_P_IPV6);

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_errno = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_ICMP6;
	serr->ee.ee_type = icmph->icmp6_type;
	serr->ee.ee_code = icmph->icmp6_code;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&(((struct ipv6hdr *)(icmph + 1))->daddr) -
				  skb_network_header(skb);
	serr->port = port;

	__skb_pull(skb, payload - skb->data);
	skb_reset_transport_header(skb);

	if (sock_queue_err_skb(sk, skb))
		kfree_skb(skb);
}
