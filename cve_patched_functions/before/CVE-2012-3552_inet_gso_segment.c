static struct sk_buff *inet_gso_segment(struct sk_buff *skb, u32 features)
{
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	struct iphdr *iph;
	const struct net_protocol *ops;
	int proto;
	int ihl;
	int id;
	unsigned int offset = 0;

	if (!(features & NETIF_F_V4_CSUM))
		features &= ~NETIF_F_SG;

	if (unlikely(skb_shinfo(skb)->gso_type &
		     ~(SKB_GSO_TCPV4 |
		       SKB_GSO_UDP |
		       SKB_GSO_DODGY |
		       SKB_GSO_TCP_ECN |
		       0)))
		goto out;

	if (unlikely(!pskb_may_pull(skb, sizeof(*iph))))
		goto out;

	iph = ip_hdr(skb);
	ihl = iph->ihl * 4;
	if (ihl < sizeof(*iph))
		goto out;

	if (unlikely(!pskb_may_pull(skb, ihl)))
		goto out;

	__skb_pull(skb, ihl);
	skb_reset_transport_header(skb);
	iph = ip_hdr(skb);
	id = ntohs(iph->id);
	proto = iph->protocol & (MAX_INET_PROTOS - 1);
	segs = ERR_PTR(-EPROTONOSUPPORT);

	rcu_read_lock();
	ops = rcu_dereference(inet_protos[proto]);
	if (likely(ops && ops->gso_segment))
		segs = ops->gso_segment(skb, features);
	rcu_read_unlock();

	if (!segs || IS_ERR(segs))
		goto out;

	skb = segs;
	do {
		iph = ip_hdr(skb);
		if (proto == IPPROTO_UDP) {
			iph->id = htons(id);
			iph->frag_off = htons(offset >> 3);
			if (skb->next != NULL)
				iph->frag_off |= htons(IP_MF);
			offset += (skb->len - skb->mac_len - iph->ihl * 4);
		} else
			iph->id = htons(id++);
		iph->tot_len = htons(skb->len - skb->mac_len);
		iph->check = 0;
		iph->check = ip_fast_csum(skb_network_header(skb), iph->ihl);
	} while ((skb = skb->next));

out:
	return segs;
}
