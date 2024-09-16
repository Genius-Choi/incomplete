int bond_dev_queue_xmit(struct bonding *bond, struct sk_buff *skb,
			struct net_device *slave_dev)
{
	skb->dev = slave_dev;
	skb->priority = 1;

	skb->queue_mapping = bond_queue_mapping(skb);

	if (unlikely(netpoll_tx_running(slave_dev)))
		bond_netpoll_send_skb(bond_get_slave_by_dev(bond, slave_dev), skb);
	else
		dev_queue_xmit(skb);

	return 0;
}
