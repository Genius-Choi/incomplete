nfsd_collect_client_openowners(struct nfs4_client *clp,
			       struct list_head *collect, u64 max)
{
	return nfsd_foreach_client_openowner(clp, max, collect,
						unhash_openowner_locked);
}
