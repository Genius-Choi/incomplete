static long btrfs_ioctl_rm_dev(struct file *file, void __user *arg)
{
	struct btrfs_root *root = BTRFS_I(fdentry(file)->d_inode)->root;
	struct btrfs_ioctl_vol_args *vol_args;
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	ret = mnt_want_write_file(file);
	if (ret)
		return ret;

	if (atomic_xchg(&root->fs_info->mutually_exclusive_operation_running,
			1)) {
		pr_info("btrfs: dev add/delete/balance/replace/resize operation in progress\n");
		mnt_drop_write_file(file);
		return -EINPROGRESS;
	}

	mutex_lock(&root->fs_info->volume_mutex);
	vol_args = memdup_user(arg, sizeof(*vol_args));
	if (IS_ERR(vol_args)) {
		ret = PTR_ERR(vol_args);
		goto out;
	}

	vol_args->name[BTRFS_PATH_NAME_MAX] = '\0';
	ret = btrfs_rm_device(root, vol_args->name);

	kfree(vol_args);
out:
	mutex_unlock(&root->fs_info->volume_mutex);
	mnt_drop_write_file(file);
	atomic_set(&root->fs_info->mutually_exclusive_operation_running, 0);
	return ret;
}
