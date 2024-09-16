static int bond_neigh_setup(struct net_device *dev, struct neigh_parms *parms)
{
	struct bonding *bond = netdev_priv(dev);
	struct slave *slave = bond->first_slave;

	if (slave) {
		const struct net_device_ops *slave_ops
			= slave->dev->netdev_ops;
		if (slave_ops->ndo_neigh_setup)
			return slave_ops->ndo_neigh_setup(slave->dev, parms);
	}
	return 0;
}
