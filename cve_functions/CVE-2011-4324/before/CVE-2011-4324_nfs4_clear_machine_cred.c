static void nfs4_clear_machine_cred(struct nfs_client *clp)
{
	struct rpc_cred *cred;

	spin_lock(&clp->cl_lock);
	cred = clp->cl_machine_cred;
	clp->cl_machine_cred = NULL;
	spin_unlock(&clp->cl_lock);
	if (cred != NULL)
		put_rpccred(cred);
}
