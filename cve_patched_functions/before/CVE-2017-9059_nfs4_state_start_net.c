nfs4_state_start_net(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	int ret;

	ret = nfs4_state_create_net(net);
	if (ret)
		return ret;
	nn->boot_time = get_seconds();
	nn->grace_ended = false;
	nn->nfsd4_manager.block_opens = true;
	locks_start_grace(net, &nn->nfsd4_manager);
	nfsd4_client_tracking_init(net);
	printk(KERN_INFO "NFSD: starting %ld-second grace period (net %p)\n",
	       nn->nfsd4_grace, net);
	queue_delayed_work(laundry_wq, &nn->laundromat_work, nn->nfsd4_grace * HZ);
	return 0;
}
