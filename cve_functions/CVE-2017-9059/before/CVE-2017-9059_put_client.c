put_client(struct nfs4_client *clp)
{
	atomic_dec(&clp->cl_refcount);
}
