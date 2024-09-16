nfsd_inject_forget_clients(u64 max)
{
	u64 count = 0;
	struct nfs4_client *clp, *next;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
						nfsd_net_id);
	LIST_HEAD(reaplist);

	if (!nfsd_netns_ready(nn))
		return count;

	spin_lock(&nn->client_lock);
	list_for_each_entry_safe(clp, next, &nn->client_lru, cl_lru) {
		if (mark_client_expired_locked(clp) == nfs_ok) {
			list_add(&clp->cl_lru, &reaplist);
			if (max != 0 && ++count >= max)
				break;
		}
	}
	spin_unlock(&nn->client_lock);

	list_for_each_entry_safe(clp, next, &reaplist, cl_lru)
		expire_client(clp);

	return count;
}
