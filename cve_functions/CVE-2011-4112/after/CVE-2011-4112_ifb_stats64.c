static struct rtnl_link_stats64 *ifb_stats64(struct net_device *dev,
					     struct rtnl_link_stats64 *stats)
{
	struct ifb_private *dp = netdev_priv(dev);
	unsigned int start;

	do {
		start = u64_stats_fetch_begin_bh(&dp->rsync);
		stats->rx_packets = dp->rx_packets;
		stats->rx_bytes = dp->rx_bytes;
	} while (u64_stats_fetch_retry_bh(&dp->rsync, start));

	do {
		start = u64_stats_fetch_begin_bh(&dp->tsync);

		stats->tx_packets = dp->tx_packets;
		stats->tx_bytes = dp->tx_bytes;

	} while (u64_stats_fetch_retry_bh(&dp->tsync, start));

	stats->rx_dropped = dev->stats.rx_dropped;
	stats->tx_dropped = dev->stats.tx_dropped;

	return stats;
}
