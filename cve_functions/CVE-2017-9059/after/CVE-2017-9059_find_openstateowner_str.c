find_openstateowner_str(unsigned int hashval, struct nfsd4_open *open,
			struct nfs4_client *clp)
{
	struct nfs4_openowner *oo;

	spin_lock(&clp->cl_lock);
	oo = find_openstateowner_str_locked(hashval, open, clp);
	spin_unlock(&clp->cl_lock);
	return oo;
}
