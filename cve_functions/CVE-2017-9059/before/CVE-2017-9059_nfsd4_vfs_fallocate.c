__be32 nfsd4_vfs_fallocate(struct svc_rqst *rqstp, struct svc_fh *fhp,
			   struct file *file, loff_t offset, loff_t len,
			   int flags)
{
	int error;

	if (!S_ISREG(file_inode(file)->i_mode))
		return nfserr_inval;

	error = vfs_fallocate(file, flags, offset, len);
	if (!error)
		error = commit_metadata(fhp);

	return nfserrno(error);
}
