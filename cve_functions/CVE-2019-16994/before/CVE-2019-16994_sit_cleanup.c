static void __exit sit_cleanup(void)
{
	rtnl_link_unregister(&sit_link_ops);
	xfrm4_tunnel_deregister(&sit_handler, AF_INET6);
	xfrm4_tunnel_deregister(&ipip_handler, AF_INET);
#if IS_ENABLED(CONFIG_MPLS)
	xfrm4_tunnel_deregister(&mplsip_handler, AF_MPLS);
#endif

	unregister_pernet_device(&sit_net_ops);
	rcu_barrier(); /* Wait for completion of call_rcu()'s */
}
