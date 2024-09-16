static long btrfs_ioctl_quota_ctl(struct file *file, void __user *arg)
{
	struct btrfs_root *root = BTRFS_I(fdentry(file)->d_inode)->root;
	struct btrfs_ioctl_quota_ctl_args *sa;
	struct btrfs_trans_handle *trans = NULL;
	int ret;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	ret = mnt_want_write_file(file);
	if (ret)
		return ret;

	sa = memdup_user(arg, sizeof(*sa));
	if (IS_ERR(sa)) {
		ret = PTR_ERR(sa);
		goto drop_write;
	}

	if (sa->cmd != BTRFS_QUOTA_CTL_RESCAN) {
		trans = btrfs_start_transaction(root, 2);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			goto out;
		}
	}

	switch (sa->cmd) {
	case BTRFS_QUOTA_CTL_ENABLE:
		ret = btrfs_quota_enable(trans, root->fs_info);
		break;
	case BTRFS_QUOTA_CTL_DISABLE:
		ret = btrfs_quota_disable(trans, root->fs_info);
		break;
	case BTRFS_QUOTA_CTL_RESCAN:
		ret = btrfs_quota_rescan(root->fs_info);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (copy_to_user(arg, sa, sizeof(*sa)))
		ret = -EFAULT;

	if (trans) {
		err = btrfs_commit_transaction(trans, root);
		if (err && !ret)
			ret = err;
	}
out:
	kfree(sa);
drop_write:
	mnt_drop_write_file(file);
	return ret;
}
