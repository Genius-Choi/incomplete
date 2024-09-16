static struct macvlan_dev *macvlan_hash_lookup(const struct macvlan_port *port,
					       const unsigned char *addr)
{
	struct macvlan_dev *vlan;
	struct hlist_node *n;

	hlist_for_each_entry_rcu(vlan, n, &port->vlan_hash[addr[5]], hlist) {
		if (!compare_ether_addr_64bits(vlan->dev->dev_addr, addr))
			return vlan;
	}
	return NULL;
}
