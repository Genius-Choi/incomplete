static struct nfs4_client *alloc_client(struct xdr_netobj name)
{
	struct nfs4_client *clp;
	int i;

	clp = kzalloc(sizeof(struct nfs4_client), GFP_KERNEL);
	if (clp == NULL)
		return NULL;
	clp->cl_name.data = kmemdup(name.data, name.len, GFP_KERNEL);
	if (clp->cl_name.data == NULL)
		goto err_no_name;
	clp->cl_ownerstr_hashtbl = kmalloc(sizeof(struct list_head) *
			OWNER_HASH_SIZE, GFP_KERNEL);
	if (!clp->cl_ownerstr_hashtbl)
		goto err_no_hashtbl;
	for (i = 0; i < OWNER_HASH_SIZE; i++)
		INIT_LIST_HEAD(&clp->cl_ownerstr_hashtbl[i]);
	clp->cl_name.len = name.len;
	INIT_LIST_HEAD(&clp->cl_sessions);
	idr_init(&clp->cl_stateids);
	atomic_set(&clp->cl_refcount, 0);
	clp->cl_cb_state = NFSD4_CB_UNKNOWN;
	INIT_LIST_HEAD(&clp->cl_idhash);
	INIT_LIST_HEAD(&clp->cl_openowners);
	INIT_LIST_HEAD(&clp->cl_delegations);
	INIT_LIST_HEAD(&clp->cl_lru);
	INIT_LIST_HEAD(&clp->cl_revoked);
#ifdef CONFIG_NFSD_PNFS
	INIT_LIST_HEAD(&clp->cl_lo_states);
#endif
	spin_lock_init(&clp->cl_lock);
	rpc_init_wait_queue(&clp->cl_cb_waitq, "Backchannel slot table");
	return clp;
err_no_hashtbl:
	kfree(clp->cl_name.data);
err_no_name:
	kfree(clp);
	return NULL;
}
