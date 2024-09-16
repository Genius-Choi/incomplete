static netdev_tx_t mpi_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
	int npacks, pending;
	unsigned long flags;
	struct airo_info *ai = dev->ml_priv;

	if (!skb) {
		airo_print_err(dev->name, "%s: skb == NULL!",__func__);
		return NETDEV_TX_OK;
	}
	npacks = skb_queue_len (&ai->txq);

	if (npacks >= MAXTXQ - 1) {
		netif_stop_queue (dev);
		if (npacks > MAXTXQ) {
			dev->stats.tx_fifo_errors++;
			return NETDEV_TX_BUSY;
		}
		skb_queue_tail (&ai->txq, skb);
		return NETDEV_TX_OK;
	}

	spin_lock_irqsave(&ai->aux_lock, flags);
	skb_queue_tail (&ai->txq, skb);
	pending = test_bit(FLAG_PENDING_XMIT, &ai->flags);
	spin_unlock_irqrestore(&ai->aux_lock,flags);
	netif_wake_queue (dev);

	if (pending == 0) {
		set_bit(FLAG_PENDING_XMIT, &ai->flags);
		mpi_send_packet (dev);
	}
	return NETDEV_TX_OK;
}
