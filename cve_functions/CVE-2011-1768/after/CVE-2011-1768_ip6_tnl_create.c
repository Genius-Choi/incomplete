static struct ip6_tnl *ip6_tnl_create(struct net *net, struct ip6_tnl_parm *p)
{
	struct net_device *dev;
	struct ip6_tnl *t;
	char name[IFNAMSIZ];
	int err;
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	if (p->name[0])
		strlcpy(name, p->name, IFNAMSIZ);
	else
		sprintf(name, "ip6tnl%%d");

	dev = alloc_netdev(sizeof (*t), name, ip6_tnl_dev_setup);
	if (dev == NULL)
		goto failed;

	dev_net_set(dev, net);

	if (strchr(name, '%')) {
		if (dev_alloc_name(dev, name) < 0)
			goto failed_free;
	}

	t = netdev_priv(dev);
	t->parms = *p;
	ip6_tnl_dev_init(dev);

	if ((err = register_netdevice(dev)) < 0)
		goto failed_free;

	dev_hold(dev);
	ip6_tnl_link(ip6n, t);
	return t;

failed_free:
	free_netdev(dev);
failed:
	return NULL;
}
