struct net_device *dev_get_by_name_rcu(struct net *net, const char *name)
{
	struct hlist_node *p;
	struct net_device *dev;
	struct hlist_head *head = dev_name_hash(net, name);

	hlist_for_each_entry_rcu(dev, p, head, name_hlist)
		if (!strncmp(dev->name, name, IFNAMSIZ))
			return dev;

	return NULL;
}
