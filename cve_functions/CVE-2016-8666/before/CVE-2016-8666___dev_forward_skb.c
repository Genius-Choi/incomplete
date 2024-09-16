int __dev_forward_skb(struct net_device *dev, struct sk_buff *skb)
{
	if (skb_orphan_frags(skb, GFP_ATOMIC) ||
	    unlikely(!is_skb_forwardable(dev, skb))) {
		atomic_long_inc(&dev->rx_dropped);
		kfree_skb(skb);
		return NET_RX_DROP;
	}

	skb_scrub_packet(skb, true);
	skb->priority = 0;
	skb->protocol = eth_type_trans(skb, dev);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);

	return 0;
}
