static void __netdev_adjacent_dev_remove(struct net_device *dev,
					 struct net_device *adj_dev,
					 struct list_head *dev_list)
{
	struct netdev_adjacent *adj;

	adj = __netdev_find_adj(adj_dev, dev_list);

	if (!adj) {
		pr_err("tried to remove device %s from %s\n",
		       dev->name, adj_dev->name);
		BUG();
	}

	if (adj->ref_nr > 1) {
		pr_debug("%s to %s ref_nr-- = %d\n", dev->name, adj_dev->name,
			 adj->ref_nr-1);
		adj->ref_nr--;
		return;
	}

	if (adj->master)
		sysfs_remove_link(&(dev->dev.kobj), "master");

	if (netdev_adjacent_is_neigh_list(dev, adj_dev, dev_list))
		netdev_adjacent_sysfs_del(dev, adj_dev->name, dev_list);

	list_del_rcu(&adj->list);
	pr_debug("dev_put for %s, because link removed from %s to %s\n",
		 adj_dev->name, dev->name, adj_dev->name);
	dev_put(adj_dev);
	kfree_rcu(adj, rcu);
}
