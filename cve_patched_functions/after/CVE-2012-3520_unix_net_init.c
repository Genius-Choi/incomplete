static int __net_init unix_net_init(struct net *net)
{
	int error = -ENOMEM;

	net->unx.sysctl_max_dgram_qlen = 10;
	if (unix_sysctl_register(net))
		goto out;

#ifdef CONFIG_PROC_FS
	if (!proc_net_fops_create(net, "unix", 0, &unix_seq_fops)) {
		unix_sysctl_unregister(net);
		goto out;
	}
#endif
	error = 0;
out:
	return error;
}
