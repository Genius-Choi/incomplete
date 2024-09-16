static int ovl_create_over_whiteout(struct dentry *dentry, struct inode *inode,
				    struct kstat *stat, const char *link,
				    struct dentry *hardlink)
{
	struct dentry *workdir = ovl_workdir(dentry);
	struct inode *wdir = workdir->d_inode;
	struct dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	struct inode *udir = upperdir->d_inode;
	struct dentry *upper;
	struct dentry *newdentry;
	int err;

	if (WARN_ON(!workdir))
		return -EROFS;

	err = ovl_lock_rename_workdir(workdir, upperdir);
	if (err)
		goto out;

	newdentry = ovl_lookup_temp(workdir, dentry);
	err = PTR_ERR(newdentry);
	if (IS_ERR(newdentry))
		goto out_unlock;

	upper = lookup_one_len(dentry->d_name.name, upperdir,
			       dentry->d_name.len);
	err = PTR_ERR(upper);
	if (IS_ERR(upper))
		goto out_dput;

	err = ovl_create_real(wdir, newdentry, stat, link, hardlink, true);
	if (err)
		goto out_dput2;

	if (S_ISDIR(stat->mode)) {
		err = ovl_set_opaque(newdentry);
		if (err)
			goto out_cleanup;

		err = ovl_do_rename(wdir, newdentry, udir, upper,
				    RENAME_EXCHANGE);
		if (err)
			goto out_cleanup;

		ovl_cleanup(wdir, upper);
	} else {
		err = ovl_do_rename(wdir, newdentry, udir, upper, 0);
		if (err)
			goto out_cleanup;
	}
	ovl_dentry_version_inc(dentry->d_parent);
	ovl_dentry_update(dentry, newdentry);
	ovl_copyattr(newdentry->d_inode, inode);
	d_instantiate(dentry, inode);
	newdentry = NULL;
out_dput2:
	dput(upper);
out_dput:
	dput(newdentry);
out_unlock:
	unlock_rename(workdir, upperdir);
out:
	return err;

out_cleanup:
	ovl_cleanup(wdir, newdentry);
	goto out_dput2;
}
