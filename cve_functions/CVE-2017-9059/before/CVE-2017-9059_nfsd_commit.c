nfsd_commit(struct svc_rqst *rqstp, struct svc_fh *fhp,
               loff_t offset, unsigned long count)
{
	struct file	*file;
	loff_t		end = LLONG_MAX;
	__be32		err = nfserr_inval;

	if (offset < 0)
		goto out;
	if (count != 0) {
		end = offset + (loff_t)count - 1;
		if (end < offset)
			goto out;
	}

	err = nfsd_open(rqstp, fhp, S_IFREG,
			NFSD_MAY_WRITE|NFSD_MAY_NOT_BREAK_LEASE, &file);
	if (err)
		goto out;
	if (EX_ISSYNC(fhp->fh_export)) {
		int err2 = vfs_fsync_range(file, offset, end, 0);

		if (err2 != -EINVAL)
			err = nfserrno(err2);
		else
			err = nfserr_notsupp;
	}

	fput(file);
out:
	return err;
}
