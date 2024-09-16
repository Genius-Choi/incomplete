static int tg3_set_channels(struct net_device *dev,
			    struct ethtool_channels *channel)
{
	struct tg3 *tp = netdev_priv(dev);

	if (!tg3_flag(tp, SUPPORT_MSIX))
		return -EOPNOTSUPP;

	if (channel->rx_count > tp->rxq_max ||
	    channel->tx_count > tp->txq_max)
		return -EINVAL;

	tp->rxq_req = channel->rx_count;
	tp->txq_req = channel->tx_count;

	if (!netif_running(dev))
		return 0;

	tg3_stop(tp);

	tg3_carrier_off(tp);

	tg3_start(tp, true, false, false);

	return 0;
}
