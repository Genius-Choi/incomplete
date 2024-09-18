find_or_allocate_block(struct nfs4_lockowner *lo, struct knfsd_fh *fh,
			struct nfsd_net *nn)
{
	struct nfsd4_blocked_lock *nbl;

	nbl = find_blocked_lock(lo, fh, nn);
	if (!nbl) {
		nbl= kmalloc(sizeof(*nbl), GFP_KERNEL);
		if (nbl) {
			fh_copy_shallow(&nbl->nbl_fh, fh);
			locks_init_lock(&nbl->nbl_lock);
			nfsd4_init_cb(&nbl->nbl_cb, lo->lo_owner.so_client,
					&nfsd4_cb_notify_lock_ops,
					NFSPROC4_CLNT_CB_NOTIFY_LOCK);
		}
	}
	return nbl;
}
