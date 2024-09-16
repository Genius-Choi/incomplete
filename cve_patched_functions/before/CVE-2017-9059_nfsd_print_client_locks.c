nfsd_print_client_locks(struct nfs4_client *clp)
{
	u64 count = nfsd_foreach_client_lock(clp, 0, NULL, NULL);
	nfsd_print_count(clp, count, "locked files");
	return count;
}
