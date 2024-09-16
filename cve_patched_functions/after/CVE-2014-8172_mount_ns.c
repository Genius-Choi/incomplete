struct dentry *mount_ns(struct file_system_type *fs_type, int flags,
	void *data, int (*fill_super)(struct super_block *, void *, int))
{
	struct super_block *sb;

	sb = sget(fs_type, ns_test_super, ns_set_super, flags, data);
	if (IS_ERR(sb))
		return ERR_CAST(sb);

	if (!sb->s_root) {
		int err;
		err = fill_super(sb, data, flags & MS_SILENT ? 1 : 0);
		if (err) {
			deactivate_locked_super(sb);
			return ERR_PTR(err);
		}

		sb->s_flags |= MS_ACTIVE;
	}

	return dget(sb->s_root);
}
