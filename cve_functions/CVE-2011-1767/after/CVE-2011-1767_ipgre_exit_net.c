static void __net_exit ipgre_exit_net(struct net *net)
{
	struct ipgre_net *ign;
	LIST_HEAD(list);

	ign = net_generic(net, ipgre_net_id);
	rtnl_lock();
	ipgre_destroy_tunnels(ign, &list);
	unregister_netdevice_many(&list);
	rtnl_unlock();
}
