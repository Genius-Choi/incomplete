__destroy_client(struct nfs4_client *clp)
{
	struct nfs4_openowner *oo;
	struct nfs4_delegation *dp;
	struct list_head reaplist;

	INIT_LIST_HEAD(&reaplist);
	spin_lock(&state_lock);
	while (!list_empty(&clp->cl_delegations)) {
		dp = list_entry(clp->cl_delegations.next, struct nfs4_delegation, dl_perclnt);
		WARN_ON(!unhash_delegation_locked(dp));
		list_add(&dp->dl_recall_lru, &reaplist);
	}
	spin_unlock(&state_lock);
	while (!list_empty(&reaplist)) {
		dp = list_entry(reaplist.next, struct nfs4_delegation, dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		put_clnt_odstate(dp->dl_clnt_odstate);
		nfs4_put_deleg_lease(dp->dl_stid.sc_file);
		nfs4_put_stid(&dp->dl_stid);
	}
	while (!list_empty(&clp->cl_revoked)) {
		dp = list_entry(clp->cl_revoked.next, struct nfs4_delegation, dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		nfs4_put_stid(&dp->dl_stid);
	}
	while (!list_empty(&clp->cl_openowners)) {
		oo = list_entry(clp->cl_openowners.next, struct nfs4_openowner, oo_perclient);
		nfs4_get_stateowner(&oo->oo_owner);
		release_openowner(oo);
	}
	nfsd4_return_all_client_layouts(clp);
	nfsd4_shutdown_callback(clp);
	if (clp->cl_cb_conn.cb_xprt)
		svc_xprt_put(clp->cl_cb_conn.cb_xprt);
	free_client(clp);
}
