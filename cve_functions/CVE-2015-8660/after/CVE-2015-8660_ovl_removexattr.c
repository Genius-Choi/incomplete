int ovl_removexattr(struct dentry *dentry, const char *name)
{
	int err;
	struct path realpath;
	enum ovl_path_type type = ovl_path_real(dentry, &realpath);

	err = ovl_want_write(dentry);
	if (err)
		goto out;

	err = -ENODATA;
	if (ovl_need_xattr_filter(dentry, type) && ovl_is_private_xattr(name))
		goto out_drop_write;

	if (!OVL_TYPE_UPPER(type)) {
		err = vfs_getxattr(realpath.dentry, name, NULL, 0);
		if (err < 0)
			goto out_drop_write;

		err = ovl_copy_up(dentry);
		if (err)
			goto out_drop_write;

		ovl_path_upper(dentry, &realpath);
	}

	err = vfs_removexattr(realpath.dentry, name);
out_drop_write:
	ovl_drop_write(dentry);
out:
	return err;
}
