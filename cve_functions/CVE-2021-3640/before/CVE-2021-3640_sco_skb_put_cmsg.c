static void sco_skb_put_cmsg(struct sk_buff *skb, struct msghdr *msg,
			     struct sock *sk)
{
	if (sco_pi(sk)->cmsg_mask & SCO_CMSG_PKT_STATUS)
		put_cmsg(msg, SOL_BLUETOOTH, BT_SCM_PKT_STATUS,
			 sizeof(bt_cb(skb)->sco.pkt_status),
			 &bt_cb(skb)->sco.pkt_status);
}
