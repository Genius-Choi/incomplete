void rt_flush_dev(struct net_device *dev)
{
	if (!list_empty(&rt_uncached_list)) {
		struct net *net = dev_net(dev);
		struct rtable *rt;

		spin_lock_bh(&rt_uncached_lock);
		list_for_each_entry(rt, &rt_uncached_list, rt_uncached) {
			if (rt->dst.dev != dev)
				continue;
			rt->dst.dev = net->loopback_dev;
			dev_hold(rt->dst.dev);
			dev_put(dev);
		}
		spin_unlock_bh(&rt_uncached_lock);
	}
}
