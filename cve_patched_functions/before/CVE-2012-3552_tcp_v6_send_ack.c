static void tcp_v6_send_ack(struct sk_buff *skb, u32 seq, u32 ack, u32 win, u32 ts,
			    struct tcp_md5sig_key *key)
{
	tcp_v6_send_response(skb, seq, ack, win, ts, key, 0);
}
