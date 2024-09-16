void br_multicast_enable_port(struct net_bridge_port *port)
{
	struct net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	if (br->multicast_disabled || !netif_running(br->dev))
		goto out;

	__br_multicast_enable_port(port);

out:
	spin_unlock(&br->multicast_lock);
}
