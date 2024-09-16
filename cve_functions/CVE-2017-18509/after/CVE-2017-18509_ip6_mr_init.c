int __init ip6_mr_init(void)
{
	int err;

	mrt_cachep = kmem_cache_create("ip6_mrt_cache",
				       sizeof(struct mfc6_cache),
				       0, SLAB_HWCACHE_ALIGN,
				       NULL);
	if (!mrt_cachep)
		return -ENOMEM;

	err = register_pernet_subsys(&ip6mr_net_ops);
	if (err)
		goto reg_pernet_fail;

	err = register_netdevice_notifier(&ip6_mr_notifier);
	if (err)
		goto reg_notif_fail;
#ifdef CONFIG_IPV6_PIMSM_V2
	if (inet6_add_protocol(&pim6_protocol, IPPROTO_PIM) < 0) {
		pr_err("%s: can't add PIM protocol\n", __func__);
		err = -EAGAIN;
		goto add_proto_fail;
	}
#endif
	rtnl_register(RTNL_FAMILY_IP6MR, RTM_GETROUTE, NULL,
		      ip6mr_rtm_dumproute, NULL);
	return 0;
#ifdef CONFIG_IPV6_PIMSM_V2
add_proto_fail:
	unregister_netdevice_notifier(&ip6_mr_notifier);
#endif
reg_notif_fail:
	unregister_pernet_subsys(&ip6mr_net_ops);
reg_pernet_fail:
	kmem_cache_destroy(mrt_cachep);
	return err;
}
