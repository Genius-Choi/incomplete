static struct netdev_queue *dev_pick_tx(struct net_device *dev,
					struct sk_buff *skb)
{
	u16 queue_index;
	struct sock *sk = skb->sk;

	if (sk_tx_queue_recorded(sk)) {
		queue_index = sk_tx_queue_get(sk);
	} else {
		const struct net_device_ops *ops = dev->netdev_ops;

		if (ops->ndo_select_queue) {
			queue_index = ops->ndo_select_queue(dev, skb);
			queue_index = dev_cap_txqueue(dev, queue_index);
		} else {
			queue_index = 0;
			if (dev->real_num_tx_queues > 1)
				queue_index = skb_tx_hash(dev, skb);

			if (sk) {
				struct dst_entry *dst = rcu_dereference_bh(sk->sk_dst_cache);

				if (dst && skb_dst(skb) == dst)
					sk_tx_queue_set(sk, queue_index);
			}
		}
	}

	skb_set_queue_mapping(skb, queue_index);
	return netdev_get_tx_queue(dev, queue_index);
}
