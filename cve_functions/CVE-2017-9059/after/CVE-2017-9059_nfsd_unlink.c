nfsd_unlink(struct svc_rqst *rqstp, struct svc_fh *fhp, int type,
				char *fname, int flen)
{
	struct dentry	*dentry, *rdentry;
	struct inode	*dirp;
	__be32		err;
	int		host_err;

	err = nfserr_acces;
	if (!flen || isdotent(fname, flen))
		goto out;
	err = fh_verify(rqstp, fhp, S_IFDIR, NFSD_MAY_REMOVE);
	if (err)
		goto out;

	host_err = fh_want_write(fhp);
	if (host_err)
		goto out_nfserr;

	fh_lock_nested(fhp, I_MUTEX_PARENT);
	dentry = fhp->fh_dentry;
	dirp = d_inode(dentry);

	rdentry = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(rdentry);
	if (IS_ERR(rdentry))
		goto out_nfserr;

	if (d_really_is_negative(rdentry)) {
		dput(rdentry);
		err = nfserr_noent;
		goto out;
	}

	if (!type)
		type = d_inode(rdentry)->i_mode & S_IFMT;

	if (type != S_IFDIR)
		host_err = vfs_unlink(dirp, rdentry, NULL);
	else
		host_err = vfs_rmdir(dirp, rdentry);
	if (!host_err)
		host_err = commit_metadata(fhp);
	dput(rdentry);

out_nfserr:
	err = nfserrno(host_err);
out:
	return err;
}
