static struct net_device_stats *veth_get_stats(struct net_device *dev)
{
	struct veth_priv *priv;
	int cpu;
	struct veth_net_stats *stats, total = {0};

	priv = netdev_priv(dev);

	for_each_possible_cpu(cpu) {
		stats = per_cpu_ptr(priv->stats, cpu);

		total.rx_packets += stats->rx_packets;
		total.tx_packets += stats->tx_packets;
		total.rx_bytes   += stats->rx_bytes;
		total.tx_bytes   += stats->tx_bytes;
		total.tx_dropped += stats->tx_dropped;
		total.rx_dropped += stats->rx_dropped;
	}
	dev->stats.rx_packets = total.rx_packets;
	dev->stats.tx_packets = total.tx_packets;
	dev->stats.rx_bytes   = total.rx_bytes;
	dev->stats.tx_bytes   = total.tx_bytes;
	dev->stats.tx_dropped = total.tx_dropped;
	dev->stats.rx_dropped = total.rx_dropped;

	return &dev->stats;
}
