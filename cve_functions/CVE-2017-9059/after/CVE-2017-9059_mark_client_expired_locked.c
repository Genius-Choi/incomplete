static __be32 mark_client_expired_locked(struct nfs4_client *clp)
{
	if (atomic_read(&clp->cl_refcount))
		return nfserr_jukebox;
	unhash_client_locked(clp);
	return nfs_ok;
}
