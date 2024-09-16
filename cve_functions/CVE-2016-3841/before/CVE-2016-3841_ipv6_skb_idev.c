static inline struct inet6_dev *ipv6_skb_idev(struct sk_buff *skb)
{
	return skb_dst(skb) ? ip6_dst_idev(skb_dst(skb)) : __in6_dev_get(skb->dev);
}
