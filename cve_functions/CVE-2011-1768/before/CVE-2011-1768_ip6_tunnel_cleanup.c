static void __exit ip6_tunnel_cleanup(void)
{
	if (xfrm6_tunnel_deregister(&ip4ip6_handler, AF_INET))
		printk(KERN_INFO "ip6_tunnel close: can't deregister ip4ip6\n");

	if (xfrm6_tunnel_deregister(&ip6ip6_handler, AF_INET6))
		printk(KERN_INFO "ip6_tunnel close: can't deregister ip6ip6\n");

	unregister_pernet_device(&ip6_tnl_net_ops);
}
