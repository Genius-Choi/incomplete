static int ovl_link(struct dentry *old, struct inode *newdir,
		    struct dentry *new)
{
	int err;
	struct dentry *upper;

	err = ovl_want_write(old);
	if (err)
		goto out;

	err = ovl_copy_up(old);
	if (err)
		goto out_drop_write;

	upper = ovl_dentry_upper(old);
	err = ovl_create_or_link(new, upper->d_inode->i_mode, 0, NULL, upper);

out_drop_write:
	ovl_drop_write(old);
out:
	return err;
}
