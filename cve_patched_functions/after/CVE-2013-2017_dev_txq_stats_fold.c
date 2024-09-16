void dev_txq_stats_fold(const struct net_device *dev,
			struct net_device_stats *stats)
{
	unsigned long tx_bytes = 0, tx_packets = 0, tx_dropped = 0;
	unsigned int i;
	struct netdev_queue *txq;

	for (i = 0; i < dev->num_tx_queues; i++) {
		txq = netdev_get_tx_queue(dev, i);
		tx_bytes   += txq->tx_bytes;
		tx_packets += txq->tx_packets;
		tx_dropped += txq->tx_dropped;
	}
	if (tx_bytes || tx_packets || tx_dropped) {
		stats->tx_bytes   = tx_bytes;
		stats->tx_packets = tx_packets;
		stats->tx_dropped = tx_dropped;
	}
}
