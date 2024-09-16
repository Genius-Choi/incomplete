nfs4_has_reclaimed_state(const char *name, struct nfsd_net *nn)
{
	struct nfs4_client_reclaim *crp;

	crp = nfsd4_find_reclaim_client(name, nn);
	return (crp && crp->cr_clp);
}
