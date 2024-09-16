find_lockowner_str(struct nfs4_client *clp, struct xdr_netobj *owner)
{
	struct nfs4_lockowner *lo;

	spin_lock(&clp->cl_lock);
	lo = find_lockowner_str_locked(clp, owner);
	spin_unlock(&clp->cl_lock);
	return lo;
}
