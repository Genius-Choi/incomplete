static void macvlan_hash_add(struct macvlan_dev *vlan)
{
	struct macvlan_port *port = vlan->port;
	const unsigned char *addr = vlan->dev->dev_addr;

	hlist_add_head_rcu(&vlan->hlist, &port->vlan_hash[addr[5]]);
}
