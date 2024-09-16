nfsd_collect_client_locks(struct nfs4_client *clp, struct list_head *collect,
			  u64 max)
{
	return nfsd_foreach_client_lock(clp, max, collect, unhash_lock_stateid);
}
