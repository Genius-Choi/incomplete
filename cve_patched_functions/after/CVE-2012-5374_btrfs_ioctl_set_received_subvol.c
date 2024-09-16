static long btrfs_ioctl_set_received_subvol(struct file *file,
					    void __user *arg)
{
	struct btrfs_ioctl_received_subvol_args *sa = NULL;
	struct inode *inode = fdentry(file)->d_inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_root_item *root_item = &root->root_item;
	struct btrfs_trans_handle *trans;
	struct timespec ct = CURRENT_TIME;
	int ret = 0;

	ret = mnt_want_write_file(file);
	if (ret < 0)
		return ret;

	down_write(&root->fs_info->subvol_sem);

	if (btrfs_ino(inode) != BTRFS_FIRST_FREE_OBJECTID) {
		ret = -EINVAL;
		goto out;
	}

	if (btrfs_root_readonly(root)) {
		ret = -EROFS;
		goto out;
	}

	if (!inode_owner_or_capable(inode)) {
		ret = -EACCES;
		goto out;
	}

	sa = memdup_user(arg, sizeof(*sa));
	if (IS_ERR(sa)) {
		ret = PTR_ERR(sa);
		sa = NULL;
		goto out;
	}

	trans = btrfs_start_transaction(root, 1);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		trans = NULL;
		goto out;
	}

	sa->rtransid = trans->transid;
	sa->rtime.sec = ct.tv_sec;
	sa->rtime.nsec = ct.tv_nsec;

	memcpy(root_item->received_uuid, sa->uuid, BTRFS_UUID_SIZE);
	btrfs_set_root_stransid(root_item, sa->stransid);
	btrfs_set_root_rtransid(root_item, sa->rtransid);
	root_item->stime.sec = cpu_to_le64(sa->stime.sec);
	root_item->stime.nsec = cpu_to_le32(sa->stime.nsec);
	root_item->rtime.sec = cpu_to_le64(sa->rtime.sec);
	root_item->rtime.nsec = cpu_to_le32(sa->rtime.nsec);

	ret = btrfs_update_root(trans, root->fs_info->tree_root,
				&root->root_key, &root->root_item);
	if (ret < 0) {
		btrfs_end_transaction(trans, root);
		trans = NULL;
		goto out;
	} else {
		ret = btrfs_commit_transaction(trans, root);
		if (ret < 0)
			goto out;
	}

	ret = copy_to_user(arg, sa, sizeof(*sa));
	if (ret)
		ret = -EFAULT;

out:
	kfree(sa);
	up_write(&root->fs_info->subvol_sem);
	mnt_drop_write_file(file);
	return ret;
}
