static void macvlan_port_destroy(struct net_device *dev)
{
	struct macvlan_port *port = macvlan_port_get(dev);

	dev->priv_flags &= ~IFF_MACVLAN_PORT;
	netdev_rx_handler_unregister(dev);
	kfree_rcu(port, rcu);
}
