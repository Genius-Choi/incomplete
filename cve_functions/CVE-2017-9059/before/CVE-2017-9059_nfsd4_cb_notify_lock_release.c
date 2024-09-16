nfsd4_cb_notify_lock_release(struct nfsd4_callback *cb)
{
	struct nfsd4_blocked_lock	*nbl = container_of(cb,
						struct nfsd4_blocked_lock, nbl_cb);

	free_blocked_lock(nbl);
}
