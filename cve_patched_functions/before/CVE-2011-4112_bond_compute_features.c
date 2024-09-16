static void bond_compute_features(struct bonding *bond)
{
	struct slave *slave;
	struct net_device *bond_dev = bond->dev;
	u32 vlan_features = BOND_VLAN_FEATURES;
	unsigned short max_hard_header_len = ETH_HLEN;
	int i;

	read_lock(&bond->lock);

	if (!bond->first_slave)
		goto done;

	bond_for_each_slave(bond, slave, i) {
		vlan_features = netdev_increment_features(vlan_features,
			slave->dev->vlan_features, BOND_VLAN_FEATURES);

		if (slave->dev->hard_header_len > max_hard_header_len)
			max_hard_header_len = slave->dev->hard_header_len;
	}

done:
	bond_dev->vlan_features = vlan_features;
	bond_dev->hard_header_len = max_hard_header_len;

	read_unlock(&bond->lock);

	netdev_change_features(bond_dev);
}
