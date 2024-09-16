nfsd_inject_recall_delegations(u64 max)
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
		count += nfsd_find_all_delegations(clp, max - count, &reaplist);
		if (max != 0 && ++count >= max)
			break;
	}
	spin_unlock(&nn->client_lock);
	nfsd_recall_delegations(&reaplist);
	return count;
}
