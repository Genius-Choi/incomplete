static int bond_sethwaddr(struct net_device *bond_dev,
			  struct net_device *slave_dev)
{
	pr_debug("bond_dev=%p\n", bond_dev);
	pr_debug("slave_dev=%p\n", slave_dev);
	pr_debug("slave_dev->addr_len=%d\n", slave_dev->addr_len);
	memcpy(bond_dev->dev_addr, slave_dev->dev_addr, slave_dev->addr_len);
	return 0;
}
