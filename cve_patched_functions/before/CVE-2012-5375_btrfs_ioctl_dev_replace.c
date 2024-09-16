static long btrfs_ioctl_dev_replace(struct btrfs_root *root, void __user *arg)
{
	struct btrfs_ioctl_dev_replace_args *p;
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	p = memdup_user(arg, sizeof(*p));
	if (IS_ERR(p))
		return PTR_ERR(p);

	switch (p->cmd) {
	case BTRFS_IOCTL_DEV_REPLACE_CMD_START:
		if (atomic_xchg(
			&root->fs_info->mutually_exclusive_operation_running,
			1)) {
			pr_info("btrfs: dev add/delete/balance/replace/resize operation in progress\n");
			ret = -EINPROGRESS;
		} else {
			ret = btrfs_dev_replace_start(root, p);
			atomic_set(
			 &root->fs_info->mutually_exclusive_operation_running,
			 0);
		}
		break;
	case BTRFS_IOCTL_DEV_REPLACE_CMD_STATUS:
		btrfs_dev_replace_status(root->fs_info, p);
		ret = 0;
		break;
	case BTRFS_IOCTL_DEV_REPLACE_CMD_CANCEL:
		ret = btrfs_dev_replace_cancel(root->fs_info, p);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (copy_to_user(arg, p, sizeof(*p)))
		ret = -EFAULT;

	kfree(p);
	return ret;
}
