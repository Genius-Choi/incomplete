void netif_wake_subqueue(struct net_device *dev, u16 queue_index)
{
	struct netdev_queue *txq = netdev_get_tx_queue(dev, queue_index);

	if (test_and_clear_bit(__QUEUE_STATE_DRV_XOFF, &txq->state)) {
		struct Qdisc *q;

		rcu_read_lock();
		q = rcu_dereference(txq->qdisc);
		__netif_schedule(q);
		rcu_read_unlock();
	}
}
