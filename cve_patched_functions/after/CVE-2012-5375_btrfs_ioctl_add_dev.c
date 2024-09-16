static long btrfs_ioctl_add_dev(struct btrfs_root *root, void __user *arg)
{
	struct btrfs_ioctl_vol_args *vol_args;
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (atomic_xchg(&root->fs_info->mutually_exclusive_operation_running,
			1)) {
		pr_info("btrfs: dev add/delete/balance/replace/resize operation in progress\n");
		return -EINPROGRESS;
	}

	mutex_lock(&root->fs_info->volume_mutex);
	vol_args = memdup_user(arg, sizeof(*vol_args));
	if (IS_ERR(vol_args)) {
		ret = PTR_ERR(vol_args);
		goto out;
	}

	vol_args->name[BTRFS_PATH_NAME_MAX] = '\0';
	ret = btrfs_init_new_device(root, vol_args->name);

	kfree(vol_args);
out:
	mutex_unlock(&root->fs_info->volume_mutex);
	atomic_set(&root->fs_info->mutually_exclusive_operation_running, 0);
	return ret;
}
