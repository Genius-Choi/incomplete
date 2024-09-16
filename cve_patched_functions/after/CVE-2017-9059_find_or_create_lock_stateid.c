find_or_create_lock_stateid(struct nfs4_lockowner *lo, struct nfs4_file *fi,
			    struct inode *inode, struct nfs4_ol_stateid *ost,
			    bool *new)
{
	struct nfs4_stid *ns = NULL;
	struct nfs4_ol_stateid *lst;
	struct nfs4_openowner *oo = openowner(ost->st_stateowner);
	struct nfs4_client *clp = oo->oo_owner.so_client;

	spin_lock(&clp->cl_lock);
	lst = find_lock_stateid(lo, fi);
	if (lst == NULL) {
		spin_unlock(&clp->cl_lock);
		ns = nfs4_alloc_stid(clp, stateid_slab, nfs4_free_lock_stateid);
		if (ns == NULL)
			return NULL;

		spin_lock(&clp->cl_lock);
		lst = find_lock_stateid(lo, fi);
		if (likely(!lst)) {
			lst = openlockstateid(ns);
			init_lock_stateid(lst, lo, fi, inode, ost);
			ns = NULL;
			*new = true;
		}
	}
	spin_unlock(&clp->cl_lock);
	if (ns)
		nfs4_put_stid(ns);
	return lst;
}
