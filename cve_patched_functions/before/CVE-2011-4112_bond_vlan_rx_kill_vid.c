static void bond_vlan_rx_kill_vid(struct net_device *bond_dev, uint16_t vid)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct slave *slave;
	int i, res;

	bond_for_each_slave(bond, slave, i) {
		struct net_device *slave_dev = slave->dev;
		const struct net_device_ops *slave_ops = slave_dev->netdev_ops;

		if ((slave_dev->features & NETIF_F_HW_VLAN_FILTER) &&
		    slave_ops->ndo_vlan_rx_kill_vid) {
			slave_ops->ndo_vlan_rx_kill_vid(slave_dev, vid);
		}
	}

	res = bond_del_vlan(bond, vid);
	if (res) {
		pr_err("%s: Error: Failed to remove vlan id %d\n",
		       bond_dev->name, vid);
	}
}
