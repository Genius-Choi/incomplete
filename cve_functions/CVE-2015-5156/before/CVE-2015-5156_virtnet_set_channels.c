static int virtnet_set_channels(struct net_device *dev,
				struct ethtool_channels *channels)
{
	struct virtnet_info *vi = netdev_priv(dev);
	u16 queue_pairs = channels->combined_count;
	int err;

	/* We don't support separate rx/tx channels.
	 * We don't allow setting 'other' channels.
	 */
	if (channels->rx_count || channels->tx_count || channels->other_count)
		return -EINVAL;

	if (queue_pairs > vi->max_queue_pairs || queue_pairs == 0)
		return -EINVAL;

	get_online_cpus();
	err = virtnet_set_queues(vi, queue_pairs);
	if (!err) {
		netif_set_real_num_tx_queues(dev, queue_pairs);
		netif_set_real_num_rx_queues(dev, queue_pairs);

		virtnet_set_affinity(vi);
	}
	put_online_cpus();

	return err;
}
