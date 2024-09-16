void llc_sap_handler(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_addr laddr;

	llc_pdu_decode_da(skb, laddr.mac);
	llc_pdu_decode_dsap(skb, &laddr.lsap);

	if (is_multicast_ether_addr(laddr.mac)) {
		llc_sap_mcast(sap, &laddr, skb);
		kfree_skb(skb);
	} else {
		struct sock *sk = llc_lookup_dgram(sap, &laddr);
		if (sk) {
			llc_sap_rcv(sap, skb, sk);
			sock_put(sk);
		} else
			kfree_skb(skb);
	}
}
