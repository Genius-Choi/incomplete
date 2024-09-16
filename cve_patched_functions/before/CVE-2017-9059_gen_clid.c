static void gen_clid(struct nfs4_client *clp, struct nfsd_net *nn)
{
	clp->cl_clientid.cl_boot = nn->boot_time;
	clp->cl_clientid.cl_id = nn->clientid_counter++;
	gen_confirm(clp, nn);
}
