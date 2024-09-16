u16 __skb_tx_hash(const struct net_device *dev, struct sk_buff *skb,
		  unsigned int num_tx_queues)
{
	u32 hash;
	u16 qoffset = 0;
	u16 qcount = num_tx_queues;

	if (skb_rx_queue_recorded(skb)) {
		hash = skb_get_rx_queue(skb);
		while (unlikely(hash >= num_tx_queues))
			hash -= num_tx_queues;
		return hash;
	}

	if (dev->num_tc) {
		u8 tc = netdev_get_prio_tc_map(dev, skb->priority);

		qoffset = dev->tc_to_txq[tc].offset;
		qcount = dev->tc_to_txq[tc].count;
	}

	return (u16) reciprocal_scale(skb_get_hash(skb), qcount) + qoffset;
}
