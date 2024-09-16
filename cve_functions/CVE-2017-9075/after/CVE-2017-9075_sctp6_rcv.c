static int sctp6_rcv(struct sk_buff *skb)
{
	return sctp_rcv(skb) ? -1 : 0;
}
