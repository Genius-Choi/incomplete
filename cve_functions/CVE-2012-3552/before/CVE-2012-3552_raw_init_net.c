static __net_init int raw_init_net(struct net *net)
{
	if (!proc_net_fops_create(net, "raw", S_IRUGO, &raw_seq_fops))
		return -ENOMEM;

	return 0;
}
