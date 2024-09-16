static void tcp_v6_send_reset(struct sock *sk, struct sk_buff *skb)
{
	struct tcphdr *th = tcp_hdr(skb);
	u32 seq = 0, ack_seq = 0;
	struct tcp_md5sig_key *key = NULL;

	if (th->rst)
		return;

	if (!ipv6_unicast_destination(skb))
		return;

#ifdef CONFIG_TCP_MD5SIG
	if (sk)
		key = tcp_v6_md5_do_lookup(sk, &ipv6_hdr(skb)->daddr);
#endif

	if (th->ack)
		seq = ntohl(th->ack_seq);
	else
		ack_seq = ntohl(th->seq) + th->syn + th->fin + skb->len -
			  (th->doff << 2);

	tcp_v6_send_response(skb, seq, ack_seq, 0, 0, key, 1);
}
