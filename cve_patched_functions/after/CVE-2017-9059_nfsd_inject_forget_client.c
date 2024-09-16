nfsd_inject_forget_client(struct sockaddr_storage *addr, size_t addr_size)
{
	u64 count = 0;
	struct nfs4_client *clp;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
					  nfsd_net_id);

	if (!nfsd_netns_ready(nn))
		return count;

	spin_lock(&nn->client_lock);
	clp = nfsd_find_client(addr, addr_size);
	if (clp) {
		if (mark_client_expired_locked(clp) == nfs_ok)
			++count;
		else
			clp = NULL;
	}
	spin_unlock(&nn->client_lock);

	if (clp)
		expire_client(clp);

	return count;
}
