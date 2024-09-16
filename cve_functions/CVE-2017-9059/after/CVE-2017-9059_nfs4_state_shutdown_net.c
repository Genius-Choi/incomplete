nfs4_state_shutdown_net(struct net *net)
{
	struct nfs4_delegation *dp = NULL;
	struct list_head *pos, *next, reaplist;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct nfsd4_blocked_lock *nbl;

	cancel_delayed_work_sync(&nn->laundromat_work);
	locks_end_grace(&nn->nfsd4_manager);

	INIT_LIST_HEAD(&reaplist);
	spin_lock(&state_lock);
	list_for_each_safe(pos, next, &nn->del_recall_lru) {
		dp = list_entry (pos, struct nfs4_delegation, dl_recall_lru);
		WARN_ON(!unhash_delegation_locked(dp));
		list_add(&dp->dl_recall_lru, &reaplist);
	}
	spin_unlock(&state_lock);
	list_for_each_safe(pos, next, &reaplist) {
		dp = list_entry (pos, struct nfs4_delegation, dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		put_clnt_odstate(dp->dl_clnt_odstate);
		nfs4_put_deleg_lease(dp->dl_stid.sc_file);
		nfs4_put_stid(&dp->dl_stid);
	}

	BUG_ON(!list_empty(&reaplist));
	spin_lock(&nn->blocked_locks_lock);
	while (!list_empty(&nn->blocked_locks_lru)) {
		nbl = list_first_entry(&nn->blocked_locks_lru,
					struct nfsd4_blocked_lock, nbl_lru);
		list_move(&nbl->nbl_lru, &reaplist);
		list_del_init(&nbl->nbl_list);
	}
	spin_unlock(&nn->blocked_locks_lock);

	while (!list_empty(&reaplist)) {
		nbl = list_first_entry(&nn->blocked_locks_lru,
					struct nfsd4_blocked_lock, nbl_lru);
		list_del_init(&nbl->nbl_lru);
		posix_unblock_lock(&nbl->nbl_lock);
		free_blocked_lock(nbl);
	}

	nfsd4_client_tracking_exit(net);
	nfs4_state_destroy_net(net);
}
