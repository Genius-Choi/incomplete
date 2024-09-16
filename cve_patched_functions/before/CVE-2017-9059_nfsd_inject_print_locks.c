nfsd_inject_print_locks(void)
{
	struct nfs4_client *clp;
	u64 count = 0;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
						nfsd_net_id);

	if (!nfsd_netns_ready(nn))
		return 0;

	spin_lock(&nn->client_lock);
	list_for_each_entry(clp, &nn->client_lru, cl_lru)
		count += nfsd_print_client_locks(clp);
	spin_unlock(&nn->client_lock);

	return count;
}
