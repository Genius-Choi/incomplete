static inline int skb_needs_linearize(struct sk_buff *skb,
				      struct net_device *dev)
{
	return (skb_has_frags(skb) && !(dev->features & NETIF_F_FRAGLIST)) ||
	       (skb_shinfo(skb)->nr_frags && (!(dev->features & NETIF_F_SG) ||
					      illegal_highdma(dev, skb)));
}
