nfsd_inject_add_lock_to_list(struct nfs4_ol_stateid *lst,
			     struct list_head *collect)
{
	struct nfs4_client *clp = lst->st_stid.sc_client;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
					  nfsd_net_id);

	if (!collect)
		return;

	lockdep_assert_held(&nn->client_lock);
	atomic_inc(&clp->cl_refcount);
	list_add(&lst->st_locks, collect);
}
