ffs_fs_mount(struct file_system_type *t, int flags,
	      const char *dev_name, void *opts)
{
	struct ffs_sb_fill_data data = {
		.perms = {
			.mode = S_IFREG | 0600,
			.uid = GLOBAL_ROOT_UID,
			.gid = GLOBAL_ROOT_GID,
		},
		.root_mode = S_IFDIR | 0500,
		.no_disconnect = false,
	};
	struct dentry *rv;
	int ret;
	void *ffs_dev;
	struct ffs_data	*ffs;

	ENTER();

	ret = ffs_fs_parse_opts(&data, opts);
	if (unlikely(ret < 0))
		return ERR_PTR(ret);

	ffs = ffs_data_new();
	if (unlikely(!ffs))
		return ERR_PTR(-ENOMEM);
	ffs->file_perms = data.perms;
	ffs->no_disconnect = data.no_disconnect;

	ffs->dev_name = kstrdup(dev_name, GFP_KERNEL);
	if (unlikely(!ffs->dev_name)) {
		ffs_data_put(ffs);
		return ERR_PTR(-ENOMEM);
	}

	ffs_dev = ffs_acquire_dev(dev_name);
	if (IS_ERR(ffs_dev)) {
		ffs_data_put(ffs);
		return ERR_CAST(ffs_dev);
	}
	ffs->private_data = ffs_dev;
	data.ffs_data = ffs;

	rv = mount_nodev(t, flags, &data, ffs_sb_fill);
	if (IS_ERR(rv) && data.ffs_data) {
		ffs_release_dev(data.ffs_data);
		ffs_data_put(data.ffs_data);
	}
	return rv;
}
