nfs4_check_file(struct svc_rqst *rqstp, struct svc_fh *fhp, struct nfs4_stid *s,
		struct file **filpp, bool *tmp_file, int flags)
{
	int acc = (flags & RD_STATE) ? NFSD_MAY_READ : NFSD_MAY_WRITE;
	struct file *file;
	__be32 status;

	file = nfs4_find_file(s, flags);
	if (file) {
		status = nfsd_permission(rqstp, fhp->fh_export, fhp->fh_dentry,
				acc | NFSD_MAY_OWNER_OVERRIDE);
		if (status) {
			fput(file);
			return status;
		}

		*filpp = file;
	} else {
		status = nfsd_open(rqstp, fhp, S_IFREG, acc, filpp);
		if (status)
			return status;

		if (tmp_file)
			*tmp_file = true;
	}

	return 0;
}
