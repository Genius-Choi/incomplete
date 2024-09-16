static int ovl_create_upper(struct dentry *dentry, struct inode *inode,
			    struct kstat *stat, const char *link,
			    struct dentry *hardlink)
{
	struct dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	struct inode *udir = upperdir->d_inode;
	struct dentry *newdentry;
	int err;

	inode_lock_nested(udir, I_MUTEX_PARENT);
	newdentry = lookup_one_len(dentry->d_name.name, upperdir,
				   dentry->d_name.len);
	err = PTR_ERR(newdentry);
	if (IS_ERR(newdentry))
		goto out_unlock;
	err = ovl_create_real(udir, newdentry, stat, link, hardlink, false);
	if (err)
		goto out_dput;

	ovl_dentry_version_inc(dentry->d_parent);
	ovl_dentry_update(dentry, newdentry);
	ovl_copyattr(newdentry->d_inode, inode);
	d_instantiate(dentry, inode);
	newdentry = NULL;
out_dput:
	dput(newdentry);
out_unlock:
	inode_unlock(udir);
	return err;
}
