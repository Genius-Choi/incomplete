static struct dentry *ovl_whiteout(struct dentry *workdir,
				   struct dentry *dentry)
{
	int err;
	struct dentry *whiteout;
	struct inode *wdir = workdir->d_inode;

	whiteout = ovl_lookup_temp(workdir, dentry);
	if (IS_ERR(whiteout))
		return whiteout;

	err = ovl_do_whiteout(wdir, whiteout);
	if (err) {
		dput(whiteout);
		whiteout = ERR_PTR(err);
	}

	return whiteout;
}
