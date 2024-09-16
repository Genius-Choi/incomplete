static void expire_client(struct nfs4_client *clp)
{
	unhash_client(clp);
	nfsd4_client_record_remove(clp);
	__destroy_client(clp);
}
