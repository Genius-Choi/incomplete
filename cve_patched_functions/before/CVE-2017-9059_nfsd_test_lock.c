static __be32 nfsd_test_lock(struct svc_rqst *rqstp, struct svc_fh *fhp, struct file_lock *lock)
{
	struct file *file;
	__be32 err = nfsd_open(rqstp, fhp, S_IFREG, NFSD_MAY_READ, &file);
	if (!err) {
		err = nfserrno(vfs_test_lock(file, lock));
		fput(file);
	}
	return err;
}
