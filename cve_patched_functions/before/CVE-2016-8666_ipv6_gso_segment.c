static struct sk_buff *ipv6_gso_segment(struct sk_buff *skb,
	netdev_features_t features)
{
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	struct ipv6hdr *ipv6h;
	const struct net_offload *ops;
	int proto;
	struct frag_hdr *fptr;
	unsigned int unfrag_ip6hlen;
	u8 *prevhdr;
	int offset = 0;
	bool encap, udpfrag;
	int nhoff;

	if (unlikely(skb_shinfo(skb)->gso_type &
		     ~(SKB_GSO_TCPV4 |
		       SKB_GSO_UDP |
		       SKB_GSO_DODGY |
		       SKB_GSO_TCP_ECN |
		       SKB_GSO_GRE |
		       SKB_GSO_GRE_CSUM |
		       SKB_GSO_IPIP |
		       SKB_GSO_SIT |
		       SKB_GSO_UDP_TUNNEL |
		       SKB_GSO_UDP_TUNNEL_CSUM |
		       SKB_GSO_TUNNEL_REMCSUM |
		       SKB_GSO_TCPV6 |
		       0)))
		goto out;

	skb_reset_network_header(skb);
	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	if (unlikely(!pskb_may_pull(skb, sizeof(*ipv6h))))
		goto out;

	encap = SKB_GSO_CB(skb)->encap_level > 0;
	if (encap)
		features &= skb->dev->hw_enc_features;
	SKB_GSO_CB(skb)->encap_level += sizeof(*ipv6h);

	ipv6h = ipv6_hdr(skb);
	__skb_pull(skb, sizeof(*ipv6h));
	segs = ERR_PTR(-EPROTONOSUPPORT);

	proto = ipv6_gso_pull_exthdrs(skb, ipv6h->nexthdr);

	if (skb->encapsulation &&
	    skb_shinfo(skb)->gso_type & (SKB_GSO_SIT|SKB_GSO_IPIP))
		udpfrag = proto == IPPROTO_UDP && encap;
	else
		udpfrag = proto == IPPROTO_UDP && !skb->encapsulation;

	ops = rcu_dereference(inet6_offloads[proto]);
	if (likely(ops && ops->callbacks.gso_segment)) {
		skb_reset_transport_header(skb);
		segs = ops->callbacks.gso_segment(skb, features);
	}

	if (IS_ERR(segs))
		goto out;

	for (skb = segs; skb; skb = skb->next) {
		ipv6h = (struct ipv6hdr *)(skb_mac_header(skb) + nhoff);
		ipv6h->payload_len = htons(skb->len - nhoff - sizeof(*ipv6h));
		skb->network_header = (u8 *)ipv6h - skb->head;

		if (udpfrag) {
			unfrag_ip6hlen = ip6_find_1stfragopt(skb, &prevhdr);
			fptr = (struct frag_hdr *)((u8 *)ipv6h + unfrag_ip6hlen);
			fptr->frag_off = htons(offset);
			if (skb->next)
				fptr->frag_off |= htons(IP6_MF);
			offset += (ntohs(ipv6h->payload_len) -
				   sizeof(struct frag_hdr));
		}
		if (encap)
			skb_reset_inner_headers(skb);
	}

out:
	return segs;
}
