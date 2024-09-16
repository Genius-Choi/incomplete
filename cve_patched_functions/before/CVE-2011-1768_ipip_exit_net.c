static void __net_exit ipip_exit_net(struct net *net)
{
	struct ipip_net *ipn = net_generic(net, ipip_net_id);
	LIST_HEAD(list);

	rtnl_lock();
	ipip_destroy_tunnels(ipn, &list);
	unregister_netdevice_queue(ipn->fb_tunnel_dev, &list);
	unregister_netdevice_many(&list);
	rtnl_unlock();
}
