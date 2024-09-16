static struct rtnl_link_stats64 *veth_get_stats64(struct net_device *dev,
						  struct rtnl_link_stats64 *tot)
{
	struct veth_priv *priv = netdev_priv(dev);
	int cpu;

	for_each_possible_cpu(cpu) {
		struct veth_net_stats *stats = per_cpu_ptr(priv->stats, cpu);
		u64 rx_packets, rx_bytes, rx_dropped;
		u64 tx_packets, tx_bytes;
		unsigned int start;

		do {
			start = u64_stats_fetch_begin_bh(&stats->syncp);
			rx_packets = stats->rx_packets;
			tx_packets = stats->tx_packets;
			rx_bytes = stats->rx_bytes;
			tx_bytes = stats->tx_bytes;
			rx_dropped = stats->rx_dropped;
		} while (u64_stats_fetch_retry_bh(&stats->syncp, start));
		tot->rx_packets += rx_packets;
		tot->tx_packets += tx_packets;
		tot->rx_bytes   += rx_bytes;
		tot->tx_bytes   += tx_bytes;
		tot->rx_dropped += rx_dropped;
	}

	return tot;
}
