unsigned int skb_gso_transport_seglen(const struct sk_buff *skb)
{
	const struct skb_shared_info *shinfo = skb_shinfo(skb);
	unsigned int thlen = 0;

	if (skb->encapsulation) {
		thlen = skb_inner_transport_header(skb) -
			skb_transport_header(skb);

		if (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)))
			thlen += inner_tcp_hdrlen(skb);
	} else if (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))) {
		thlen = tcp_hdrlen(skb);
	} else if (unlikely(shinfo->gso_type & SKB_GSO_SCTP)) {
		thlen = sizeof(struct sctphdr);
	}
	/* UFO sets gso_size to the size of the fragmentation
	 * payload, i.e. the size of the L4 (UDP) header is already
	 * accounted for.
	 */
	return thlen + shinfo->gso_size;
}
