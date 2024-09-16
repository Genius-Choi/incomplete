static int bond_netpoll_setup(struct net_device *dev, struct netpoll_info *ni)
{
	struct bonding *bond = netdev_priv(dev);
	struct slave *slave;
	int i, err = 0;

	read_lock(&bond->lock);
	bond_for_each_slave(bond, slave, i) {
		err = slave_enable_netpoll(slave);
		if (err) {
			__bond_netpoll_cleanup(bond);
			break;
		}
	}
	read_unlock(&bond->lock);
	return err;
}
