static void __bond_netpoll_cleanup(struct bonding *bond)
{
	struct slave *slave;
	int i;

	bond_for_each_slave(bond, slave, i)
		if (IS_UP(slave->dev))
			slave_disable_netpoll(slave);
}
