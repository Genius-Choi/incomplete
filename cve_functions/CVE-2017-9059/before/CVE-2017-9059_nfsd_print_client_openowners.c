nfsd_print_client_openowners(struct nfs4_client *clp)
{
	u64 count = nfsd_foreach_client_openowner(clp, 0, NULL, NULL);

	nfsd_print_count(clp, count, "openowners");
	return count;
}
