static netdev_tx_t reg_vif_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	struct net *net = dev_net(dev);
	struct mr6_table *mrt;
	struct flowi6 fl6 = {
		.flowi6_oif	= dev->ifindex,
		.flowi6_iif	= skb->skb_iif ? : LOOPBACK_IFINDEX,
		.flowi6_mark	= skb->mark,
	};
	int err;

	err = ip6mr_fib_lookup(net, &fl6, &mrt);
	if (err < 0) {
		kfree_skb(skb);
		return err;
	}

	read_lock(&mrt_lock);
	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	ip6mr_cache_report(mrt, skb, mrt->mroute_reg_vif_num, MRT6MSG_WHOLEPKT);
	read_unlock(&mrt_lock);
	kfree_skb(skb);
	return NETDEV_TX_OK;
}
