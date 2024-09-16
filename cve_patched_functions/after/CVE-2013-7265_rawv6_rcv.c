int rawv6_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct inet_sock *inet = inet_sk(sk);
	struct raw6_sock *rp = raw6_sk(sk);

	if (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb)) {
		atomic_inc(&sk->sk_drops);
		kfree_skb(skb);
		return NET_RX_DROP;
	}

	if (!rp->checksum)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		skb_postpull_rcsum(skb, skb_network_header(skb),
				   skb_network_header_len(skb));
		if (!csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
				     &ipv6_hdr(skb)->daddr,
				     skb->len, inet->inet_num, skb->csum))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
	if (!skb_csum_unnecessary(skb))
		skb->csum = ~csum_unfold(csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
							 &ipv6_hdr(skb)->daddr,
							 skb->len,
							 inet->inet_num, 0));

	if (inet->hdrincl) {
		if (skb_checksum_complete(skb)) {
			atomic_inc(&sk->sk_drops);
			kfree_skb(skb);
			return NET_RX_DROP;
		}
	}

	rawv6_rcv_skb(sk, skb);
	return 0;
}
