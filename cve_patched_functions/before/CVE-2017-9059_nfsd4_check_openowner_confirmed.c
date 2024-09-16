static __be32 nfsd4_check_openowner_confirmed(struct nfs4_ol_stateid *ols)
{
	if (ols->st_stateowner->so_is_open_owner &&
	    !(openowner(ols->st_stateowner)->oo_flags & NFS4_OO_CONFIRMED))
		return nfserr_bad_stateid;
	return nfs_ok;
}
