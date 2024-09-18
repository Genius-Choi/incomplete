static bool is_client_expired(struct nfs4_client *clp)
{
	return clp->cl_time == 0;
}
