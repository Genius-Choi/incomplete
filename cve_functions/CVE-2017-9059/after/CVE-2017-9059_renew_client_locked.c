renew_client_locked(struct nfs4_client *clp)
{
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	if (is_client_expired(clp)) {
		WARN_ON(1);
		printk("%s: client (clientid %08x/%08x) already expired\n",
			__func__,
			clp->cl_clientid.cl_boot,
			clp->cl_clientid.cl_id);
		return;
	}

	dprintk("renewing client (clientid %08x/%08x)\n",
			clp->cl_clientid.cl_boot,
			clp->cl_clientid.cl_id);
	list_move_tail(&clp->cl_lru, &nn->client_lru);
	clp->cl_time = get_seconds();
}
