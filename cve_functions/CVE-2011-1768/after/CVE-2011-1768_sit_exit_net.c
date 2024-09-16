static void __net_exit sit_exit_net(struct net *net)
{
	struct sit_net *sitn = net_generic(net, sit_net_id);
	LIST_HEAD(list);

	rtnl_lock();
	sit_destroy_tunnels(sitn, &list);
	unregister_netdevice_queue(sitn->fb_tunnel_dev, &list);
	unregister_netdevice_many(&list);
	rtnl_unlock();
}
