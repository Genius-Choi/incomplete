static inline struct sk_buff *dn_alloc_send_pskb(struct sock *sk,
			      unsigned long datalen, int noblock,
			      int *errcode)
{
	struct sk_buff *skb = sock_alloc_send_skb(sk, datalen,
						   noblock, errcode);
	if (skb) {
		skb->protocol = htons(ETH_P_DNA_RT);
		skb->pkt_type = PACKET_OUTGOING;
	}
	return skb;
}
