static inline int ip6_tnl_xmit_ctl(struct ip6_tnl *t)
{
	struct ip6_tnl_parm *p = &t->parms;
	int ret = 0;
	struct net *net = dev_net(t->dev);

	if (p->flags & IP6_TNL_F_CAP_XMIT) {
		struct net_device *ldev = NULL;

		rcu_read_lock();
		if (p->link)
			ldev = dev_get_by_index_rcu(net, p->link);

		if (unlikely(!ipv6_chk_addr(net, &p->laddr, ldev, 0)))
			printk(KERN_WARNING
			       "%s xmit: Local address not yet configured!\n",
			       p->name);
		else if (!ipv6_addr_is_multicast(&p->raddr) &&
			 unlikely(ipv6_chk_addr(net, &p->raddr, NULL, 0)))
			printk(KERN_WARNING
			       "%s xmit: Routing loop! "
			       "Remote address found on this node!\n",
			       p->name);
		else
			ret = 1;
		rcu_read_unlock();
	}
	return ret;
}
