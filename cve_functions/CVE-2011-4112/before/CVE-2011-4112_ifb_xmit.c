static netdev_tx_t ifb_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ifb_private *dp = netdev_priv(dev);
	u32 from = G_TC_FROM(skb->tc_verd);

	u64_stats_update_begin(&dp->rsync);
	dp->rx_packets++;
	dp->rx_bytes += skb->len;
	u64_stats_update_end(&dp->rsync);

	if (!(from & (AT_INGRESS|AT_EGRESS)) || !skb->skb_iif) {
		dev_kfree_skb(skb);
		dev->stats.rx_dropped++;
		return NETDEV_TX_OK;
	}

	if (skb_queue_len(&dp->rq) >= dev->tx_queue_len) {
		netif_stop_queue(dev);
	}

	__skb_queue_tail(&dp->rq, skb);
	if (!dp->tasklet_pending) {
		dp->tasklet_pending = 1;
		tasklet_schedule(&dp->ifb_tasklet);
	}

	return NETDEV_TX_OK;
}
