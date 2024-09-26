static int __init sit_init(void)
{
	int err;

	pr_info("IPv6, IPv4 and MPLS over IPv4 tunneling driver\n");

	err = register_pernet_device(&sit_net_ops);
	if (err < 0)
		return err;
	err = xfrm4_tunnel_register(&sit_handler, AF_INET6);
	if (err < 0) {
		pr_info("%s: can't register ip6ip4\n", __func__);
		goto xfrm_tunnel_failed;
	}
	err = xfrm4_tunnel_register(&ipip_handler, AF_INET);
	if (err < 0) {
		pr_info("%s: can't register ip4ip4\n", __func__);
		goto xfrm_tunnel4_failed;
	}
#if IS_ENABLED(CONFIG_MPLS)
	err = xfrm4_tunnel_register(&mplsip_handler, AF_MPLS);
	if (err < 0) {
		pr_info("%s: can't register mplsip\n", __func__);
		goto xfrm_tunnel_mpls_failed;
	}
#endif
	err = rtnl_link_register(&sit_link_ops);
	if (err < 0)
		goto rtnl_link_failed;

out:
	return err;

rtnl_link_failed:
#if IS_ENABLED(CONFIG_MPLS)
	xfrm4_tunnel_deregister(&mplsip_handler, AF_MPLS);
xfrm_tunnel_mpls_failed:
#endif
	xfrm4_tunnel_deregister(&ipip_handler, AF_INET);
xfrm_tunnel4_failed:
	xfrm4_tunnel_deregister(&sit_handler, AF_INET6);
xfrm_tunnel_failed:
	unregister_pernet_device(&sit_net_ops);
	goto out;
}
