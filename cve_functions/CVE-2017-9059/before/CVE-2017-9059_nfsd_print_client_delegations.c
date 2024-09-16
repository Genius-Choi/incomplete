nfsd_print_client_delegations(struct nfs4_client *clp)
{
	u64 count = nfsd_find_all_delegations(clp, 0, NULL);

	nfsd_print_count(clp, count, "delegations");
	return count;
}
