void ip6_datagram_recv_ctl(struct sock *sk, struct msghdr *msg,
			  struct sk_buff *skb)
{
	ip6_datagram_recv_common_ctl(sk, msg, skb);
	ip6_datagram_recv_specific_ctl(sk, msg, skb);
}
