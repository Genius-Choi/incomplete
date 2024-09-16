static int __net_init netlink_net_init(struct net *net)
{
#ifdef CONFIG_PROC_FS
	if (!proc_net_fops_create(net, "netlink", 0, &netlink_seq_fops))
		return -ENOMEM;
#endif
	return 0;
}
