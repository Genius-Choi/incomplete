static void macvlan_uninit(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvlan_port *port = vlan->port;

	free_percpu(vlan->pcpu_stats);

	port->count -= 1;
	if (!port->count)
		macvlan_port_destroy(port->dev);
}
