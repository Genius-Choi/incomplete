static inline __be32 nfs4_check_fh(struct svc_fh *fhp, struct nfs4_stid *stp)
{
	if (!fh_match(&fhp->fh_handle, &stp->sc_file->fi_fhandle))
		return nfserr_bad_stateid;
	return nfs_ok;
}
