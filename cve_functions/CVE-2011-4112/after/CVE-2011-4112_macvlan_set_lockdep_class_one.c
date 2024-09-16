static void macvlan_set_lockdep_class_one(struct net_device *dev,
					  struct netdev_queue *txq,
					  void *_unused)
{
	lockdep_set_class(&txq->_xmit_lock,
			  &macvlan_netdev_xmit_lock_key);
}
