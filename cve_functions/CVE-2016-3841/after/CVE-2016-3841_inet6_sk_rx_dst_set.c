static void inet6_sk_rx_dst_set(struct sock *sk, const struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);

	if (dst) {
		const struct rt6_info *rt = (const struct rt6_info *)dst;

		dst_hold(dst);
		sk->sk_rx_dst = dst;
		inet_sk(sk)->rx_dst_ifindex = skb->skb_iif;
		inet6_sk(sk)->rx_dst_cookie = rt6_get_cookie(rt);
	}
}
