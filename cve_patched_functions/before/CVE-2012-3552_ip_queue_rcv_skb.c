int ip_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	if (!(inet_sk(sk)->cmsg_flags & IP_CMSG_PKTINFO))
		skb_dst_drop(skb);
	return sock_queue_rcv_skb(sk, skb);
}
